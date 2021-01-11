#ifndef CHIPSSYSTEM_COMPONENETS_RENDERERCOMPONENETS_CAPSULERENDERER_H
#define CHIPSSYSTEM_COMPONENETS_RENDERERCOMPONENETS_CAPSULERENDERER_H
#include "DirectX/Effects/LightHelper.h"
#include "ChipsSystem/Components/RendererComponents/AMeshRenderer.h"

namespace ChipsEngine
{
	/*
	Ä¸½¶ ¸ð¾çÀ» ·»´õ¸µÇÏ´Â ÄÄÆ÷³ÍÆ®ÀÌ´Ù.
	*/
	class CapsuleRenderer final : public AMeshRenderer
	{
	public:
		CapsuleRenderer();
	protected:
		virtual ~CapsuleRenderer() = default;
	private:
		virtual VOID InitGemometryBuffer() override;
	};
}

#endif //CHIPSSYSTEM_COMPONENETS_RENDERERCOMPONENETS_CAPSULERENDERER_H