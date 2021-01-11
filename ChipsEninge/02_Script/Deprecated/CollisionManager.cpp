#include "ChipsSystem/Manager/CollisionManager.h"
#include "ChipsSystem/Components/ColliderComponents/ACollider.h"
#include "ChipsSystem/Components/ColliderComponents/BoxCollider.h"
#include "ChipsSystem/Components/ColliderComponents/SphereCollider.h"
#include "ChipsSystem/Etc/Mathf.h"

using namespace DirectX;

namespace ChipsEngine
{
	VOID CollisionManager::AddCollision(CollisionInfo* _collisionInfo)
	{
		m_collisionInfos.emplace_back(_collisionInfo);
	}

	VOID CollisionManager::RemoveCollision(CollisionInfo* _collisionInfo)
	{
		m_collisionInfos.remove(_collisionInfo);
	}

	VOID CollisionManager::CheckBoxCollision(XMVECTOR _direction, XMVECTOR _axis, CollisionInfo* _info1, CollisionInfo*_info2, bool& _isCollision)
	{
		float distance = Mathf::Abs(Mathf::Dot(_direction, _axis));

		Transform* trs1 = _info1->first->GetGameObject()->GetTransform();
		Transform* trs2 = _info2->first->GetGameObject()->GetTransform();
		XMFLOAT4 size1 = _info1->second;
		XMFLOAT4 size2 = _info2->second;

		XMVECTOR vector1 = XMVector3Cross(trs1->GetRight() * size1.x * 0.5f, trs2->GetRight() * size2.x * 0.5f);
		XMVECTOR vector2 = XMVector3Cross(trs1->GetRight() * size1.x * 0.5f, trs2->GetForward() * size2.z * 0.5f);
		XMVECTOR vector3 = XMVector3Cross(trs1->GetRight() * size1.x * 0.5f, trs2->GetUp() * size2.y * 0.5f);

		XMVECTOR vector4 = XMVector3Cross(trs1->GetUp() * size1.y * 0.5f, trs2->GetRight() * size2.x * 0.5f);
		XMVECTOR vector5 = XMVector3Cross(trs1->GetUp() * size1.y * 0.5f, trs2->GetForward() * size2.z * 0.5f);
		XMVECTOR vector6 = XMVector3Cross(trs1->GetUp() * size1.y * 0.5f, trs2->GetUp() * size2.y * 0.5f);

		XMVECTOR vector7 = XMVector3Cross(trs1->GetForward() * size1.z * 0.5f, trs2->GetRight() * size2.x * 0.5f);
		XMVECTOR vector8 = XMVector3Cross(trs1->GetForward() * size1.z * 0.5f, trs2->GetForward() * size2.z * 0.5f);
		XMVECTOR vector9 = XMVector3Cross(trs1->GetForward() * size1.z * 0.5f, trs2->GetUp() * size2.y * 0.5f);

		if (distance >
			Mathf::Abs(Mathf::Dot(_axis, trs1->GetUp() * size1.y * 0.5f))
			+ Mathf::Abs(Mathf::Dot(_axis, trs1->GetRight() * size1.x  * 0.5f))
			+ Mathf::Abs(Mathf::Dot(_axis, trs1->GetForward() * size1.z * 0.5f))
			+ Mathf::Abs(Mathf::Dot(_axis, trs2->GetUp() * size2.y * 0.5f))
			+ Mathf::Abs(Mathf::Dot(_axis, trs2->GetRight() * size2.x  * 0.5f))
			+ Mathf::Abs(Mathf::Dot(_axis, trs2->GetForward() * size2.z * 0.5f)))
		{
			_isCollision = false;
		}
	}

	VOID CollisionManager::CheckSphereCollision(CollisionInfo* _info1, CollisionInfo* _info2, bool& _isCollision)
	{
		float radius1 = _info1->second.w;
		float radius2 = _info2->second.w;
		XMFLOAT3 object1PosFloat3 = _info1->first->GetGameObject()->GetTransform()->GetWorldPosition();
		XMFLOAT3 object2PosFloat3 = _info2->first->GetGameObject()->GetTransform()->GetWorldPosition();
			
		float distance = Mathf::Sqrt(Mathf::Pow(object1PosFloat3.x - object2PosFloat3.x)
									 + Mathf::Pow(object1PosFloat3.y - object2PosFloat3.y)
									 + Mathf::Pow(object1PosFloat3.z - object2PosFloat3.z)); 

		_isCollision = ((radius1 + radius2) >= distance);
	}

