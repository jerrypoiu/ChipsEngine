#ifndef CHIPSSYSTEM_MANAGER_EVENTMANAGER_H
#define CHIPSSYSTEM_MANAGER_EVENTMANAGER_H
#include "ChipsSystem/Etc/Singleton.h"
#include "ChipsSystem/BasicFrame/GameObject.h"

namespace ChipsEngine
{
	enum class COLLISION_SHAPE : char
	{
		NON, BOX, SPHERE
	};

	enum class COLLISION_STATE : char
	{
		ENTER, STAY, EXIT
	};

	enum class COLLISION_LAYER : char
	{
		NON_FIXED, FIXED
	};

#define COLLISION_EVENT_DECL [](GameObject* _coll)

	class ACollider;
	using CollisionInfo = pair<ACollider*, XMFLOAT4>;
	using CollsitionEvent = function<void(GameObject*)>;

	class CollisionManager final : public Singletone<CollisionManager>
	{
	private:
		list<CollisionInfo*> m_collisionInfos;
	public:
		CollisionManager() = default;
		~CollisionManager() = default;
	public:
		VOID AddCollision(CollisionInfo* _collisionInfo);
		VOID RemoveCollision(CollisionInfo* _collisionInfo);
	private:
		VOID CheckBoxCollision(XMVECTOR _direction, XMVECTOR _axis, CollisionInfo* _info1, CollisionInfo*_info2, bool& _isCollision);
		VOID CheckSphereCollision(CollisionInfo* _info1, CollisionInfo* _info2, bool& _isCollision);
		VOID CheckCrossCollision(CollisionInfo* _box, CollisionInfo* _sphere, bool& _isCollision);
	public:
		VOID Init();
		VOID Update();
		VOID Clear();
	};
}

#endif //CHIPSSYSTEM_MANAGER_EVENTMANAGER_H