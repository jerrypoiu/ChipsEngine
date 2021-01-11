#ifndef CHIPSSYSTEM_MANAGER_PARTICLEMANAGER_H
#define CHIPSSYSTEM_MANAGER_PARTICLEMANAGER_H
#include "DirectX/Effects/Effects.h"
#include "DirectX/Effects/LightHelper.h"
#include "ChipsSystem/Components/BaiscComponents/Transform.h"
#include "ChipsSystem/Components/RendererComponents/ParticleRenderer.h"
#include "ChipsSystem/Etc/Singleton.h"

namespace ChipsEngine
{
	/*
	ParticleSystem �� �������� �۵��� ���� �����ϴ� Manager �̸�,
	����ڿ��� ���������� �����Ǵ� ����� �������� �ʴ�.
	*/
	class ParticleManager final : public Singletone<ParticleManager>
	{
		friend class ParticleRenderer;
	private:
		int m_particleCurrentCount;
		__int64 m_oldTime;
		__int64 m_curTime;
		float m_deltaTime;
		double m_secondsPerCount;
		list<ParticleData*> m_particleDatas;
	public:
		ParticleManager();
		~ParticleManager() = default;
	private:
		VOID AddParticleData(ParticleData* _particleData);
		VOID DeleteParticleData(ParticleData* _particleData);
	public:
		VOID Awake();
		VOID Update();
		VOID Render();
		VOID Clear();
	};
}

#endif //CHIPSSYSTEM_MANAGER_PARTICLEMANAGER_H