#ifndef CHIPSSYSTEM_COMPONENETS_COLLIDERCOMPONENETS_ACOLLIDER_H
#define CHIPSSYSTEM_COMPONENETS_COLLIDERCOMPONENETS_ACOLLIDER_H
#include "ChipsSystem/BasicFrame/AComponent.h"
#include "ChipsSystem/Manager/CollisionManager.h"
#include "DirectX/Effects/LightHelper.h"

namespace ChipsEngine
{
	class ACollider abstract : public AComponent
	{
		friend CollisionManager;
#ifdef _DEBUG
	protected:
		bool m_isLoaded;
		UINT m_indexCount;
		Material	  m_material;
		ID3D11Buffer* m_vertexBuffer;
		ID3D11Buffer* m_indexBuffer;
		ID3D11ShaderResourceView* m_diffuseSRV;
#endif
	private:
		CollisionInfo  m_collisionInfo;
		CollsitionEvent m_collisionEnter;
		CollsitionEvent m_collisionStay;
		CollsitionEvent m_collisionExit;
		COLLISION_SHAPE m_collisionShpae;
		COLLISION_LAYER m_collisionLayer;
		map<GameObject*,COLLISION_STATE> m_collisionStates;
	public:
		ACollider(string _componentType);
	protected:
		virtual ~ACollider() = default;
	public:
		VOID SetCollisionEvent(COLLISION_STATE _collisionEventType, CollsitionEvent _collsitionEvent);
		inline VOID SetCollsionLayer(COLLISION_LAYER _collisionLayer)
		{
			m_collisionLayer = _collisionLayer;
		}
		inline COLLISION_LAYER GetCollsionLayer()
		{
			return m_collisionLayer;
		}
	private:
		inline COLLISION_SHAPE GetCollisionShpae()
		{
			return m_collisionShpae;
		}
		VOID CalculateCollisionResult(bool _isCollision,GameObject* _coll);
	protected:
		inline XMFLOAT4 GetCollisionInfoSecondValue()
		{
			return m_collisionInfo.second;
		}
		inline VOID SetCollisionInfoSecondValue(XMFLOAT4 _secondValue)
		{
			m_collisionInfo.second = _secondValue;
		}
		inline VOID SetCollisionShpae(COLLISION_SHAPE _collisionShpae)
		{
			m_collisionShpae = _collisionShpae;
		}
	private:
#ifdef _DEBUG
		virtual VOID InitGemometryBuffer() abstract;
#endif
	protected:
		virtual VOID Init() abstract;
		virtual VOID Update() final;
		virtual VOID Render() final;
		virtual VOID Release() final;
	};
}

#endif //CHIPSSYSTEM_COMPONENETS_COLLIDERCOMPONENETS_ACOLLIDER_H