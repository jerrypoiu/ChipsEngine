#ifndef CHIPSSYSTEM_COMPONENETS_UICOMPONENETS_TEXTUIERENDERER_H
#define CHIPSSYSTEM_COMPONENETS_UICOMPONENETS_TEXTUIERENDERER_H
#include "ChipsSystem/Components/UIComponents/AUIRenderer.h"
#include "ChipsSystem/Components/RendererComponents/TextRenderer.h"

namespace ChipsEngine
{
	/*
	Text 를 스크린 공간에 렌더링하는 컴포넌트이다. 
	다음과 같은 기능들을 제공한다.
	디음과 같은 기능들을 TextStyle 클래스로 인스턴스화하여 포함할 수 있으며,
	사용한 스타일을 다른 TextRenderer 에도 쉽게 적용할 수 있다.
	*기능들*
	✓ 글 내용
	✓ 폰트
	✓ 색상
	✓ 자간
	✓ 띄어쓰기
	✓ 공간
	✓ 문장 정렬 방향(왼쪽, 오른쪽)
	✓ 글자 꾸미기(Bold, Italic, Strikeout, Underline)
	*/
	class TextUIRenderer final : public AUIRenderer
	{
	private:
		TextStyle m_textStyle;
		string m_renderText;
		vector<wstring> m_renderTexts;
		unique_ptr<SpriteFont> m_spriteFont;
		unique_ptr<SpriteBatch> m_spriteBatch;
	public:
		TextUIRenderer();
	protected:
		virtual ~TextUIRenderer() = default;
	public:
		VOID SetText(string _renderText);
		VOID SetFont(string _fontPath);
		inline VOID SetStyle(TextStyle _textStyle);
		virtual VOID SetColor(float _r, float _g, float _b, float _a = 1.0f) final;
		virtual VOID SetColor(XMVECTOR _color) final;
		inline VOID SetLetterSpace(int _spacingAmount)
		{
			m_textStyle.m_letterSpace = Mathf::Clamp(_spacingAmount, 0, _spacingAmount);
		}
		inline VOID SetWordSpace(int _spacingAmount)
		{
			m_textStyle.m_wordSpace = Mathf::Clamp(_spacingAmount, 0, _spacingAmount);
		}
		VOID SetLineHeight(float _lineHeight);
		VOID SetTextDirection(TEXT_DIRECTION _direction)
		{
			m_textStyle.m_direction = _direction;
		}
		VOID SetTextDecoration(TEXT_DECORATION _textDecoration);

		string GetText();
		inline string GetFontName()
		{
			return m_textStyle.m_fontName;
		}
		inline TextStyle GetTextStyle()
		{
			return m_textStyle;
		}
		virtual XMVECTOR GetColor() final;
		inline int GetLetterSpace()
		{
			return m_textStyle.m_letterSpace;
		}
		inline int GetWordSpace()
		{
			return m_textStyle.m_wordSpace;
		}
		float GetLineHegiht();
		inline TEXT_DIRECTION GetTextDirection()
		{
			return m_textStyle.m_direction;
		}
		inline TEXT_DECORATION GetTextDecoration()
		{
			return m_textStyle.m_decoration;
		}
	private:
		virtual VOID RenderUI() final;
	private:
		virtual VOID Awake() final;
		virtual VOID Start() final;
		virtual VOID Update() final;
		virtual VOID FixedUpdate() final;
		virtual VOID Render() final;
		virtual VOID Release() final;
	};
}
#endif //CHIPSSYSTEM_COMPONENETS_UICOMPONENETS_TEXTUIERENDERER_H