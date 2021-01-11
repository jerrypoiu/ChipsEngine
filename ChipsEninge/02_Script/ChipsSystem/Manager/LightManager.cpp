#include "DirectX/Effects/Effects.h"
#include "ChipsSystem/BasicFrame/GameObject.h"
#include "ChipsSystem/Components/BaiscComponents/Transform.h"
#include "ChipsSystem/Camera/Camera.h"
#include "ChipsSystem/Manager/LightManager.h"
#include "ChipsSystem/Manager/GraphicManager.h"
#include "ChipsSystem/Global/Global.h"
#include "ChipsSystem/Etc/Mathf.h"
#include "ChipsSystem/Etc/Debug.h"

namespace ChipsEngine
{
	LightManager::LightManager() : 
		m_spotLightMaxCount(50), m_pointLightMaxCount(50), m_directionalLightMaxCount(3),
		m_directionalLightCount(0), m_width(4096*2), m_height(4096*2), m_radius(10.0f),
		m_isMakeShadow(true), m_depthMapDSV(nullptr), m_depthMapSRV(nullptr)
	{
	}

	VOID LightManager::LoadSRVandDSV()
	{
		m_viewport.TopLeftX = 0.0f;
		m_viewport.TopLeftY = 0.0f;
		m_viewport.Width = static_cast<float>(m_width);
		m_viewport.Height = static_cast<float>(m_height);
		m_viewport.MinDepth = 0.0f;
		m_viewport.MaxDepth = 1.0f;

		D3D11_TEXTURE2D_DESC texDesc;
		texDesc.Width = m_width;
		texDesc.Height = m_height;
		texDesc.MipLevels = 1;
		texDesc.ArraySize = 1;
		texDesc.Format = DXGI_FORMAT_R24G8_TYPELESS;
		texDesc.SampleDesc.Count = 1;
		texDesc.SampleDesc.Quality = 0;
		texDesc.Usage = D3D11_USAGE_DEFAULT;
		texDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL | D3D11_BIND_SHADER_RESOURCE;
		texDesc.CPUAccessFlags = 0;
		texDesc.MiscFlags = 0;

		ID3D11Texture2D* depthMap = 0;
		Global::g_d3dDevice->CreateTexture2D(&texDesc, 0, &depthMap);

		D3D11_DEPTH_STENCIL_VIEW_DESC dsvDesc;
		dsvDesc.Flags = 0;
		dsvDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
		dsvDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
		dsvDesc.Texture2D.MipSlice = 0;
		Global::g_d3dDevice->CreateDepthStencilView(depthMap, &dsvDesc, &m_depthMapDSV);

		D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc;
		srvDesc.Format = DXGI_FORMAT_R24_UNORM_X8_TYPELESS;
		srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
		srvDesc.Texture2D.MipLevels = texDesc.MipLevels;
		srvDesc.Texture2D.MostDetailedMip = 0;
		Global::g_d3dDevice->CreateShaderResourceView(depthMap, &srvDesc, &m_depthMapSRV);

		SAFE_RELEASE(depthMap);
	}

	VOID LightManager::AddMeshRenderer(AMeshRenderer* _meshRenderer)
	{
		m_meshRenderers.emplace_back(_meshRenderer);
	}

	VOID LightManager::RemoveMeshRenderer(AMeshRenderer* _meshRenderer)
	{
		m_meshRenderers.remove(_meshRenderer);
	}

	VOID LightManager::CreateSpotLight(int* _index)
	{
		Debug::ErrorMessage(m_spotLightMaxCount <= (int)m_spotLights.size(), "There is no more SpotLight!", "SpotLight Access Error");

		m_spotLights.emplace_back(SpotLightData());
		m_spotLightsIndexs.emplace_back(_index);
		*m_spotLightsIndexs.back() = m_spotLights.size() - 1;

		m_spotLights.back().Ambient = XMFLOAT4(0.0f, 0.0f, 0.0f, 0.0f);
		m_spotLights.back().Diffuse = XMFLOAT4(0.0f, 0.0f, 0.0f, 0.0f);
		m_spotLights.back().Specular = XMFLOAT4(0.0f, 0.0f, 0.0f, 0.0f);
		m_spotLights.back().Position = XMFLOAT3(0.0f, 0.0f, 0.0f);
		m_spotLights.back().Range = 0.0f;
		m_spotLights.back().Direction = XMFLOAT3(0.0f, 0.0f, 0.0f);
		m_spotLights.back().Spot = 0.0f;
		m_spotLights.back().Pad = 0.0f;
		m_spotLights.back().Att = XMFLOAT3(0.0f, 1.0f, 0.0f);
	}

