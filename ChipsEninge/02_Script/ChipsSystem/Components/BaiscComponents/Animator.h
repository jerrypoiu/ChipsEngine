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

	//���ϸ��̼� �̺�Ʈ �߰�
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
	1. Fbx ���Ͽ��� �ε��� �ִϸ��̼� ������ SkinMeshRenderer �� �����Ű�� ������Ʈ�̴�.
	2. ���ο� FSM �� �����Ǿ� ������, Parameter �� ���������� �߰��Ͽ�,
	   ���� ���� �� �ڵ����� �ִϸ��̼��� ��ȯ�ǰ� �� �� ������,
	   ����ڰ� �����ϴ� �ִϸ��̼� Ŭ���� ��� �����ų ���� �ִ�
	*/
	class Animator final : public AComponent
	{
	friend SkinRenderer;
	private: 
		//FSM �� ���ȴ� �������
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
		// FSM�� ���������� �߰��ϴ� �Լ�.
		VOID SetCondition(string _clipName, FsmCondition _contidion);
	public: //public animation funtions
		VOID LoadAnimationClip(string _clipName, string _animationFile, UINT _endFrame = INT_MAX);
		//���� ���ϸ��̼� Ŭ���� ����
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
		// Ư�� Ŭ���� Ư�� �����ӿ� �̺�Ʈ�� �����ϴ� �Լ�. 
		// AnimEvent�� �Լ����η� �̷���� ������, �����ڴ� �̸� ANIM_EVENT_DECL�� �̿��Ͽ� ���ٽ����� �ѱ� �� ����
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