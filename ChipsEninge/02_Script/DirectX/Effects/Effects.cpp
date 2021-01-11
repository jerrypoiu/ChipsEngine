#include "DirectX/Effects/Effects.h"

#pragma region Effect
Effect::Effect(ID3D11Device* device, const std::wstring& filename)
	: mFX(0)
{
	std::ifstream fin(filename, std::ios::binary);

	fin.seekg(0, std::ios_base::end);
	int size = (int)fin.tellg();
	fin.seekg(0, std::ios_base::beg);
	std::vector<char> compiledShader(size);

	fin.read(&compiledShader[0], size);
	fin.close();

	D3DX11CreateEffectFromMemory(&compiledShader[0], size,0, device, &mFX);
}

Effect::~Effect()
{
	SAFE_RELEASE(mFX);
}
#pragma endregion

#pragma region StandardShaderEffect
StandardShaderEffect::StandardShaderEffect(ID3D11Device* device, const std::wstring& filename)
	: Effect(device, filename)
{
	DebugTech = mFX->GetTechniqueByName("Debug");
	StandardTech = mFX->GetTechniqueByName("Standard");
	CartoonTech = mFX->GetTechniqueByName("Cartoon");
	DepthTech = mFX->GetTechniqueByName("Depth");

	UseDiffuse = mFX->GetVariableByName("gUseDiffuse")->AsScalar();
	UseAlphaClip = mFX->GetVariableByName("gUseAlphaClip")->AsScalar();
	UseNormal = mFX->GetVariableByName("gUseNormal")->AsScalar();
	UseSpecular = mFX->GetVariableByName("gUseSpecular")->AsScalar();
	UseReflect = mFX->GetVariableByName("gUseReflect")->AsScalar();
	UseCartoon = mFX->GetVariableByName("gUseCartoon")->AsScalar();
	UseFog = mFX->GetVariableByName("gUseFog")->AsScalar();
	UseShadow = mFX->GetVariableByName("gUseShadow")->AsScalar();
	UseRimLight = mFX->GetVariableByName("gRimLight")->AsScalar();
	UseSkinning = mFX->GetVariableByName("gSkinning")->AsScalar();

	WorldViewProj = mFX->GetVariableByName("gWorldViewProj")->AsMatrix();
	World = mFX->GetVariableByName("gWorld")->AsMatrix();
	WorldView = mFX->GetVariableByName("gWorldView")->AsMatrix();
	WorldInvTranspose = mFX->GetVariableByName("gWorldInvTranspose")->AsMatrix();
	ShadowTransform = mFX->GetVariableByName("gShadowTransform")->AsMatrix();
	TexTransform = mFX->GetVariableByName("gTexTransform")->AsMatrix();
	BoneTransforms = mFX->GetVariableByName("gBoneTransforms")->AsMatrix();

	NearFar = mFX->GetVariableByName("gNearFar")->AsVector();
	EyePosW = mFX->GetVariableByName("gEyePosW")->AsVector();
	FogColor = mFX->GetVariableByName("gFogColor")->AsVector();
	FogStart = mFX->GetVariableByName("gFogStart")->AsScalar();
	FogRange = mFX->GetVariableByName("gFogRange")->AsScalar();
	DirLights = mFX->GetVariableByName("gDirLights");
	PointLights = mFX->GetVariableByName("gPointLights");
	SpotLights = mFX->GetVariableByName("gSpotLights");
	MatNum = mFX->GetVariableByName("gMatNum")->AsScalar();
	PointLightCount = mFX->GetVariableByName("gPointLightCount")->AsScalar();
	SpotLightCount = mFX->GetVariableByName("gSpotLightCount")->AsScalar();
	Mat = mFX->GetVariableByName("gMaterial");
	DiffuseMap = mFX->GetVariableByName("gDiffuseMap")->AsShaderResource();
	SpecularMap = mFX->GetVariableByName("gSpecularMap")->AsShaderResource();
	CubeMap = mFX->GetVariableByName("gCubeMap")->AsShaderResource();
	NormalMap = mFX->GetVariableByName("gNormalMap")->AsShaderResource();
	ShadowMap = mFX->GetVariableByName("gShadowMap")->AsShaderResource();
}

