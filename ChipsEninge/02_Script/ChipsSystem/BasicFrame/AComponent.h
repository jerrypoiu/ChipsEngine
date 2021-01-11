#ifndef CHIPSSYSTEM_BASICFRAME_ACOMPONENET_H
#define CHIPSSYSTEM_BASICFRAME_ACOMPONENET_H
#include "ChipsSystem/BasicFrame/IEngineFrame.h"

namespace ChipsEngine
{
	class GameObject;

	/*
	GameObject의 기능적인 부분을 추가하고 싶을 때 사용되는 클래스입니다.
	예를 들어 렌더링, 소리, 물리 등의 기능을 추가하고 싶을 때 사용되는 클래스입니다.
	*/
	class AComponent abstract : public IEngineFrame
	{
	private:
		bool   m_isActive;
		bool   m_isStart;
		string m_type;
		GameObject* m_gameObject;
	private:
		AComponent(const AComponent&) = delete;
		AComponent(const AComponent&&) = delete;
		AComponent& operator=(const AComponent&) = delete;
		AComponent& operator=(const AComponent&&) = delete;
	public:
		explicit AComponent(string _type);
	protected:
		virtual ~AComponent() = default;
	public:
		inline string GetType()
		{
			return m_type;
		}
		inline VOID SetOwner(GameObject* _owner)
		{
			m_gameObject = _owner;
		}
		inline GameObject* const GetGameObject()
		{
			return m_gameObject;
		}
		inline bool GetActive()
		{
			return m_isActive;
		}
		inline VOID SetActive(bool _active)
		{
			m_isActive = _active;
		}
	private:
		/*
		_Awake_, _Update_, _FixedUpdate_, _Render_ , _Release_ 의 함수들은 private 로
		override(final)되어 있어 기본적인 Component 의 작동이 구현되어 있습니다. 해당
		부분은 사용자가 직접 수정하지 못합니다.
		*/
		virtual VOID _Awake_() final;
		virtual VOID _Update_() final;
		virtual VOID _FixedUpdate_() final;
		virtual VOID _Render_() final;
		virtual VOID _Release_() final;
	private:
		/*
		사용자에게는 Awake, Start, Update, FixedUpdate, Render, Release 가상함수들이
		제공됩니다. 해당 함수들은 사용자들이 Scene 에 대한 추가적인 구현을 제공하고
		싶을 때 override 하여 사용할 수 있습니다.
		*/
		virtual VOID Awake() abstract;
		virtual VOID Start() abstract;
		virtual VOID Update() abstract;
		virtual VOID FixedUpdate() abstract;
		virtual VOID Render() abstract;
		virtual VOID Release() abstract;
	private:
		/*
		OnCollisionEnter, OnCollisionStay, OnCollisionExit, OnTriggerEnter, OnTriggerStay,
		OnTriggerExit 가상 함수들이 제공됩니다. 해당 함수들을 물리적인 충돌에 대한
		행동을 지정될 때 사용됩니다.
		*/
		virtual VOID OnCollisionEnter(GameObject* _coll) override;
		virtual VOID OnCollisionStay(GameObject* _coll) override;
		virtual VOID OnCollisionExit(GameObject* _coll) override;
		virtual VOID OnTriggerEnter(GameObject* _coll) override;
		virtual VOID OnTriggerStay(GameObject* _coll) override;
		virtual VOID OnTriggerExit(GameObject* _coll) override;
	};
}
#endif //CHIPSSYSTEM_BASICFRAME_ACOMPONENET_H