	VOID LightManager::CreatePointLight(int* _index)
	{
		Debug::ErrorMessage(m_pointLightMaxCount <= (int)m_pointLights.size(), "There is no more SpotLight!", "SpotLight Access Error");

		m_pointLights.emplace_back(PointLightData());
		m_pointLightsIndexs.emplace_back(_index);
		*m_pointLightsIndexs.back() = m_pointLights.size() - 1;

		m_pointLights.back().Ambient = XMFLOAT4(0.0f, 0.0f, 0.0f, 0.0f);
		m_pointLights.back().Diffuse = XMFLOAT4(0.0f, 0.0f, 0.0f, 0.0f);
		m_pointLights.back().Specular = XMFLOAT4(0.0f, 0.0f, 0.0f, 0.0f);
		m_pointLights.back().Position = XMFLOAT3(0.0f, 0.0f, 0.0f);
		m_pointLights.back().Range = 0.0f;
		m_pointLights.back().Pad = 0.0f;
		m_pointLights.back().Att = XMFLOAT3(0.0f, 1.0f, 0.0f);
	}

	DirectionalLightData* LightManager::GetDirectionalLight()
	{
		Debug::ErrorMessage(m_directionalLightMaxCount <= m_directionalLightCount, "There is no more SpotLight!", "SpotLight Access Error");
		return &m_directionalLights[m_directionalLightCount++];
	}

	VOID LightManager::RemoveSpotLight(int _index)
	{
		m_spotLights.erase(m_spotLights.begin() + _index);
		for (int i = _index; i < (int)m_spotLightsIndexs.size(); i++)
		{
			(*m_spotLightsIndexs[i])--;
		}
		m_spotLightsIndexs.erase(m_spotLightsIndexs.begin() + _index);
	}

	VOID LightManager::RemovePointLight(int _index)
	{
		m_pointLights.erase(m_pointLights.begin() + _index);
		for (int i = _index; i < (int)m_pointLightsIndexs.size(); i++)
		{
			(*m_pointLightsIndexs[i])--;
		}
		m_pointLightsIndexs.erase(m_pointLightsIndexs.begin() + _index);
	}

	VOID LightManager::Awake()
	{
		LoadSRVandDSV();
		m_center = XMFLOAT3(0.0f, 0.0f, 0.0f);
		
		m_t = XMMATRIX(0.5f, 0.0f, 0.0f, 0.0f,
					   0.0f, -0.5f, 0.0f, 0.0f,
					   0.0f, 0.0f, 1.0f, 0.0f,
					   0.5f, 0.5f, 0.0f, 1.0f);

		//Init Dir
		m_spotLights.resize(0);
		m_pointLights.resize(0);
		m_meshRenderers.resize(0);
		m_directionalLights.resize(3);

		m_directionalLights[0].Ambient = XMFLOAT4(0.3f, 0.3f, 0.3f, 1.0f);
		m_directionalLights[0].Diffuse = XMFLOAT4(0.7f, 0.7f, 0.7f, 1.0f);
		m_directionalLights[0].Specular = XMFLOAT4(0.8f, 0.8f, 0.8f, 1.0f);
		m_directionalLights[0].Direction = XMFLOAT3(-0.57735f, -0.57735f, 0.57735f);

		m_directionalLights[1].Ambient = XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f);
		m_directionalLights[1].Diffuse = XMFLOAT4(0.40f, 0.40f, 0.40f, 1.0f);
		m_directionalLights[1].Specular = XMFLOAT4(0.2f, 0.2f, 0.2f, 1.0f);
		m_directionalLights[1].Direction = XMFLOAT3(0.707f, -0.707f, 0.0f);

