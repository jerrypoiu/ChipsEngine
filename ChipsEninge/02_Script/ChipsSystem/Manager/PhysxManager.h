#ifndef CHIPSSYSTEM_MANAGER_PHYSXMANAGER_H
#define CHIPSSYSTEM_MANAGER_PHYSXMANAGER_H
#include "ChipsSystem/Etc/Singleton.h"
#include "ChipsSystem/Etc/ChipsCallbacks.h"

namespace ChipsEngine
{
	class GameObject;
	struct RaycastHit final
	{
	public:
		GameObject* m_gameObject;
		XMFLOAT3 m_hitPosition;
		float m_hitDistance;
	};

	/*
	Phyx 물리엔진의 정상적인 작동을 위해 존재하는 Manager이다.
	Raycasting 기능을 지원한다. 
	Ray 함수로 사용 가능하다
	*/
	class PhysxManager final : public Singletone<PhysxManager>
	{
	private:
		PxScene* m_scene;
		PxSceneDesc m_sceneDesc;
		PxPhysics* m_physics;
		PxCooking* m_cooking;
		PxFoundation* m_foundation;
		PxPvdTransport* m_pvdTransport;
		PxTolerancesScale m_tolerancesScale;
		ChipsEventCallback m_eventCallback;
		ChipsFillterCallback m_filterCallback;
		PxControllerManager* m_controllerManager;
		PxDefaultAllocator m_defaultAllocator;
		PxDefaultErrorCallback m_defaultErrorCallback;
		PxDefaultCpuDispatcher* m_cpuDispatcher;
		PxCudaContextManager* m_cudaContextManager;
		PxCudaContextManagerDesc m_cudaContextManagerDesc;
	public:
		PhysxManager();
		~PhysxManager();
	public:
		inline PxPhysics* GetPhysics()
		{
			return m_physics;
		}
		inline PxCooking* GetCooking()
		{
			return m_cooking;
		}
		inline PxScene* GetScene()
		{
			return m_scene;
		}
		inline PxFoundation* GetFoundation()
		{
			return m_foundation;
		}
		inline PxControllerManager* GetControllerManager()
		{
			return m_controllerManager;
		}
		bool Ray(XMFLOAT3& _orign, XMFLOAT3& _unitDir, float& _distance, RaycastHit& _hit);
	public:
		VOID Awake();
		VOID FixedUpdate();
		VOID Render();
		VOID Clear();
	};
}

#endif //CHIPSSYSTEM_MANAGER_PHYSXMANAGER_H