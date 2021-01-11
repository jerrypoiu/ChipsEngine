#ifndef DIRECTX_EFFECTS_EFFECTS_H
#define DIRECTX_EFFECTS_EFFECTS_H
#include "DirectX/Effects/LightHelper.h"

class Effect
{
public:
	Effect(ID3D11Device* device, const std::wstring& filename);
	virtual ~Effect();

private:
	Effect(const Effect& rhs);
	Effect& operator=(const Effect& rhs) = delete;

protected:
	ID3DX11Effect* mFX;
};

#pragma region StandardShaderEffect
class StandardShaderEffect : public Effect
{
public:
	StandardShaderEffect(ID3D11Device* device, const std::wstring& filename);
	~StandardShaderEffect();

	void SetWorldViewProj(XMMATRIX M) { WorldViewProj->SetMatrix(reinterpret_cast<const float*>(&M)); }
	void SetWorld(XMMATRIX M) { World->SetMatrix(reinterpret_cast<const float*>(&M)); }
	void SetWorldView(XMMATRIX M) { WorldView->SetMatrix(reinterpret_cast<const float*>(&M)); }
	void SetWorldInvTranspose(XMMATRIX M) { WorldInvTranspose->SetMatrix(reinterpret_cast<const float*>(&M)); }
	void SetShadowTransform(XMMATRIX M) { ShadowTransform->SetMatrix(reinterpret_cast<const float*>(&M)); }
	void SetTexTransform(XMMATRIX M) { TexTransform->SetMatrix(reinterpret_cast<const float*>(&M)); }
	void SetBoneTransforms(const XMMATRIX* M, int cnt) { BoneTransforms->SetMatrixArray(reinterpret_cast<const float*>(M), 0, cnt); }
	void SetNearFar(const XMFLOAT2& v) { NearFar->SetRawValue(&v, 0, sizeof(XMFLOAT2)); }
	void SetEyePosW(const XMFLOAT3& v) { EyePosW->SetRawValue(&v, 0, sizeof(XMFLOAT3)); }
	void SetFogColor(const XMVECTOR v) { FogColor->SetFloatVector(reinterpret_cast<const float*>(&v)); }
	void SetFogStart(float f) { FogStart->SetFloat(f); }
	void SetFogRange(float f) { FogRange->SetFloat(f); }
	void SetDirLights(const DirectionalLightData* lights) { DirLights->SetRawValue(lights, 0, 3 * sizeof(DirectionalLightData)); }
	void SetPointLights(const PointLightData* lights, int count)
	{
		PointLights->SetRawValue(lights, 0, count * sizeof(PointLightData));
		PointLightCount->SetInt(count);
	}
	void SetSpotLights(const SpotLightData* lights, int count)
	{
		SpotLights->SetRawValue(lights, 0, count * sizeof(SpotLightData));
		SpotLightCount->SetInt(count);
	}
	void SetMaterialCount(int count) {
		MatNum->SetInt(count);
	}

	void SetUseDiffuse(bool _use) { UseDiffuse->SetBool(_use); }
	void SetUseAlphaClip(bool _use) { UseAlphaClip->SetBool(_use); }
	void SetUseNormal(bool _use) { UseNormal->SetBool(_use); }
	void SetUseSpecular(bool _use) { UseSpecular->SetBool(_use); }
	void SetUseReflect(bool _use) { UseReflect->SetBool(_use); }
	void SetUseCartoon(bool _use) { UseCartoon->SetBool(_use); }
	void SetUseFog(bool _use) { UseFog->SetBool(_use); }
	void SetUseShadow(bool _use) { UseShadow->SetBool(_use); }
	void SetUseRimLight(bool _use) { UseRimLight->SetBool(_use); }
	void SetUseSkinning(bool _use) { UseSkinning->SetBool(_use); }

