#include "ChipsSystem/Components/ColliderComponents/ACollider.h"
#include "ChipsSystem/Components/BaiscComponents/Rigidbody.h"
#include "ChipsSystem/BasicFrame/GameObject.h"
#include "ChipsSystem/Manager/PhysxManager.h"
#include "ChipsSystem/Etc/Mathf.h"
#include "ChipsSystem/Etc/Debug.h"
#include "DirectX/Effects/Effects.h"
#include "DirectX/Effects/RenderStates.h"

namespace ChipsEngine
{
	ACollider::ACollider(string _componentType) : AComponent(_componentType), 
		m_isLoaded(false), m_isTrigger(false), m_staticFriction(0.0f), m_dynamicFriction(0.0f), m_restitution(0.0f), 
		m_offset(XMFLOAT3()), m_pxTransform(PxTransform(0.0f, 0.0f, 0.0f)), m_shape(nullptr), m_material(nullptr)
	{	}

	VOID ACollider::SetPhysicsMaterial(float _staticFriction, float _dynamicFriction, float _restitution)
	{
		if (m_isLoaded == false)
		{
			Debug::Log("WARING : You tried to modify the Physics Material while it is not loaded.\"" + GetGameObject()->GetName() + "\" GameObject", LOG_TYPE::WARING_LOG);
			return;
		}

		m_staticFriction = Mathf::Clamp(_staticFriction, 0.0f, Mathf::Abs(_staticFriction));
		m_dynamicFriction = Mathf::Clamp(_dynamicFriction, 0.0f, Mathf::Abs(_dynamicFriction));
		m_restitution = Mathf::Clamp(_restitution, 0.0f, Mathf::Abs(_restitution));
		m_material = PhysxManager::GetInstance()->GetPhysics()->createMaterial(m_staticFriction, m_dynamicFriction, m_restitution);
		ResetShape();
	}

	VOID ACollider::SetStaticFriction(float _staticFriction)
	{
		if (m_isLoaded == false)
		{
			Debug::Log("WARING : You tried to modify the Static Friction while it is not loaded.\"" + GetGameObject()->GetName() + "\" GameObject", LOG_TYPE::WARING_LOG);
			return;
		}

		m_staticFriction = Mathf::Clamp(_staticFriction, 0.0f, Mathf::Abs(_staticFriction));
		m_material = PhysxManager::GetInstance()->GetPhysics()->createMaterial(m_staticFriction, m_dynamicFriction, m_restitution);
		ResetShape();
	}

	VOID ACollider::SetDynamicFriction(float _dynamicFriction)
	{
		if (m_isLoaded == false)
		{
			Debug::Log("WARING : You tried to modify the Dynamic Friction while it is not loaded.\"" + GetGameObject()->GetName() + "\" GameObject", LOG_TYPE::WARING_LOG);
			return;
		}

		m_dynamicFriction = Mathf::Clamp(_dynamicFriction, 0.0f, Mathf::Abs(_dynamicFriction));
		m_material = PhysxManager::GetInstance()->GetPhysics()->createMaterial(m_staticFriction, m_dynamicFriction, m_restitution);
		ResetShape();
	}

	VOID ACollider::SetRestitution(float _restitution)
	{
		if (m_isLoaded == false)
		{
			Debug::Log("WARING : You tried to modify the Restitution while it is not loaded.\"" + GetGameObject()->GetName() + "\" GameObject", LOG_TYPE::WARING_LOG);
			return;
		}

		m_restitution = Mathf::Clamp(_restitution, 0.0f, Mathf::Abs(_restitution));
		m_material = PhysxManager::GetInstance()->GetPhysics()->createMaterial(m_staticFriction, m_dynamicFriction, m_restitution);
		ResetShape();
	}

	VOID ACollider::SetOffset(XMFLOAT3 _offset)
	{
		if (m_isLoaded == false)
		{
			Debug::Log("WARING : You tried to modify the offset while it is not loaded.\"" + GetGameObject()->GetName() + "\" GameObject", LOG_TYPE::WARING_LOG);
			return;
		}
#if defined(DEBUG) | defined(_DEBUG)
		m_offsetMatrix.r[3].m128_f32[0] = _offset.x;
		m_offsetMatrix.r[3].m128_f32[1] = _offset.y;
		m_offsetMatrix.r[3].m128_f32[2] = _offset.z;
#endif

		m_offset = _offset;
		m_pxTransform = PxTransform(m_offset.x, m_offset.y, m_offset.z);
		ResetShape();
	}

