#include "ChipsSystem/Manager/TextManager.h"

namespace ChipsEngine
{
	VOID TextManager::AddTextRenderFunc(TextReunderFunc _textRenderer)
	{
		m_textRenderFuncs.emplace_back(_textRenderer);
	}

	VOID TextManager::Awake()
	{
		m_textRenderFuncs.resize(0);
	}

	VOID TextManager::Render()
	{
		for (auto& func : m_textRenderFuncs)
		{
			func();
		}
	}

	VOID TextManager::Clear()
	{
		m_textRenderFuncs.clear();
	}
}