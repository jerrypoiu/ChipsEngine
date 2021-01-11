#ifndef CHIPSSYSTEM_COMPONENETS_RENDERERCOMPONENETS_QUADRENDERER_H
#define CHIPSSYSTEM_COMPONENETS_RENDERERCOMPONENETS_QUADRENDERER_H
#include "ChipsSystem/Components/RendererComponents/AMeshRenderer.h"

namespace ChipsEngine
{
	/*
	Quad 모양을 렌더링하는 컴포넌트이다.
	*/
	class QuadRenderer final : public AMeshRenderer
	{
	public:
		QuadRenderer();
	protected:
		virtual ~QuadRenderer() = default;
	private:
		virtual VOID InitGemometryBuffer() final;
	};
}

#endif //CHIPSSYSTEM_COMPONENETS_RENDERERCOMPONENETS_QUADRENDERER_H