StandardShaderEffect::~StandardShaderEffect()
{
}
#pragma endregion

#pragma region BuildShadowMapEffect
BuildShadowMapEffect::BuildShadowMapEffect(ID3D11Device* device, const std::wstring& filename)
	: Effect(device, filename)
{
	UseSkinning = mFX->GetVariableByName("gSkinning")->AsScalar();
	BoneTransforms = mFX->GetVariableByName("gBoneTransforms")->AsMatrix();

	BuildShadowMapTech = mFX->GetTechniqueByName("BuildShadowMapTech");

	ViewProj = mFX->GetVariableByName("gViewProj")->AsMatrix();
	WorldViewProj = mFX->GetVariableByName("gWorldViewProj")->AsMatrix();
	World = mFX->GetVariableByName("gWorld")->AsMatrix();
	WorldInvTranspose = mFX->GetVariableByName("gWorldInvTranspose")->AsMatrix();
	TexTransform = mFX->GetVariableByName("gTexTransform")->AsMatrix();
	EyePosW = mFX->GetVariableByName("gEyePosW")->AsVector();
	HeightScale = mFX->GetVariableByName("gHeightScale")->AsScalar();
}

BuildShadowMapEffect::~BuildShadowMapEffect()
{
}
#pragma endregion

#pragma region SkyEffect
SkyEffect::SkyEffect(ID3D11Device* device, const std::wstring& filename)
	: Effect(device, filename)
{
	SkyTech = mFX->GetTechniqueByName("SkyTech");
	WorldViewProj = mFX->GetVariableByName("gWorldViewProj")->AsMatrix();
	WorldView = mFX->GetVariableByName("gWorldView")->AsMatrix();
	NearFar = mFX->GetVariableByName("gNearFar")->AsVector();
	CubeMap = mFX->GetVariableByName("gCubeMap")->AsShaderResource();

}

SkyEffect::~SkyEffect()
{
}
#pragma endregion

#pragma region ParticleEffect
ParticleEffect::ParticleEffect(ID3D11Device* device, const std::wstring& filename)
	: Effect(device, filename)
{
	StreamOutTech = mFX->GetTechniqueByName("StreamOutTech");
	DrawTech = mFX->GetTechniqueByName("DrawTech");
	NearFar = mFX->GetVariableByName("gNearFar")->AsVector();

	View = mFX->GetVariableByName("gView")->AsMatrix();
	ViewProj = mFX->GetVariableByName("gViewProj")->AsMatrix();
	GameTime = mFX->GetVariableByName("gGameTime")->AsScalar();
	TimeStep = mFX->GetVariableByName("gTimeStep")->AsScalar();
	EmitSpread = mFX->GetVariableByName("gEmitSpread")->AsScalar();	
	CreateIntervalTime = mFX->GetVariableByName("gCreateIntervalTime")->AsScalar();
	DeleteTime = mFX->GetVariableByName("gDeleteTime")->AsScalar();
	FadeTime = mFX->GetVariableByName("gFadeTime")->AsScalar();
	RandomizePosition = mFX->GetVariableByName("gRandomizePosition")->AsScalar();
	EyePosW = mFX->GetVariableByName("gEyePosW")->AsVector();
	EmitPosW = mFX->GetVariableByName("gEmitPosW")->AsVector();
	EmitDirW = mFX->GetVariableByName("gEmitDirW")->AsVector();
	EmitColor = mFX->GetVariableByName("gEmitColor")->AsVector();
	EmitSizeW = mFX->GetVariableByName("gEmitSizeW")->AsVector();
	EmitMove = mFX->GetVariableByName("gAccelW")->AsVector();
	TexArray = mFX->GetVariableByName("gTexArray")->AsShaderResource();
	RandomTex = mFX->GetVariableByName("gRandomTex")->AsShaderResource();
}

ParticleEffect::~ParticleEffect()
{
}
#pragma endregion

