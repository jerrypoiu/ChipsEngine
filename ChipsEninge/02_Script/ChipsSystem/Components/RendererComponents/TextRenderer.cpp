#include "ChipsSystem/BasicFrame/GameObject.h"
#include "ChipsSystem/Manager/GraphicManager.h"
#include "ChipsSystem/Components/RendererComponents/TextRenderer.h"
#include "ChipsSystem/Components/BaiscComponents/Transform.h"
#include "ChipsSystem/Manager/TextManager.h"
#include "ChipsSystem/Manager/GraphicManager.h"
#include "ChipsSystem/Camera/Camera.h"
#include "ChipsSystem/Global/Global.h"
#include "ChipsSystem/Etc/Mathf.h"
#include "ChipsSystem/Etc/StringLib.h"

namespace ChipsEngine
{
	TextStyle::TextStyle() : 
		m_wordSpace(1), m_letterSpace(0), m_lineHeight(5.0f), 
		m_fontName("arial"), m_direction(TEXT_DIRECTION::LTR), m_decoration(TEXT_DECORATION::DEFAULT),
		m_lineHeightStandard(15.0f)
	{
		m_colors.m128_f32[0] = 1.0f;
		m_colors.m128_f32[1] = 1.0f;
		m_colors.m128_f32[2] = 1.0f;
		m_colors.m128_f32[3] = 1.0f;
	}

	TextRenderer::TextRenderer() : AComponent("TextRenderer"), m_textStyle()
	{
	}

	VOID TextRenderer::SetFont(string _font)
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

	VOID TextRenderer::SetText(string _renderText)
	{
		m_renderText = _renderText;
	}

	VOID TextRenderer::SetStyle(TextStyle _textStyle)
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

	string TextRenderer::GetText()
	{
		return m_renderText;
	}

	VOID TextRenderer::SetTextDecoration(TEXT_DECORATION _textDecoration)
	{
		m_textStyle.m_decoration = _textDecoration;
		SetFont(m_textStyle.m_fontName);
	}

	VOID TextRenderer::SetLineHeight(float _lineHeight)
	{
		float temp = m_textStyle.m_lineHeightStandard * _lineHeight * GetGameObject()->GetTransform()->GetWorldScale().y;
		m_textStyle.m_lineHeight = Mathf::Clamp(temp, 0.0f, temp);
	}

	float TextRenderer::GetLineHegiht()
	{
		return m_textStyle.m_lineHeight / m_textStyle.m_lineHeightStandard / GetGameObject()->GetTransform()->GetWorldScale().y;
	}

	bool TextRenderer::WorldToScreen(XMVECTOR _vector, XMFLOAT2* _outFloat2)
	{
		XMMATRIX world = XMMatrixIdentity();
		XMMATRIX projection = Camera::GetInstance()->Proj();
		XMMATRIX view = Camera::GetInstance()->View();

		float height = GraphicManager::GetInstance()->GetHeight();
		float width = GraphicManager::GetInstance()->GetWidth();

		XMVECTOR projectedVector = XMVector3Project(_vector, 0, 0, width, height, 0, 1, projection, view, world);

		XMFLOAT3 outFloat3;
		XMStoreFloat3(&outFloat3, projectedVector);

		if (outFloat3.z < 1.0f)
		{
			_outFloat2->x = outFloat3.x; _outFloat2->y = outFloat3.y;
			return true;
		}

		return false;
	}

	VOID TextRenderer::RenderText()
	{
		int i = 0;
		for (auto& renderText : m_renderTexts)
		{
			m_spriteBatch->Begin();
			XMFLOAT4 worldFloat4 = XMFLOAT4(
				GetGameObject()->GetTransform()->GetWorldPosition().x,
				GetGameObject()->GetTransform()->GetWorldPosition().y,
				GetGameObject()->GetTransform()->GetWorldPosition().z,
				1.0f);

			XMVECTOR worldVector = XMLoadFloat4(&worldFloat4);
			XMVECTOR originVector = m_spriteFont->MeasureString(renderText.c_str());
			XMFLOAT2 originFloat2 = XMFLOAT2(originVector.m128_f32[0] * 0.5f, originVector.m128_f32[1] * 0.5f);
			XMFLOAT2 scale = XMFLOAT2(GetGameObject()->GetTransform()->GetWorldScale().x, GetGameObject()->GetTransform()->GetWorldScale().y);

			XMFLOAT2 position = XMFLOAT2();
			WorldToScreen(worldVector, &position);
			position.y += m_textStyle.m_lineHeight * i++;
			m_spriteFont->DrawString(m_spriteBatch.get(), renderText.c_str(), position, GetColor(), 0, originFloat2, scale);
			m_spriteBatch->End();
		}

		Global::g_d3dImmediateContext->OMSetDepthStencilState(Global::g_depthStencilState, 1);
	}

	VOID TextRenderer::Awake()
	{
		SetText("Hello World");
		SetStyle(TextStyle());
		m_spriteBatch.reset(new SpriteBatch(Global::g_d3dImmediateContext));
		TextManager::GetInstance()->AddTextRenderFunc(bind(&TextRenderer::RenderText, this));
	}

	VOID TextRenderer::Start()
	{
	}

	VOID TextRenderer::Update()
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

	VOID TextRenderer::FixedUpdate()
	{
	}

	VOID TextRenderer::Render()
	{
	}

	VOID TextRenderer::Release()
	{
		m_spriteBatch.release();
		m_spriteFont.release();
	}
}