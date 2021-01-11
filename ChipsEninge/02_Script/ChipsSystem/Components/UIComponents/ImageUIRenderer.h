#ifndef CHIPSSYSTEM_COMPONENETS_UICOMPONENETS_IMAGEUIRENDERER_H
#define CHIPSSYSTEM_COMPONENETS_UICOMPONENETS_IMAGEUIRENDERER_H
#include "ChipsSystem/Components/UIComponents/AUIRenderer.h"

namespace ChipsEngine
{
	/*
	Image 를 스크린 공간에 렌더링하는 컴포넌트이다. 
	LoadTexture 함수를 사용하여, 원하는 Image 를 로드할 수 있다.
	*/
	class ImageUIRenderer final : public AUIRenderer
	{
	private:
		XMFLOAT2 m_imageSize;
		unique_ptr<SpriteBatch> m_spriteBatch;
		ID3D11ShaderResourceView* m_diffuseSRV;
	public:
		ImageUIRenderer();
	protected:
		virtual ~ImageUIRenderer() = default;
	public:
		VOID LoadTexture(const string _fileName);
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
#endif //CHIPSSYSTEM_COMPONENETS_UICOMPONENETS_IMAGEUIRENDERER_H