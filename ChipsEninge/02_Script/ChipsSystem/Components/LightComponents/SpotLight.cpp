#include "ChipsSystem/BasicFrame/GameObject.h"
#include "ChipsSystem/Components/BaiscComponents/Transform.h"
#include "ChipsSystem/Components/LightComponents/SpotLight.h"
#include "ChipsSystem/Manager/LightManager.h"

namespace ChipsEngine
{
	SpotLight::SpotLight() : AComponent("SpotLight"), m_index(0)
	{
	}

	VOID SpotLight::SetAmbient(XMFLOAT4 _ambient)
	{
		LightManager::GetInstance()->m_spotLights[m_index].Ambient = _ambient;
	}

	VOID SpotLight::SetDiffuse(XMFLOAT4 _diffuse)
	{
		LightManager::GetInstance()->m_spotLights[m_index].Diffuse = _diffuse;
	}

	VOID SpotLight::SetSpecular(XMFLOAT4 _specular)
	{
		LightManager::GetInstance()->m_spotLights[m_index].Specular = _specular;
	}

	VOID SpotLight::SetRange(float _range)
	{
		LightManager::GetInstance()->m_spotLights[m_index].Range = _range;
	}

	VOID SpotLight::SetSpot(float _spot)
	{
		LightManager::GetInstance()->m_spotLights[m_index].Spot = _spot;
	}

	XMFLOAT4 SpotLight::GetAmbient()
	{
		return LightManager::GetInstance()->m_spotLights[m_index].Ambient;
	}

	XMFLOAT4 SpotLight::GetDiffuse()
	{
		return LightManager::GetInstance()->m_spotLights[m_index].Diffuse;
	}

	XMFLOAT4 SpotLight::GetSpecular()
	{
		return LightManager::GetInstance()->m_spotLights[m_index].Specular;
	}

	float SpotLight::GetRange()
	{
		return LightManager::GetInstance()->m_spotLights[m_index].Range;
	}

	float SpotLight::GetSpot()
	{
		return LightManager::GetInstance()->m_spotLights[m_index].Spot;
	}

	VOID SpotLight::Awake()
	{
		LightManager::GetInstance()->CreateSpotLight(&m_index);
		LightManager::GetInstance()->m_spotLights[m_index].Ambient = XMFLOAT4(0.2f, 0.225f, 0.225f, 1.0f);
		LightManager::GetInstance()->m_spotLights[m_index].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
		LightManager::GetInstance()->m_spotLights[m_index].Specular = XMFLOAT4(0.7f, 0.7f, 0.7f, 1.0f);
		LightManager::GetInstance()->m_spotLights[m_index].Range = 10.0f;
		LightManager::GetInstance()->m_spotLights[m_index].Spot = 25.0f;
	}

	VOID SpotLight::Start()
	{
	}

	VOID SpotLight::Update()
	{
		GetGameObject()->GetTransform()->GetWorldMatrix();
		LightManager::GetInstance()->m_spotLights[m_index].Position = GetGameObject()->GetTransform()->GetWorldPosition();
		
		XMMATRIX rotationMatrix = GetGameObject()->GetTransform()->GetWorldRotationMatrix();
		XMVECTOR rotationVector = rotationMatrix.r[2];
		XMFLOAT3 rotationFloat3;
		
		XMStoreFloat3(&rotationFloat3, rotationVector);
		LightManager::GetInstance()->m_spotLights[m_index].Direction = rotationFloat3;
	}

	VOID SpotLight::FixedUpdate()
	{
	}

	VOID SpotLight::Render()
	{

	}

	VOID SpotLight::Release()
	{
		LightManager::GetInstance()->RemoveSpotLight(m_index);
	}
}