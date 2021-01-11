#include "ChipsSystem/Components/BaiscComponents/Animator.h"
#include "ChipsSystem/BasicFrame/GameObject.h"
#include "ChipsSystem/BasicFrame/AComponent.h"
#include "ChipsSystem/Components/BaiscComponents/Transform.h"
#include "ChipsSystem/Time/Time.h"
#include "ChipsSystem/Etc/Debug.h"
#include "ChipsSystem/Etc/FbxLoader.h"

namespace ChipsEngine
{
#pragma region Keyframe, BoneAnimation, AnimationClip
	Keyframe::Keyframe() : m_timePos(0.0f), m_translation(0.0f, 0.0f, 0.0f), m_scale(1.0f, 1.0f, 1.0f), m_rotationQuat(0.0f, 0.0f, 0.0f, 1.0f)
	{	}

	float BoneAnimation::GetStartTime() const
	{
		return m_keyframes.front().m_timePos;
	}

	float BoneAnimation::GetEndTime() const
	{
		float f = m_keyframes.back().m_timePos;
		return f;
	}

	AnimationClip::AnimationClip() : m_isLoop(true), m_curIndex(0), m_oldIndex(0)
	{}

	float AnimationClip::GetClipStartTime() const
	{
		float t = FLT_MAX;
		for (UINT i = 0; i < m_boneAnimations.size(); ++i)
		{
			t = min(t, m_boneAnimations[i].GetStartTime());
		}

		return t;
	}

	float AnimationClip::GetClipEndTime() const
	{
		float t = 0.0f;
		for (UINT i = 0; i < m_boneAnimations.size(); ++i)
		{
			t = max(t, m_boneAnimations[i].GetEndTime());
		}

		return t;
	}

	VOID AnimationClip::Interpolate(float _t, vector<XMMATRIX>& _animationTransforms, GameObject* _gameObject)
	{
		XMVECTOR zero = XMVectorSet(0.0f, 0.0f, 0.0f, 1.0f);
		for (UINT i = 0; i < _animationTransforms.size(); ++i)
		{
			XMMATRIX animMatrix;
			Keyframe curFrame;
			if (_t <= GetClipStartTime())
			{
				m_curIndex = 0;
				curFrame = m_boneAnimations.front().m_keyframes[i];				
				XMVECTOR S = XMLoadFloat3(&curFrame.m_scale);
				XMVECTOR P = XMLoadFloat3(&curFrame.m_translation);
				XMVECTOR Q = XMLoadFloat4(&curFrame.m_rotationQuat);
				animMatrix = XMMatrixAffineTransformation(S, zero, Q, P);
				_animationTransforms[i] = animMatrix;
			}
			else if(_t >= GetClipEndTime())
			{
				m_curIndex = (m_boneAnimations.size() - 1);
				curFrame = m_boneAnimations.back().m_keyframes[i];
				XMVECTOR S = XMLoadFloat3(&curFrame.m_scale);
				XMVECTOR P = XMLoadFloat3(&curFrame.m_translation);
				XMVECTOR Q = XMLoadFloat4(&curFrame.m_rotationQuat);
				animMatrix = XMMatrixAffineTransformation(S, zero, Q, P);
				_animationTransforms[i] = animMatrix;
			}
			else
			{
				m_curIndex = (UINT)(_t * 24.0f);
				curFrame = m_boneAnimations[m_curIndex].m_keyframes[i];
				Keyframe nextFrame = m_boneAnimations[m_curIndex +1].m_keyframes[i];

				float lerpPercent = (_t - curFrame.m_timePos) / (nextFrame.m_timePos - curFrame.m_timePos);

				XMVECTOR s0 = XMLoadFloat3(&curFrame.m_scale);
				XMVECTOR s1 = XMLoadFloat3(&nextFrame.m_scale);

				XMVECTOR p0 = XMLoadFloat3(&curFrame.m_translation);
				XMVECTOR p1 = XMLoadFloat3(&nextFrame.m_translation);

				XMVECTOR q0 = XMLoadFloat4(&curFrame.m_rotationQuat);
				XMVECTOR q1 = XMLoadFloat4(&nextFrame.m_rotationQuat);

				XMVECTOR S = DirectX::XMVectorLerp(s0, s1, lerpPercent);
				XMVECTOR P = DirectX::XMVectorLerp(p0, p1, lerpPercent);
				XMVECTOR Q = DirectX::XMQuaternionSlerp(q0, q1, lerpPercent);
				animMatrix = XMMatrixAffineTransformation(S, zero, Q, P);
				_animationTransforms[i] = animMatrix;
			}
		}

		if (m_oldIndex != m_curIndex)
		{
			m_animEvents[m_curIndex](_gameObject);
		}
		m_oldIndex = m_curIndex;
	}
#pragma endregion

	Animator::Animator() : AComponent("Animator"), m_isPause(true), m_timePos(0.0f), m_animSpeed(1.0f), m_curClipName(""),  m_transform(nullptr), m_curClip(nullptr), m_skinRenderer(nullptr)
	{			
	}

	VOID Animator::SetAnimationEvent(string _clipName, UINT _frameNum, AnimEvent _animEvent)
	{
		auto clip = m_animations.find(_clipName);
		if (clip != m_animations.end())
		{
			UINT index = min(_frameNum, (UINT)(clip->second.GetClipEndTime() * 24.0f));
			clip->second.m_animEvents[index] = _animEvent;
		}
		else
		{
			Debug::ErrorMessage("Wrong name", "Check animation clip name");
		}
	}

