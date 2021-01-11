#ifndef CHIPSSYSTEM_COMPONENETS_BASICCOMPONENETS_ANIMATOR_H 
#define	CHIPSSYSTEM_COMPONENETS_BASICCOMPONENETS_ANIMATOR_H
#include "ChipsSystem/BasicFrame/AComponent.h"
#include "ChipsSystem/Components/RendererComponents/SkinRenderer.h"

namespace ChipsEngine
{
#pragma region Keyframe, BoneAnimation, AnimationClip
	struct Keyframe final
	{
	public:
		float m_timePos;
		XMFLOAT3 m_translation;
		XMFLOAT3 m_scale;
		XMFLOAT4 m_rotationQuat;
	public:
		Keyframe();
		~Keyframe() = default;
	};

	struct BoneAnimation final
	{
	public:
		vector<Keyframe> m_keyframes;
	public:
		float GetStartTime()const;
		float GetEndTime()const;
	};

	//에니메이션 이벤트 추가
	using AnimEvent = function<VOID(GameObject* _gameObject)>;

	struct AnimationClip final
	{
	public:
		bool m_isLoop;
		UINT m_curIndex;
		UINT m_oldIndex;
		vector<AnimEvent> m_animEvents;
		vector<BoneAnimation> m_boneAnimations;
	public:
		AnimationClip();
		~AnimationClip() = default;
	public:
		float GetClipStartTime()const;
		float GetClipEndTime()const;
		VOID Interpolate(float _t, vector<XMMATRIX>& _animationTransforms, GameObject* _gameObject);
	};
#pragma endregion

#define ANIM_EVENT_DECL [](GameObject* _gameObject)
#define ANIM_CONDITION_DECL [](Animator* _animator)
	
	class Transform;

	using FsmCondition = function<VOID(Animator* _animator)>;

	/*
	1. Fbx 파일에서 로드한 애니메이션 파일을 SkinMeshRenderer 에 적용시키는 컴포넌트이다.
	2. 내부에 FSM 이 구현되어 있으며, Parameter 와 전이조건을 추가하여,
	   게임 실행 중 자동으로 애니메이션이 전환되게 할 수 있으며,
	   사용자가 지정하는 애니메이션 클립을 즉시 재생시킬 수도 있다
	*/
	class Animator final : public AComponent
	{
	friend SkinRenderer;
	private: 
		//FSM 에 사용된는 멤버변수
		map<string, int>   m_intParameter;
		map<string, float> m_floatParameter;
		map<string, bool>  m_boolParameter;
		map<string, function<VOID(Animator* _animator)>> m_conditions;
	private: 
		//Animation
		bool m_isPause;
		float m_timePos;
		float m_animSpeed;
		string m_curClipName;
		Transform* m_transform;
		AnimationClip* m_curClip;
		SkinRenderer* m_skinRenderer;
		map<string, AnimationClip> m_animations;
	public:
		Animator();
	protected:
		~Animator() override = default;
	public: //public FSM funtions
		inline VOID SetIntParameter(string _key, int _value)
		{
			m_intParameter[_key] = _value;
		}
		inline VOID SetFloatParameter(string _key, float _value)
		{
			m_floatParameter[_key] = _value;
		}
		inline VOID SetBoolParameter(string _key, bool _value)
		{
			m_boolParameter[_key] = _value;
		}
		inline int GetIntParameter(string _key)
		{
			return m_intParameter[_key];
		}
		inline float GetFloatParameter(string _key)
		{
			return m_floatParameter[_key];
		}
		inline bool GetBoolParameter(string _key)
		{
			return m_boolParameter[_key];
		}
		// FSM에 전이조건을 추가하는 함수.
		VOID SetCondition(string _clipName, FsmCondition _contidion);
	public: //public animation funtions
		VOID LoadAnimationClip(string _clipName, string _animationFile, UINT _endFrame = INT_MAX);
		//현재 에니메이션 클립을 설정
		VOID SetCurrentClip(string _clipName);
		VOID SetIsLoopClip(string _clipName, bool _isLoop);
		bool GetIsLoopClip(string _clipName);
		inline VOID SetAnimationSpeed(float _speed)
		{
			m_animSpeed = _speed;
		}
		inline float GetAnimationSpeed()
		{
			return m_animSpeed;
		}	
		// 특정 클립의 특정 프레임에 이벤트를 설정하는 함수. 
		// AnimEvent는 함수포인로 이루어져 있으며, 개발자는 이를 ANIM_EVENT_DECL를 이용하여 람다식으로 넘길 수 있음
		VOID SetAnimationEvent(string _clipName, UINT _frameNum, AnimEvent _animEvent);
	private: //private animation funtion
		VOID GetFinalTransforms(vector<XMMATRIX>& _finalTransforms, vector<XMMATRIX>& _boneTransforms);
	private: //BasicFram functions
		virtual VOID Awake() final;
		virtual	VOID Start() final;
		virtual VOID Update() final;
		virtual VOID FixedUpdate() final;
		virtual VOID Render() final;
		virtual VOID Release() final;
	};
}
#endif//CHIPSSYSTEM_COMPONENETS_BASICCOMPONENETS_ANIMATOR_H