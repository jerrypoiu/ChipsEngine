#ifndef CHIPSSYSTEM_COMPONENETS_RENDERERCOMPONENETS_BOXRENDERER_H
#define CHIPSSYSTEM_COMPONENETS_RENDERERCOMPONENETS_BOXRENDERER_H
#include "DirectX/Effects/LightHelper.h"
#include "ChipsSystem/Components/RendererComponents/AMeshRenderer.h"

namespace ChipsEngine
{
	/*
	�ڽ� ����� �������ϴ� ������Ʈ�̴�.
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