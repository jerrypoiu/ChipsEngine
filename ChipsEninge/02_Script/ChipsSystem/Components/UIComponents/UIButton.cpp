#include "ChipsSystem/BasicFrame/GameObject.h"
#include "ChipsSystem/Components/UIComponents/UIButton.h"
#include "ChipsSystem/Components/BaiscComponents/Transform.h"
#include "ChipsSystem/Etc/Input.h"
#include "ChipsSystem/Manager/GraphicManager.h"
#include "ChipsSystem/Manager/UIManager.h"
#include "ChipsSystem/Global/Global.h"
#include"ChipsSystem/Etc/Debug.h"

namespace ChipsEngine
{
	UIButton::UIButton() : AComponent("UIButton"), m_uiRenderer(nullptr)
	{}

	VOID UIButton::AddPressedEventFunc(PressedEventFunc _fressedEventFunc)
	{
		m_fressedEventFuncs.emplace_back(_fressedEventFunc);
	}

	VOID UIButton::SetUIRenderer(AUIRenderer* _uiRenderer)
	{
		m_uiRenderer = _uiRenderer;
	}

	VOID UIButton::SetNormalColor(XMVECTOR _normalColor)
	{
		m_normalColor = _normalColor;
	}
	VOID UIButton::SetPressedColor(XMVECTOR _pressedColor)
	{
		m_pressedColor = _pressedColor;
	}
	VOID UIButton::SetHighlightedColor(XMVECTOR _highlightedColor)
	{
		m_highlightedColor = _highlightedColor;
	}

	VOID UIButton::Awake()
	{
		m_fressedEventFuncs.resize(0);
		SetNormalColor(White);
		SetPressedColor(Black);
		SetHighlightedColor(Gray);
	}

	VOID UIButton::Start()
	{
	}

	VOID UIButton::Update()
	{
		if (PtInRect(&m_uiRenderer->GetRect(), Input::GetMousePosition()))
		{
			if (Input::GetMouseButton(0))
			{
				m_uiRenderer->SetColor(m_pressedColor);
			}
			else if (Input::GetMouseButtonUp(0))
			{
				for (auto& _event : m_fressedEventFuncs)
				{
					_event();
				}
			}
			else
			{
				m_uiRenderer->SetColor(m_highlightedColor);
			}
		}
		else
		{
			m_uiRenderer->SetColor(m_normalColor);
		}
	}

	VOID UIButton::FixedUpdate()
	{
	}

	VOID UIButton::Render()
	{

	}

	VOID UIButton::Release()
	{
		m_fressedEventFuncs.clear();
	}
}