#ifndef CHIPSSYSTEM_MANAGER_TEXTMANAGER_H
#define CHIPSSYSTEM_MANAGER_TEXTMANAGER_H
#include "ChipsSystem/Etc/Singleton.h"
#include "ChipsSystem/Components/RendererComponents/TextRenderer.h"
#include "ChipsSystem/Global/Global.h"

namespace ChipsEngine
{
	using TextReunderFunc = function<VOID(VOID)> ;

	/*
	TextRenderer 의 정상적인 작동을 위해 존재하는 Manager 이며,
	사용자에게 직접적으로 제공되는 기능은 존재하지 않다.
	*/
	class TextManager final : public Singletone<TextManager>
	{
	private:
		list<TextReunderFunc> m_textRenderFuncs;
	public:
		TextManager() = default;
		~TextManager() = default;
	public:
		VOID Awake();
		VOID AddTextRenderFunc(TextReunderFunc m_textRenderfuncs);
		VOID Render();
		VOID Clear();
	};
}
#endif //CHIPSSYSTEM_MANAGER_TEXTMANAGER_H