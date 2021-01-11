#include "DirectX/Effects/Effects.h"
#include "DirectX/Effects/RenderStates.h"
#include "ChipsSystem/Global/Global.h"
#include "DirectX/MeshGenerator/MeshGenerator.h"
#include "ChipsSystem/BasicFrame/GameObject.h"
#include "ChipsSystem/Camera/Camera.h"
#include "ChipsSystem/Components/BaiscComponents/Transform.h"
#include "ChipsSystem/Components/RendererComponents/AMeshRenderer.h"
#include "ChipsSystem/Manager/LightManager.h"
#include "ChipsSystem/Etc/Mathf.h"

namespace ChipsEngine
{ 
	AMeshRenderer::AMeshRenderer(string _componentType) : AComponent(_componentType),
		m_isTextureUse(false), m_isNormalUse(false), m_isSpecularUse(false), m_isReflectUse(true), m_isCartoonUse(false), 
		m_isUseShadow(true), m_isRimLightUse(false), m_isAlphaClipUse(true), 
		m_frustumRadius(1.0f), m_isFrustumCullingActive(false), m_isLoaded(false), m_isMakeShadow(true), m_indexCount(0),
		m_vertexBuffer(nullptr), m_indexBuffer(nullptr), m_blendState(nullptr), m_tech(nullptr), m_matCount(3)
	{
	}

	VOID AMeshRenderer::SetCartoonStyleRendering(bool _active)
	{
		m_isCartoonUse = _active;
		if (_active)
		{
			m_tech = Effects::StandardShaderFX->CartoonTech;
		}
		else
		{
			m_tech = Effects::StandardShaderFX->StandardTech;
		}
	}

