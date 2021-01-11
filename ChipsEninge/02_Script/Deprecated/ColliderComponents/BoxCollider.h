#ifndef CHIPSSYSTEM_COMPONENETS_COLLIDERCOMPONENETS_BOXCOLLIDER_H
#define CHIPSSYSTEM_COMPONENETS_COLLIDERCOMPONENETS_BOXCOLLIDER_H
#include "ChipsSystem/Components/ColliderComponents/ACollider.h"

namespace ChipsEngine
{
	class BoxCollider final : public ACollider
	{
	public:
		BoxCollider();
	protected:
		virtual ~BoxCollider() = default;
	public:
		VOID SetBoxSize(float _x, float _y, float _z);
		VOID SetBoxSize(XMFLOAT3 _boxSize);
		XMFLOAT3 GetBoxSize();
	private:
#ifdef _DEBUG
		virtual VOID InitGemometryBuffer() override;
#endif
	private:
		virtual VOID Init() final;
	};
}

#endif //CHIPSSYSTEM_COMPONENETS_COLLIDERCCOMPONENETS_BOXCOLLIDER_H