#ifndef CHIPSSYSTEM_COMPONENETS_COLLIDERCOMPONENETS_ACOLLIDER_H
#define CHIPSSYSTEM_COMPONENETS_COLLIDERCOMPONENETS_ACOLLIDER_H
#include "ChipsSystem/BasicFrame/AComponent.h"

namespace ChipsEngine
{
	class Rigidbody;
	/*
		Box, Capsule 등의 Collider 부모 클래스들입니다. 
		기본적으로 충돌체를 만들어주는 클래스이다. (트리거로도 사용할 수 있다.)
	*/
	class ACollider abstract : public AComponent
	{
	#if defined(DEBUG) | defined(_DEBUG)
	protected:
		UINT m_indexCount;
		XMMATRIX m_scaleMatrix;
		XMMATRIX m_offsetMatrix;
		ID3D11Buffer* m_vertexBuffer;
		ID3D11Buffer* m_indexBuffer;
	#endif
	protected:
		bool m_isLoaded;
		bool m_isTrigger;
		PxShape* m_shape;
		XMFLOAT4 m_shapeInfo;
		PxMaterial* m_material;
		Rigidbody* m_rigidbody;
		PxTransform m_pxTransform;
	private:
		float m_staticFriction;
		float m_dynamicFriction;
		float m_restitution;
		XMFLOAT3 m_offset;
	public:
		ACollider(string _componentType);
	protected:
		virtual ~ACollider() = default;
	public:
		VOID SetPhysicsMaterial(float _staticFriction, float _dynamicFriction, float _restitution);
		VOID SetStaticFriction(float _staticFriction);
		VOID SetDynamicFriction(float _dynamicFriction);
		VOID SetRestitution(float _restitution);
		VOID SetOffset(XMFLOAT3 _offset);
		VOID SetOffset(float _x, float _y, float _z);
		VOID SetTrigger(bool _active);
		inline float GetStaticFriction()
		{
			return m_staticFriction;
		}
		inline float GetDynamicFriction()
		{
			return m_dynamicFriction;
		}
		inline float GetRestitution()
		{
			return m_restitution;
		}
		inline XMFLOAT3 GetOffset()
		{
			return m_offset;
		}
		inline bool GetIsTrigger()
		{
			return m_isTrigger;
		}
	private:
		virtual VOID InitShape() abstract;
		virtual VOID ResetShape() abstract;
	protected:
		virtual VOID Awake() final;
		virtual	VOID Start() final;
		virtual VOID Update() final;
		virtual VOID FixedUpdate() final;
		virtual VOID Render() final;
		virtual VOID Release() final;
	};
}

#endif //CHIPSSYSTEM_COMPONENETS_COLLIDERCOMPONENETS_ACOLLIDER_H