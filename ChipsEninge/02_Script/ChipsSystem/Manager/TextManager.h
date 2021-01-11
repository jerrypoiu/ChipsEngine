#ifndef CHIPSSYSTEM_MANAGER_TEXTMANAGER_H
#define CHIPSSYSTEM_MANAGER_TEXTMANAGER_H
#include "ChipsSystem/Etc/Singleton.h"
#include "ChipsSystem/Components/RendererComponents/TextRenderer.h"
#include "ChipsSystem/Global/Global.h"

namespace ChipsEngine
{
	using TextReunderFunc = function<VOID(VOID)> ;

	/*
	TextRenderer �� �������� �۵��� ���� �����ϴ� Manager �̸�,
	����ڿ��� ���������� �����Ǵ� ����� �������� �ʴ�.
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