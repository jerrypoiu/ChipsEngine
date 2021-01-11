#include "ChipsSystem/BasicFrame/GameObject.h"
#include "ChipsSystem/Components/BaiscComponents/Transform.h"
#include "ChipsSystem/Components/UIComponents/TextUIRenderer.h"
#include "ChipsSystem/Manager/GraphicManager.h"
#include "ChipsSystem/Manager/UIManager.h"
#include "ChipsSystem/Global/Global.h"
#include "ChipsSystem/Etc/StringLib.h"
#include "ChipsSystem/Etc/Debug.h"

namespace ChipsEngine
{
	TextUIRenderer::TextUIRenderer() : AUIRenderer("TextUIRenderer"), m_textStyle()
	{
	}

	VOID TextUIRenderer::SetFont(string _font)
	{
		m_textStyle.m_fontName = _font;
		switch (m_textStyle.m_decoration)
		{
		case TEXT_DECORATION::DEFAULT:
			_font = "01_Asset/Font/" + _font + ".spritefont";
			break;
		case TEXT_DECORATION::BOLD:
			_font = "01_Asset/Font/" + _font + "Bold" + ".spritefont";
			break;
		case TEXT_DECORATION::ITALIC:
			_font = "01_Asset/Font/" + _font + "Italic" + ".spritefont";
			break;
		case TEXT_DECORATION::STRIKEOUT:
			_font = "01_Asset/Font/" + _font + "Strikeout" + ".spritefont";
			break;
		case TEXT_DECORATION::UNDERLINE:
			_font = "01_Asset/Font/" + _font + "Underline" + ".spritefont";
			break;
		}
		wstring path(_font.begin(), _font.end());
		m_spriteFont.reset(new SpriteFont(Global::g_d3dDevice, path.c_str()));
	}

	VOID TextUIRenderer::SetText(string _renderText)
	{
		m_renderText = _renderText;
	}

	VOID TextUIRenderer::SetStyle(TextStyle _textStyle)
	{
		m_textStyle = _textStyle;
		SetFont(m_textStyle.m_fontName);
		SetColor(m_textStyle.m_colors);
		SetTextDirection(m_textStyle.m_direction);
		SetTextDecoration(m_textStyle.m_decoration);
		SetWordSpace(m_textStyle.m_wordSpace);
		SetLetterSpace(m_textStyle.m_letterSpace);
		SetLineHeight(m_textStyle.m_lineHeight);
	}

	string TextUIRenderer::GetText()
	{
		return m_renderText;
	}

	VOID TextUIRenderer::SetColor(float _r, float _g, float _b, float _a)
	{
		XMVECTOR color;
		color.m128_f32[0] = _r;
		color.m128_f32[1] = _g;
		color.m128_f32[2] = _b;
		color.m128_f32[3] = _a;
		m_textStyle.m_colors = color;
	}

	VOID TextUIRenderer::SetColor(XMVECTOR _color)
	{
		m_textStyle.m_colors = _color;
	}

	XMVECTOR TextUIRenderer::GetColor()
	{
		return m_textStyle.m_colors;
	}

	VOID TextUIRenderer::SetLineHeight(float _lineHeight)
	{
		float temp = m_textStyle.m_lineHeightStandard * _lineHeight * GetGameObject()->GetTransform()->GetWorldScale().y;
		m_textStyle.m_lineHeight = Mathf::Clamp(temp, 0.0f, temp);
	}

	float TextUIRenderer::GetLineHegiht()
	{
		return m_textStyle.m_lineHeight / m_textStyle.m_lineHeightStandard / GetGameObject()->GetTransform()->GetWorldScale().y;
	}

	VOID TextUIRenderer::SetTextDecoration(TEXT_DECORATION _textDecoration)
	{
		m_textStyle.m_decoration = _textDecoration;
		SetFont(m_textStyle.m_fontName);
	}

