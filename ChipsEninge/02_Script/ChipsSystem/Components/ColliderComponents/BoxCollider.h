#ifndef CHIPSSYSTEM_COMPONENETS_COLLIDERCOMPONENETS_BOXCOLLIDER_H
#define CHIPSSYSTEM_COMPONENETS_COLLIDERCOMPONENETS_BOXCOLLIDER_H
#include "ChipsSystem/Components/ColliderComponents/ACollider.h"

namespace ChipsEngine
{
	/*
	�ڽ� ����� Collider �� ������Ʈ�� �߰���Ű�� ������Ʈ�̴�.
	*/
	class BoxCollider final : public ACollider
	{
	private:
		PxBoxGeometry m_boxGeometry;
	public:
		BoxCollider();
	protected:
		virtual ~BoxCollider() = default;
	public:
		VOID SetBoxSize(float _x, float _y, float _z);
		VOID SetBoxSize(XMFLOAT3 _boxSize);
		XMFLOAT3 GetBoxSize();
	private:
		virtual VOID InitShape() override;
		virtual VOID ResetShape() override;
	};
}

#endif //CHIPSSYSTEM_COMPONENETS_COLLIDERCCOMPONENETS_BOXCOLLIDER_H