#pragma region PostProcessingEffect
PostProcessingEffect::PostProcessingEffect(ID3D11Device* device, const std::wstring& filename)
	: Effect(device, filename)
{
	PostProcessingTech = mFX->GetTechniqueByName("PostProcessing");
	DownSamplingTech = mFX->GetTechniqueByName("DownSampling");
	SSAOTech = mFX->GetTechniqueByName("ScreenSpaceAmbientOcclusion");
	RayMarchingTech = mFX->GetTechniqueByName("RayMarching");

	CameraRotMat = mFX->GetVariableByName("gCameraRotMat")->AsMatrix();
	Proj = mFX->GetVariableByName("gProj")->AsMatrix();
	View = mFX->GetVariableByName("gView")->AsMatrix();
	EyePosW = mFX->GetVariableByName("gEyePosW")->AsVector();
	Resolution = mFX->GetVariableByName("gResolution")->AsVector();
	NearFar = mFX->GetVariableByName("gNearFar")->AsVector();
	DirLights = mFX->GetVariableByName("gDirLights");
	PointLights = mFX->GetVariableByName("gPointLights");
	SpotLights = mFX->GetVariableByName("gSpotLights");
	PointLightCount = mFX->GetVariableByName("gPointLightCount")->AsScalar();
	SpotLightCount = mFX->GetVariableByName("gSpotLightCount")->AsScalar();
	LutSize = mFX->GetVariableByName("gLutSize")->AsScalar();
	LutCoordinateInverse = mFX->GetVariableByName("gLutCoordinateInverse")->AsScalar();
	TotalTime = mFX->GetVariableByName("gTotalTime")->AsScalar();
	StartFadeInTime = mFX->GetVariableByName("gStartFadeInTime")->AsScalar();
	StartFadeOutTime = mFX->GetVariableByName("gStartFadeOutTime")->AsScalar();
	Mat = mFX->GetVariableByName("gMaterial");
	DownsampledScreenTexture = mFX->GetVariableByName("gDownsampledScreenTexture")->AsShaderResource();
	SSAOTexture = mFX->GetVariableByName("gSSAOTexture")->AsShaderResource();
	RayMarchingTexture = mFX->GetVariableByName("gRayMarchingTexture")->AsShaderResource();
	ScreenTexture = mFX->GetVariableByName("gScreenTexture")->AsShaderResource();
	PreScreenTexture = mFX->GetVariableByName("gPreScreenTexture")->AsShaderResource();
	DepthTexture = mFX->GetVariableByName("gDepthTexture")->AsShaderResource();
	LutTexture = mFX->GetVariableByName("gLutTexture")->AsShaderResource();
	GrayNoiseTexture = mFX->GetVariableByName("gGrayNoiseTexture")->AsShaderResource();
	CubeMap = mFX->GetVariableByName("gSkyBox")->AsShaderResource();

	//RayMarching
	RayMarching = mFX->GetVariableByName("gRaymarching")->AsScalar();
	//Ambient Occlusion & Dark
	SSAO = mFX->GetVariableByName("gSSAO")->AsScalar();
	SSAOradius = mFX->GetVariableByName("gSsaoRadius")->AsScalar();
	SSAObias = mFX->GetVariableByName("gSsaoBias")->AsScalar();
	SSAOscale = mFX->GetVariableByName("gSsaoScale")->AsScalar();
	SSAOamount = mFX->GetVariableByName("gSsaoAmount")->AsScalar();
	Dark = mFX->GetVariableByName("gDark")->AsScalar();
	DarkAmount = mFX->GetVariableByName("gDarkAmount")->AsScalar();
	//Depth of field
	DepthOfField = mFX->GetVariableByName("gDepthOfField")->AsScalar();
	DepthOfFieldAmount = mFX->GetVariableByName("gDepthOfFieldAmount")->AsScalar();
	DepthOfFieldFocalDepth = mFX->GetVariableByName("gDepthOfFieldFocalDepth")->AsScalar();
	DepthOfFieldFallOffStart = mFX->GetVariableByName("gDepthOfFieldFallOffStart")->AsScalar();
	DepthOfFieldFallOffEnd = mFX->GetVariableByName("gDepthOfFieldFallOffEnd")->AsScalar();
	//Blur
	MotionBlur = mFX->GetVariableByName("gMotionBlur")->AsScalar();
	MotionBlurReferenceDistance = mFX->GetVariableByName("gMdotionBlurReferenceDistance")->AsScalar();
	MotionBlurAmount = mFX->GetVariableByName("gMdotionBlurAmount")->AsScalar();
	GaussianBlur = mFX->GetVariableByName("gGaussianBlur")->AsScalar();
	GaussianBlurAmount = mFX->GetVariableByName("gGaussianBlurAmount")->AsScalar();
	BoxBlur = mFX->GetVariableByName("gBoxBlur")->AsScalar();
	BoxBlurAmount = mFX->GetVariableByName("gBoxBlurAmount")->AsScalar();
	VerticalBlur = mFX->GetVariableByName("gVerticalBlur")->AsScalar();
	VerticalBlurAmount = mFX->GetVariableByName("gVerticalBlurAmount")->AsScalar();
	HorizontalBlur = mFX->GetVariableByName("gHorizontalBlur")->AsScalar();
	HorizontalBlurAmount = mFX->GetVariableByName("gHorizontalBlurAmount")->AsScalar();
	//Lens Distortion
	Rain = mFX->GetVariableByName("gRain")->AsScalar();
	RainSpeed = mFX->GetVariableByName("gRainSpeed")->AsScalar();
	RainAmount = mFX->GetVariableByName("gRainAmount")->AsScalar();
	Blood = mFX->GetVariableByName("gBlood")->AsScalar();
	BloodSpeed = mFX->GetVariableByName("gBloodSpeed")->AsScalar();
	BloodAmount = mFX->GetVariableByName("gBloodAmount")->AsScalar();
	//Chromatic Averration
	ChromaticAberration = mFX->GetVariableByName("gChromaticAberration")->AsScalar();
	ChromaticAberrationAmount = mFX->GetVariableByName("gChromaticAberrationAmount")->AsScalar();
	//Bloom
	Bloom = mFX->GetVariableByName("gBloom")->AsScalar();
	OverBloom = mFX->GetVariableByName("gOverBloom")->AsScalar();
	BloomAmount = mFX->GetVariableByName("gBloomAmount")->AsScalar();
	//Vignette
	Vignette = mFX->GetVariableByName("gVignetting")->AsScalar();
	VignetteAmount = mFX->GetVariableByName("gVignettingAmount")->AsScalar();
	//Color Grading
	Gamma = mFX->GetVariableByName("gGamma")->AsScalar();
	GammaAmount = mFX->GetVariableByName("gGammaAmount")->AsScalar();
	Contrast = mFX->GetVariableByName("gContrast")->AsScalar();
	ContrastAmount = mFX->GetVariableByName("gContrastAmount")->AsScalar();
	Bright = mFX->GetVariableByName("gBright")->AsScalar();
	BrightAmount = mFX->GetVariableByName("gBrightAmount")->AsScalar();
	Saturate = mFX->GetVariableByName("gSaturate")->AsScalar();
	SaturateAmount = mFX->GetVariableByName("gSaturateAmount")->AsScalar();
	SmoothStep = mFX->GetVariableByName("gSmoothStep")->AsScalar();
	SmoothStepMin = mFX->GetVariableByName("gSmoothStepMin")->AsScalar();
	SmoothStepMax = mFX->GetVariableByName("gSmoothStepMax")->AsScalar();
	Tint = mFX->GetVariableByName("gTint")->AsScalar();
	TintColor = mFX->GetVariableByName("gTintColor")->AsVector();
	Sepia = mFX->GetVariableByName("gSepia")->AsScalar();
	GrayScale = mFX->GetVariableByName("gGrayScale")->AsScalar();
	Inverse = mFX->GetVariableByName("gInverse")->AsScalar();
	Lut = mFX->GetVariableByName("gLUT")->AsScalar();
	LutAmount = mFX->GetVariableByName("gLutAmount")->AsScalar();
	TonemapACES = mFX->GetVariableByName("gTonemapACES")->AsScalar();
	TonemapUnreal = mFX->GetVariableByName("gTonemapUnreal")->AsScalar();
	TonemapUnrealExposure = mFX->GetVariableByName("gTonemapUnrealExposure")->AsScalar();
	TonemapReinhard = mFX->GetVariableByName("gTonemapReinhard")->AsScalar();
	//Film Effect
	OldGame = mFX->GetVariableByName("gOldGame")->AsScalar();
	OldGameAmount = mFX->GetVariableByName("gOldGameMosaicAmount")->AsScalar();
	OldGameLevel = mFX->GetVariableByName("gOldGameColorLevel")->AsScalar();
	OldGameMaxColor = mFX->GetVariableByName("gOldGameMaxColor")->AsVector();
	OldGameMinColor = mFX->GetVariableByName("gOldGameMinColor")->AsVector();
	Edge = mFX->GetVariableByName("gEdge")->AsScalar();
	EdgeIndex = mFX->GetVariableByName("gEdgeIndex")->AsScalar();
	Embossed = mFX->GetVariableByName("gEmbossed")->AsScalar();
	Flicker = mFX->GetVariableByName("gFlicker")->AsScalar();
	FlickerAmount = mFX->GetVariableByName("gFlickerAmount")->AsScalar();
	FlickerFrequence = mFX->GetVariableByName("gFlickerFrequence")->AsScalar();
	Cartoon = mFX->GetVariableByName("gCartoon")->AsScalar();
	Mosaic = mFX->GetVariableByName("gMosaic")->AsScalar();
	MosaicAmount = mFX->GetVariableByName("gMosaicAmount")->AsScalar();
	VerticalLines = mFX->GetVariableByName("gVerticalLines")->AsScalar();
	VerticalLinesAmount = mFX->GetVariableByName("gVerticalLinesAmount")->AsScalar();
	HorizontalLines = mFX->GetVariableByName("gHorizontalLines")->AsScalar();
	HorizontalLinesAmount = mFX->GetVariableByName("gHorizontalLinesAmount")->AsScalar();
	Noise = mFX->GetVariableByName("gNoise")->AsScalar();
	NoiseFiness = mFX->GetVariableByName("gNoiseFiness")->AsScalar();
	NoiseBlend = mFX->GetVariableByName("gNoiseBlend")->AsScalar();
	CinematicLine = mFX->GetVariableByName("gCinematicLine")->AsScalar();
	CinematicLineAmount = mFX->GetVariableByName("gCinematicLineAmount")->AsScalar();
	//Fade In, Out
	FadeIn = mFX->GetVariableByName("gFadeIn")->AsScalar();
	FadeInSpeed = mFX->GetVariableByName("gFadeInSpeed")->AsScalar();
	FadeOut = mFX->GetVariableByName("gFadeOut")->AsScalar();
	FadeOutSpeed = mFX->GetVariableByName("gFadeOutSpeed")->AsScalar();
}

