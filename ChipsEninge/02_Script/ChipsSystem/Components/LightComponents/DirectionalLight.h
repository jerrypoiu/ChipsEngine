#ifndef CHIPSSYSTEM_COMPONENETS_LIGHTCOMPONENETS_DIRECTOINALLIGHT_H 
#define	CHIPSSYSTEM_COMPONENETS_LIGHTCOMPONENETS_DIRECTOINALLIGHT_H
#include "DirectX/Effects/LightHelper.h"
#include "ChipsSystem/BasicFrame/AComponent.h"

namespace ChipsEngine
{
	/*
	1. �¾籤 ������ ����Ʈ�� �߰��ϴ� ������Ʈ�̴�.
	2. DirectionalLight �� �ִ� 3 ������ ����� �� ������, 1 ��°�� �߰��� Directional Light �� �ǽð� �׸��ڸ� ������.
	*/
	class DirectionalLight final : public AComponent
	{
	private:
		DirectionalLightData* m_directionalLightData;
	public:
		DirectionalLight();
	protected:
		~DirectionalLight() override = default;
	public:
		inline VOID SetAmbient(XMFLOAT4 _ambient)
		{
			m_directionalLightData->Ambient = _ambient;
		}
		inline VOID SetDiffuse(XMFLOAT4 _diffuse)
		{
			m_directionalLightData->Diffuse = _diffuse;
		}
		inline VOID SetSpecular(XMFLOAT4 _specular)
		{
			m_directionalLightData->Specular = _specular;
		}
		inline XMFLOAT4 GetAmbient()
		{
			return m_directionalLightData->Ambient;
		}
		inline XMFLOAT4 GetDiffuse()
		{
			return m_directionalLightData->Diffuse;
		}
		inline XMFLOAT4 GetSpecular()
		{
			return m_directionalLightData->Specular;
		}
	private:
		virtual VOID Awake() final;
		virtual	VOID Start() final;
		virtual VOID Update() final;
		virtual VOID FixedUpdate() final;
		virtual VOID Render() final;
		virtual VOID Release() final;
	};
}
#endif //CHIPSSYSTEM_COMPONENETS_LIGHTCOMPONENETS_DIRECTOINALLIGHT_H