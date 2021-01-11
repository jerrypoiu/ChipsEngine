#ifndef CHIPSSYSTEM_COMPONENETS_COLLIDERCOMPONENETS_SPHERECOLLIDER_H
#define CHIPSSYSTEM_COMPONENETS_COLLIDERCOMPONENETS_SPHERECOLLIDER_H
#include "ChipsSystem/Components/ColliderComponents/ACollider.h"

namespace ChipsEngine
{
	class SphereCollider final : public ACollider
	{
	public:
		SphereCollider();
	protected:
		virtual ~SphereCollider() = default;
	public:
		float GetRadius();
		VOID SetRadius(float _radius);
	private:
#ifdef _DEBUG
		virtual VOID InitGemometryBuffer() override;
#endif
	private:
		virtual VOID Init() final;
	};
}

#endif //CHIPSSYSTEM_COMPONENETS_COLLIDERCOMPONENETS_SPHERECOLLIDER_H