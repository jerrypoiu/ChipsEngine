#include "ChipsSystem/BasicFrame/GameObject.h"
#include "ChipsSystem/Components/BaiscComponents/Transform.h"
#include "ChipsSystem/Components/UIComponents/ImageUIRenderer.h"
#include "ChipsSystem/Manager/GraphicManager.h"
#include "ChipsSystem/Manager/UIManager.h"
#include "ChipsSystem/Global/Global.h"
#include "ChipsSystem/Etc/Debug.h"

namespace ChipsEngine
{
	ImageUIRenderer::ImageUIRenderer() : AUIRenderer("ImageUIRenderer")
	{
	}

	VOID ImageUIRenderer::LoadTexture(const string _fileName)
	{
		wstring ws(_fileName.begin(), _fileName.end());
		DirectX::ScratchImage image;
		DirectX::LoadFromDDSFile(ws.c_str(), DirectX::DDS_FLAGS_NONE, nullptr, image);
		m_imageSize.x = (float)image.GetImages()->width;
		m_imageSize.y = (float)image.GetImages()->height;
		DirectX::CreateShaderResourceView(Global::g_d3dDevice, image.GetImages(), image.GetImageCount(), image.GetMetadata(), &m_diffuseSRV);
	}

	VOID ImageUIRenderer::RenderUI()
	{
		m_spriteBatch->Begin();

		RECT clientRect;
		GetClientRect(Global::g_hwnd, &clientRect);
		XMFLOAT2 offset{ GraphicManager::GetInstance()->GetWidth() - clientRect.right, GraphicManager::GetInstance()->GetHeight() - clientRect.bottom };

		float xScreenProportion = 1.0f;
		float yScreenProportion = 1.0f;

		if (GraphicManager::GetInstance()->GetIsFullScreen())
		{
			xScreenProportion = clientRect.right / GraphicManager::GetInstance()->GetWidth();
			yScreenProportion = clientRect.bottom / GraphicManager::GetInstance()->GetHeight();
		}

		float posX = GetGameObject()->GetTransform()->GetWorldPosition().x + GraphicManager::GetInstance()->GetWidth() * GetPiviot().x;
		float posY = -GetGameObject()->GetTransform()->GetWorldPosition().y + GraphicManager::GetInstance()->GetHeight() * GetPiviot().y;
		float rotZ = GetGameObject()->GetTransform()->GetWorldRotation().z;

		XMFLOAT2 position = XMFLOAT2(posX, posY);
		XMFLOAT2 anchorPoint = XMFLOAT2(m_imageSize.x * GetAnchorPoint().x, m_imageSize.y * GetAnchorPoint().y);
		XMFLOAT2 scale = XMFLOAT2(GetGameObject()->GetTransform()->GetWorldScale().x, GetGameObject()->GetTransform()->GetWorldScale().y);
		
		if (UIManager::GetInstance()->GetIsConstantSize())
		{
			scale.x /= xScreenProportion;
			scale.y /= yScreenProportion;
		}

		RECT rect;
		rect.left   = (LONG)(posX - (offset.x * GetPiviot().x) - (anchorPoint.x * scale.x * xScreenProportion));
		rect.top    = (LONG)(posY - (offset.y * GetPiviot().y) - (anchorPoint.y * scale.y * yScreenProportion));
		rect.right  = (LONG)(rect.left + m_imageSize.x * scale.x * xScreenProportion);
		rect.bottom = (LONG)(rect.top + m_imageSize.y * scale.y * yScreenProportion);
		SetRect(rect);

		m_spriteBatch->Draw(m_diffuseSRV, position, nullptr, GetColor(), rotZ, anchorPoint, scale);

		m_spriteBatch->End();
		Global::g_d3dImmediateContext->OMSetDepthStencilState(Global::g_depthStencilState, 1);
	}

	VOID ImageUIRenderer::Awake()
	{
		m_spriteBatch.reset(new SpriteBatch(Global::g_d3dImmediateContext));
		UIManager::GetInstance()->AddUIRenderer(UIRenderComponent(this, bind(&ImageUIRenderer::RenderUI, this)));
		SetAnchorPoint(0.5f, 0.5f);
		SetPivot(0.5f, 0.5f);
		SetColor(White);
	}

	VOID ImageUIRenderer::Start()
	{
	}

	VOID ImageUIRenderer::Update()
	{
	}

	VOID ImageUIRenderer::FixedUpdate()
	{
	}

	VOID ImageUIRenderer::Render()
	{
	}

	VOID ImageUIRenderer::Release()
	{
		m_spriteBatch.release();
	}
}