		m_directionalLights[2].Ambient = XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f);
		m_directionalLights[2].Diffuse = XMFLOAT4(0.4f, 0.4f, 0.4f, 1.0f);
		m_directionalLights[2].Specular = XMFLOAT4(0.2f, 0.2f, 0.2f, 1.0f);
		m_directionalLights[2].Direction = XMFLOAT3(0.0f, 0.0, -1.0f);
	}

	VOID LightManager::Update()
	{
		//SetEyeW
		Effects::StandardShaderFX->SetEyePosW(Camera::GetInstance()->GetTransform()->GetWorldPosition());

		//SetDirectional
		Effects::StandardShaderFX->SetDirLights(m_directionalLights.data());
		Effects::PostProcessingFX->SetDirLights(m_directionalLights.data());

		//SetPoint And Count
		Effects::StandardShaderFX->SetPointLights(m_pointLights.data(), m_pointLights.size());
		Effects::PostProcessingFX->SetPointLights(m_pointLights.data(), m_pointLights.size());

		//SetSpot And Count
		Effects::StandardShaderFX->SetSpotLights(m_spotLights.data(), m_spotLights.size());
		Effects::PostProcessingFX->SetSpotLights(m_spotLights.data(), m_spotLights.size());
		m_center = Camera::GetInstance()->GetTransform()->GetWorldPosition();

		XMVECTOR lightDir = XMLoadFloat3(&m_directionalLights[0].Direction);
		m_lightPos.m128_f32[0] = m_center.x + (-2.0f * m_radius * lightDir.m128_f32[0]);
		m_lightPos.m128_f32[1] = m_center.y + (-2.0f * m_radius * lightDir.m128_f32[1]);
		m_lightPos.m128_f32[2] = m_center.z + (-2.0f * m_radius * lightDir.m128_f32[2]);
		m_lightPos.m128_f32[3] = 1 + (-2.0f * m_radius * lightDir.m128_f32[3]);

		XMVECTOR targetPos = XMLoadFloat3(& m_center);
		XMVECTOR up = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
		XMMATRIX V = XMMatrixLookAtLH(m_lightPos, targetPos, up);

		XMFLOAT3 sphereCenterLS;
		XMStoreFloat3(&sphereCenterLS, XMVector3TransformCoord(targetPos, V));

		float l = sphereCenterLS.x - m_radius;
		float b = sphereCenterLS.y - m_radius;
		float n = sphereCenterLS.z - m_radius;
		float r = sphereCenterLS.x + m_radius;
		float t = sphereCenterLS.y + m_radius;
		float f = sphereCenterLS.z + m_radius;
		XMMATRIX P = XMMatrixOrthographicOffCenterLH(l, r, b, t, n, f);

		XMMATRIX S = V * P * m_t;

		m_lightView = V;
		m_lightProj = P;
		m_shadowTransform = S;
	}

	VOID LightManager::Render()
	{
		if (m_isMakeShadow == false)
			return;

		ID3D11RenderTargetView* renderTargets1[1] = { 0 };
		Global::g_d3dImmediateContext->OMSetRenderTargets(1, renderTargets1, m_depthMapDSV);
		Global::g_d3dImmediateContext->ClearDepthStencilView(m_depthMapDSV, D3D11_CLEAR_DEPTH, 1.0f, 0);
		Global::g_d3dImmediateContext->RSSetViewports(1, &m_viewport);

		XMMATRIX viewProj = m_lightView * m_lightProj;
		Effects::BuildShadowMapFX->SetEyePosW(Camera::GetInstance()->GetTransform()->GetWorldPosition());
		Effects::BuildShadowMapFX->SetViewProj(viewProj);
		Effects::BuildShadowMapFX->SetHeightScale(0.07f);

		//Make Shadows from GameObjects
		for (auto& meshRenderer : m_meshRenderers)
		{
			meshRenderer->BuildShadowMap();
		}

		//Shadow
		Effects::StandardShaderFX->SetShadowMap(m_depthMapSRV);		
	}

	VOID LightManager::Clear()
	{
		m_meshRenderers.clear();
		m_pointLights.clear();
		m_spotLights.clear();
		m_spotLightsIndexs.clear();
		m_pointLightsIndexs.clear();
		m_directionalLights.clear();
		SAFE_RELEASE(m_depthMapDSV);
		SAFE_RELEASE(m_depthMapSRV);
	}
}