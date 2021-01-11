#include "ChipsSystem/BasicFrame/GameObject.h"
#include "ChipsSystem/Components/BaiscComponents/Rigidbody.h"
#include "ChipsSystem/Components/BaiscComponents/Transform.h"
#include "ChipsSystem/Manager/PhysxManager.h"
#include "ChipsSystem/Etc/Mathf.h"
#include "ChipsSystem/Etc/Debug.h"

namespace ChipsEngine
{
	Rigidbody::Rigidbody() : AComponent("Rigidbody"), m_layer(0),
		m_transform(nullptr), m_rigidDynamic(nullptr), m_rigidStatic(nullptr),
		m_pxQuaternion(PxQuat()), m_currentRigidbodyType(CURRENT_RIGIDBODY_TYPE::NON)
	{}

	VOID Rigidbody::SetMass(float _mass)
	{
		if (CanCallRigidDynamicFunc() == false)
			return;

		_mass = Mathf::Clamp(_mass, 0.0f, Mathf::Abs(_mass));
		m_rigidDynamic->setMass(_mass);
	}

	VOID Rigidbody::SetDrag(float _drag)
	{
		if (CanCallRigidDynamicFunc() == false)
			return;

		_drag = Mathf::Clamp(_drag, 0.0f, Mathf::Abs(_drag));
		m_rigidDynamic->setLinearDamping(_drag);
	}

	VOID Rigidbody::SetAngularDarg(float _drag)
	{
		if (CanCallRigidDynamicFunc() == false)
			return;

		_drag = Mathf::Clamp(_drag, 0.0f, Mathf::Abs(_drag));
		m_rigidDynamic->setAngularDamping(_drag);
	}

	VOID Rigidbody::SetFreeze(bool _posX, bool _posY, bool _posZ, bool _rotX, bool _rotY, bool _rotZ)
	{
		if (CanCallRigidDynamicFunc() == false)
			return;

		physx::PxRigidDynamicLockFlags flags;

		if (_posX)
		{
			flags |= physx::PxRigidDynamicLockFlag::eLOCK_LINEAR_X;
		}

		if (_posY)
		{
			flags |= physx::PxRigidDynamicLockFlag::eLOCK_LINEAR_Y;
		}

		if (_posZ)
		{
			flags |= physx::PxRigidDynamicLockFlag::eLOCK_LINEAR_Z;
		}

		if (_rotX)
		{
			flags |= physx::PxRigidDynamicLockFlag::eLOCK_ANGULAR_X;
		}

		if (_rotY)
		{
			flags |= physx::PxRigidDynamicLockFlag::eLOCK_ANGULAR_Y;
		}

		if (_rotZ)
		{
			flags |= physx::PxRigidDynamicLockFlag::eLOCK_ANGULAR_Z;
		}

		m_rigidDynamic->setRigidDynamicLockFlags(flags);
	}

	VOID Rigidbody::SetKinematic(bool _isActive)
	{
		if (CanCallRigidDynamicFunc() == false)
			return;

		m_rigidDynamic->setRigidBodyFlag(physx::PxRigidBodyFlag::eKINEMATIC, _isActive);
	}

	VOID Rigidbody::SetGravity(bool _isActive)
	{
		if (CanCallRigidDynamicFunc() == false)
			return;

		m_rigidDynamic->setActorFlag(physx::PxActorFlag::eDISABLE_GRAVITY, !_isActive);
	}

	VOID Rigidbody::SetMassPose(XMFLOAT3 _position)
	{
		if (CanCallRigidDynamicFunc() == false)
			return;

		m_rigidDynamic->setCMassLocalPose(PxTransform(PxVec3(_position.x, _position.y, _position.z)));
	}

	VOID Rigidbody::SetMassPose(float _x, float _y, float _z)
	{
		if (CanCallRigidDynamicFunc() == false)
			return;

		m_rigidDynamic->setCMassLocalPose(PxTransform(PxVec3(_x, _y, _z)));
	}

	VOID Rigidbody::AddTorque(XMVECTOR _torque)
	{
		if (CanCallRigidDynamicFunc() == false)
			return;

		m_rigidDynamic->addTorque(PxVec3(_torque.m128_f32[0], _torque.m128_f32[1], _torque.m128_f32[2]));
	}