	VOID AMeshRenderer::AddMaterial()
	{
		Material material;
		material.Ambient =  XMFLOAT4(0.3f, 0.3f, 0.3f, 1.0f);
		material.Diffuse =  XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
		material.Specular = XMFLOAT4(0.2f, 0.2f, 0.2f, 16.0f);
		material.Reflect = XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f);
		m_material.emplace_back(material);
	}

	VOID AMeshRenderer::AddMaterial(Material _material)
	{
		m_material.emplace_back(_material);
	}

	VOID AMeshRenderer::AddDiffuseTexture(const string _fileName)
	{
		m_isTextureUse = true;
		wstring ws(_fileName.begin(), _fileName.end());
		DirectX::ScratchImage image;
		DirectX::LoadFromDDSFile(ws.c_str(), DirectX::DDS_FLAGS_NONE, nullptr, image);
		ID3D11ShaderResourceView* temp;
		DirectX::CreateShaderResourceView(Global::g_d3dDevice, image.GetImages(), image.GetImageCount(), image.GetMetadata(), &temp);
		m_diffuseSRV.emplace_back(temp);
	}

	VOID AMeshRenderer::AddNormalTexture(const string _fileName)
	{
		m_isNormalUse = true;
		wstring ws(_fileName.begin(), _fileName.end());
		DirectX::ScratchImage image;
		DirectX::LoadFromDDSFile(ws.c_str(), DirectX::DDS_FLAGS_NONE, nullptr, image);
		ID3D11ShaderResourceView* temp;
		DirectX::CreateShaderResourceView(Global::g_d3dDevice, image.GetImages(), image.GetImageCount(), image.GetMetadata(), &temp);
		m_normalSRV.emplace_back(temp);
	}

	VOID AMeshRenderer::AddSpecularTexture(const string _fileName)
	{
		m_isSpecularUse = true;
		wstring ws(_fileName.begin(), _fileName.end());
		DirectX::ScratchImage image;
		DirectX::LoadFromDDSFile(ws.c_str(), DirectX::DDS_FLAGS_NONE, nullptr, image);
		ID3D11ShaderResourceView* temp;
		DirectX::CreateShaderResourceView(Global::g_d3dDevice, image.GetImages(), image.GetImageCount(), image.GetMetadata(), &temp);
		m_specularSRV.emplace_back(temp);
	}

	VOID AMeshRenderer::SetTextureTiling(float _x, float _y)
	{
		m_texTransform = XMMatrixScaling(_x, _y, 1.0f);
	}

	VOID AMeshRenderer::SetTransparentRendering(bool _isActive)
	{
		if (_isActive)
		{
			m_blendState = RenderStates::TransparentBS;
			SetAlphaClipRendering(false);
		}
		else
		{
			m_blendState = RenderStates::AlphaToCoverageBS;
			SetAlphaClipRendering(true);
		}
	}

	VOID AMeshRenderer::BuildShadowMap()
	{
		if (m_isLoaded == false || m_isMakeShadow == false)
			return;

		UINT stride = sizeof(Vertex36);
		UINT offset = 0;

		Global::g_d3dImmediateContext->IASetInputLayout(InputLayouts::Vertex36);
		Global::g_d3dImmediateContext->IASetVertexBuffers(0, 1, &m_vertexBuffer, &stride, &offset);
		Global::g_d3dImmediateContext->IASetIndexBuffer(m_indexBuffer, DXGI_FORMAT_R32_UINT, 0);
		Global::g_d3dImmediateContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

		ID3DX11EffectTechnique* tech = Effects::BuildShadowMapFX->BuildShadowMapTech;

		XMMATRIX world = GetGameObject()->GetTransform()->GetWorldMatrix();
		XMMATRIX view = LightManager::GetInstance()->GetLightView();
		XMMATRIX proj = LightManager::GetInstance()->GetLightProj();
		XMMATRIX worldInvTranspose = Mathf::InverseTranspose(world);
		XMMATRIX worldViewProj = world * view * proj;

		Effects::BuildShadowMapFX->SetWorld(world);
		Effects::BuildShadowMapFX->SetWorldInvTranspose(worldInvTranspose);
		Effects::BuildShadowMapFX->SetWorldViewProj(worldViewProj);
		Effects::BuildShadowMapFX->SetTexTransform(XMMatrixIdentity()); 
		SetShaderSkinningShadowValues();

		D3DX11_TECHNIQUE_DESC techDesc;
		tech->GetDesc(&techDesc);

		for (UINT p = 0; p < techDesc.Passes; ++p)
		{
			tech->GetPassByIndex(p)->Apply(0, Global::g_d3dImmediateContext);
			Global::g_d3dImmediateContext->DrawIndexed(m_indexCount, 0, 0);
		}
	}

	VOID AMeshRenderer::WriteLinearDepth()
	{
		if (m_isLoaded == false)
			return;

		if (m_isFrustumCullingActive && Mathf::CheckFrustumCulling(GetGameObject()->GetTransform(), m_frustumRadius))
			return;

		UINT stride = sizeof(Vertex36);
		UINT offset = 0;
		float blendFactor[] = { 0.0f, 0.0f, 0.0f, 0.0f };

		XMMATRIX world = GetGameObject()->GetTransform()->GetWorldMatrix();
		XMMATRIX view = Camera::GetInstance()->View();
		XMMATRIX proj = Camera::GetInstance()->Proj();
		XMMATRIX worldView = world * view;
		XMMATRIX worldViewProj = world * view * proj;
		XMMATRIX worldInvTranspose = Mathf::InverseTranspose(GetGameObject()->GetTransform()->GetWorldMatrix());

		Global::g_d3dImmediateContext->RSSetState(RenderStates::NoCullRS);
		Global::g_d3dImmediateContext->IASetInputLayout(InputLayouts::Vertex36);
		Global::g_d3dImmediateContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
		Global::g_d3dImmediateContext->IASetVertexBuffers(0, 1, &m_vertexBuffer, &stride, &offset);
		Global::g_d3dImmediateContext->IASetIndexBuffer(m_indexBuffer, DXGI_FORMAT_R32_UINT, 0);

		Effects::StandardShaderFX->SetWorld(world);
		Effects::StandardShaderFX->SetWorldInvTranspose(worldInvTranspose);
		Effects::StandardShaderFX->SetWorldViewProj(worldViewProj);
		Effects::StandardShaderFX->SetWorldView(worldView);
		Effects::StandardShaderFX->SetTexTransform(m_texTransform);
		Effects::StandardShaderFX->SetNearFar(XMFLOAT2(Camera::GetInstance()->GetNearZ(), Camera::GetInstance()->GetFarZ()));
		Effects::StandardShaderFX->SetShadowTransform(GetGameObject()->GetTransform()->GetWorldMatrix() * LightManager::GetInstance()->GetShadowTransform());
		Effects::StandardShaderFX->SetMaterialCount(0);

		SetShaderSkinningValues();

		D3DX11_TECHNIQUE_DESC techDesc;
		ID3DX11EffectTechnique* tech = Effects::StandardShaderFX->DepthTech;
		tech->GetDesc(&techDesc);
		for (UINT p = 0; p < techDesc.Passes; ++p)
		{
			Global::g_d3dImmediateContext->OMSetBlendState(0, blendFactor, 0xffffffff);
			tech->GetPassByIndex(p)->Apply(0, Global::g_d3dImmediateContext);
			Global::g_d3dImmediateContext->DrawIndexed(m_indexCount, 0, 0);
		}

		Global::g_d3dImmediateContext->OMSetBlendState(0, blendFactor, 0xffffffff);
	}

	VOID AMeshRenderer::SetShaderSkinningValues()
	{
		Effects::StandardShaderFX->SetUseSkinning(false);
	}

	VOID AMeshRenderer::SetShaderSkinningShadowValues()
	{
		Effects::BuildShadowMapFX->SetUseSkinning(false);
	}

	VOID AMeshRenderer::Awake()
	{
		InitGemometryBuffer();
		AddMaterial();
		SetTextureTiling(1.0f, 1.0f);
		m_tech  = Effects::StandardShaderFX->StandardTech;
		m_blendState = RenderStates::AlphaToCoverageBS;
	}

	VOID AMeshRenderer::Start()
	{
		LightManager::GetInstance()->AddMeshRenderer(this);
	}

	VOID AMeshRenderer::Update()
	{
	}

	VOID AMeshRenderer::FixedUpdate()
	{
	}

	VOID AMeshRenderer::Render()
	{
		if (m_isLoaded == false)
			return;

		if (m_isFrustumCullingActive && Mathf::CheckFrustumCulling(GetGameObject()->GetTransform(), m_frustumRadius))
			return;

		UINT stride = sizeof(Vertex36);
		UINT offset = 0;
		float blendFactor[] = { 0.0f, 0.0f, 0.0f, 0.0f };

		XMMATRIX world = GetGameObject()->GetTransform()->GetWorldMatrix();
		XMMATRIX view = Camera::GetInstance()->View();
		XMMATRIX proj = Camera::GetInstance()->Proj();
		XMMATRIX worldView = world * view;
		XMMATRIX worldViewProj = world * view * proj;
		XMMATRIX worldInvTranspose = Mathf::InverseTranspose(GetGameObject()->GetTransform()->GetWorldMatrix());

		for (int i = 0; i < m_matCount; i++)
		{
			Global::g_d3dImmediateContext->RSSetState(RenderStates::NoCullRS);
			Global::g_d3dImmediateContext->IASetInputLayout(InputLayouts::Vertex36);
			Global::g_d3dImmediateContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
			Global::g_d3dImmediateContext->IASetVertexBuffers(0, 1, &m_vertexBuffer, &stride, &offset);
			Global::g_d3dImmediateContext->IASetIndexBuffer(m_indexBuffer, DXGI_FORMAT_R32_UINT, 0);

			Effects::StandardShaderFX->SetWorld(world);
			Effects::StandardShaderFX->SetWorldInvTranspose(worldInvTranspose);
			Effects::StandardShaderFX->SetWorldViewProj(worldViewProj);
			Effects::StandardShaderFX->SetWorldView(worldView);
			Effects::StandardShaderFX->SetTexTransform(m_texTransform);
			Effects::StandardShaderFX->SetNearFar(XMFLOAT2(Camera::GetInstance()->GetNearZ(), Camera::GetInstance()->GetFarZ()));
			Effects::StandardShaderFX->SetShadowTransform(GetGameObject()->GetTransform()->GetWorldMatrix() * LightManager::GetInstance()->GetShadowTransform());
			Effects::StandardShaderFX->SetMaterialCount(i);

			Effects::StandardShaderFX->SetUseDiffuse(m_isTextureUse);
			Effects::StandardShaderFX->SetUseAlphaClip(m_isAlphaClipUse);
			Effects::StandardShaderFX->SetUseNormal(m_isNormalUse);
			Effects::StandardShaderFX->SetUseSpecular(m_isSpecularUse);
			Effects::StandardShaderFX->SetUseReflect(m_isReflectUse);
			Effects::StandardShaderFX->SetUseCartoon(m_isCartoonUse);
			Effects::StandardShaderFX->SetUseShadow(m_isUseShadow && LightManager::GetInstance()->GetMakeShadow());
			Effects::StandardShaderFX->SetUseRimLight(m_isRimLightUse);
			Effects::StandardShaderFX->SetUseFog(false);

			SetShaderSkinningValues();

			int materialSize = m_material.size() - 1;
			int index = materialSize < i ? materialSize : i;
			Effects::StandardShaderFX->SetMaterial(m_material[index]);

			if (m_isTextureUse)
			{
				int diffuseSize = m_diffuseSRV.size() - 1;
				index = diffuseSize < i ? diffuseSize : i;
				Effects::StandardShaderFX->SetDiffuseMap(m_diffuseSRV[(int)index]);
			}

			if (m_isNormalUse)
			{
				int normalSize = m_normalSRV.size() - 1;
				index = normalSize < i ? normalSize : i;
				Effects::StandardShaderFX->SetNormalMap(m_normalSRV[(int)index]);
			}

			if (m_isSpecularUse)
			{
				int specularSize = m_specularSRV.size() - 1;
				index = specularSize < i ? specularSize : i;
				Effects::StandardShaderFX->SetSpecularMap(m_specularSRV[(int)index]);
			}

			D3DX11_TECHNIQUE_DESC techDesc;
			m_tech->GetDesc(&techDesc);
			for (UINT p = 0; p < techDesc.Passes; ++p)
			{
				Global::g_d3dImmediateContext->OMSetBlendState(m_blendState, blendFactor, 0xffffffff);
				m_tech->GetPassByIndex(p)->Apply(0, Global::g_d3dImmediateContext);
				Global::g_d3dImmediateContext->DrawIndexed(m_indexCount, 0, 0);
			}

			Global::g_d3dImmediateContext->OMSetBlendState(0, blendFactor, 0xffffffff);
		}
	}

	VOID AMeshRenderer::Release()
	{
		SAFE_RELEASE(m_vertexBuffer);
		SAFE_RELEASE(m_indexBuffer);
		SAFE_RELEASE(m_tech);
		
		m_material.clear();

		for (auto it = m_diffuseSRV.begin(); it!= m_diffuseSRV.end(); it++)
		{
			(*it)->Release();
		}
		m_diffuseSRV.clear();

		for (auto it = m_normalSRV.begin(); it != m_normalSRV.end(); it++)
		{
			(*it)->Release();
		}
		m_normalSRV.clear();

		for (auto it = m_specularSRV.begin(); it != m_specularSRV.end(); it++)
		{
			(*it)->Release();
		}
		m_specularSRV.clear();

		LightManager::GetInstance()->RemoveMeshRenderer(this);
	}
}