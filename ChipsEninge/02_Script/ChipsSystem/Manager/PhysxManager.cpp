#include "ChipsSystem/Manager/PhysxManager.h"
#include "ChipsSystem/Time/Time.h"
#include "ChipsSystem/Global/Global.h"
#include "DirectX/Effects/Effects.h"
#include "DirectX/Effects/RenderStates.h"

namespace ChipsEngine
{
	PhysxManager::PhysxManager() :
		m_defaultAllocator(PxDefaultAllocator()),
		m_defaultErrorCallback(PxDefaultErrorCallback()),
		m_tolerancesScale(PxTolerancesScale()),
		m_sceneDesc(PxSceneDesc(m_tolerancesScale))
	{
		m_tolerancesScale.length = 1.0f;
		m_tolerancesScale.speed = 10.0f;

		m_foundation = PxCreateFoundation(PX_PHYSICS_VERSION, m_defaultAllocator, m_defaultErrorCallback);

		m_physics = PxCreatePhysics(PX_PHYSICS_VERSION, *m_foundation, m_tolerancesScale, true, nullptr);
		m_cooking = PxCreateCooking(PX_PHYSICS_VERSION, *m_foundation, m_tolerancesScale);
		
		//Vehicle
		PxInitVehicleSDK(*m_physics);
		physx::PxVehicleSetBasisVectors(PxVec3(0.0f, 1.0f, 0.0f), PxVec3(0.0f, 0.0f, 1.0f));
		physx::PxVehicleSetUpdateMode(physx::PxVehicleUpdateMode::eVELOCITY_CHANGE);

		m_cudaContextManager = PxCreateCudaContextManager(*m_foundation, m_cudaContextManagerDesc);
		m_cpuDispatcher = PxDefaultCpuDispatcherCreate(4);

		m_sceneDesc = PxSceneDesc(m_tolerancesScale);
		m_sceneDesc.gravity = PxVec3(0.0f, -9.81f, 0.0f);
		m_sceneDesc.cpuDispatcher = m_cpuDispatcher;
		m_sceneDesc.cudaContextManager = m_cudaContextManager;
		m_sceneDesc.filterShader = ChipsSimulationFilterShader;
		m_sceneDesc.flags |= PxSceneFlag::eENABLE_PCM;
		m_sceneDesc.flags |= PxSceneFlag::eENABLE_STABILIZATION;
		m_sceneDesc.sceneQueryUpdateMode = PxSceneQueryUpdateMode::eBUILD_ENABLED_COMMIT_DISABLED;
		m_sceneDesc.simulationEventCallback = &m_eventCallback;
		m_sceneDesc.filterCallback = &m_filterCallback;
		m_sceneDesc.gpuDynamicsConfig.constraintBufferCapacity *= 2;
		m_sceneDesc.gpuDynamicsConfig.contactBufferCapacity *= 2;
		m_sceneDesc.gpuDynamicsConfig.tempBufferCapacity *= 2;
		m_sceneDesc.gpuDynamicsConfig.contactStreamSize *= 2;
		m_sceneDesc.gpuDynamicsConfig.patchStreamSize *= 2;
		m_sceneDesc.gpuDynamicsConfig.forceStreamCapacity *= 2;
	}

	PhysxManager::~PhysxManager()
	{
		//Vehicle
		physx::PxCloseVehicleSDK();
		m_cudaContextManager->release();
		m_cooking->release();
		m_physics->release();
		m_foundation->release();
		m_pvdTransport->release();
		m_cpuDispatcher->release();	
	}

	bool PhysxManager::Ray(XMFLOAT3& _orign, XMFLOAT3& _unitDir, float& _distance, RaycastHit& _hit)
	{
		const physx::PxHitFlags outputFlags = physx::PxHitFlag::ePOSITION | physx::PxHitFlag::eNORMAL;

		physx::PxQueryFilterData filterData;
		filterData.flags = physx::PxQueryFlag::eDYNAMIC | physx::PxQueryFlag::eSTATIC;

		physx::PxQueryFilterCallback* filterCall = NULL;

		physx::PxRaycastBuffer buf1;
		PxVec3 origin = PxVec3(_orign.x, _orign.y, _orign.z );
		PxVec3 unitDir = PxVec3(_unitDir.x, _unitDir.y, _unitDir.z);

		physx::PxRaycastHit hit;

		m_scene->raycast(origin, unitDir, _distance, buf1, outputFlags, filterData, filterCall, NULL);

		_orign = XMFLOAT3(origin.x, origin.y, origin.z);
		_unitDir = XMFLOAT3(unitDir.x, unitDir.y, unitDir.z);

		hit = buf1.block;
		if (buf1.hasBlock)
		{
			_hit.m_gameObject = (GameObject*)hit.actor->userData;
			_hit.m_hitDistance = hit.distance;
			_hit.m_hitPosition = XMFLOAT3(hit.position.x, hit.position.y, hit.position.z);
		}
		return buf1.hasBlock;
	}

	VOID PhysxManager::Awake()
	{
		m_scene = m_physics->createScene(m_sceneDesc);

		m_controllerManager = PxCreateControllerManager(*m_scene);
	}

	VOID PhysxManager::FixedUpdate()
	{
		m_scene->simulate(Time::GetFixedDeltaTime());
		m_scene->fetchResults(true);	
	}

	VOID PhysxManager::Render()
	{
	}

	VOID PhysxManager::Clear()
	{


		m_scene->release();
		m_scene = nullptr;
		
		m_controllerManager->release();
		m_controllerManager = nullptr;
	}
}