#include "ChipsSystem/BasicFrame/GameObject.h"
#include "ChipsSystem/Components/RendererComponents/ParticleRenderer.h"
#include "ChipsSystem/Manager/ParticleManager.h"
#include "ChipsSystem/Global/Global.h"
#include "ChipsSystem/Etc/Mathf.h"

namespace ChipsEngine
{
	ParticleData::ParticleData() : m_isLoaded(false), m_firstRun(true), m_isFrustumCullingActive(true), m_frustumCullingRadius(1.0f), m_gameTime(0.0f), m_timeStep(0.0f), m_age(0.0f),
		m_speed(7.8f), m_spread(4.0f), m_maxParticles(0), m_createIntervalTime(0.005f), m_deleteTime(1.0f), m_fadeTime(1.0f),
		m_randomizePosition(0.0f), m_emitColor(1.0f, 1.0f, 1.0f), m_initVB(nullptr), m_drawVB(nullptr), m_streamOutVB(nullptr),
		m_texArraySRV(nullptr), m_randomTexSRV(nullptr)
	{}

	ParticleData::~ParticleData()
	{
		SAFE_RELEASE(m_initVB);
		SAFE_RELEASE(m_drawVB);
		SAFE_RELEASE(m_streamOutVB);
		SAFE_RELEASE(m_texArraySRV);
		SAFE_RELEASE(m_randomTexSRV);
	}

	ParticleRenderer::ParticleRenderer() : AComponent("ParticleRenderer"), m_particleData(nullptr)
	{
	}

	VOID ParticleRenderer::LoadTexture(const string _texturePath, UINT _maxParticlesCount)
	{
		if (m_particleData->m_isLoaded)
			return;

		m_particleData->m_isLoaded = true;
		m_particleData->m_maxParticles = _maxParticlesCount;
		
		wstring ws(_texturePath.begin(), _texturePath.end());
		DirectX::ScratchImage image;
		DirectX::LoadFromDDSFile(ws.c_str(), DirectX::DDS_FLAGS_NONE, nullptr, image);
		DirectX::CreateShaderResourceView(Global::g_d3dDevice, image.GetImages(), image.GetImageCount(), image.GetMetadata(), &m_particleData->m_texArraySRV);
		
		MakeRandomSRV();
		BuildVB();
	}

	VOID ParticleRenderer::MakeRandomSRV()
	{
		XMFLOAT4 randomValues[1024];

		for (int i = 0; i < 1024; ++i)
		{
			randomValues[i].x = Mathf::Random(-1.0f, 1.0f);
			randomValues[i].y = Mathf::Random(-1.0f, 1.0f);
			randomValues[i].z = Mathf::Random(-1.0f, 1.0f);
			randomValues[i].w = Mathf::Random(-1.0f, 1.0f);
		}

		D3D11_SUBRESOURCE_DATA initData;
		initData.pSysMem = randomValues;
		initData.SysMemPitch = 1024 * sizeof(XMFLOAT4);
		initData.SysMemSlicePitch = 0;

	
		D3D11_TEXTURE1D_DESC texDesc;
		texDesc.Width = 1024;
		texDesc.MipLevels = 1;
		texDesc.Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
		texDesc.Usage = D3D11_USAGE_IMMUTABLE;
		texDesc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
		texDesc.CPUAccessFlags = 0;
		texDesc.MiscFlags = 0;
		texDesc.ArraySize = 1;

		ID3D11Texture1D* randomTex = 0;
		Global::g_d3dDevice->CreateTexture1D(&texDesc, &initData, &randomTex);


		D3D11_SHADER_RESOURCE_VIEW_DESC viewDesc;
		viewDesc.Format = texDesc.Format;
		viewDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE1D;
		viewDesc.Texture1D.MipLevels = texDesc.MipLevels;
		viewDesc.Texture1D.MostDetailedMip = 0;

		Global::g_d3dDevice->CreateShaderResourceView(randomTex, &viewDesc, &m_particleData->m_randomTexSRV);

		SAFE_RELEASE(randomTex);
	}

	VOID ParticleRenderer::BuildVB()
	{
		D3D11_BUFFER_DESC vbd;
		vbd.Usage = D3D11_USAGE_DEFAULT;
		vbd.ByteWidth = sizeof(Particle) * 1;
		vbd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		vbd.CPUAccessFlags = 0;
		vbd.MiscFlags = 0;
		vbd.StructureByteStride = 0;

		Particle p;
		ZeroMemory(&p, sizeof(Particle));
		p.Age = 0.0f;
		p.Type = 0;

		D3D11_SUBRESOURCE_DATA vinitData;
		vinitData.pSysMem = &p;

		Global::g_d3dDevice->CreateBuffer(&vbd, &vinitData, &m_particleData->m_initVB);

		vbd.ByteWidth = sizeof(Particle) * m_particleData->m_maxParticles;
		vbd.BindFlags = D3D11_BIND_VERTEX_BUFFER | D3D11_BIND_STREAM_OUTPUT;

		Global::g_d3dDevice->CreateBuffer(&vbd, 0, &m_particleData->m_drawVB);
		Global::g_d3dDevice->CreateBuffer(&vbd, 0, &m_particleData->m_streamOutVB);
	}

	VOID ParticleRenderer::Awake()
	{
		m_particleData = new ParticleData();
		ParticleManager::GetInstance()->AddParticleData(m_particleData);
		m_particleData->m_transform = GetGameObject()->GetTransform();
	}

	VOID ParticleRenderer::Start()
	{
	}

	VOID ParticleRenderer::Update()
	{
	}

	VOID ParticleRenderer::FixedUpdate()
	{
	}

	VOID ParticleRenderer::Render()
	{
	}
	
	VOID ParticleRenderer::Release()
	{
		ParticleManager::GetInstance()->DeleteParticleData(m_particleData);
		SAFE_DELETE(m_particleData);
	}
}