	VOID TextUIRenderer::RenderUI()
	{
		int i = 0;
		float xSizeCorrection = 0.0f;
		float xScreenProportion = 1.0f;
		float yScreenProportion = 1.0f;
		RECT rect{0, 0, 0, 0};

		RECT clientRect;
		GetClientRect(Global::g_hwnd, &clientRect);
		XMFLOAT2 offset{ GraphicManager::GetInstance()->GetWidth() - clientRect.right, GraphicManager::GetInstance()->GetHeight() - clientRect.bottom };
		
		if (GraphicManager::GetInstance()->GetIsFullScreen())
		{
			xScreenProportion = clientRect.right / GraphicManager::GetInstance()->GetWidth();
			yScreenProportion = clientRect.bottom / GraphicManager::GetInstance()->GetHeight();
		}

		for (auto& renderText : m_renderTexts)
		{
			m_spriteBatch->Begin();

			XMVECTOR fontSizeVector = m_spriteFont->MeasureString(renderText.c_str());
			
			if (renderText.length() != 0)
			{
				xSizeCorrection = (float)(fontSizeVector.m128_f32[1] / renderText.length()) * 0.5f ;
			}

			float posX = GetGameObject()->GetTransform()->GetWorldPosition().x  + GraphicManager::GetInstance()->GetWidth() * GetPiviot().x;
			float posY = -GetGameObject()->GetTransform()->GetWorldPosition().y + GraphicManager::GetInstance()->GetHeight() * GetPiviot().y ;
			float rotZ = GetGameObject()->GetTransform()->GetWorldRotation().z;

			XMFLOAT2 position = XMFLOAT2(posX, posY);
			XMFLOAT2 anchorPoint{ fontSizeVector.m128_f32[0] * GetAnchorPoint().x,  fontSizeVector.m128_f32[1] * GetAnchorPoint().y };
			XMFLOAT2 scale = XMFLOAT2(GetGameObject()->GetTransform()->GetWorldScale().x * 0.5f, GetGameObject()->GetTransform()->GetWorldScale().y * 0.5f);
				
			if (UIManager::GetInstance()->GetIsConstantSize())
			{
				scale.x /= xScreenProportion;
				scale.y /= yScreenProportion;
			}

			position.x -= xSizeCorrection * GetPiviot().x;
			position.y += m_textStyle.m_lineHeight * i++;
			rect.left   = (LONG)(posX - (offset.x * GetPiviot().x) - (anchorPoint.x * scale.x * xScreenProportion));
			rect.top    = (LONG)(posY - (offset.y * GetPiviot().y) - (anchorPoint.y * scale.y * yScreenProportion));
			rect.right  = (LONG)(rect.left + xSizeCorrection + fontSizeVector.m128_f32[0] * scale.x * xScreenProportion);
			rect.bottom = (LONG)(rect.top + fontSizeVector.m128_f32[1] * scale.y * yScreenProportion);

			//크기 체크
			if (0 < i)
			{
				float rectTop = (position.y - (offset.y * GetPiviot().y) - (anchorPoint.y * scale.y * yScreenProportion));
				rect.bottom = (LONG)(rectTop + fontSizeVector.m128_f32[1] * scale.y * yScreenProportion);
			}

			SetRect(rect);

			m_spriteFont->DrawString(m_spriteBatch.get(), renderText.c_str(), position, GetColor(), rotZ, anchorPoint, scale);
			m_spriteBatch->End();
		}

		Global::g_d3dImmediateContext->OMSetDepthStencilState(Global::g_depthStencilState, 1);
	}

	VOID TextUIRenderer::Awake()
	{
		SetAnchorPoint(0.5f, 0.5f);
		SetPivot(0.5f, 0.5f);
		SetText("Hello World");
		SetStyle(TextStyle());

		m_spriteBatch.reset(new SpriteBatch(Global::g_d3dImmediateContext));
		UIManager::GetInstance()->AddUIRenderer(UIRenderComponent(this, bind(&TextUIRenderer::RenderUI, this)));
	}

	VOID TextUIRenderer::Start()
	{
	}

	VOID TextUIRenderer::Update()
	{
		m_renderTexts.clear();
		string temp = "";
		string fullText = "";

		switch (m_textStyle.m_direction)
		{
		case TEXT_DIRECTION::LTR:
			temp = m_renderText;
			break;

		case TEXT_DIRECTION::RTL:
			for (int i = m_renderText.length() - 1; i >= 0; i--)
			{
				temp += m_renderText[i];
			}

			break;
		}

		vector<string> renderTexts = StringLib::Split(temp, ' ');
		temp = "";
		for (auto& renderText : renderTexts)
		{
			string space;
			for (int i = 0; i < m_textStyle.m_wordSpace; i++)
			{
				space += " ";
			}

			temp += renderText + space;
		}

		for (int i = 0; i < (int)temp.length(); i++)
		{
			string space;
			for (int j = 0; j < m_textStyle.m_letterSpace; j++)
			{
				if (temp[i] == '\\')
					break;

				if ((i + 1 < (int)temp.length()) && temp[i] == ' ' && temp[i + 1] == ' ')
					break;

				if ((i + 1 > (int)temp.length()) && temp[i] == ' ' && temp[i - 1] == ' ')
					break;
				space += " ";
			}

			fullText += temp[i] + space;
		}

		renderTexts = StringLib::Split(fullText, '\\');

		for (auto& renderText : renderTexts)
		{
			wstring text = wstring(renderText.begin(), renderText.end());
			m_renderTexts.emplace_back(text);
		}
	}

	VOID TextUIRenderer::FixedUpdate()
	{
	}

	VOID TextUIRenderer::Render()
	{
	}

	VOID TextUIRenderer::Release()
	{
		m_spriteBatch.release();
		m_spriteFont.release();
	}
}