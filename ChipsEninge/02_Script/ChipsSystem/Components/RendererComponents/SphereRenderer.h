#ifndef CHIPSSYSTEM_COMPONENETS_RENDERERCOMPONENETS_SPHERERENDERER_H
#define CHIPSSYSTEM_COMPONENETS_RENDERERCOMPONENETS_SPHERERENDERER_H
#include "DirectX/Effects/LightHelper.h"
#include "ChipsSystem/Components/RendererComponents/AMeshRenderer.h"

namespace ChipsEngine
{
	/*
	�� ����� �������ϴ� ������Ʈ�̴�.
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