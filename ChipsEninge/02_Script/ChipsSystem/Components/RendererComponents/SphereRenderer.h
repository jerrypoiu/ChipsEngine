#ifndef CHIPSSYSTEM_COMPONENETS_RENDERERCOMPONENETS_SPHERERENDERER_H
#define CHIPSSYSTEM_COMPONENETS_RENDERERCOMPONENETS_SPHERERENDERER_H
#include "DirectX/Effects/LightHelper.h"
#include "ChipsSystem/Components/RendererComponents/AMeshRenderer.h"

namespace ChipsEngine
{
	/*
	구 모양을 렌더링하는 컴포넌트이다.
	*/
	class SphereRenderer final : public AMeshRenderer
	{
	public:
		SphereRenderer();
	protected:
		virtual ~SphereRenderer() = default;
	private:
		virtual VOID InitGemometryBuffer() final;
	};
}

#endif //CHIPSSYSTEM_COMPONENETS_RENDERERCOMPONENETS_SPHERERENDERER_H