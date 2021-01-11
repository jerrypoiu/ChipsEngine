#ifndef CHIPSSYSTEM_COMPONENETS_RENDERERCOMPONENETS_CYLINDERRENDERER_H
#define CHIPSSYSTEM_COMPONENETS_RENDERERCOMPONENETS_CYLINDERRENDERER_H
#include "DirectX/Effects/LightHelper.h"
#include "ChipsSystem/Components/RendererComponents/AMeshRenderer.h"

namespace ChipsEngine
{
	/*
	�Ǹ��� ����� �������ϴ� ������Ʈ�̴�.
	*/
	class CylinderRenderer final : public AMeshRenderer
	{
	public:
		CylinderRenderer();
	protected:
		virtual ~CylinderRenderer() = default;
	private:
		virtual VOID InitGemometryBuffer() override;
	};
}

#endif //CHIPSSYSTEM_COMPONENETS_RENDERERCOMPONENETS_CYLINDERRENDERER_H