	void SetMaterial(const Material& mat) { Mat->SetRawValue(&mat, 0, sizeof(Material)); }
	void SetDiffuseMap(ID3D11ShaderResourceView* tex) { DiffuseMap->SetResource(tex); }
	void SetSpecularMap(ID3D11ShaderResourceView* tex) { SpecularMap->SetResource(tex); }
	void SetCubeMap(ID3D11ShaderResourceView* tex) { CubeMap->SetResource(tex); }
	void SetNormalMap(ID3D11ShaderResourceView* tex) { NormalMap->SetResource(tex); }
	void SetShadowMap(ID3D11ShaderResourceView* tex) { ShadowMap->SetResource(tex); }

	ID3DX11EffectTechnique* DebugTech;
	ID3DX11EffectTechnique* StandardTech;
	ID3DX11EffectTechnique* CartoonTech;	
	ID3DX11EffectTechnique* DepthTech;	

	ID3DX11EffectScalarVariable* UseDiffuse;
	ID3DX11EffectScalarVariable* UseAlphaClip;
	ID3DX11EffectScalarVariable* UseNormal;
	ID3DX11EffectScalarVariable* UseSpecular;
	ID3DX11EffectScalarVariable* UseReflect;
	ID3DX11EffectScalarVariable* UseCartoon;
	ID3DX11EffectScalarVariable* UseFog;
	ID3DX11EffectScalarVariable* UseShadow;
	ID3DX11EffectScalarVariable* UseRimLight;
	ID3DX11EffectScalarVariable* UseSkinning;

	ID3DX11EffectMatrixVariable* WorldViewProj;
	ID3DX11EffectMatrixVariable* World;
	ID3DX11EffectMatrixVariable* WorldView;
	ID3DX11EffectMatrixVariable* WorldInvTranspose;
	ID3DX11EffectMatrixVariable* ShadowTransform;
	ID3DX11EffectMatrixVariable* TexTransform;
	ID3DX11EffectMatrixVariable* BoneTransforms;
	ID3DX11EffectVectorVariable* NearFar;
	ID3DX11EffectVectorVariable* EyePosW;
	ID3DX11EffectVectorVariable* FogColor;
	ID3DX11EffectScalarVariable* FogStart;
	ID3DX11EffectScalarVariable* FogRange;
	ID3DX11EffectVariable* DirLights;
	ID3DX11EffectVariable* PointLights;
	ID3DX11EffectVariable* SpotLights;
	ID3DX11EffectScalarVariable* MatNum;
	ID3DX11EffectScalarVariable* PointLightCount;
	ID3DX11EffectScalarVariable* SpotLightCount;
	ID3DX11EffectVariable* Mat;
	ID3DX11EffectShaderResourceVariable* SpecularMap;
	ID3DX11EffectShaderResourceVariable* DiffuseMap;
	ID3DX11EffectShaderResourceVariable* CubeMap;
	ID3DX11EffectShaderResourceVariable* NormalMap;
	ID3DX11EffectShaderResourceVariable* ShadowMap;
};
#pragma endregion

#pragma region BuildShadowMapEffect
class BuildShadowMapEffect : public Effect
{
public:
	BuildShadowMapEffect(ID3D11Device* device, const std::wstring& filename);
	~BuildShadowMapEffect();

	void SetUseSkinning(bool _use) { UseSkinning->SetBool(_use); }
	void SetBoneTransforms(const XMMATRIX* M, int cnt) { BoneTransforms->SetMatrixArray(reinterpret_cast<const float*>(M), 0, (UINT)cnt); }

	void SetViewProj(XMMATRIX M) { ViewProj->SetMatrix(reinterpret_cast<const float*>(&M)); }
	void SetWorldViewProj(XMMATRIX M) { WorldViewProj->SetMatrix(reinterpret_cast<const float*>(&M)); }
	void SetWorld(XMMATRIX M) { World->SetMatrix(reinterpret_cast<const float*>(&M)); }
	void SetWorldInvTranspose(XMMATRIX M) { WorldInvTranspose->SetMatrix(reinterpret_cast<const float*>(&M)); }
	void SetTexTransform(XMMATRIX M) { TexTransform->SetMatrix(reinterpret_cast<const float*>(&M)); }
	void SetEyePosW(const XMFLOAT3& v) { EyePosW->SetRawValue(&v, 0, sizeof(XMFLOAT3)); }
	void SetHeightScale(float f) { HeightScale->SetFloat(f); }
	
