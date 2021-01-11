#ifndef CHIPSSYSTEM_BASICFRAME_IENGINEFRAME_H
#define CHIPSSYSTEM_BASICFRAME_IENGINEFRAME_H

namespace ChipsEngine
{
	class Application;
	class Scene;
	class GameObject;
	class Sensor;

	/*
	엔진의 기본 뼈대를 이루기 위한 가장  기초적인 클래스입니다.
	사용자가 직접 조작할 상황은 없습니다.
	*/
	class IEngineFrame abstract
	{
		friend class Application;
		friend class Scene;
		friend class GameObject;
		friend class Sensor;
	private:
		// 오브젝트가 생성되고, 딱 한 번 호출되는 함수
		virtual VOID _Awake_() abstract;
		// 매 프레임마다 한 번씩 호출되는 함수
		virtual VOID _Update_() abstract;
		// 물리 엔진의 업데이트 주기마다 한 번씩 호출되는 함수
		virtual VOID _FixedUpdate_() abstract;
		// 매 프레임마다 한 번씩 호출되는 함수, 렌더링을 위해 불러지나, 엔진 사용자가 직접 함수를 Override할 경우는 없음.
		virtual VOID _Render_() abstract;
		//객체가 소멸할 때 호출되는 함수, 사용자 지정 소멸자 이며 멤버변수의 메모리 해제는 여기서 처리해야 함
		virtual VOID _Release_() abstract;
	private:
		//물리적 충돌이 시작 될 때 호출되는 함수
		virtual VOID OnCollisionEnter(GameObject* _coll);
		//물리적 충돌이 지속 될 때 호출되는 함수
		virtual VOID OnCollisionStay(GameObject* _coll);
		//물리적 충돌이 끝날 때 호출되는 함수
		virtual VOID OnCollisionExit(GameObject* _coll);
		//트리거 충돌이 시작 될 때 호출되는 함수
		virtual VOID OnTriggerEnter(GameObject* _coll);
		//트리거 충돌이 지속 될 때 호출되는 함수
		virtual VOID OnTriggerStay(GameObject* _coll);
		//트리거 충돌이 끝날 때 호출되는 함수
		virtual VOID OnTriggerExit(GameObject* _coll);
	};
}

#endif //CHIPSSYSTEM_BASICFRAME_IENGINEFRAME_H
