#ifndef CHIPSSYSTEM_COMPONENETS_BASICCOMPONENETS_AUDIOSOURCE_H 
#define	CHIPSSYSTEM_COMPONENETS_BASICCOMPONENETS_AUDIOSOURCE_H
#include "ChipsSystem/BasicFrame/AComponent.h"

namespace ChipsEngine
{
	enum class AUDIO_SOUND_TYPE : char
	{
		AUDIO_SOUND_TYPE_3D = 0, AUDIO_SOUND_TYPE_2D
	};

	enum class AUDIO_LOOP_TYPE : char
	{
		AUDIO_LOOP_TYPE_ONCE = 0, AUDIO_LOOP_TYPE_LOOP
	};

	class Transform;
	/*
	1. 소리를 발생시키는 컴포넌트입니다. Fmod 로 구현되어 있다. 
	   필요에 따라 3D, 2D 로 재생시킬 수 있으며, 반복, 소리조절, 기능을 탑재하고 있다.
	2. .mp3, wav 파일을 재생할 수 있다.
	*/
	class AudioSource final : public AComponent
	{
	private:
		System*  m_system;
		Channel* m_channel;
		float	 m_volume;
		Transform* m_transform;
		map<string, Sound*> m_audio;
	private:
		FMOD_VECTOR m_audioPos;
		FMOD_VECTOR m_oldAudioPos;
		FMOD_VECTOR m_audioVel;
	private:
		FMOD_VECTOR m_camPos;
		FMOD_VECTOR m_oldCamPos;
		FMOD_VECTOR m_camVel;
		FMOD_VECTOR m_camForward;
		FMOD_VECTOR m_camUp;
	public:
		AudioSource();
	protected:
		~AudioSource() override = default;
	public:
		VOID CreateAudio(string _name, const char* _path, bool _playAudioWhenCreate = true, AUDIO_LOOP_TYPE _loopType = AUDIO_LOOP_TYPE::AUDIO_LOOP_TYPE_LOOP, AUDIO_SOUND_TYPE _soundType = AUDIO_SOUND_TYPE::AUDIO_SOUND_TYPE_3D);
		VOID PlayAudio(string _name, bool _isCompulsion = true);
		VOID SetFrequency(float _frequency);
		VOID SetVolume(float _volume);
		VOID StopAudio();
	private:
		virtual VOID Awake() final;
		virtual	VOID Start() final;
		virtual VOID Update() final;
		virtual VOID FixedUpdate() final;
		virtual VOID Render() final;
		virtual VOID Release() final;
	};
}

#endif//CHIPSSYSTEM_COMPONENETS_BASICCOMPONENETS_AUDIOSOURCE_H