	ID3DX11EffectScalarVariable* UseSkinning;
	ID3DX11EffectMatrixVariable* BoneTransforms;

	ID3DX11EffectTechnique* BuildShadowMapTech;
	ID3DX11EffectMatrixVariable* ViewProj;
	ID3DX11EffectMatrixVariable* WorldViewProj;
	ID3DX11EffectMatrixVariable* World;
	ID3DX11EffectMatrixVariable* WorldInvTranspose;
	ID3DX11EffectMatrixVariable* TexTransform;
	ID3DX11EffectVectorVariable* EyePosW;
	ID3DX11EffectScalarVariable* HeightScale;
};
#pragma endregion

#pragma region SkyEffect
class SkyEffect : public Effect
{
public:
	SkyEffect(ID3D11Device* device, const std::wstring& filename);
	~SkyEffect();

	void SetWorldViewProj(XMMATRIX M) { WorldViewProj->SetMatrix(reinterpret_cast<const float*>(&M)); }
	void SetWorldView(XMMATRIX M) { WorldView->SetMatrix(reinterpret_cast<const float*>(&M)); }
	void SetNearFar(const XMFLOAT2& v) { NearFar->SetRawValue(&v, 0, sizeof(XMFLOAT2)); }

	void SetCubeMap(ID3D11ShaderResourceView* cubemap) { CubeMap->SetResource(cubemap); }

	ID3DX11EffectTechnique* SkyTech;

	ID3DX11EffectMatrixVariable* WorldViewProj;
	ID3DX11EffectMatrixVariable* WorldView;
	ID3DX11EffectVectorVariable* NearFar;

	ID3DX11EffectShaderResourceVariable* CubeMap;
};
#pragma endregion

#pragma region ParticleEffect
class ParticleEffect : public Effect
{
public:
	ParticleEffect(ID3D11Device* device, const std::wstring& filename);
	~ParticleEffect();

	void SetView(XMMATRIX M) { View->SetMatrix(reinterpret_cast<const float*>(&M)); }
	void SetViewProj(XMMATRIX M) { ViewProj->SetMatrix(reinterpret_cast<const float*>(&M)); }
	void SetNearFar(const XMFLOAT2& v) { NearFar->SetRawValue(&v, 0, sizeof(XMFLOAT2)); }

	void SetGameTime(float f) { GameTime->SetFloat(f); }
	void SetTimeStep(float f) { TimeStep->SetFloat(f); }
	void SetEmitSpread(float f) { EmitSpread->SetFloat(f); }	
	void SetCreateIntervalTime(float f) { CreateIntervalTime->SetFloat(f); }
	void SetDeleteTime(float f) { DeleteTime->SetFloat(f); }
	void SetFadeTime(float f) { FadeTime->SetFloat(f); }
	void SetRandomizePosition(float f) { RandomizePosition->SetFloat(f); }
	void SetEyePosW(const XMFLOAT3& v) { EyePosW->SetRawValue(&v, 0, sizeof(XMFLOAT3)); }
	void SetEmitPosW(const XMFLOAT3& v) { EmitPosW->SetRawValue(&v, 0, sizeof(XMFLOAT3)); }
	void SetEmitDirW(const XMFLOAT3& v) { EmitDirW->SetRawValue(&v, 0, sizeof(XMFLOAT3)); }
	void SetEmitColor(const XMFLOAT3& v) { EmitColor->SetRawValue(&v, 0, sizeof(XMFLOAT3)); }
	void SetEmitSizeW(const XMFLOAT2& v) { EmitSizeW->SetRawValue(&v, 0, sizeof(XMFLOAT2)); }
	void SetEmitMove(const XMFLOAT3& v) { EmitMove->SetRawValue(&v, 0, sizeof(XMFLOAT3)); }