	VOID Rigidbody::AddTorque(float _torque, XMVECTOR _direction)
	{
		if (CanCallRigidDynamicFunc() == false)
			return;

		XMVECTOR torque = XMVECTOR();
		torque.m128_f32[0] = _direction.m128_f32[0] * _torque;
		torque.m128_f32[1] = _direction.m128_f32[1] * _torque;
		torque.m128_f32[1] = _direction.m128_f32[2] * _torque;
		AddTorque(torque);
	}

	VOID Rigidbody::AddTorque(XMFLOAT3 _torque)
	{
		if (CanCallRigidDynamicFunc() == false)
			return;

		m_rigidDynamic->addTorque(PxVec3(_torque.x, _torque.y, _torque.z));
	}

	VOID Rigidbody::AddTorque(float _x, float _y, float _z)
	{
		if (CanCallRigidDynamicFunc() == false)
			return;

		m_rigidDynamic->addTorque(PxVec3(_x, _y, _z));
	}

	VOID Rigidbody::AddTorque(float _torque, XMFLOAT3 _direction)
	{
		if (CanCallRigidDynamicFunc() == false)
			return;

		XMVECTOR torque = XMVECTOR();
		torque.m128_f32[0] = _direction.x * _torque;
		torque.m128_f32[1] = _direction.y * _torque;
		torque.m128_f32[1] = _direction.z * _torque;
		AddTorque(torque);
	}

	VOID Rigidbody::AddForce(XMVECTOR _force)
	{
		if (CanCallRigidDynamicFunc() == false)
			return;

		m_rigidDynamic->addForce(PxVec3(_force.m128_f32[0], _force.m128_f32[1], _force.m128_f32[2]));
	}

	VOID Rigidbody::AddForce(float _force, XMVECTOR _direction)
	{
		if (CanCallRigidDynamicFunc() == false)
			return;

		XMVECTOR force = XMVECTOR();
		force.m128_f32[0] = _direction.m128_f32[0] * _force;
		force.m128_f32[1] = _direction.m128_f32[1] * _force;
		force.m128_f32[1] = _direction.m128_f32[2] * _force;

		AddForce(force);
	}

	VOID Rigidbody::AddForce(XMFLOAT3 _force)
	{
		if (CanCallRigidDynamicFunc() == false)
			return;

		m_rigidDynamic->addForce(PxVec3(_force.x, _force.y, _force.z));
	}

	VOID Rigidbody::AddForce(float _x, float _y, float _z)
	{
		if (CanCallRigidDynamicFunc() == false)
			return;

		m_rigidDynamic->addForce(PxVec3(_x, _y, _z));
	}

	VOID Rigidbody::AddForce(float _force, XMFLOAT3 _direction)
	{
		if (CanCallRigidDynamicFunc() == false)
			return;

		XMVECTOR force = XMVECTOR();
		force.m128_f32[0] = _direction.x * _force;
		force.m128_f32[1] = _direction.y * _force;
		force.m128_f32[1] = _direction.z * _force;

		AddForce(force);
	}

	VOID Rigidbody::SetVelocity(XMVECTOR _velocity)
	{
		if (CanCallRigidDynamicFunc() == false)
			return;

		m_rigidDynamic->setLinearVelocity(PxVec3(_velocity.m128_f32[0], _velocity.m128_f32[1], _velocity.m128_f32[2]));
	}

	VOID Rigidbody::SetVelocity(float _velocity, XMVECTOR _direction)
	{
		if (CanCallRigidDynamicFunc() == false)
			return;

		XMVECTOR velocity = XMVECTOR();
		velocity.m128_f32[0] = _direction.m128_f32[0] * _velocity;
		velocity.m128_f32[1] = _direction.m128_f32[1] * _velocity;
		velocity.m128_f32[1] = _direction.m128_f32[2] * _velocity;
		SetVelocity(velocity);
	}

	VOID Rigidbody::SetVelocity(XMFLOAT3 _velocity)
	{
		if (CanCallRigidDynamicFunc() == false)
			return;

		m_rigidDynamic->setLinearVelocity(PxVec3(_velocity.x, _velocity.y, _velocity.z));
	}

	VOID Rigidbody::SetVelocity(float _x, float _y, float _z)
	{
		if (CanCallRigidDynamicFunc() == false)
			return;

		m_rigidDynamic->setLinearVelocity(PxVec3(_x, _y, _z));
	}

