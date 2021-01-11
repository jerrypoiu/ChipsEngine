#ifndef CHIPSSYSTEM_COMPONENETS_RENDERERCOMPONENTS_TEXTREDERER_H
#define CHIPSSYSTEM_COMPONENETS_RENDERERCOMPONENTS_TEXTREDERER_H
#include "ChipsSystem/BasicFrame/AComponent.h"
#include "ChipsSystem/Etc/Mathf.h"

namespace ChipsEngine
{
	enum class TEXT_DIRECTION : char
	{
		LTR, RTL
	};

	enum class TEXT_DECORATION : char
	{
		DEFAULT, BOLD, ITALIC, STRIKEOUT, UNDERLINE
	};

	struct TextStyle final
	{
	public:
		int m_wordSpace;
		int m_letterSpace;
		float m_lineHeight;
		float m_lineHeightStandard;
		string m_fontName;
		XMVECTOR m_colors;
		TEXT_DIRECTION m_direction;
		TEXT_DECORATION m_decoration;
	public:
		TextStyle();
		~TextStyle() = default;
	public:
		inline VOID SetTextColor(float _r, float _g, float _b, float _a = 1.0f)
		{
			XMVECTOR color;
			color.m128_f32[0] = _r;
			color.m128_f32[1] = _g;
			color.m128_f32[2] = _b;
			color.m128_f32[3] = _a;
			m_colors = color;
		}
	};

	/*
	3D Text 를 렌더링 하는 컴포넌트 이다.
	다음의 기능들을 제공한다.
	해당 기능들은 TextStyle 클래스로 인스턴스화하여 포함할 수 있으며,
	사용한 스타일을 다른 TextRenderer 에도 쉽게 적용할 수 있다.
	*기능들*
	✓글 내용
	✓ 폰트
	✓ 색상
	✓ 자간
	✓ 띄어쓰기 공간
	✓ 문장 정렬 방향(왼쪽, 오른쪽)
	✓ 글자 꾸미기(Bold, Italic, Strikeout, Underline)
	*/
	class TextRenderer final : public AComponent
	{
	private:
		TextStyle m_textStyle;
		string m_renderText;
		vector<wstring> m_renderTexts;
		unique_ptr<SpriteFont> m_spriteFont;
		unique_ptr<SpriteBatch> m_spriteBatch;
	public:
		TextRenderer();
	protected:
		virtual ~TextRenderer() = default;
	public:
		VOID SetText(string _renderText);
		VOID SetFont(string _fontPath);
		inline VOID SetStyle(TextStyle _textStyle);
		inline VOID SetColor(float _r, float _g, float _b, float _a = 1.0f)
		{
			XMVECTOR color;
			color.m128_f32[0] = _r;
			color.m128_f32[1] = _g;
			color.m128_f32[2] = _b;
			color.m128_f32[3] = _a;
			m_textStyle.m_colors = color;
		}
		inline VOID SetColor(XMVECTOR _color)
		{
			m_textStyle.m_colors = _color;
		}
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
		inline TextStyle GetStyle()
		{
			return m_textStyle;
		}	
		inline XMVECTOR GetColor()
		{
			return m_textStyle.m_colors;
		}
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
		VOID RenderText();
		bool WorldToScreen(XMVECTOR _vector, XMFLOAT2* _outFloat2);
	private:
		virtual VOID Awake() final;
		virtual VOID Start() final;
		virtual VOID Update() final;
		virtual VOID FixedUpdate() final;
		virtual VOID Render() final;
		virtual VOID Release() final;
	};
}

#endif //CHIPSSYSTEM_COMPONENETS_RENDERERCOMPONENTS_TEXTREDERER_H