	void SetTexArray(ID3D11ShaderResourceView* tex) { TexArray->SetResource(tex); }
	void SetRandomTex(ID3D11ShaderResourceView* tex) { RandomTex->SetResource(tex); }

	ID3DX11EffectTechnique* StreamOutTech;
	ID3DX11EffectTechnique* DrawTech;

	ID3DX11EffectMatrixVariable* View;
	ID3DX11EffectMatrixVariable* ViewProj;
	ID3DX11EffectScalarVariable* EmitSpread;
	ID3DX11EffectScalarVariable* GameTime;
	ID3DX11EffectScalarVariable* TimeStep;
	ID3DX11EffectScalarVariable* CreateIntervalTime;
	ID3DX11EffectScalarVariable* DeleteTime;
	ID3DX11EffectScalarVariable* FadeTime;
	ID3DX11EffectScalarVariable* RandomizePosition;
	ID3DX11EffectVectorVariable* EyePosW;
	ID3DX11EffectVectorVariable* EmitPosW;
	ID3DX11EffectVectorVariable* EmitDirW;
	ID3DX11EffectVectorVariable* EmitColor;
	ID3DX11EffectVectorVariable* EmitSizeW;
	ID3DX11EffectVectorVariable* EmitMove;
	ID3DX11EffectVectorVariable* NearFar;
	ID3DX11EffectShaderResourceVariable* TexArray;
	ID3DX11EffectShaderResourceVariable* RandomTex;
};
#pragma endregion

#pragma region PostProcessing
class PostProcessingEffect : public Effect
{
public:
	PostProcessingEffect(ID3D11Device* device, const std::wstring& filename);
	~PostProcessingEffect();