	VOID ACollider::SetOffset(float _x, float _y, float _z)
	{
		SetOffset(XMFLOAT3(_x, _y, _z));
	}

	VOID ACollider::SetTrigger(bool _active)
	{
		if (m_isLoaded == false)
		{
			Debug::Log("WARING : You tried to modify the Trigger while it is not loaded.\"" + GetGameObject()->GetName() + "\" GameObject", LOG_TYPE::WARING_LOG);
			return;
		}

		m_isTrigger = _active;
		ResetShape();
	}

	VOID ACollider::Awake()
	{
#if defined(DEBUG) | defined(_DEBUG)
		m_offsetMatrix = XMMatrixIdentity();
		m_scaleMatrix = XMMatrixScaling(1.0f, 1.0f, 1.0f);
#endif
		m_rigidbody = GetGameObject()->GetComponent<Rigidbody>();
		m_material = PhysxManager::GetInstance()->GetPhysics()->createMaterial(0.5f, 0.5f, 0.1f);
		InitShape();
	}

	VOID ACollider::Start()
	{
	}

	VOID ACollider::Update()
	{
	}

	VOID ACollider::FixedUpdate()
	{
	}

	VOID ACollider::Render()
	{
#if defined(DEBUG) | defined(_DEBUG)
		if (m_isLoaded == false)
			return;

		UINT stride = sizeof(Vertex36);
		UINT offset = 0;
		float blendFactor[] = { 0.0f, 0.0f, 0.0f, 0.0f };

		XMMATRIX view = Camera::GetInstance()->View();
		XMMATRIX proj = Camera::GetInstance()->Proj();
		XMMATRIX worldMatrix = m_scaleMatrix * GetGameObject()->GetTransform()->GetWorldRotationMatrix()
			* GetGameObject()->GetTransform()->GetWorldTranslationMatrix() * m_offsetMatrix;
		XMMATRIX worldViewProj = worldMatrix * view * proj;
		XMMATRIX worldInvTranspose = Mathf::InverseTranspose(worldMatrix);

		Global::g_d3dImmediateContext->RSSetState(RenderStates::NoCullRS);
		Global::g_d3dImmediateContext->IASetInputLayout(InputLayouts::Vertex36);
		Global::g_d3dImmediateContext->IASetPrimitiveTopology(D3D10_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
		Global::g_d3dImmediateContext->IASetVertexBuffers(0, 1, &m_vertexBuffer, &stride, &offset);
		Global::g_d3dImmediateContext->IASetIndexBuffer(m_indexBuffer, DXGI_FORMAT_R32_UINT, 0);

		Effects::StandardShaderFX->SetWorld(worldMatrix);
		Effects::StandardShaderFX->SetWorldInvTranspose(worldInvTranspose);
		Effects::StandardShaderFX->SetWorldViewProj(worldViewProj);
		Effects::StandardShaderFX->SetNearFar(XMFLOAT2(Camera::GetInstance()->GetNearZ(), Camera::GetInstance()->GetFarZ()));
		Effects::StandardShaderFX->SetTexTransform(XMMatrixIdentity());
		Effects::StandardShaderFX->SetShadowTransform(XMMatrixIdentity());

		ID3DX11EffectTechnique* tech = Effects::StandardShaderFX->DebugTech;
		D3DX11_TECHNIQUE_DESC techDesc;
		tech->GetDesc(&techDesc);
		for (UINT p = 0; p < techDesc.Passes; ++p)
		{
			Global::g_d3dImmediateContext->OMSetBlendState(RenderStates::AlphaToCoverageBS, blendFactor, 0xffffffff);
			tech->GetPassByIndex(p)->Apply(0, Global::g_d3dImmediateContext);
			Global::g_d3dImmediateContext->DrawIndexed(m_indexCount, 0, 0);
		}

		Global::g_d3dImmediateContext->OMSetBlendState(0, blendFactor, 0xffffffff);
		Global::g_d3dImmediateContext->RSSetState(RenderStates::NoCullRS);
#endif
	} 

	VOID ACollider::Release()
	{
#if defined(DEBUG) | defined(_DEBUG)
		SAFE_RELEASE(m_vertexBuffer);
		SAFE_RELEASE(m_indexBuffer);
#endif

		if (m_shape != nullptr)
		{
			m_rigidbody->DettachShape(m_shape);
			m_shape->release();
			m_shape = nullptr;
		}
		
		if (m_material != nullptr)
		{
			m_material->release();
			m_material = nullptr;
		}
	}
}