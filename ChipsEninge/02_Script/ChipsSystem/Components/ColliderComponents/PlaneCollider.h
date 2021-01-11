#ifndef CHIPSSYSTEM_COMPONENETS_COLLIDERCOMPONENETS_PLANECOLLIDER_H
#define CHIPSSYSTEM_COMPONENETS_COLLIDERCOMPONENETS_PLANECOLLIDER_H
#include "ChipsSystem/Components/ColliderComponents/ACollider.h"

namespace ChipsEngine
{
	/*
	�ٴ� ����� Collider �� ������Ʈ�� �߰���Ű�� ������Ʈ�̴�.
	*/
	class PlaneCollider final : public ACollider
	{
	private:
		float m_planeHeight;
		PxBoxGeometry m_planeGeometry;
	public:
		PlaneCollider();
	protected:
		virtual ~PlaneCollider() = default;
	public:
		VOID SetFloorSize(float _x, float _z);
		VOID SetFloorSize(XMFLOAT2 _planeSize);
		XMFLOAT2 GetFloorSize();
	private:
		virtual VOID InitShape() override;
		virtual VOID ResetShape() override;
	};
}

#endif //CHIPSSYSTEM_COMPONENETS_COLLIDERCOMPONENETS_PLANECOLLIDER_H