	void SetCameraRotMat(XMMATRIX M) { CameraRotMat->SetMatrix(reinterpret_cast<const float*>(&M)); }
	void SetProj(XMMATRIX M) { Proj->SetMatrix(reinterpret_cast<const float*>(&M)); }
	void SetView(XMMATRIX M) { View->SetMatrix(reinterpret_cast<const float*>(&M)); }
	void SetDirLights(const DirectionalLightData* lights) { DirLights->SetRawValue(lights, 0, 3 * sizeof(DirectionalLightData)); }
	void SetPointLights(const PointLightData* lights, int count)
	{
		PointLights->SetRawValue(lights, 0, count * sizeof(PointLightData));
		PointLightCount->SetInt(count);
	}
	void SetSpotLights(const SpotLightData* lights, int count)
	{
		SpotLights->SetRawValue(lights, 0, count * sizeof(SpotLightData));
		SpotLightCount->SetInt(count);
	}
	void SetLutSize(float lutSize)
	{
		LutSize->SetFloat(lutSize);
	}
	void SetTotalTime(float totalTime)
	{
		TotalTime->SetFloat(totalTime);
	}
	void SetStartFadeInTime(float startFadeInTime)
	{
		StartFadeInTime->SetFloat(startFadeInTime);
	}	
	void SetStartFadeOutTime(float startFadeOutTime)
	{
		StartFadeOutTime->SetFloat(startFadeOutTime);
	}
	void SetLutCoordinateInverse(bool isInverse)
	{
		LutCoordinateInverse->SetBool(isInverse);
	}
	void SetEyePosW(const XMFLOAT3& v) { EyePosW->SetRawValue(&v, 0, sizeof(XMFLOAT3)); }
	void SetResolution(const XMFLOAT2& v) { Resolution->SetRawValue(&v, 0, sizeof(XMFLOAT2)); }
	void SetNearFar(const XMFLOAT2& v) { NearFar->SetRawValue(&v, 0, sizeof(XMFLOAT2)); }
	void SetMaterial(const Material& mat) { Mat->SetRawValue(&mat, 0, sizeof(Material)); }
	void SetScreenTexture(ID3D11ShaderResourceView* tex) { ScreenTexture->SetResource(tex); }
	void SetPreScreenTexture(vector<ID3D11ShaderResourceView*> tex) { PreScreenTexture->SetResourceArray(tex.data(), 0, 32); }
	void SetDownsampledScreenTexture(ID3D11ShaderResourceView* tex) { DownsampledScreenTexture->SetResource(tex); }
	void SetSSAOTexture(ID3D11ShaderResourceView* tex) { SSAOTexture->SetResource(tex); }
	void SetRayMarchingTexture(ID3D11ShaderResourceView* tex) { RayMarchingTexture->SetResource(tex); }
	void SetGrayNoiseTexture(ID3D11ShaderResourceView* tex) { GrayNoiseTexture->SetResource(tex); }
	void SetDepthTexture(ID3D11ShaderResourceView* tex) { DepthTexture->SetResource(tex); }
	void SetLutTexture(ID3D11ShaderResourceView* tex) { LutTexture->SetResource(tex); }
	void SetCubeMap(ID3D11ShaderResourceView* tex) { CubeMap->SetResource(tex); }
	void SetRaymarching(bool _active)
	{
		RayMarching->SetBool(_active);
	}
	void SetSSAO(bool _active, float _radius, float _bias, float _scale, float _amount)
	{
		SSAO->SetBool(_active);
		SSAOradius->SetFloat(_radius);
		SSAObias->SetFloat(_bias);
		SSAOscale->SetFloat(_scale);
		SSAOamount->SetFloat(_amount);
	}
	void SetDark(bool _active, float _amount)
	{
		Dark->SetBool(_active);
		DarkAmount->SetFloat(_amount);
	}
	void SetDepthOfField(bool _active, float _amount, float _focalDepth, float _fallOffStart, float _fallOffEnd)
	{
		DepthOfField->SetBool(_active);
		DepthOfFieldAmount->SetFloat(_amount);
		DepthOfFieldFocalDepth->SetFloat(_focalDepth);
		DepthOfFieldFallOffStart->SetFloat(_fallOffStart);
		DepthOfFieldFallOffEnd->SetFloat(_fallOffEnd);
	}
	void SetMotionBlur(bool _active, float _amount, float _referenceDistance)
	{
		MotionBlur->SetBool(_active);
		MotionBlurAmount->SetFloat(_amount);
		MotionBlurReferenceDistance->SetFloat(_referenceDistance);
	}
	void SetGaussianBlur(bool _active, float _amount)
	{
		GaussianBlur->SetBool(_active);
		GaussianBlurAmount->SetFloat(_amount);
	}
	void SetBoxBlur(bool _active, int _amount)
	{
		BoxBlur->SetBool(_active);
		BoxBlurAmount->SetInt(_amount);
	}
	void SetVerticalBlur(bool _active, int _amount)
	{
		VerticalBlur->SetBool(_active);
		VerticalBlurAmount->SetInt(_amount);
	}
	void SetHorizontalBlur(bool _active, int _amount)
	{
		HorizontalBlur->SetBool(_active);
		HorizontalBlurAmount->SetInt(_amount);
	}
	void SetRain(bool _active, float _speed, float _amount)
	{
		Rain->SetBool(_active);
		RainSpeed->SetFloat(_speed);
		RainAmount->SetFloat(_amount);
	}
	void SetBlood(bool _active, float _speed, float _amount)
	{
		Blood->SetBool(_active);
		BloodSpeed->SetFloat(_speed);
		BloodAmount->SetFloat(_amount);
	}
	void SetChromaticAberration(bool _active, float _amount)
	{
		ChromaticAberration->SetBool(_active);
		ChromaticAberrationAmount->SetFloat(_amount);
	}
	void SetBloom(bool _active, bool _over, float _amount)
	{
		Bloom->SetBool(_active);
		OverBloom->SetBool(_over);
		BloomAmount->SetFloat(_amount);
	}
	void SetVignette(bool _active, float _amount)
	{
		Vignette->SetBool(_active);
		VignetteAmount->SetFloat(_amount);
	}
	void SetGamma(bool _active, float _amount)
	{
		Gamma->SetBool(_active);
		GammaAmount->SetFloat(_amount);
	}
	void SetContrast(bool _active, float _amount)
	{
		Contrast->SetBool(_active);
		ContrastAmount->SetFloat(_amount);
	}
	void SetBright(bool _active, float _amount)
	{
		Bright->SetBool(_active);
		BrightAmount->SetFloat(_amount);
	}
	void SetSaturate(bool _active, float _amount)
	{
		Saturate->SetBool(_active);
		SaturateAmount->SetFloat(_amount);
	}
	void SetSmoothStep(bool _active, float _min, float _max)
	{
		SmoothStep->SetBool(_active);
		SmoothStepMin->SetFloat(_min);
		SmoothStepMax->SetFloat(_max);
	}
	void SetTint(bool _active, float _tintColor[3])
	{
		Tint->SetBool(_active);
		TintColor->SetRawValue(_tintColor, 0, sizeof(float) * 3);
	}
	void SetSepia(bool _active)
	{
		Sepia->SetBool(_active);
	}
	void SetGrayScale(bool _active)
	{
		GrayScale->SetBool(_active);
	}
	void SetInverse(bool _active)
	{
		Inverse->SetBool(_active);
	}
	void SetLut(bool _active, float _amount)
	{
		Lut->SetBool(_active);
		LutAmount->SetFloat(_amount);
	}
	void SetTonemapACES(bool _active)
	{
		TonemapACES->SetBool(_active);
	}
	void SetTonemapUnreal(bool _active, float _exposure)
	{
		TonemapUnreal->SetBool(_active);
		TonemapUnrealExposure->SetFloat(_exposure);
	}
	void SetTonemapReinhard(bool _active)
	{
		TonemapReinhard->SetBool(_active);
	}
	void SetOldGame(bool _active, float _amount, float _level, float _minColor[3], float _maxColor[3])
	{
		OldGame->SetBool(_active);
		OldGameAmount->SetFloat(_amount);
		OldGameLevel->SetFloat(_level);
		OldGameMinColor->SetRawValue(_minColor, 0, sizeof(float) * 3);
		OldGameMaxColor->SetRawValue(_maxColor, 0, sizeof(float) * 3);
	}
	void SetEdge(bool _active, int _index)
	{
		Edge->SetBool(_active);
		EdgeIndex->SetInt(_index);
	}
	void SetEmbossed(bool _active)
	{
		Embossed->SetBool(_active);
	}
	void SetFlicker(bool _active, float _amount, float _frequence)
	{
		Flicker->SetBool(_active);
		FlickerAmount->SetFloat(_amount);
		FlickerFrequence->SetFloat(_frequence);
	}
	void SetCartoon(bool _active)
	{
		Cartoon->SetBool(_active);
	}
	void SetMosaic(bool _active, float _amount)
	{
		Mosaic->SetBool(_active);
		MosaicAmount->SetFloat(_amount);
	}
	void SetVerticalLines(bool _active, float _amount)
	{
		VerticalLines->SetBool(_active);
		VerticalLinesAmount->SetFloat(_amount);
	}
	void SetHorizontalLines(bool _active, float _amount)
	{
		HorizontalLines->SetBool(_active);
		HorizontalLinesAmount->SetFloat(_amount);
	}
	void SetNoise(bool _active, float _finess, float _blend)
	{
		Noise->SetBool(_active);
		NoiseFiness->SetFloat(_finess);
		NoiseBlend->SetFloat(_blend);
	}
	void SetCinematicLine(bool _active, float _amount)
	{
		CinematicLine->SetBool(_active);
		CinematicLineAmount->SetFloat(_amount);
	}
	void SetFadeIn(bool _active, float _speed)
	{
		FadeIn->SetBool(_active);
		FadeInSpeed->SetFloat(_speed);
	}
	void SetFadeOut(bool _active, float _speed)
	{
		FadeOut->SetBool(_active);
		FadeOutSpeed->SetFloat(_speed);
	}

