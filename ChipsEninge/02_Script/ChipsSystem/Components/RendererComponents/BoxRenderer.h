#ifndef CHIPSSYSTEM_COMPONENETS_RENDERERCOMPONENETS_BOXRENDERER_H
#define CHIPSSYSTEM_COMPONENETS_RENDERERCOMPONENETS_BOXRENDERER_H
#include "DirectX/Effects/LightHelper.h"
#include "ChipsSystem/Components/RendererComponents/AMeshRenderer.h"

namespace ChipsEngine
{
	/*
	박스 모양을 렌더링하는 컴포넌트이다.
	*/
	class BoxRenderer final : public AMeshRenderer
	{
	public:
		BoxRenderer();
	protected:
		virtual ~BoxRenderer() = default;
	private:
		virtual VOID InitGemometryBuffer() override;
	};
}

#endif //CHIPSSYSTEM_COMPONENETS_RENDERERCOMPONENETS_BOXRENDERER_H