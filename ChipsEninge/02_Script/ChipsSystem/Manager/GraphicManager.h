#ifndef CHIPSSYSTEM_MANAGER_GRAPHICMANAGER_H
#define CHIPSSYSTEM_MANAGER_GRAPHICMANAGER_H
#include "ChipsSystem/Etc/Singleton.h"
#include "ChipsSystem/Global/Global.h"
#include "DirectX/Effects/LightHelper.h"

namespace ChipsEngine
{
	/*
	전체화면, FPS 제한 설정, 화면 해상도, 다양한 PostProcessing 이 구현되어 있다.
	구현되어 있는 PostProcessing 목록은 다음과 같다.
	*PostProcessing 기능*
	✓ RayMarching
	✓ ScreenSpaceAmbientOcclusion
	✓ Dark
	✓ DepthOfField
	✓ MotionBlur
	✓ GaussianBlur
	✓ BoxBlur
	✓ VerticalBlur
	✓ HorizontalBlur
	✓ Rain
	✓ Blood
	✓ ChromaticAberration
	✓ Bloom
	✓ Vignetting
	✓ Gamma
	✓ Contrast
	✓ Bright
	✓ Saturate
	✓ SmoothStep
	✓ Tint
	✓ Sepia
	✓ GrayScale
	✓ Inverse
	✓ LUT (2D)
	✓ Tonemap-ACES
	✓ Tonemap-Unreal
	✓ Tonemap-Reinhard
	✓ OldGameStyle
	✓ Edge
	✓ Embossed
	✓ Flicker
	✓ Cartoon
	✓ Mosaic
	✓ VerticalLines
	✓ HorizontalLines
	✓ Noise
	✓ CinematicLine
	✓ FaleIn
	✓ FadeOut
	*/
	class GraphicManager final : public Singletone<GraphicManager>
	{
	private:
#pragma region FPS
		int m_limitFps;
		int m_currentFps;
		int m_fpsCount;
		__int64 m_oldTime;
		__int64 m_curTime;
		float m_deltaTime;
		float m_limitDeltaTime;
		float m_timeElapsed;
		float m_totalTime;
		double m_secondsPerCount;
#pragma endregion

#pragma region ScreenMode, AA
		//ScreenMode
		bool m_isFullScreenMode;
		float m_width; 
		float m_height;
		//MSAA
		bool m_isUseMSAA;
		UINT m_msaaQuality;
		//SSAA
		bool m_isUseSSAA;
		float m_ssaaAmount;
		D3D11_VIEWPORT m_ssaaViewPort;
#pragma endregion

#pragma region RTV, SRV, DSV
		ID3D11RenderTargetView*  m_offscreenRenderTargetView;
		ID3D11ShaderResourceView* m_offscreenShdaerResourceView;
		vector<ID3D11ShaderResourceView*> m_preOffscreenShdaerResourceView;
		ID3D11DepthStencilView*  m_offscreenDepthStencilView;
		ID3D11ShaderResourceView* m_offscreenShdaerResourceViewAboutDepth;

		float m_dowsampleAmount;
		D3D11_VIEWPORT m_downSamplingViewPort;
		ID3D11RenderTargetView*  m_downSampledRenderTargetView;
		ID3D11ShaderResourceView* m_downSampledShdaerResourceView;
		ID3D11DepthStencilView*  m_downSampledDepthStencilView;

		ID3D11RenderTargetView*   m_ssaoRenderTargetView;
		ID3D11ShaderResourceView* m_ssaoShdaerResourceView;
		ID3D11DepthStencilView*   m_ssaoDepthStencilView;

