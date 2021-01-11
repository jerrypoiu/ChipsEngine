#include "ChipsSystem/BasicFrame/GameObject.h"
#include "ChipsSystem/Components/BaiscComponents/Transform.h"
#include "ChipsSystem/Components/LightComponents/DirectionalLight.h"
#include "ChipsSystem/Manager/LightManager.h"

namespace ChipsEngine
{
	DirectionalLight::DirectionalLight() : AComponent("DirectionalLight")
	{
	}

	VOID DirectionalLight::Awake()
	{
		m_directionalLightData = LightManager::GetInstance()->GetDirectionalLight();
		m_directionalLightData->Ambient = XMFLOAT4(0.2f, 0.2f, 0.2f, 1.0f);
		m_directionalLightData->Diffuse = XMFLOAT4(0.7f, 0.7f, 0.7f, 1.0f);
		m_directionalLightData->Specular = XMFLOAT4(0.8f, 0.8f, 0.8f, 1.0f);
	}

	VOID DirectionalLight::Start()
	{
	}
	
	VOID DirectionalLight::Update()
	{
		XMMATRIX rotationMatrix = GetGameObject()->GetTransform()->GetWorldRotationMatrix();
		XMVECTOR rotationVector = rotationMatrix.r[2];
		XMFLOAT3 rotationFloat3;
		XMStoreFloat3(&rotationFloat3, rotationVector);
		m_directionalLightData->Direction = rotationFloat3;
	}

	VOID DirectionalLight::FixedUpdate()
	{
	}

	VOID DirectionalLight::Render()
	{
	}

	VOID DirectionalLight::Release()
	{
	}
}