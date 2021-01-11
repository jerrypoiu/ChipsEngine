#ifndef CHIPSSYSTEM_COMPONENETS_COLLIDERCOMPONENETS_CAPSULECOLLIDER_H
#define CHIPSSYSTEM_COMPONENETS_COLLIDERCOMPONENETS_CAPSULECOLLIDER_H
#include "ChipsSystem/Components/ColliderComponents/ACollider.h"

namespace ChipsEngine
{
	/*
	캡슐 모양의 Collider 를 오브젝트에 추가시키는 컴포넌트이다.
	*/
	class CapsuleCollider final : public ACollider
	{
	private:
		PxCapsuleGeometry m_capsuleGeometry;
	public:
		CapsuleCollider();
	protected:
		virtual ~CapsuleCollider() = default;
	public:
		VOID SetCapsuleSize(float _raduis, float _halfHeight);
		VOID SetCapsuleSize(XMFLOAT2 _capsuleSize);
		XMFLOAT2 GetCapsuleSize();
	private:
		virtual VOID InitShape() override;
		virtual VOID ResetShape() override;
	};
}

#endif //CHIPSSYSTEM_COMPONENETS_COLLIDERCOMPONENETS_CAPSULECOLLIDER_H