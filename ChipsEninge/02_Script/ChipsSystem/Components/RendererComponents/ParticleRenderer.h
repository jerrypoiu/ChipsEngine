#ifndef CHIPSSYSTEM_COMPONENETS_RENDERERCOMPONENETS_PARTICLERENDERER_H
#define CHIPSSYSTEM_COMPONENETS_RENDERERCOMPONENETS_PARTICLERENDERER_H
#include "DirectX/Effects/Effects.h"
#include "DirectX/Effects/LightHelper.h"
#include "ChipsSystem/BasicFrame/AComponent.h"

namespace ChipsEngine
{
	struct ParticleData final
	{
		ParticleData();
		~ParticleData();
		bool m_isLoaded;
		bool m_firstRun;
		bool m_isFrustumCullingActive;
		float m_frustumCullingRadius;
		float m_age;
		float m_speed;
		float m_spread;
		float m_createIntervalTime;
		float m_deleteTime;
		float m_fadeTime;
		float m_randomizePosition;
		float m_timeStep;
		float m_gameTime;
		UINT m_maxParticles;
		XMFLOAT3 m_cameraPos;
		XMFLOAT3 m_emitColor;
		XMFLOAT2 m_size;
		Transform* m_transform;
		ID3D11Buffer* m_initVB;
		ID3D11Buffer* m_drawVB;
		ID3D11Buffer* m_streamOutVB;
		ID3D11ShaderResourceView* m_texArraySRV;
		ID3D11ShaderResourceView* m_randomTexSRV;
	};

	/*
	파티클을 렌더링 하는 컴포넌트이다. 
	다음과 같은 기능들을 제공한다.
	*기능들*
	✓ 텍스쳐
	✓ 최대 파티클 수
	✓ 색상
	✓ 날아가는 속도
	✓ 퍼지는 속도
	✓ 생성 속도
	✓ 삭제 속도
	✓ Fade out 속도
	✓ 생성되는 위치에 랜덤성 추가
	✓ 초기화
	*/
	class ParticleRenderer final : public AComponent
	{
	private:
		ParticleData* m_particleData;
	public:
		ParticleRenderer();
	protected:
		virtual ~ParticleRenderer() = default;
	public:
		VOID LoadTexture(const string _texturePath, UINT _maxParticlesCount = 500);
		inline VOID SetFrustumCulling(bool _active)
		{
			m_particleData->m_isFrustumCullingActive = _active;
		}
		inline VOID SetFrustumCullingRadius(float _radius)
		{
			m_particleData->m_frustumCullingRadius = _radius;
		}
		inline VOID SetSpeed(float _speed)
		{
			m_particleData->m_speed = _speed;
		}
		inline VOID SetSpread(float _spread)
		{
			m_particleData->m_spread = _spread;
		}
		inline VOID SetCreateIntervalTime(float _createIntervalTime)
		{
			m_particleData->m_createIntervalTime = _createIntervalTime;
		}
		inline VOID SetDeleteTime(float _deleteTime)
		{
			m_particleData->m_deleteTime = _deleteTime;
		}
		inline VOID SetFadeTime(float _fadeTime)
		{
			m_particleData->m_fadeTime = _fadeTime;
		}
		inline VOID SetRandomizePosition(float _randomizePosition)
		{
			m_particleData->m_randomizePosition = _randomizePosition;
		}
		inline VOID SetColor(XMFLOAT3 _color)
		{
			m_particleData->m_emitColor = _color;
		}
		inline VOID SetColor(float _red, float _green, float _blue)
		{
			m_particleData->m_emitColor = XMFLOAT3(_red, _green, _blue);
		}
		inline VOID Reset()
		{
			m_particleData->m_firstRun = true;
			m_particleData->m_age = 0.0f;
		}
	    inline float GetAge() const
		{
			return m_particleData->m_age;
		}
	private:
		VOID MakeRandomSRV();
		VOID BuildVB();
	private:
		virtual VOID Awake() final;
		virtual VOID Start() final;
		virtual VOID Update() final;
		virtual VOID FixedUpdate() final;
		virtual VOID Render() final;
		virtual VOID Release() final;
	};
}

#endif //CHIPSSYSTEM_COMPONENETS_RENDERERCOMPONENETS_PARTICLERENDERER_H