	VOID CollisionManager::CheckCrossCollision(CollisionInfo* _box, CollisionInfo* _sphere, bool& _isCollision)
	{
		Transform* boxTrs = _box->first->GetGameObject()->GetTransform();
		Transform* sphereTrs = _sphere->first->GetGameObject()->GetTransform();
		
		XMMATRIX boxRotationInverseMatrix = XMMatrixTranspose(boxTrs->GetWorldRotationMatrix());
		XMMATRIX boxTranslationInverseMatrix = boxTrs->GetWorldTranslationMatrix();
		boxTranslationInverseMatrix.r[3].m128_f32[0] *= -1;
		boxTranslationInverseMatrix.r[3].m128_f32[1] *= -1;
		boxTranslationInverseMatrix.r[3].m128_f32[2] *= -1;
		XMMATRIX boxViewMatrix = boxTranslationInverseMatrix * boxRotationInverseMatrix;

		XMMATRIX sphrereMatrix = sphereTrs->GetWorldMatrix() * boxViewMatrix;

		XMFLOAT3 boxPosition = boxTrs->GetWorldPosition();
		XMFLOAT3 spherePosition = XMFLOAT3();
		spherePosition.x = sphrereMatrix.r[3].m128_f32[0];
		spherePosition.y = sphrereMatrix.r[3].m128_f32[1];
		spherePosition.z = sphrereMatrix.r[3].m128_f32[2];

		XMFLOAT4 boxSize = _box->second;
		XMFLOAT4 sphereSize = _sphere->second;

		XMVECTOR rightVector = XMLoadFloat3(new XMFLOAT3(1.0f, 0.0f, 0.0f));
		XMVECTOR upVector = XMLoadFloat3(new XMFLOAT3(0.0f, 1.0f, 0.0f));
		XMVECTOR forwardVector = XMLoadFloat3(new XMFLOAT3(0.0f, 0.0f, 1.0f));

		XMVECTOR temp = (rightVector * boxSize.x + upVector * boxSize.y + forwardVector * boxSize.z) * -0.5f;
		XMFLOAT3 boxMinCorner = XMFLOAT3();
		XMStoreFloat3(&boxMinCorner, temp);

		temp = (rightVector * boxSize.x + upVector * boxSize.y + forwardVector * boxSize.z) * 0.5f;
		XMFLOAT3 boxMaxCorner = XMFLOAT3();
		XMStoreFloat3(&boxMaxCorner, temp);

		XMFLOAT3 closestPosition = XMFLOAT3();
		closestPosition.x = max(boxMinCorner.x, min(spherePosition.x, boxMaxCorner.x));
		closestPosition.y = max(boxMinCorner.y, min(spherePosition.y, boxMaxCorner.y));
		closestPosition.z = max(boxMinCorner.z, min(spherePosition.z, boxMaxCorner.z));
		
		float distance = Mathf::Sqrt(Mathf::Pow(closestPosition.x - spherePosition.x)
								   + Mathf::Pow(closestPosition.y - spherePosition.y)
								   + Mathf::Pow(closestPosition.z - spherePosition.z));


		distance = round(distance * 100) * 0.01f;		
		_isCollision = (distance <= sphereSize.w);
	}

	VOID CollisionManager::Init()
	{
		m_collisionInfos.resize(0);
	}