	VOID Animator::SetCurrentClip(string _clipName)
	{
		if(m_animations.find(_clipName) != m_animations.end())
		{
			m_curClipName = _clipName;
			m_curClip = &m_animations[_clipName];
			m_timePos = 0.0f;
		}
		else
		{
			Debug::ErrorMessage("Wrong name", "Check animation clip name");
		}
	}

	VOID Animator::SetCondition(string _clipName, FsmCondition _contidion)
	{
		if (m_animations.find(_clipName) == m_animations.end())
		{
			Debug::Log("Check animation clip name", LOG_TYPE::WARING_LOG);
		}
		m_conditions[_clipName] = _contidion;
	}

	VOID Animator::LoadAnimationClip(string _clipName, string _animationFile, UINT _endFrame)
	{
		//FBX 로더에서 Animation 로드
		FbxLoader::GetInstance()->LoadAnimation(_animationFile);
		auto temp = FbxLoader::GetInstance()->GetAnimationMatrix();

		UINT frameCount = 0;
		vector<Keyframe> keyFrame;
		vector<BoneAnimation> boneAnimation;
		
		for (const auto& vec : temp)
		{

			if (_endFrame < frameCount)
			{
				break;
			}

			BoneAnimation boneAni;
			keyFrame.clear();
			for (const auto& ele : vec)
			{
				XMVECTOR scale;
				XMVECTOR trans;
				XMVECTOR rot;
				DirectX::XMMatrixDecompose(&scale, &rot, &trans, XMLoadFloat4x4(&ele));

				Keyframe key;
				XMStoreFloat3(&key.m_scale, scale);
				XMStoreFloat3(&key.m_translation, trans);
				XMStoreFloat4(&key.m_rotationQuat, rot);
				key.m_timePos = (float)frameCount / 24.0f;
				keyFrame.push_back(key);
			}
			frameCount++;
			boneAni.m_keyframes = keyFrame;
			boneAnimation.push_back(boneAni);
		}

		AnimationClip clip;
		clip.m_boneAnimations = boneAnimation;
		for (UINT i = 0; i < boneAnimation.size(); i++)
		{
			clip.m_animEvents.push_back(ANIM_EVENT_DECL{});

		}
		m_animations[_clipName] = clip;

		if (m_curClipName.length() == 0)
		{
			m_curClipName = _clipName;
			m_curClip = &m_animations[_clipName];
		}

		m_isPause = false;
	}

	VOID Animator::SetIsLoopClip(string _clipName, bool _isLoop)
	{
		auto clip = m_animations.find(_clipName);
		if (clip != m_animations.end())
		{
			clip->second.m_isLoop = _isLoop;
		}
		else
		{
			Debug::ErrorMessage("Wrong name", "Check animation clip name");
		}
	}

	bool Animator::GetIsLoopClip(string _clipName)
	{
		auto clip = m_animations.find(_clipName);
		if (clip != m_animations.end())
		{
			return clip->second.m_isLoop;
		}
		else
		{
			Debug::ErrorMessage("Wrong name", "Check animation clip name");
			return true;
		}
	}

	VOID Animator::GetFinalTransforms(std::vector<XMMATRIX>& _finalTransforms, vector<XMMATRIX>& _boneTransforms)
	{
		UINT numBones = m_curClip->m_boneAnimations[0].m_keyframes.size();
		std::vector<XMMATRIX> animationMatrix(numBones);

		m_curClip->Interpolate(m_timePos, animationMatrix, GetGameObject());
	
		UINT count = animationMatrix.size();
		for (UINT i = 0; i < count; i++)
		{
			_finalTransforms[i] = _boneTransforms[i] * animationMatrix[i];
		}

		//curPos = _finalTransforms[0].r[3];
		//XMFLOAT3 trans = XMFLOAT3(curPos.m128_f32[0] - oldPos.m128_f32[0], curPos.m128_f32[1] - oldPos.m128_f32[1], curPos.m128_f32[2] - oldPos.m128_f32[2]);
		//cout << m_transform->GetWorldPosition().y << endl;
		//m_transform->Translate(0.0f, curPos.m128_f32[1] * 0.01f, 0.0f, false);
		//oldPos = curPos;
	}

	VOID Animator::Awake()
	{
		m_transform = GetGameObject()->GetTransform();
	}

	VOID Animator::Start()
	{
	}

	VOID Animator::Update()
	{
		//뼈 갯수 맞는지 확인하는거 추가 고려.
		if (m_isPause || m_skinRenderer == nullptr || m_animations.size() <= 0)
			return;

		m_timePos += (Time::GetDeltaTime() * m_animSpeed);

		//Condition Check
		if (m_conditions.find(m_curClipName) != m_conditions.end())
		{
			m_conditions[m_curClipName](this);
		}

		//Update Bone Matrix
		GetFinalTransforms(m_skinRenderer->GetFinalTransforms(), m_skinRenderer->GetBoneTransforms());

		//Animation Loop Check
		if (m_curClip->m_isLoop && m_timePos > m_curClip->GetClipEndTime())
			m_timePos = 0.0f;
	}

	VOID Animator::FixedUpdate()
	{

	}

	VOID Animator::Render()
	{

	}

	VOID Animator::Release()
	{
	}
}