	ID3DX11EffectTechnique* PostProcessingTech;
	ID3DX11EffectTechnique* DownSamplingTech;
	ID3DX11EffectTechnique* SSAOTech;
	ID3DX11EffectTechnique* RayMarchingTech;

	ID3DX11EffectVariable* DirLights;
	ID3DX11EffectVariable* PointLights;
	ID3DX11EffectVariable* SpotLights;
	ID3DX11EffectScalarVariable* LutSize;
	ID3DX11EffectScalarVariable* LutCoordinateInverse;
	ID3DX11EffectScalarVariable* PointLightCount;
	ID3DX11EffectScalarVariable* SpotLightCount;
	ID3DX11EffectScalarVariable* TotalTime;
	ID3DX11EffectScalarVariable* StartFadeInTime;
	ID3DX11EffectScalarVariable* StartFadeOutTime;
	ID3DX11EffectVectorVariable* EyePosW;
	ID3DX11EffectVectorVariable* Resolution;
	ID3DX11EffectVectorVariable* NearFar;
	ID3DX11EffectVariable* Mat;
	ID3DX11EffectShaderResourceVariable* DownsampledScreenTexture;
	ID3DX11EffectShaderResourceVariable* DepthTexture;
	ID3DX11EffectShaderResourceVariable* ScreenTexture;
	ID3DX11EffectShaderResourceVariable* SSAOTexture;
	ID3DX11EffectShaderResourceVariable* RayMarchingTexture;
	ID3DX11EffectShaderResourceVariable* PreScreenTexture;
	ID3DX11EffectShaderResourceVariable* GrayNoiseTexture;
	ID3DX11EffectShaderResourceVariable* LutTexture;
	ID3DX11EffectShaderResourceVariable* CubeMap;
	ID3DX11EffectMatrixVariable* View;
	ID3DX11EffectMatrixVariable* Proj;
	ID3DX11EffectMatrixVariable* CameraRotMat;

