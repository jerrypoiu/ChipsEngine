#include "ChipsSystem/BasicFrame/GameObject.h"
#include "ChipsSystem/Components/BaiscComponents/Transform.h"
#include "ChipsSystem/Components/LightComponents/PointLight.h"
#include "ChipsSystem/Manager/LightManager.h"

namespace ChipsEngine
{
	PointLight::PointLight() : AComponent("PointLight"), m_index(0)
	{
	}

	VOID PointLight::SetAmbient(XMFLOAT4 _ambient)
	{
		LightManager::GetInstance()->m_pointLights[m_index].Ambient = _ambient;
	}

	VOID PointLight::SetDiffuse(XMFLOAT4 _diffuse)
	{
		LightManager::GetInstance()->m_pointLights[m_index].Diffuse = _diffuse;
	}

	VOID PointLight::SetSpecular(XMFLOAT4 _specular)
	{
		LightManager::GetInstance()->m_pointLights[m_index].Specular = _specular;
	}

	VOID PointLight::SetRange(float _range)
	{
		LightManager::GetInstance()->m_pointLights[m_index].Range = _range;
	}

	XMFLOAT4 PointLight::GetAmbient()
	{
		return LightManager::GetInstance()->m_pointLights[m_index].Ambient;
	}

	XMFLOAT4 PointLight::GetDiffuse()
	{
		return LightManager::GetInstance()->m_pointLights[m_index].Diffuse;
	}

	XMFLOAT4 PointLight::GetSpecular()
	{
		return LightManager::GetInstance()->m_pointLights[m_index].Specular;
	}

	float PointLight::GetRange()
	{
		return LightManager::GetInstance()->m_pointLights[m_index].Range;
	}

	VOID PointLight::Awake()
	{
		LightManager::GetInstance()->CreatePointLight(&m_index);

		LightManager::GetInstance()->m_pointLights[m_index].Ambient = XMFLOAT4(0.2f, 0.225f, 0.225f, 1.0f);
		LightManager::GetInstance()->m_pointLights[m_index].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
		LightManager::GetInstance()->m_pointLights[m_index].Specular = XMFLOAT4(0.7f, 0.7f, 0.7f, 1.0f);
		LightManager::GetInstance()->m_pointLights[m_index].Range = 25.0f;
	}

	VOID PointLight::Start()
	{
	}

	VOID PointLight::Update()
	{
		GetGameObject()->GetTransform()->GetWorldMatrix();
		LightManager::GetInstance()->m_pointLights[m_index].Position = GetGameObject()->GetTransform()->GetWorldPosition();
	}

	VOID PointLight::FixedUpdate()
	{
	}

	VOID PointLight::Render()
	{
	}

	VOID PointLight::Release()
	{
		LightManager::GetInstance()->RemovePointLight(m_index);
	}
}