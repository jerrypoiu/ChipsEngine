#include "ChipsSystem/Components/ColliderComponents/ACollider.h"
#include "ChipsSystem/Global/Global.h"
#include "ChipsSystem/Camera/Camera.h"
#include "ChipsSystem/Etc/Mathf.h"
#include "ChipsSystem/Etc/Debug.h"
#include "DirectX/Effects/Effects.h"
#include "DirectX/Effects/RenderStates.h"

namespace ChipsEngine
{
	ACollider::ACollider(string _componentType) : AComponent(_componentType), 
		m_collisionShpae(COLLISION_SHAPE::NON), m_collisionLayer(COLLISION_LAYER::NON_FIXED)
	{
#ifdef _DEBUG
		m_isLoaded = false;
		m_indexCount = 0;
		m_vertexBuffer = nullptr;
		m_indexBuffer = nullptr;

		m_material.Ambient = XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f);
		m_material.Diffuse = XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f);
		m_material.Specular = XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f);
		m_material.Reflect = XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f);
#endif
	}

	VOID ACollider::SetCollisionEvent(COLLISION_STATE _collisionEventType, CollsitionEvent _collsitionEvent)
	{
		switch (_collisionEventType)
		{
		case COLLISION_STATE::ENTER:
			m_collisionEnter = _collsitionEvent;
			break;
		case COLLISION_STATE::STAY:
			m_collisionStay = _collsitionEvent;
			break;
		case COLLISION_STATE::EXIT:
			m_collisionExit = _collsitionEvent;
			break;
		default:
			break;
		}
	}

	VOID ACollider::CalculateCollisionResult(bool _isCollision, GameObject* _coll)
	{
		if (m_collisionStates.find(_coll) == m_collisionStates.end())
		{
			m_collisionStates[_coll] = COLLISION_STATE::ENTER;
		}

		if (_isCollision)
		{
			switch (m_collisionStates[_coll])
			{
			case COLLISION_STATE::ENTER:
				m_collisionStates[_coll] = COLLISION_STATE::STAY; 
				m_collisionEnter(_coll);
				break;
			case COLLISION_STATE::STAY:
				m_collisionStates[_coll] = COLLISION_STATE::STAY;
				m_collisionStay(_coll);
				break;
			}
		}
		else
		{
			if (m_collisionStates[_coll] == COLLISION_STATE::STAY)
			{
				m_collisionStates[_coll] = COLLISION_STATE::ENTER;
				m_collisionExit(_coll);
			}
		}
	}

	VOID ACollider::Init()
	{
#ifdef _DEBUG
		InitGemometryBuffer();

		//LoadTexture
		DirectX::ScratchImage image;
		DirectX::LoadFromDDSFile(TEXT("01_Asset/Texture/Collider.dds"), DirectX::DDS_FLAGS_NONE, nullptr, image);
		DirectX::CreateShaderResourceView(Global::g_d3dDevice, image.GetImages(), image.GetImageCount(), image.GetMetadata(), &m_diffuseSRV);
#endif
		m_collisionEnter = [](GameObject* _marObject) { Debug::Log(_marObject->GetName() + " Enter"); };
		m_collisionStay = [](GameObject* _marObject) {};
		m_collisionExit = [](GameObject* _marObject) { Debug::Log(_marObject->GetName() + " Exit"); };
		m_collisionInfo = make_pair(this, XMFLOAT4());
		m_collisionInfo.first = this;
		CollisionManager::GetInstance()->AddCollision(&m_collisionInfo);
	}

	VOID ACollider::Update()
	{

	}

	VOID ACollider::Render()
	{
#ifdef _DEBUG
		if (m_isLoaded == false)
			return;

		UINT stride = sizeof(Basic32);
		UINT offset = 0;
		float blendFactor[] = { 0.0f, 0.0f, 0.0f, 0.0f };
		
		XMMATRIX world = XMMatrixScaling(m_collisionInfo.second.x + 0.01f, m_collisionInfo.second.y + 0.01f, m_collisionInfo.second.z + 0.01f)
						 * GetGameObject()->GetTransform()->GetWorldRotationMatrix() 
						 * GetGameObject()->GetTransform()->GetWorldTranslationMatrix();
		XMMATRIX view = Camera::GetInstance()->View();
		XMMATRIX proj = Camera::GetInstance()->Proj();
		XMMATRIX worldViewProj = world * view * proj;
		XMMATRIX worldInvTranspose = Mathf::InverseTranspose(world);

		Global::g_d3dImmediateContext->RSSetState(RenderStates::NoCullRS);
		Global::g_d3dImmediateContext->IASetInputLayout(InputLayouts::Basic32);
		Global::g_d3dImmediateContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
		Global::g_d3dImmediateContext->IASetVertexBuffers(0, 1, &m_vertexBuffer, &stride, &offset);
		Global::g_d3dImmediateContext->IASetIndexBuffer(m_indexBuffer, DXGI_FORMAT_R32_UINT, 0);

		ID3DX11EffectTechnique* activeSkullTech = Effects::BasicFX->Light0TexTech;

		D3DX11_TECHNIQUE_DESC techDesc;
		activeSkullTech->GetDesc(&techDesc);

		Effects::BasicFX->SetEyePosW(Camera::GetInstance()->GetTransform()->GetWorldPosition());
		Effects::BasicFX->SetWorld(world);
		Effects::BasicFX->SetWorldInvTranspose(worldInvTranspose);
		Effects::BasicFX->SetDiffuseMap(m_diffuseSRV);
		Effects::BasicFX->SetWorldViewProj(worldViewProj);
		Effects::BasicFX->SetMaterial(m_material);

		for (UINT p = 0; p < techDesc.Passes; ++p)
		{
			activeSkullTech->GetPassByIndex(p)->Apply(0, Global::g_d3dImmediateContext);
			Global::g_d3dImmediateContext->OMSetBlendState(RenderStates::TransparentBS, blendFactor, 0xffffffff);
			Global::g_d3dImmediateContext->DrawIndexed(m_indexCount, 0, 0);
		}
#endif
	}

	VOID ACollider::Release()
	{
		m_collisionStates.clear();
#ifdef _DEBUG
		SAFE_RELEASE(m_vertexBuffer);
		SAFE_RELEASE(m_indexBuffer);
		SAFE_RELEASE(m_diffuseSRV);
#endif
	}
}