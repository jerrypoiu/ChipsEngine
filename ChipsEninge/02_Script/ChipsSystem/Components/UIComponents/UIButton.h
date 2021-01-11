#ifndef CHIPSSYSTEM_COMPONENETS_UICOMPONENETS_UIBUTTON_H
#define CHIPSSYSTEM_COMPONENETS_UICOMPONENETS_UIBUTTON_H
#include "ChipsSystem/BasicFrame/AComponent.h"
#include "ChipsSystem/Components/UIComponents/AUIRenderer.h"

namespace ChipsEngine
{
	using PressedEventFunc = function<void(void)>;

	/*
	ImageUIRenderer, TextUIRenderer �� Button �� �Ӽ��� �߰��� �� �ִ� ������Ʈ�̴�.
	Image �Ǵ� Text �� ���콺�� �ø��� Ŭ���� �ϸ� ������ �̺�Ʈ�� �߻��Ѵ�.
	���콺�� Ŭ�� ����, ���콺�� Ŭ�� ������ ���������� ����, 
	Image �Ǵ� Text �� ������ �ٲ� �� �ִ�.
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