#ifndef CHIPSSYSTEM_COMPONENTS_BASICCOMPONENTS_RIGIDBODY_H
#define CHIPSSYSTEM_COMPONENTS_BASICCOMPONENTS_RIGIDBODY_H
#include "ChipsSystem/BasicFrame/AComponent.h"
#include "ChipsSystem/Manager/PhysxManager.h"

namespace ChipsEngine
{
	class Transform;

	/*
	GameObject �� ������ �������ִ� ������Ʈ�Դϴ�. GameObject �� �߷� ���� ������ �ް� �ʹٸ� �߰��� ����� �Ѵ�. 
	�ش� ������Ʈ�� GameObject �� �߰��ϸ�, StaticRigidbody ���� DynamicRigidbody �� ��ȯ�ȴ�. 
	Physx �� ����Ͽ� ������ ������ ���������� ���ӿ��� �۵��ȴ�.
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
		//�浹ü �߰� (�ڵ����� �̷���� �����ڱ� ���� ȣ������ �ʾƵ� ��)
		VOID AttachShape(PxShape* _shape);
		//�浹ü ���� (�ڵ����� �̷���� �����ڱ� ���� ȣ������ �ʾƵ� ��)
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