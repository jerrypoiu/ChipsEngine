#ifndef CHIPSSYSTEM_COMPONENETS_RENDERERCOMPONENETS_PLANERENDERER_H
#define CHIPSSYSTEM_COMPONENETS_RENDERERCOMPONENETS_PLANERENDERER_H
#include "DirectX/Effects/LightHelper.h"
#include "ChipsSystem/Components/RendererComponents/AMeshRenderer.h"

namespace ChipsEngine
{
	/*
	�ٴ� ����� �������ϴ� ������Ʈ�̴�.
	*/
	class PlaneRenderer final : public AMeshRenderer
	{
	public:
		PlaneRenderer();
	protected:
		virtual ~PlaneRenderer() = default;
	private:
		virtual VOID InitGemometryBuffer() override;
	};
}

#endif //CHIPSSYSTEM_COMPONENETS_RENDERERCOMPONENETS_PLANERENDERER_H