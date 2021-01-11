#include "DirectX/Effects/RenderStates.h"
#include "ChipsSystem/Manager/ParticleManager.h"
#include "ChipsSystem/Global/Global.h"
#include "ChipsSystem/Camera/Camera.h"
#include "ChipsSystem/Time/Time.h"
#include "ChipsSystem/Etc/Mathf.h"

namespace ChipsEngine
{
	ParticleManager::ParticleManager() : m_particleCurrentCount(0), m_curTime(0), m_oldTime(0), m_deltaTime(0.0f)
	{}

	VOID ParticleManager::AddParticleData(ParticleData* _particleData)
	{
		m_particleCurrentCount++;
		m_particleDatas.emplace_back(_particleData);
	}

	VOID ParticleManager::DeleteParticleData(ParticleData* _particleData)
	{
		m_particleDatas.remove(_particleData);
	}

	VOID ParticleManager::Awake()
	{
		m_particleDatas.resize(0);
		__int64 countsPerSec;
		QueryPerformanceFrequency((LARGE_INTEGER*)&countsPerSec);
		m_secondsPerCount = 1.0 / (double)countsPerSec;
		QueryPerformanceCounter((LARGE_INTEGER*)&m_oldTime);
	}

	VOID ParticleManager::Update()
	{	}

	VOID ParticleManager::Render()
	{
		QueryPerformanceCounter((LARGE_INTEGER*)&m_curTime);
		m_deltaTime = (float)((m_curTime - m_oldTime) * m_secondsPerCount);
		m_oldTime = m_curTime;

		for (auto const data : m_particleDatas)
		{
			if (data->m_isLoaded == false)
				return;

			data->m_gameTime = Time::GetTotalTime();
			data->m_timeStep = m_deltaTime;
			data->m_age += m_deltaTime;
			data->m_size.x = data->m_transform->GetWorldScale().x;
			data->m_size.y = data->m_transform->GetWorldScale().y;
			data->m_cameraPos = Camera::GetInstance()->GetTransform()->GetWorldPosition();

			if (data->m_isFrustumCullingActive && Mathf::CheckFrustumCulling(data->m_transform, data->m_frustumCullingRadius))
				continue;

			XMMATRIX VP = Camera::GetInstance()->View() * Camera::GetInstance()->Proj();
			Effects::ParticleFX->SetViewProj(VP);
			Effects::ParticleFX->SetView(Camera::GetInstance()->View());
			Effects::ParticleFX->SetNearFar(XMFLOAT2(Camera::GetInstance()->GetNearZ(), Camera::GetInstance()->GetFarZ()));
			Effects::ParticleFX->SetGameTime(data->m_gameTime);
			Effects::ParticleFX->SetTimeStep(data->m_timeStep);
			Effects::ParticleFX->SetEmitSpread(data->m_spread);
			Effects::ParticleFX->SetCreateIntervalTime(data->m_createIntervalTime);
			Effects::ParticleFX->SetDeleteTime(data->m_deleteTime);
			Effects::ParticleFX->SetFadeTime(data->m_fadeTime);
			Effects::ParticleFX->SetRandomizePosition(data->m_randomizePosition);
			Effects::ParticleFX->SetEyePosW(data->m_cameraPos);
			Effects::ParticleFX->SetEmitPosW(data->m_transform->GetWorldPosition());
			Effects::ParticleFX->SetEmitColor(data->m_emitColor);
			Effects::ParticleFX->SetEmitSizeW(data->m_size);
			Effects::ParticleFX->SetTexArray(data->m_texArraySRV);
			Effects::ParticleFX->SetRandomTex(data->m_randomTexSRV);

			XMMATRIX rotationMatrix = data->m_transform->GetWorldRotationMatrix();
			XMVECTOR rotationVector = rotationMatrix.r[2];
			XMFLOAT3 emitFloat3;
			XMStoreFloat3(&emitFloat3, rotationVector);
			emitFloat3.x *= data->m_speed;
			emitFloat3.y *= data->m_speed;
			emitFloat3.z *= data->m_speed;
			Effects::ParticleFX->SetEmitMove(emitFloat3);

			Global::g_d3dImmediateContext->RSSetState(RenderStates::NoCullRS);
			Global::g_d3dImmediateContext->IASetInputLayout(InputLayouts::Particle);
			Global::g_d3dImmediateContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_POINTLIST);

			UINT stride = sizeof(Particle);
			UINT offset = 0;

			if (data->m_firstRun)
			{
				Global::g_d3dImmediateContext->IASetVertexBuffers(0, 1, &data->m_initVB, &stride, &offset);
			}
			else
			{
				Global::g_d3dImmediateContext->IASetVertexBuffers(0, 1, &data->m_drawVB, &stride, &offset);
			}

			Global::g_d3dImmediateContext->SOSetTargets(1, &data->m_streamOutVB, &offset);

			D3DX11_TECHNIQUE_DESC techDesc;
			Effects::ParticleFX->StreamOutTech->GetDesc(&techDesc);
			for (UINT p = 0; p < techDesc.Passes; ++p)
			{
				Effects::ParticleFX->StreamOutTech->GetPassByIndex(p)->Apply(0, Global::g_d3dImmediateContext);

				if (data->m_firstRun)
				{
					Global::g_d3dImmediateContext->Draw(1, 0);
					data->m_firstRun = false;
				}
				else
				{
					Global::g_d3dImmediateContext->DrawAuto();
				}
			}

			float blendFactor[] = { 0.0f, 0.0f, 0.0f, 0.0f };

			ID3D11Buffer* bufferArray[1] = { 0 };			
			Global::g_d3dImmediateContext->SOSetTargets(1, bufferArray, &offset);
			std::swap(data->m_drawVB, data->m_streamOutVB);
			Global::g_d3dImmediateContext->OMSetBlendState(RenderStates::AlphaToCoverageBS, blendFactor, 0xffffffff);
			Global::g_d3dImmediateContext->IASetVertexBuffers(0, 1, &data->m_drawVB, &stride, &offset);
			
			Effects::ParticleFX->DrawTech->GetDesc(&techDesc);
			for (UINT p = 0; p < techDesc.Passes; ++p)
			{
				Effects::ParticleFX->DrawTech->GetPassByIndex(p)->Apply(0, Global::g_d3dImmediateContext);
				Global::g_d3dImmediateContext->DrawAuto();
			}

			Global::g_d3dImmediateContext->SOSetTargets(0, 0, 0);
			Global::g_d3dImmediateContext->RSSetState(RenderStates::NoCullRS);
			Global::g_d3dImmediateContext->OMSetBlendState(0, blendFactor, 0xffffffff);
			Global::g_d3dImmediateContext->OMSetDepthStencilState(Global::g_depthStencilState, 1);
		}
	}

	VOID ParticleManager::Clear()
	{
		m_particleDatas.clear();
	}
}