	//RayMarching
	ID3DX11EffectScalarVariable* RayMarching;
	//Ambient Occlusion & Dark
	ID3DX11EffectScalarVariable* SSAO;
	ID3DX11EffectScalarVariable* SSAOradius;
	ID3DX11EffectScalarVariable* SSAObias;
	ID3DX11EffectScalarVariable* SSAOscale;
	ID3DX11EffectScalarVariable* SSAOamount;
	ID3DX11EffectScalarVariable* Dark;
	ID3DX11EffectScalarVariable* DarkAmount;
	//Depth of field
	ID3DX11EffectScalarVariable* DepthOfField;
	ID3DX11EffectScalarVariable* DepthOfFieldAmount;
	ID3DX11EffectScalarVariable* DepthOfFieldFocalDepth;
	ID3DX11EffectScalarVariable* DepthOfFieldFallOffStart;
	ID3DX11EffectScalarVariable* DepthOfFieldFallOffEnd;
	//Blur
	ID3DX11EffectScalarVariable* MotionBlur;
	ID3DX11EffectScalarVariable* MotionBlurReferenceDistance;
	ID3DX11EffectScalarVariable* MotionBlurAmount;
	ID3DX11EffectScalarVariable* GaussianBlur;
	ID3DX11EffectScalarVariable* GaussianBlurAmount;
	ID3DX11EffectScalarVariable* BoxBlur;
	ID3DX11EffectScalarVariable* BoxBlurAmount;
	ID3DX11EffectScalarVariable* VerticalBlur;
	ID3DX11EffectScalarVariable* VerticalBlurAmount;
	ID3DX11EffectScalarVariable* HorizontalBlur;
	ID3DX11EffectScalarVariable* HorizontalBlurAmount;
	//Lens Distortion
	ID3DX11EffectScalarVariable* Rain;
	ID3DX11EffectScalarVariable* RainSpeed;
	ID3DX11EffectScalarVariable* RainAmount;
	ID3DX11EffectScalarVariable* Blood;
	ID3DX11EffectScalarVariable* BloodSpeed;
	ID3DX11EffectScalarVariable* BloodAmount;
	//Chromatic Averration
	ID3DX11EffectScalarVariable* ChromaticAberration;
	ID3DX11EffectScalarVariable* ChromaticAberrationAmount;
	//Bloom
	ID3DX11EffectScalarVariable* Bloom;
	ID3DX11EffectScalarVariable* OverBloom;
	ID3DX11EffectScalarVariable* BloomAmount;
	//Vignette
	ID3DX11EffectScalarVariable* Vignette;
	ID3DX11EffectScalarVariable* VignetteAmount;
	//Color Grading
	ID3DX11EffectScalarVariable* Gamma;
	ID3DX11EffectScalarVariable* GammaAmount;
	ID3DX11EffectScalarVariable* Contrast;
	ID3DX11EffectScalarVariable* ContrastAmount;
	ID3DX11EffectScalarVariable* Bright;
	ID3DX11EffectScalarVariable* BrightAmount;
	ID3DX11EffectScalarVariable* Saturate;
	ID3DX11EffectScalarVariable* SaturateAmount;
	ID3DX11EffectScalarVariable* SmoothStep;
	ID3DX11EffectScalarVariable* SmoothStepMin;
	ID3DX11EffectScalarVariable* SmoothStepMax;
	ID3DX11EffectScalarVariable* Tint;
	ID3DX11EffectVectorVariable* TintColor;
	ID3DX11EffectScalarVariable* Sepia;
	ID3DX11EffectScalarVariable* GrayScale;
	ID3DX11EffectScalarVariable* Inverse;
	ID3DX11EffectScalarVariable* Lut;
	ID3DX11EffectScalarVariable* LutAmount;
	ID3DX11EffectScalarVariable* TonemapACES;
	ID3DX11EffectScalarVariable* TonemapUnreal;
	ID3DX11EffectScalarVariable* TonemapUnrealExposure;
	ID3DX11EffectScalarVariable* TonemapReinhard;
	//Film Effect
	ID3DX11EffectScalarVariable* OldGame;
	ID3DX11EffectScalarVariable* OldGameAmount;
	ID3DX11EffectScalarVariable* OldGameLevel;
	ID3DX11EffectVectorVariable* OldGameMinColor;
	ID3DX11EffectVectorVariable* OldGameMaxColor;
	ID3DX11EffectScalarVariable* Edge;
	ID3DX11EffectScalarVariable* EdgeIndex;
	ID3DX11EffectScalarVariable* Embossed;
	ID3DX11EffectScalarVariable* Flicker;
	ID3DX11EffectScalarVariable* FlickerAmount;
	ID3DX11EffectScalarVariable* FlickerFrequence;
	ID3DX11EffectScalarVariable* Cartoon;
	ID3DX11EffectScalarVariable* Mosaic;
	ID3DX11EffectScalarVariable* MosaicAmount;
	ID3DX11EffectScalarVariable* VerticalLines;
	ID3DX11EffectScalarVariable* VerticalLinesAmount;
	ID3DX11EffectScalarVariable* HorizontalLines;
	ID3DX11EffectScalarVariable* HorizontalLinesAmount;
	ID3DX11EffectScalarVariable* Noise;
	ID3DX11EffectScalarVariable* NoiseFiness;
	ID3DX11EffectScalarVariable* NoiseBlend;
	ID3DX11EffectScalarVariable* CinematicLine;
	ID3DX11EffectScalarVariable* CinematicLineAmount;
	//Fade In, Out
	ID3DX11EffectScalarVariable* FadeIn;
	ID3DX11EffectScalarVariable* FadeInSpeed;
	ID3DX11EffectScalarVariable* FadeOut;
	ID3DX11EffectScalarVariable* FadeOutSpeed;	
};
#pragma endregion

#pragma region Effects
class Effects
{
public:
	static void InitAll(ID3D11Device* device);
	static void DestroyAll();

	static SkyEffect* SkyFX;
	static StandardShaderEffect* StandardShaderFX;
	static ParticleEffect* ParticleFX;
	static BuildShadowMapEffect* BuildShadowMapFX;
	static PostProcessingEffect* PostProcessingFX;
};
#endif //DIRECTX_EFFECTS_EFFECTS_H