	VOID Rigidbody::SetVelocity(float _velocity, XMFLOAT3 _direction)
	{
		if (CanCallRigidDynamicFunc() == false)
			return;

		XMVECTOR velocity = XMVECTOR();
		velocity.m128_f32[0] = _direction.x * _velocity;
		velocity.m128_f32[1] = _direction.y * _velocity;
		velocity.m128_f32[1] = _direction.z * _velocity;
		SetVelocity(velocity);
	}

	VOID Rigidbody::SetAngularVelocity(XMVECTOR _velocity)
	{
		if (CanCallRigidDynamicFunc() == false)
			return;

		m_rigidDynamic->setAngularVelocity(PxVec3(_velocity.m128_f32[0], _velocity.m128_f32[1], _velocity.m128_f32[2]));
	}

	VOID Rigidbody::SetAngularVelocity(float _velocity, XMVECTOR _direction)
	{
		if (CanCallRigidDynamicFunc() == false)
			return;

		XMVECTOR velocity = XMVECTOR();
		velocity.m128_f32[0] = _direction.m128_f32[0] * _velocity;
		velocity.m128_f32[1] = _direction.m128_f32[1] * _velocity;
		velocity.m128_f32[1] = _direction.m128_f32[2] * _velocity;
		SetAngularVelocity(velocity);
	}

	VOID Rigidbody::SetAngularVelocity(XMFLOAT3 _velocity)
	{
		if (CanCallRigidDynamicFunc() == false)
			return;

		m_rigidDynamic->setAngularVelocity(PxVec3(_velocity.x, _velocity.y, _velocity.z));
	}

	VOID Rigidbody::SetAngularVelocity(float _x, float _y, float _z)
	{
		if (CanCallRigidDynamicFunc() == false)
			return;

		m_rigidDynamic->setAngularVelocity(PxVec3(_x, _y, _z));
	}

	VOID Rigidbody::SetAngularVelocity(float _velocity, XMFLOAT3 _direction)
	{
		if (CanCallRigidDynamicFunc() == false)
			return;

		XMVECTOR velocity = XMVECTOR();
		velocity.m128_f32[0] = _direction.x * _velocity;
		velocity.m128_f32[1] = _direction.y * _velocity;
		velocity.m128_f32[1] = _direction.z * _velocity;
		SetAngularVelocity(velocity);
	}

	bool Rigidbody::CanCallRigidDynamicFunc()
	{
		if (m_currentRigidbodyType != CURRENT_RIGIDBODY_TYPE::DYNAMIC)
		{
			#ifdef _DEBUG
			Debug::Log("WARNING : You didn't add a Rigidbody Component to \"" + GetGameObject()->GetName() + "\" GameObject.", LOG_TYPE::WARING_LOG);
			#endif
			return false;
		}
		else if (m_rigidDynamic->getRigidBodyFlags() & physx::PxRigidBodyFlag::eKINEMATIC)
		{
			#ifdef _DEBUG
			Debug::Log("WARNING : You can't be manipulated when it's kinematic. \"" + GetGameObject()->GetName() + "\" GameObject.", LOG_TYPE::WARING_LOG);
			#endif
			return false;
		}

		return true;
	}

	float Rigidbody::GetMass()
	{
		if (CanCallRigidDynamicFunc() == false)
			return 0.0f;

		return m_rigidDynamic->getMass();
	}

	float Rigidbody::GetDrag()
	{
		if (CanCallRigidDynamicFunc() == false)
			return 0.0f;

		return m_rigidDynamic->getLinearDamping();
	}

	float Rigidbody::GetAngularDarg()
	{
		if (CanCallRigidDynamicFunc() == false)
			return 0.0f;

		return m_rigidDynamic->getAngularDamping();
	}

	bool Rigidbody::GetKinematic()
	{
		if (CanCallRigidDynamicFunc() == false)
			return false;
		return m_rigidDynamic->getRigidBodyFlags().isSet(physx::PxRigidBodyFlag::eKINEMATIC);
	}

	bool Rigidbody::SetGravity()
	{
		if (CanCallRigidDynamicFunc() == false)
			return false;

		return m_rigidDynamic->getActorFlags().isSet(physx::PxActorFlag::eDISABLE_GRAVITY);
	}

