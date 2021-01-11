#ifndef CHIPSSYSTEM_COMPONENETS_LIGHTCOMPONENETS_POINTLIGHT_H 
#define	CHIPSSYSTEM_COMPONENETS_LIGHTCOMPONENETS_POINTLIGHT_H
#include "DirectX/Effects/LightHelper.h"
#include "ChipsSystem/BasicFrame/AComponent.h"

namespace ChipsEngine
{
	/*
	1. 점 광원 형태의 라이트를 추가하는 컴포넌트있다.
	2. PointLight 는 최대 50 개까지 사용할 수 있으며, 실시간 그림자를 만들 수 없다.
	*/
	class PointLight final : public AComponent
	{
	private:
		int m_index;
	public:
		PointLight();
	protected:
		~PointLight() override = default;
	public:
		VOID SetAmbient(XMFLOAT4 _ambient);
		VOID SetDiffuse(XMFLOAT4 _diffuse);
		VOID SetSpecular(XMFLOAT4 _specular);
		VOID SetRange(float _range);
		XMFLOAT4 GetAmbient();
		XMFLOAT4 GetDiffuse();
		XMFLOAT4 GetSpecular();
		float GetRange();
	private:
		virtual VOID Awake() final;
		virtual	VOID Start() final;
		virtual VOID Update() final;
		virtual VOID FixedUpdate() final;
		virtual VOID Render() final;
		virtual VOID Release() final;
	};
}
#endif //CHIPSSYSTEM_COMPONENETS_LIGHTCOMPONENETS_POINTLIGHT_H