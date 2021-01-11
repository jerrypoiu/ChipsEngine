#ifndef CHIPSSYSTEM_COMPONENETS_RENDERERCOMPONENETS_QUADRENDERER_H
#define CHIPSSYSTEM_COMPONENETS_RENDERERCOMPONENETS_QUADRENDERER_H
#include "ChipsSystem/Components/RendererComponents/AMeshRenderer.h"

namespace ChipsEngine
{
	/*
	Quad ����� �������ϴ� ������Ʈ�̴�.
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