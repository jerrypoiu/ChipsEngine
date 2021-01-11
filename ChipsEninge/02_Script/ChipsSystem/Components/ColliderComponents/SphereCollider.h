#ifndef CHIPSSYSTEM_COMPONENETS_COLLIDERCOMPONENETS_SPHERECOLLIDER_H
#define CHIPSSYSTEM_COMPONENETS_COLLIDERCOMPONENETS_SPHERECOLLIDER_H
#include "ChipsSystem/Components/ColliderComponents/ACollider.h"

namespace ChipsEngine
{
	/*
	구 모양의 Collider 를 오브젝트에 추가시키는 컴포넌트이다.
	*/
	class SphereCollider final : public ACollider
	{
	private:
		PxSphereGeometry m_sphereGeometry;
	public:
		SphereCollider();
	protected:
		virtual ~SphereCollider() = default;
	public:
		float GetRadius();
		VOID SetRadius(float _radius);
	private:
		virtual VOID InitShape() override;
		virtual VOID ResetShape() override;
	};
}

#endif //CHIPSSYSTEM_COMPONENETS_COLLIDERCOMPONENETS_SPHERECOLLIDER_H