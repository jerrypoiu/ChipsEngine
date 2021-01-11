#include "DirectX/Effects/Effects.h"
#include "ChipsSystem/Global/Global.h"
#include "DirectX/MeshGenerator/MeshGenerator.h"
#include "ChipsSystem/BasicFrame/GameObject.h"
#include "ChipsSystem/Camera/Camera.h"
#include "ChipsSystem/Components/BaiscComponents/Transform.h"
#include "ChipsSystem/Components/RendererComponents/SkyRenderer.h"

namespace ChipsEngine
{
	SkyRenderer::SkyRenderer() : AComponent("SkyRenderer"), m_skyRotate(0.0f), m_vertexBuffer(nullptr), m_indexBuffer(nullptr), m_cubeMapSRV(nullptr)
	{
	}

	VOID SkyRenderer::LoadTexture(const string _fileName)
	{
		wstring ws(_fileName.begin(), _fileName.end());
		DirectX::ScratchImage image;
		DirectX::LoadFromDDSFile(ws.c_str(), DirectX::DDS_FLAGS_NONE, nullptr, image);
		DirectX::CreateShaderResourceView(Global::g_d3dDevice, image.GetImages(), image.GetImageCount(), image.GetMetadata(), &m_cubeMapSRV);
	}

	VOID SkyRenderer::InitGemometryBuffer()
	{
		MeshData meshData;
		MeshGenerator::CreateSphere(5000.0f, 30, 30, meshData);

		vector<XMFLOAT3> vertecBufferIn(meshData.Vertices.size());
		
		for (size_t i = 0; i < meshData.Vertices.size(); ++i)
		{
			vertecBufferIn[i] = meshData.Vertices[i].pos;
		}

		D3D11_BUFFER_DESC vbd;
		vbd.Usage = D3D11_USAGE_IMMUTABLE;
		vbd.ByteWidth = sizeof(XMFLOAT3) * vertecBufferIn.size();
		vbd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		vbd.CPUAccessFlags = 0;
		vbd.MiscFlags = 0;
		vbd.StructureByteStride = 0;

		D3D11_SUBRESOURCE_DATA vinitData;
		vinitData.pSysMem = &vertecBufferIn[0];

		Global::g_d3dDevice->CreateBuffer(&vbd, &vinitData, &m_vertexBuffer);

		m_indexCount = meshData.Indices.size();

		D3D11_BUFFER_DESC ibd;
		ibd.Usage = D3D11_USAGE_IMMUTABLE;
		ibd.ByteWidth = sizeof(USHORT) * m_indexCount;
		ibd.BindFlags = D3D11_BIND_INDEX_BUFFER;
		ibd.CPUAccessFlags = 0;
		ibd.StructureByteStride = 0;
		ibd.MiscFlags = 0;

		std::vector<USHORT> indices16;
		indices16.assign(meshData.Indices.begin(), meshData.Indices.end());

		D3D11_SUBRESOURCE_DATA iinitData;
		iinitData.pSysMem = &indices16[0];

		Global::g_d3dDevice->CreateBuffer(&ibd, &iinitData, &m_indexBuffer);
	}

	VOID SkyRenderer::Awake()
	{
		InitGemometryBuffer();
	}

	VOID SkyRenderer::Start()
	{
	}
	
	VOID SkyRenderer::Update()
	{
		GetGameObject()->GetTransform()->SetWorldPosition(Camera::GetInstance()->GetTransform()->GetWorldPosition());
	}

	VOID SkyRenderer::FixedUpdate()
	{
	}
	
	VOID SkyRenderer::Render()
	{
		XMFLOAT3 eyePos = Camera::GetInstance()->GetTransform()->GetWorldPosition();
		XMMATRIX T = DirectX::XMMatrixTranslation(eyePos.x, eyePos.y, eyePos.z);
		XMMATRIX R = DirectX::XMMatrixRotationRollPitchYaw(0.0f, m_skyRotate * DEGREES_TO_RADIANS, 0.0f);

		XMMATRIX WV = T * R * Camera::GetInstance()->View();
		XMMATRIX WVP =  T * R * Camera::GetInstance()->View() * Camera::GetInstance()->Proj();

		Effects::SkyFX->SetWorldViewProj(WVP);
		Effects::SkyFX->SetWorldView(WV);
		Effects::SkyFX->SetNearFar(XMFLOAT2(Camera::GetInstance()->GetNearZ(), Camera::GetInstance()->GetFarZ()));
		Effects::SkyFX->SetCubeMap(m_cubeMapSRV);
		Effects::StandardShaderFX->SetCubeMap(m_cubeMapSRV);
		Effects::PostProcessingFX->SetCubeMap(m_cubeMapSRV);

		UINT stride = sizeof(XMFLOAT3);
		UINT offset = 0;
		Global::g_d3dImmediateContext->IASetInputLayout(InputLayouts::Pos);
		Global::g_d3dImmediateContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
		Global::g_d3dImmediateContext->IASetVertexBuffers(0, 1, &m_vertexBuffer, &stride, &offset);
		Global::g_d3dImmediateContext->IASetIndexBuffer(m_indexBuffer, DXGI_FORMAT_R16_UINT, 0);

		D3DX11_TECHNIQUE_DESC techDesc;
		Effects::SkyFX->SkyTech->GetDesc(&techDesc);

		for (UINT p = 0; p < techDesc.Passes; ++p)
		{
			ID3DX11EffectPass* pass = Effects::SkyFX->SkyTech->GetPassByIndex(p);
			pass->Apply(0, Global::g_d3dImmediateContext);
			Global::g_d3dImmediateContext->DrawIndexed(m_indexCount, 0, 0);
		}
	}
	
	VOID SkyRenderer::Release()
	{
		SAFE_RELEASE(m_vertexBuffer);
		SAFE_RELEASE(m_indexBuffer);
		SAFE_RELEASE(m_cubeMapSRV);
	}
}