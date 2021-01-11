#include "ChipsSystem/Components/BaiscComponents/AudioSource.h"
#include "ChipsSystem/BasicFrame/GameObject.h"
#include "ChipsSystem/Components/BaiscComponents/Transform.h"
#include "ChipsSystem/Camera/Camera.h"

namespace ChipsEngine
{
	AudioSource::AudioSource() : AComponent("AudioSource"), m_channel(nullptr)
	{
	}

	VOID AudioSource::CreateAudio(string _name, const char* _path, bool _playAudioWhenCreate, AUDIO_LOOP_TYPE _loopType, AUDIO_SOUND_TYPE _soundType)
	{
		Sound* soundTemp = nullptr;
		
		FMOD_MODE mode;
		switch (_soundType)
		{
		case ChipsEngine::AUDIO_SOUND_TYPE::AUDIO_SOUND_TYPE_3D:
			mode = FMOD_3D;
			break;
		case ChipsEngine::AUDIO_SOUND_TYPE::AUDIO_SOUND_TYPE_2D:
			mode = FMOD_2D;
			break;
		}

		switch (_loopType)
		{
		case AUDIO_LOOP_TYPE::AUDIO_LOOP_TYPE_ONCE:
			m_system->createSound(_path, mode | FMOD_DEFAULT | FMOD_HARDWARE, NULL, &soundTemp);
			break;
		case AUDIO_LOOP_TYPE::AUDIO_LOOP_TYPE_LOOP:
			m_system->createSound(_path, mode | FMOD_LOOP_NORMAL | FMOD_HARDWARE, NULL, &soundTemp);
			break;
		}

		m_audio.erase(_name);
		m_audio[_name] = soundTemp;

		if (_playAudioWhenCreate)
		{
			PlayAudio(_name, true);
		}

#ifdef _DEBUG
		printf("Audio Create name : %s\n", _name.c_str());
#endif
	}
	
	void AudioSource::PlayAudio(string _name, bool _isCompulsion)
	{
		bool isPlay = false;
		m_channel->isPlaying(&isPlay);

		if (_isCompulsion)
		{
			m_system->playSound(FMOD_CHANNEL_FREE, m_audio[_name], false, &m_channel);
		}
		else if (!isPlay)
		{
			m_system->playSound(FMOD_CHANNEL_FREE, m_audio[_name], false, &m_channel);
		}

		m_channel->setVolume(m_volume);
	}

	void AudioSource::SetFrequency(float _frequency)
	{
		m_channel->setFrequency(441000 * _frequency);
	}

	void AudioSource::StopAudio()
	{
		bool isPlay = false;
		m_channel->isPlaying(&isPlay);
		if (isPlay)
		{
			m_channel->stop();
		}
	}

	void AudioSource::SetVolume(float _volume)
	{
		m_volume = _volume;
		m_channel->setVolume(m_volume);
	}

	VOID AudioSource::Awake()
	{
		System_Create(&m_system);
		m_system->init(1, FMOD_Awake_NORMAL, NULL);
		m_transform = GetGameObject()->GetTransform();

		m_audioPos = FMOD_VECTOR();
		m_oldAudioPos = FMOD_VECTOR();
		m_audioVel = FMOD_VECTOR();

		m_camPos = FMOD_VECTOR();
		m_oldCamPos = FMOD_VECTOR();
		m_camVel = FMOD_VECTOR();
		m_camForward = FMOD_VECTOR();
		m_camUp = FMOD_VECTOR();
	}
	
	VOID AudioSource::Start()
	{
		m_audioPos = FMOD_VECTOR{ m_transform->GetWorldPosition().x, m_transform->GetWorldPosition().y, m_transform->GetWorldPosition().z };

		XMFLOAT3 pos = Camera::GetInstance()->GetTransform()->GetWorldPosition();
		m_camPos = FMOD_VECTOR{ pos.x, pos.y, pos.z };

		XMVECTOR forward = Camera::GetInstance()->GetTransform()->GetForward();
		m_camForward = FMOD_VECTOR{ forward.m128_f32[0], forward.m128_f32[1], forward.m128_f32[2] };

		XMVECTOR up = Camera::GetInstance()->GetTransform()->GetUp();
		m_camUp = FMOD_VECTOR{ up.m128_f32[0], up.m128_f32[1], up.m128_f32[2] };
	}

	VOID AudioSource::Update()
	{
		m_audioPos = FMOD_VECTOR{m_transform->GetWorldPosition().x, m_transform->GetWorldPosition().y, m_transform->GetWorldPosition().z};

		XMFLOAT3 pos = Camera::GetInstance()->GetTransform()->GetWorldPosition();
		m_camPos = FMOD_VECTOR{ pos.x, pos.y, pos.z};

		XMVECTOR forward = Camera::GetInstance()->GetTransform()->GetForward();
		m_camForward = FMOD_VECTOR{ forward.m128_f32[0], forward.m128_f32[1], forward.m128_f32[2] };

		XMVECTOR up = Camera::GetInstance()->GetTransform()->GetUp();
		m_camUp = FMOD_VECTOR{ up.m128_f32[0], up.m128_f32[1], up.m128_f32[2] };
	}

	VOID AudioSource::FixedUpdate()
	{

	}
	
	VOID AudioSource::Render() 
	{
		m_channel->set3DAttributes(&m_audioPos, &m_audioVel);
		m_system->set3DListenerAttributes(0, &m_camPos, &m_camVel, &m_camForward, &m_camUp);
		m_system->update();
		m_oldCamPos = m_camPos;
		m_oldAudioPos = m_audioPos;
	}

	VOID AudioSource::Release()
	{
		StopAudio();
		auto it = m_audio.begin();
		while (it != m_audio.end())
		{
#ifdef _DEBUG
			printf("Audio Delete name : %s\n", it->first.c_str());
#endif
			it->second->release();
			m_audio.erase(it++);
		}
		m_audio.clear();
		m_system->release();
		m_system->close();
	}
}