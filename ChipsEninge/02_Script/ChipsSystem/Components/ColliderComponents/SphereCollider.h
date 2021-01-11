#ifndef CHIPSSYSTEM_COMPONENETS_COLLIDERCOMPONENETS_SPHERECOLLIDER_H
#define CHIPSSYSTEM_COMPONENETS_COLLIDERCOMPONENETS_SPHERECOLLIDER_H
#include "ChipsSystem/Components/ColliderComponents/ACollider.h"

namespace ChipsEngine
{
	/*
	�� ����� Collider �� ������Ʈ�� �߰���Ű�� ������Ʈ�̴�.
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