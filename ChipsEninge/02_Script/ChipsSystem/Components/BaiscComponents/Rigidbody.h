#ifndef CHIPSSYSTEM_COMPONENTS_BASICCOMPONENTS_RIGIDBODY_H
#define CHIPSSYSTEM_COMPONENTS_BASICCOMPONENTS_RIGIDBODY_H
#include "ChipsSystem/BasicFrame/AComponent.h"
#include "ChipsSystem/Manager/PhysxManager.h"

namespace ChipsEngine
{
	class Transform;

	/*
	GameObject 에 물리를 적용해주는 컴포넌트입니다. GameObject 가 중력 등의 영향을 받고 싶다면 추가를 해줘야 한다. 
	해당 컴포넌트를 GameObject 에 추가하면, StaticRigidbody 에서 DynamicRigidbody 로 전환된다. 
	Physx 를 사용하여 구현된 물리는 현실적으로 게임에서 작동된다.
	*/
	class Rigidbody final : public AComponent
	{
	private:
		enum class CURRENT_RIGIDBODY_TYPE : char
		{
			NON, STATIC, DYNAMIC
		};
	private:
		PxU32 m_layer;
		XMFLOAT3 m_position;
		XMFLOAT3 m_rotation;
		XMVECTOR m_quaternion;
		PxQuat   m_pxQuaternion;
		Transform* m_transform;
		PxTransform m_pxTransform;
		PxRigidStatic* m_rigidStatic;
		PxRigidDynamic* m_rigidDynamic;
		CURRENT_RIGIDBODY_TYPE m_currentRigidbodyType;
	public:
		Rigidbody();
	protected:
		~Rigidbody() override = default;
	public:
		VOID SetMass(float _mass);		
		VOID SetDrag(float _drag);	
		VOID SetAngularDarg(float _drag);	
		VOID SetFreeze(bool _posX, bool _posY, bool _posZ, bool _rotX, bool _rotY, bool _rotZ);		
		VOID SetKinematic(bool _isActive);		
		VOID SetGravity(bool _isActive);
		VOID SetMassPose(XMFLOAT3 _position);
		VOID SetMassPose(float _x, float _y, float _z);
		VOID SetVelocity(XMVECTOR _velocity);
		VOID SetVelocity(float _velocity, XMVECTOR _direction);
		VOID SetVelocity(XMFLOAT3 _velocity);
		VOID SetVelocity(float _x, float _y, float _z);
		VOID SetVelocity(float _velocity, XMFLOAT3 _direction);
		VOID SetAngularVelocity(XMVECTOR _velocity);
		VOID SetAngularVelocity(float _velocity, XMVECTOR _direction);
		VOID SetAngularVelocity(XMFLOAT3 _velocity);
		VOID SetAngularVelocity(float _x, float _y, float _z);
		VOID SetAngularVelocity(float _velocity, XMFLOAT3 _direction);
		VOID AddTorque(XMVECTOR _torque);
		VOID AddTorque(float _torque, XMVECTOR _direction);
		VOID AddTorque(XMFLOAT3 _torque);
		VOID AddTorque(float _x, float _y, float _z);
		VOID AddTorque(float _torque, XMFLOAT3 _direction);
		VOID AddForce(XMVECTOR _force);
		VOID AddForce(float _force, XMVECTOR _direction);
		VOID AddForce(XMFLOAT3 _force);
		VOID AddForce(float _x, float _y, float _z);
		VOID AddForce(float _force, XMFLOAT3 _direction);
	public:
		//충돌체 추가 (자동으로 이루어짐 개발자까 따로 호출하지 않아도 됨)
		VOID AttachShape(PxShape* _shape);
		//충돌체 삭제 (자동으로 이루어짐 개발자까 따로 호출하지 않아도 됨)
		VOID DettachShape(PxShape* _shape);
	public:
		float GetMass();
		float GetDrag();
		float GetAngularDarg();
		bool GetKinematic();
		bool SetGravity();
		XMFLOAT3 GetMassPose();
		XMFLOAT3 GetVelocity();
		XMFLOAT3 GetAngularVelocity();
	private:
		bool CanCallRigidDynamicFunc();
	private:
		virtual VOID Awake() final;
		virtual	VOID Start() final;
		virtual VOID Update() final;
		virtual VOID FixedUpdate() final;
		virtual VOID Render() final;
		virtual VOID Release() final;
	};
}
#endif //CHIPSSYSTEM_COMPONENTS_BASICCOMPONENTS_RIGIDBODY_H