#include "ChipsSystem/Manager/UIManager.h"

namespace ChipsEngine
{
	UIManager::UIManager() : m_isConstantSize(true)
	{
	}

	VOID UIManager::AddUIRenderer(UIRenderComponent _uiRenderer)
	{
		m_uiRenderers.emplace_back(_uiRenderer);
		SortLayer();
	}

	VOID UIManager::SortLayer()
	{
		m_uiRenderers.sort([](UIRenderComponent _a, UIRenderComponent _b) {return _a.first->GetLayer() < _b.first->GetLayer(); });
	}
	
	VOID UIManager::Awake()
	{
		m_uiRenderers.resize(0);
	}
	
	VOID UIManager::Render()
	{
		//·»´õ
		for (auto& renderer : m_uiRenderers)
		{
			renderer.second();
		}
	}

	VOID UIManager::Clear()
	{
		m_uiRenderers.clear();
	}
}