PostProcessingEffect::~PostProcessingEffect()
{
}
#pragma endregion

#pragma region Effects

StandardShaderEffect* Effects::StandardShaderFX = 0;
SkyEffect*            Effects::SkyFX = 0;
ParticleEffect*		  Effects::ParticleFX = 0;
BuildShadowMapEffect* Effects::BuildShadowMapFX = 0;
PostProcessingEffect*    Effects::PostProcessingFX = 0;

void Effects::InitAll(ID3D11Device* device)
{
	StandardShaderFX = new StandardShaderEffect(device, TEXT("01_Asset/Fx/StandardShader.fxo"));
	SkyFX = new SkyEffect(device, TEXT("01_Asset/Fx/Sky.fxo"));
	ParticleFX = new ParticleEffect(device, TEXT("01_Asset/Fx/Particle.fxo"));
	BuildShadowMapFX = new BuildShadowMapEffect(device, TEXT("01_Asset/Fx/BuildShadowMap.fxo"));
	PostProcessingFX = new PostProcessingEffect(device, TEXT("01_Asset/Fx/PostProcessing.fxo"));
}

void Effects::DestroyAll()
{
	SAFE_DELETE(StandardShaderFX);
	SAFE_DELETE(SkyFX);
	SAFE_DELETE(ParticleFX);
	SAFE_DELETE(BuildShadowMapFX);
	SAFE_DELETE(PostProcessingFX);
}
#pragma endregion