	VOID CollisionManager::Update()
	{
		for (auto iter1 = m_collisionInfos.begin(); iter1 != m_collisionInfos.end(); iter1++)
		{
			for (auto iter2 = next(iter1, 1); iter2 != m_collisionInfos.end(); iter2++)
			{		
				if ((*iter1)->first->GetCollsionLayer() == COLLISION_LAYER::FIXED
					&& (*iter2)->first->GetCollsionLayer() == COLLISION_LAYER::FIXED)
				{
					continue;
				}
				
				bool isCollision = false;

				//Sphere
				CheckSphereCollision(*iter1, *iter2, isCollision);

				if (isCollision)
				{
					Transform* trs1 = (*iter1)->first->GetGameObject()->GetTransform();
					Transform* trs2 = (*iter2)->first->GetGameObject()->GetTransform();
					XMVECTOR worldPosition1 = trs1->GetWorldTranslationMatrix().r[3];
					XMVECTOR worldPosition2 = trs2->GetWorldTranslationMatrix().r[3];
					XMVECTOR direction = worldPosition1 - worldPosition2;

					// Box
					if ((*iter1)->first->GetCollisionShpae() == COLLISION_SHAPE::BOX
						&& (*iter2)->first->GetCollisionShpae() == COLLISION_SHAPE::BOX)
					{
						Transform* trs1 = (*iter1)->first->GetGameObject()->GetTransform();
						Transform* trs2 = (*iter2)->first->GetGameObject()->GetTransform();
						XMFLOAT4 size1 = (*iter1)->second;
						XMFLOAT4 size2 = (*iter2)->second;

						XMVECTOR vector1 = XMVector3Cross(trs1->GetRight() * size1.x * 0.5f, trs2->GetRight() * size2.x * 0.5f);
						XMVECTOR vector2 = XMVector3Cross(trs1->GetRight() * size1.x * 0.5f, trs2->GetForward() * size2.z * 0.5f);
						XMVECTOR vector3 = XMVector3Cross(trs1->GetRight() * size1.x * 0.5f, trs2->GetUp() * size2.y * 0.5f);

						XMVECTOR vector4 = XMVector3Cross(trs1->GetUp() * size1.y * 0.5f, trs2->GetRight() * size2.x * 0.5f);
						XMVECTOR vector5 = XMVector3Cross(trs1->GetUp() * size1.y * 0.5f, trs2->GetForward() * size2.z * 0.5f);
						XMVECTOR vector6 = XMVector3Cross(trs1->GetUp() * size1.y * 0.5f, trs2->GetUp() * size2.y * 0.5f);

						XMVECTOR vector7 = XMVector3Cross(trs1->GetForward() * size1.z * 0.5f, trs2->GetRight() * size2.x * 0.5f);
						XMVECTOR vector8 = XMVector3Cross(trs1->GetForward() * size1.z * 0.5f, trs2->GetForward() * size2.z * 0.5f);
						XMVECTOR vector9 = XMVector3Cross(trs1->GetForward() * size1.z * 0.5f, trs2->GetUp() * size2.y * 0.5f);

						CheckBoxCollision(direction, trs1->GetUp(), (*iter1), (*iter2), isCollision);
						CheckBoxCollision(direction, trs2->GetUp(), (*iter1), (*iter2), isCollision);
					
						CheckBoxCollision(direction, trs1->GetRight(), (*iter1), (*iter2), isCollision);
						CheckBoxCollision(direction, trs2->GetRight(), (*iter1), (*iter2), isCollision);
					
						CheckBoxCollision(direction, trs1->GetForward(), (*iter1), (*iter2), isCollision);
						CheckBoxCollision(direction, trs2->GetForward(), (*iter1), (*iter2), isCollision);

						CheckBoxCollision(direction, vector1, (*iter1), (*iter2), isCollision);
						CheckBoxCollision(direction, vector2, (*iter1), (*iter2), isCollision);
						CheckBoxCollision(direction, vector3, (*iter1), (*iter2), isCollision);

						CheckBoxCollision(direction, vector4, (*iter1), (*iter2), isCollision);
						CheckBoxCollision(direction, vector5, (*iter1), (*iter2), isCollision);
						CheckBoxCollision(direction, vector6, (*iter1), (*iter2), isCollision);

						CheckBoxCollision(direction, vector7, (*iter1), (*iter2), isCollision);
						CheckBoxCollision(direction, vector8, (*iter1), (*iter2), isCollision);
						CheckBoxCollision(direction, vector9, (*iter1), (*iter2), isCollision);
					}
					// Cross
					else if((*iter1)->first->GetCollisionShpae() != COLLISION_SHAPE::SPHERE
							|| (*iter2)->first->GetCollisionShpae() != COLLISION_SHAPE::SPHERE)
					{
						if ((*iter1)->first->GetCollisionShpae() == COLLISION_SHAPE::BOX)
						{
							CheckCrossCollision((*iter1), (*iter2), isCollision);
						}
						else
						{
							CheckCrossCollision((*iter2), (*iter1), isCollision);
						}
					}
				}

				(*iter1)->first->CalculateCollisionResult(isCollision, (*iter2)->first->GetGameObject());
				(*iter2)->first->CalculateCollisionResult(isCollision, (*iter1)->first->GetGameObject());
			}
		}
	}

	VOID CollisionManager::Clear()
	{
		m_collisionInfos.clear();
	}
}