#ifndef CHIPSSYSTEM_COMPONENETS_UICOMPONENETS_UIBUTTON_H
#define CHIPSSYSTEM_COMPONENETS_UICOMPONENETS_UIBUTTON_H
#include "ChipsSystem/BasicFrame/AComponent.h"
#include "ChipsSystem/Components/UIComponents/AUIRenderer.h"

namespace ChipsEngine
{
	using PressedEventFunc = function<void(void)>;

	/*
	ImageUIRenderer, TextUIRenderer 에 Button 의 속성을 추가할 수 있는 컴포넌트이다.
	Image 또는 Text 에 마우스를 올리고 클릭을 하면 지정한 이벤트가 발생한다.
	마우스의 클릭 유무, 마우스가 클릭 가능한 상태인지에 따라, 
	Image 또는 Text 의 색상을 바꿀 수 있다.
	*/
	class UIButton final : public AComponent
	{
	private:
		XMVECTOR m_normalColor;
		XMVECTOR m_pressedColor;
		XMVECTOR m_highlightedColor;
		AUIRenderer* m_uiRenderer;
		list<PressedEventFunc> m_fressedEventFuncs;
	public:
		UIButton();
		~UIButton() = default;
	public:
		VOID SetNormalColor(XMVECTOR _normalColor);
		VOID SetPressedColor(XMVECTOR _pressedColor);
		VOID SetHighlightedColor(XMVECTOR _highlightedColor);
		VOID AddPressedEventFunc(PressedEventFunc _fressedEventFunc);
		VOID SetUIRenderer(AUIRenderer* _uiRenderer);
	private:
		virtual VOID Awake() final;
		virtual VOID Start() final;
		virtual VOID Update() final;
		virtual VOID FixedUpdate() final;
		virtual VOID Render() final;
		virtual VOID Release() final;
	};
}
#endif //CHIPSSYSTEM_COMPONENETS_UICOMPONENETS_UIBUTTON_H