	XMFLOAT3 Rigidbody::GetMassPose()
	{
		if (CanCallRigidDynamicFunc() == false)
			return XMFLOAT3();

		return XMFLOAT3(m_rigidDynamic->getCMassLocalPose().p.x, m_rigidDynamic->getCMassLocalPose().p.y, m_rigidDynamic->getCMassLocalPose().p.z);
	}
	
	XMFLOAT3 Rigidbody::GetVelocity()
	{
		if (CanCallRigidDynamicFunc() == false)
			return XMFLOAT3();
	
		return XMFLOAT3(m_rigidDynamic->getLinearVelocity().x, m_rigidDynamic->getLinearVelocity().y, m_rigidDynamic->getLinearVelocity().z);
	}

	XMFLOAT3 Rigidbody::GetAngularVelocity()
	{
		if (CanCallRigidDynamicFunc() == false)
			return XMFLOAT3();

		return XMFLOAT3(m_rigidDynamic->getAngularVelocity().x, m_rigidDynamic->getAngularVelocity().y, m_rigidDynamic->getAngularVelocity().z);
	}

	VOID Rigidbody::AttachShape(PxShape* _shape)
	{
		physx::PxFilterData filterData;
		filterData.word0 = m_layer;
		_shape->setSimulationFilterData(filterData);

		if (m_currentRigidbodyType == CURRENT_RIGIDBODY_TYPE::STATIC)
		{
			m_rigidStatic->attachShape(*_shape);
		}
		else if (m_currentRigidbodyType == CURRENT_RIGIDBODY_TYPE::DYNAMIC)
		{
			m_rigidDynamic->attachShape(*_shape);
		}
	}

	VOID Rigidbody::DettachShape(PxShape* _shape)
	{
		if (m_currentRigidbodyType == CURRENT_RIGIDBODY_TYPE::STATIC)
		{
			m_rigidStatic->detachShape(*_shape);
		}
		else if (m_currentRigidbodyType == CURRENT_RIGIDBODY_TYPE::DYNAMIC)
		{
			m_rigidDynamic->detachShape(*_shape);
		}
	}

	VOID Rigidbody::Awake()
	{
		if (m_currentRigidbodyType == CURRENT_RIGIDBODY_TYPE::NON)
		{
			m_layer = GetGameObject()->GetLayer();

			m_currentRigidbodyType = CURRENT_RIGIDBODY_TYPE::STATIC;
			m_transform = GetGameObject()->GetTransform();
			m_position = m_transform->GetWorldPosition();
			m_rotation = m_transform->GetWorldRotation();
			m_quaternion = XMQuaternionRotationRollPitchYaw(m_rotation.x * DEGREES_TO_RADIANS, m_rotation.y * DEGREES_TO_RADIANS, m_rotation.z * DEGREES_TO_RADIANS);

			m_pxQuaternion.x = m_quaternion.m128_f32[0];
			m_pxQuaternion.y = m_quaternion.m128_f32[1];
			m_pxQuaternion.z = m_quaternion.m128_f32[2];
			m_pxQuaternion.w = m_quaternion.m128_f32[3];

			m_pxTransform = PxTransform(m_position.x, m_position.y, m_position.z, m_pxQuaternion);
			m_rigidStatic = PhysxManager::GetInstance()->GetPhysics()->createRigidStatic(m_pxTransform);
			m_rigidStatic->userData = this->GetGameObject();

			PhysxManager::GetInstance()->GetScene()->addActor(*m_rigidStatic);
		}
		else if (m_currentRigidbodyType == CURRENT_RIGIDBODY_TYPE::STATIC)
		{
			m_currentRigidbodyType = CURRENT_RIGIDBODY_TYPE::DYNAMIC;
			Debug::Log("Changed from RigidStatic to RigidDynamic.", LOG_TYPE::CREATE_LOG);

			vector<PxShape*> shapes(m_rigidStatic->getNbShapes());
			if (m_rigidStatic->getNbShapes() > 0)
			{
				m_rigidStatic->getShapes(shapes.data(), m_rigidStatic->getNbShapes());
			}

			PhysxManager::GetInstance()->GetScene()->removeActor(*m_rigidStatic);

			//m_rigidDynamic Ãß°¡
			m_rigidDynamic = PhysxManager::GetInstance()->GetPhysics()->createRigidDynamic(m_pxTransform);
			m_rigidDynamic->userData = this->GetGameObject();
			
			if (shapes.size() > 0)
			{
				for (auto& shape : shapes)
				{
					m_rigidDynamic->attachShape(*shape);
				}
			}
			shapes.clear();

			SetMass(10.0f);
			SetGravity(true);
			SetKinematic(false);
			SetDrag(0.5f);
			SetAngularDarg(0.5f);
			SetFreeze(false, false, false, false, false, false);
			PhysxManager::GetInstance()->GetScene()->addActor(*m_rigidDynamic);
		}
		else
		{
			Debug::Log("WARNING : You have already add a Rigidbody Component to \"" + GetGameObject()->GetName() + "\" GameObject.", LOG_TYPE::WARING_LOG);
		}
	}