		ID3D11RenderTargetView*   m_rayMarchingRenderTargetView;
		ID3D11ShaderResourceView* m_rayMarchingShdaerResourceView;
		ID3D11DepthStencilView*   m_rayMarchingDepthStencilView;
#pragma endregion

#pragma region PostProcessing
		bool m_isUsePostProcessing;

#pragma region Raymarching
		bool m_isUseRaymarching;
		UINT m_indexCount;
		Material m_material;
		ID3D11Buffer* m_vertexBuffer;
		ID3D11Buffer* m_indexBuffer;
		ID3DX11EffectTechnique* m_tech;
#pragma endregion

#pragma region Ambient Occlusion & Dark
		//SSAO
		bool m_isSsao;
		float m_ssaoRadius;
		float m_ssaoBias;
		float m_ssaoScale;
		float m_ssaoAmount;
		//Dark
		bool m_isDark;	 
		float m_darkAmount;	 
#pragma endregion

#pragma region DepthOfField
		bool m_isDepthOfField; 
		float m_depthOfFieldAmount;
		float m_depthOfFieldFocalDepth;
		float m_depthOfFieldFallOffStart;
		float m_depthOfFieldFallOffEnd;
#pragma endregion

#pragma region Blur
		//MotionBlur
		bool m_isMotionBlur;
		float m_motionBlurAmount;
		float m_motionBlurReferenceDistance;
		//GaussianBlur
		bool m_isGaussianBlur;
		float m_gaussianBlurAmount;
		//BoxBlur
		bool m_isBoxBlur;
		int m_boxBlurAmount;
		//VerticalBlur
		bool m_isVerticalBlur;
		int m_verticalBlurAmount;
		//HorizontalBlur
		bool m_isHorizontalBlur;
		int m_horizontalBlurAmount;
#pragma endregion

#pragma region Lens Distortion
		//Rain
		bool m_isRain;
		float m_rainSpeed;
		float m_rainAmount;
		//Blood
		bool m_isBlood;
		float m_bloodSpeed;
		float m_bloodAmount;
#pragma endregion

#pragma region ChromaticAberration
		bool m_isChromaticAberration;
		float m_chromaticAberrationAmount;
#pragma endregion

#pragma region Bloom
		bool m_isBloom ;
		bool m_isOverBloom;
		float m_bloomAmount;
#pragma endregion

#pragma region Vignette
		bool m_isVigneting;
		float m_vignetingAmount;
#pragma endregion

#pragma region Color Grading
		//Gamma
		bool m_isGamma;
		float m_gammaAmount;
		//Contrast
		bool m_isContrast;
		float m_contrastAmount;
		//Bright
		bool m_isBright;
		float m_brightAmount;
		//Saturate
		bool m_isSaturate;
		float m_saturateAmount;
		//SmoothStep
		bool m_isSmoothStep;
		float m_smoothStepMin;
		float m_smoothStepMax;
		//Tint
		bool m_isTint;
		float m_tintColor[3];
		//Sepia
		bool m_isSepia;
		//GrayScale
		bool m_isGrayScale;
		//Inverse
		bool m_isInverse;
		//Lut
		bool m_isLut;
		float m_lutAmount;
		ID3D11ShaderResourceView* m_lutShdaerResourceView;
		//Tonemap
		bool m_isTonemapACES;
		bool m_isTonemapUnreal;
		float m_tonemapUnrealExposure;
		bool m_isTonemapReinhard;
#pragma endregion

#pragma region Film Effect
		//OldGame
		bool m_isOldGame;
		float m_oldGameMosaicAmount;
		float m_oldGameColorLevel;
		float m_oldGameMinColor[3];
		float m_oldGameMaxColor[3];
		//Edge
		bool m_isEdge;
		int m_edgeIndex;
		//Embossed
		bool m_isEmbossed;
		//Flicker
		bool m_isFlicker;
		float m_flickerAmount;
		float m_flickerFrequence;
		//Cartoon
		bool m_isCartoon;
		//Mosaic
		bool m_isMosaic;
		float m_mosaicAmount;
		//VerticalLines
		bool m_isVerticalLines;
		float m_verticalLinesAmount;
		//HorizontalLines
		bool m_isHorizontalLines;
		float m_horizontalLinesAmount;
		//Nosie
		bool m_isNoise;
		float m_noiseFiness;
		float m_noiseBlend;
		ID3D11ShaderResourceView* m_grayNoiseShdaerResourceView;
		//CinematicLine
		bool m_isCinematicLine;
		float m_cinematicLineAmount;
#pragma endregion

#pragma region Fand In, Out
		//FadeIn
		bool m_isFadeIn;
		float m_fadeInSpeed;
		//FadeOut
		bool m_isFadeOut;
		float m_fadeOutSpeed;
#pragma endregion

#pragma endregion
	public:
		GraphicManager();
		~GraphicManager();
	public:
#pragma region FPS
		bool CalculateFPS();
		inline int GetLimitFps()
		{
			return m_limitFps;
		}
		inline int GetCurrentFps()
		{
			return m_currentFps;
		}
		VOID SetLimitFps(int _limitFps);
#pragma endregion

#pragma region ScreenMode, AA
		inline float GetWidth()
		{
			return m_width;
		}
		inline float GetHeight()
		{
			return m_height;
		}
		inline bool GetIsFullScreen()
		{
			return m_isFullScreenMode;
		}
		inline bool GetIsMSAA()
		{
			return m_isUseMSAA;
		}
		VOID SetMSAA(bool _active);
		VOID SetSSAA(bool _active, int _amount = 2);
		VOID SetFullScreen(bool _isFullScreen);
		VOID SetScreenResolution(float _width, float _height);
#pragma endregion

#pragma region PostProcessing
		inline VOID SetPostProcessing(bool _active)
		{
			m_isUsePostProcessing = _active;
		}
		inline bool GetPostProcessing()
		{
			return m_isUsePostProcessing;
		}

#pragma region Raymarching
		inline VOID SetRaymarching(bool _active)
		{
			m_isUseRaymarching = _active;
		}
#pragma endregion

#pragma region Ambient Occlusion & Dark
		inline VOID SetSSAO(bool _active, float _radius = 1.0f, float _bias = 0.3f, float _scale = 1.0f, float _amount = 1.0f)
		{
			m_isSsao = _active;
			m_ssaoRadius = _radius;
			m_ssaoBias = _bias;
			m_ssaoScale = _scale;
			m_ssaoAmount = _amount;
		}
		inline VOID SetDark(bool _active, float _amount = 2.0f)
		{
			m_isDark = _active;
			m_darkAmount = _amount;
		}
#pragma endregion

#pragma region DepthOfField
		inline VOID SetDepthOfField(bool _active, float _amount = 5.0f, float _focalDepth = 1.0f, float _fallOffStart = 7.0f, float _fallOffEnd = 30.0f)
		{
			m_isDepthOfField = _active;
			m_depthOfFieldAmount = _amount;
			m_depthOfFieldFocalDepth = _focalDepth;
			m_depthOfFieldFallOffStart = _fallOffStart;
			m_depthOfFieldFallOffEnd = _fallOffEnd;
		}
#pragma endregion

#pragma region Blur
		inline VOID SetMotionBlur(bool _active, float _amount = 0.5f, float _referenceDistance = 100.0f)
		{
			m_isMotionBlur = _active;
			m_motionBlurAmount = _amount;
			m_motionBlurReferenceDistance = _referenceDistance;
		}
		inline VOID SetGaussianBlur(bool _active, float _amount = 5.0f)
		{
			m_isGaussianBlur = _active;
			m_gaussianBlurAmount = _amount;
		}
		inline VOID SetBoxBlur(bool _active, int _amount = 5)
		{
			m_isBoxBlur = _active;
			m_boxBlurAmount = _amount;
		}
		inline VOID SetVerticalBlur(bool _active, int _amount = 5)
		{
			m_isVerticalBlur = _active;
			m_verticalBlurAmount = _amount;
		}
		inline VOID SetHorizontalBlur(bool _active, int _amount = 5)
		{
			m_isHorizontalBlur = _active;
			m_horizontalBlurAmount = _amount;
		}
#pragma endregion

#pragma region Lens Distortion
		inline VOID SetRain(bool _active, float _speed = 0.0125f, float _amount = 0.02f)
		{
			m_isRain = _active;
			m_rainSpeed = _speed;
			m_rainAmount = _amount;
		}
		inline VOID SetBlood(bool _active, float _speed = 0.006f, float _amount = 0.02f)
		{
			m_isBlood = _active;
			m_bloodSpeed = _speed;
			m_bloodAmount = _amount;
		}
#pragma endregion

#pragma region ChromaticAberration
		inline VOID SetChromaticAberration(bool _active, float _amount = 0.003f)
		{
			m_isChromaticAberration = _active;
			m_chromaticAberrationAmount = _amount;
		}
#pragma endregion

#pragma region Bloom
		//Over
		inline VOID SetBloom(bool _active, bool _over = true, float _amount = 1.0f)
		{
			m_isBloom = _active;
			m_isOverBloom = _over;
			m_bloomAmount = _amount;
		}
#pragma endregion

#pragma region Vignette
		inline VOID SetVigneting(bool _active, float _amount = 0.45f)
		{
			m_isVigneting = _active;
			m_vignetingAmount = _amount;
		}
#pragma endregion

#pragma region Color Grading
		inline VOID SetGamma(bool _active, float _amount = 1.2f)
		{
			m_isGamma = _active;
			m_gammaAmount = _amount;
		}
		inline VOID SetContrast(bool _active, float _amount = 1.2f)
		{
			m_isContrast = _active;
			m_contrastAmount = _amount;
		}
		inline VOID SetBright(bool _active, float _amount = 0.5f)
		{
			m_isBright = _active;
			m_brightAmount = _amount;
		}
		inline VOID SetSaturate(bool _active, float _amount = 2.0f)
		{
			m_isSaturate = _active;
			m_saturateAmount = _amount;
		}
		inline VOID SetSmoothStep(bool _active, float _min = 0.0f, float _max = 1.0f)
		{
			m_isSmoothStep = _active;
			m_smoothStepMin = _min;
			m_smoothStepMax = _max;
		}
		inline VOID SetTint(bool _active, XMFLOAT3 _tintColor = XMFLOAT3(0.95f, 0.95f, 1.05f))
		{
			m_isTint = _active;
			m_tintColor[0] = _tintColor.x;
			m_tintColor[1] = _tintColor.y;
			m_tintColor[2] = _tintColor.z;
		}
		inline VOID SetSepia(bool _active)
		{
			m_isSepia = _active;
		}
		inline VOID SetGrayScale(bool _active)
		{
			m_isGrayScale = _active;
		}
		inline VOID SetInverse(bool _active)
		{
			m_isInverse = _active;
		}
		inline VOID SetLUT(bool _active, float _amount = 1.0f)
		{
			m_isLut = _active;
			m_lutAmount = _amount;
		}
		VOID LoadLutTexture(string _fileName, float _lutSize = 16, bool _isInverse = false);
		inline VOID SetTonemapACES(bool _active)
		{
			m_isTonemapACES = _active;
		}
		inline VOID SetTonemapUnreal(bool _active, float _exposure = 1.0f)
		{
			m_isTonemapUnreal = _active;
			m_tonemapUnrealExposure = _exposure;
		}
		inline VOID SetTonemapReinhard(bool _active)
		{
			m_isTonemapReinhard = _active;
		}
#pragma endregion

#pragma region Film Effect
		inline VOID SetOldGame(bool _active, float _mosaicAmount = 400.0f, float _colorLevel = 20.0f, 
							XMFLOAT3 _minColor = XMFLOAT3(0.063f, 0.247f, 0.063f), XMFLOAT3 _maxColor = XMFLOAT3(0.612f, 0.715f, 0.086f))
		{
			m_isOldGame = _active;
			m_oldGameMosaicAmount = _mosaicAmount;
			m_oldGameColorLevel = _colorLevel;
			m_oldGameMinColor[0] = _minColor.x;
			m_oldGameMinColor[1] = _minColor.y;
			m_oldGameMinColor[2] = _minColor.z;

			m_oldGameMaxColor[0] = _maxColor.x;
			m_oldGameMaxColor[1] = _maxColor.y;
			m_oldGameMaxColor[2] = _maxColor.z;			
		}
		inline VOID SetEdge(bool _active, int _type = 0)
		{
			m_isEdge = _active;
			m_edgeIndex = _type;
		}
		inline VOID SetEmbossed(bool _active)
		{
			m_isEmbossed = _active;
		}
		inline VOID SetFlicker(bool _active, float _amount = 0.01f, float _frequence = 100.0f)
		{
			m_isFlicker = _active;
			m_flickerAmount = _amount;
			m_flickerFrequence = _frequence;
		}
		inline VOID SetCartoon(bool _active)
		{
			m_isCartoon = _active;
		}
		inline VOID SetMosaic(bool _active, float _amount = 100.0f)
		{
			m_isMosaic = _active;
			m_mosaicAmount = _amount;
		}
		inline VOID SetVerticalLines(bool _active, float _amount = 1000.0f)
		{
			m_isVerticalLines = _active;
			m_verticalLinesAmount = _amount;
		}
		inline VOID SetHorizontalLines(bool _active, float _amount = 1000.0f)
		{
			m_isHorizontalLines = _active;
			m_horizontalLinesAmount = _amount;
		}
		inline VOID SetNoise(bool _active, float _finess = 3.0f, float _blend = 0.5f)
		{
			m_isNoise = _active;
			m_noiseFiness = _finess;
			m_noiseBlend = _blend;
		}
		inline VOID SetCinematicLine(bool _active, float _amount = 0.12f)
		{
			m_isCinematicLine = _active;
			m_cinematicLineAmount = _amount;
		}

#pragma endregion

#pragma region Fand In, Out
		VOID SetFadeIn(bool _active, float _speed = 0.5f);
		VOID SetFadeOut(bool _active, float _speed = 0.5f);
#pragma endregion

#pragma endregion
	public:
		VOID Awake();
		VOID Render();
	public:
		VOID PreSettingToPostProcessing();
	private:
		VOID ResetD3D();
		VOID ResetOffscreen();
		VOID InitPostprocessingTexture();
		VOID InitFullScreenGemometryBuffer();
		VOID RenderDownSampling();
		VOID ScreenSpaceAmbientOcclusion();
		VOID RayMarching();
		VOID RenderPostProcessing();
	};
}
#endif//CHIPSSYSTEM_MANAGER_GRAPHICMANAGER_H