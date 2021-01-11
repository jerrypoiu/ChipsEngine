#ifndef CHIPSSYSTEM_COMPONENETS_LIGHTCOMPONENETS_SPOTLIGHT_H 
#define	CHIPSSYSTEM_COMPONENETS_LIGHTCOMPONENETS_SPOTLIGHT_H
#include "DirectX/Effects/LightHelper.h"
#include "ChipsSystem/BasicFrame/AComponent.h"

namespace ChipsEngine
{
	/*
	1. ���� ���� ������ ����Ʈ�� �߰��ϴ� ������Ʈ�̴�.
	2. SpotLight �� �ִ� 50 ������ ����� �� ������, �ǽð� �׸��ڸ� ���� �� ����.
	*/
	class SpotLight final : public AComponent
	{
	private:
		int m_index;
	public:
		SpotLight();
	protected:
		~SpotLight() override = default;
	public:
		VOID SetAmbient(XMFLOAT4 _ambient);
		VOID SetDiffuse(XMFLOAT4 _diffuse);
		VOID SetSpecular(XMFLOAT4 _specular);
		VOID SetRange(float _range);
		VOID SetSpot(float _spot);
		XMFLOAT4 GetAmbient();
		XMFLOAT4 GetDiffuse();
		XMFLOAT4 GetSpecular();
		float GetRange();
		float GetSpot();
	private:
		virtual VOID Awake() final;
		virtual	VOID Start() final;
		virtual VOID Update() final;
		virtual VOID FixedUpdate() final;
		virtual VOID Render() final;
		virtual VOID Release() final;
	};
}
#endif //CHIPSSYSTEM_COMPONENETS_LIGHTCOMPONENETS_SPOTLIGHT_H