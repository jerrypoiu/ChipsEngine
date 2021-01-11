#ifndef CHIPSSYSTEM_COMPONENETS_RENDERERCOMPONENETS_CYLINDERRENDERER_H
#define CHIPSSYSTEM_COMPONENETS_RENDERERCOMPONENETS_CYLINDERRENDERER_H
#include "DirectX/Effects/LightHelper.h"
#include "ChipsSystem/Components/RendererComponents/AMeshRenderer.h"

namespace ChipsEngine
{
	/*
	실린더 모양을 렌더링하는 컴포넌트이다.
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