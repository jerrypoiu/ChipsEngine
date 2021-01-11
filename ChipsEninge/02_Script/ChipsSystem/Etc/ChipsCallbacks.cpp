#include "ChipsSystem/Etc/ChipsCallbacks.h"
#include "ChipsSystem/BasicFrame/GameObject.h"
#include "ChipsSystem/BasicFrame/AComponent.h"
#include "ChipsSystem/Components/BaiscComponents/Rigidbody.h"
#include "ChipsSystem/Etc/LayerMask.h"

namespace ChipsEngine
{
	void ChipsEventCallback::onConstraintBreak(PxConstraintInfo* constraints, PxU32 count)
	{
	}

	void ChipsEventCallback::onWake(PxActor** actors, PxU32 count)
	{
	}

	void ChipsEventCallback::onSleep(PxActor** actors, PxU32 count)
	{
	}

	void ChipsEventCallback::onContact(const PxContactPairHeader& pairHeader, const PxContactPair* pairs, PxU32 nbPairs)
	{
		GameObject* gameObject1 = ((GameObject*)pairHeader.actors[0]->userData);
		GameObject* gameObject2 = ((GameObject*)pairHeader.actors[1]->userData);

		if (pairs->events.isSet(PxPairFlag::eNOTIFY_TOUCH_FOUND))
		{
			gameObject1->OnCollisionEnter(gameObject2);
			gameObject2->OnCollisionEnter(gameObject1);
		}
		else if (pairs->events.isSet(PxPairFlag::eNOTIFY_TOUCH_PERSISTS))
		{
			gameObject1->OnCollisionStay(gameObject2);
			gameObject2->OnCollisionStay(gameObject1);
		}
		else if (pairs->events.isSet(PxPairFlag::eNOTIFY_TOUCH_LOST))
		{
			gameObject1->OnCollisionExit(gameObject2);
			gameObject2->OnCollisionExit(gameObject1);
		}
	}

	void ChipsEventCallback::onTrigger(PxTriggerPair* pairs, PxU32 count)
	{
		GameObject* gameObject1 = ((GameObject*)pairs->triggerActor->userData);
		GameObject* gameObject2 = ((GameObject*)pairs->otherActor->userData);

		if (pairs->status & PxPairFlag::eNOTIFY_TOUCH_FOUND)
		{
			gameObject1->OnTriggerEnter(gameObject2);
			gameObject2->OnTriggerEnter(gameObject1);
		}
		else if (pairs->status & PxPairFlag::eNOTIFY_TOUCH_LOST)
		{
			gameObject1->OnTriggerExit(gameObject2);
			gameObject2->OnTriggerExit(gameObject1);
		}
	}

	void ChipsEventCallback::onAdvance(const PxRigidBody*const* bodyBuffer, const PxTransform* poseBuffer, const PxU32 count)
	{
	}

	PxFilterFlags ChipsFillterCallback::pairFound(PxU32 pairID,
		PxFilterObjectAttributes attributes0, PxFilterData filterData0, const PxActor* a0, const PxShape* s0,
		PxFilterObjectAttributes attributes1, PxFilterData filterData1, const PxActor* a1, const PxShape* s1,
		PxPairFlags& pairFlags)
	{
		pairFlags |= PxPairFlag::eNOTIFY_TOUCH_PERSISTS | PxPairFlag::eNOTIFY_TOUCH_LOST;
		return PxFilterFlag::eCALLBACK | PxFilterFlag::eNOTIFY;
	}

	void ChipsFillterCallback::pairLost(PxU32 pairID, PxFilterObjectAttributes attributes0, PxFilterData filterData0,
		PxFilterObjectAttributes attributes1, PxFilterData filterData1, bool objectRemoved)
	{
	}

	bool ChipsFillterCallback::statusChange(PxU32& pairID, PxPairFlags& pairFlags, PxFilterFlags& filterFlags)
	{
		return false;
	}

	
	PxFilterFlags ChipsSimulationFilterShader(PxFilterObjectAttributes attributes0, PxFilterData filterData0,
											  PxFilterObjectAttributes attributes1, PxFilterData filterData1,
											  PxPairFlags& pairFlags, const void* constantBlock, PxU32 constantBlockSize)
	{
		//필터링
		if (LayerMask::IsCanCollision(filterData0.word0, filterData1.word0) != 0)
		{
			//트리거 처리
			if (PxFilterObjectIsTrigger(attributes0) || PxFilterObjectIsTrigger(attributes1))
			{
				pairFlags = PxPairFlag::eTRIGGER_DEFAULT;
			}
			else
			{
				pairFlags = PxPairFlag::eCONTACT_DEFAULT;
			}

			pairFlags |= PxPairFlag::eNOTIFY_TOUCH_FOUND;
		}
		else
		{
			return PxFilterFlag::eKILL;
		}

		return PxFilterFlag::eCALLBACK;
	}
}