	VOID Rigidbody::Start()
	{
	}

	VOID Rigidbody::Update()
	{
		if (m_currentRigidbodyType != CURRENT_RIGIDBODY_TYPE::DYNAMIC)
			return;

		m_position = m_transform->GetWorldPosition();
		m_pxTransform.p = PxVec3(m_position.x, m_position.y, m_position.z);
		
		m_rotation = m_transform->GetWorldRotation();
		m_quaternion = XMQuaternionRotationRollPitchYaw(m_rotation.x * DEGREES_TO_RADIANS, m_rotation.y * DEGREES_TO_RADIANS, m_rotation.z * DEGREES_TO_RADIANS);
		m_pxQuaternion.x = m_quaternion.m128_f32[0];
		m_pxQuaternion.y = m_quaternion.m128_f32[1];
		m_pxQuaternion.z = m_quaternion.m128_f32[2];
		m_pxQuaternion.w = m_quaternion.m128_f32[3];

		if (m_pxQuaternion.isSane())
		{
			m_pxTransform.q = m_pxQuaternion;
			m_rigidDynamic->setGlobalPose(m_pxTransform);
		}
	}

	VOID Rigidbody::FixedUpdate()
	{
		if (m_currentRigidbodyType != CURRENT_RIGIDBODY_TYPE::DYNAMIC)
			return;

		m_position.x = m_rigidDynamic->getGlobalPose().p.x;
		m_position.y = m_rigidDynamic->getGlobalPose().p.y;
		m_position.z = m_rigidDynamic->getGlobalPose().p.z;
		m_transform->SetWorldPosition(m_position);
		
		m_pxQuaternion = m_rigidDynamic->getGlobalPose().q;
		m_quaternion.m128_f32[0] = m_pxQuaternion.x;
		m_quaternion.m128_f32[1] = m_pxQuaternion.y;
		m_quaternion.m128_f32[2] = m_pxQuaternion.z;
		m_quaternion.m128_f32[3] = m_pxQuaternion.w;
		XMMATRIX rotMatrix = XMMatrixRotationQuaternion(m_quaternion);
		
		float rotX = 0.0f;
		float rotY = 0.0f;
		float rotZ = 0.0f;
		Mathf::DecomposeRollPitchYawZXYMatrix(rotMatrix, rotX, rotY, rotZ);

		m_quaternion = XMQuaternionRotationRollPitchYaw(rotX, rotY, rotZ);
		m_pxQuaternion.x = m_quaternion.m128_f32[0];
		m_pxQuaternion.y = m_quaternion.m128_f32[1];
		m_pxQuaternion.z = m_quaternion.m128_f32[2];
		m_pxQuaternion.w = m_quaternion.m128_f32[3];
		
		if (m_pxQuaternion.isSane())
		{
			rotX *= RADIANS_TO_DEGRESS;
			rotY *= RADIANS_TO_DEGRESS;
			rotZ *= RADIANS_TO_DEGRESS;
			m_transform->SetWorldRotation(rotX, rotY, rotZ);
		}
	}

	VOID Rigidbody::Render()
	{
	}

	VOID Rigidbody::Release()
	{
		if (m_currentRigidbodyType == CURRENT_RIGIDBODY_TYPE::STATIC)
		{
			PhysxManager::GetInstance()->GetScene()->removeActor(*m_rigidStatic);
			m_rigidStatic->release();
			m_rigidStatic = nullptr;
		}
		else if (m_currentRigidbodyType == CURRENT_RIGIDBODY_TYPE::DYNAMIC)
		{
			PhysxManager::GetInstance()->GetScene()->removeActor(*m_rigidDynamic);
			m_rigidDynamic->release();
			m_rigidDynamic = nullptr;
		}
	}
}