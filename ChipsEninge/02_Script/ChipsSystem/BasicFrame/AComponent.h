#ifndef CHIPSSYSTEM_BASICFRAME_ACOMPONENET_H
#define CHIPSSYSTEM_BASICFRAME_ACOMPONENET_H
#include "ChipsSystem/BasicFrame/IEngineFrame.h"

namespace ChipsEngine
{
	class GameObject;

	/*
	GameObject�� ������� �κ��� �߰��ϰ� ���� �� ���Ǵ� Ŭ�����Դϴ�.
	���� ��� ������, �Ҹ�, ���� ���� ����� �߰��ϰ� ���� �� ���Ǵ� Ŭ�����Դϴ�.
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
		_Awake_, _Update_, _FixedUpdate_, _Render_ , _Release_ �� �Լ����� private ��
		override(final)�Ǿ� �־� �⺻���� Component �� �۵��� �����Ǿ� �ֽ��ϴ�. �ش�
		�κ��� ����ڰ� ���� �������� ���մϴ�.
		*/
		virtual VOID _Awake_() final;
		virtual VOID _Update_() final;
		virtual VOID _FixedUpdate_() final;
		virtual VOID _Render_() final;
		virtual VOID _Release_() final;
	private:
		/*
		����ڿ��Դ� Awake, Start, Update, FixedUpdate, Render, Release �����Լ�����
		�����˴ϴ�. �ش� �Լ����� ����ڵ��� Scene �� ���� �߰����� ������ �����ϰ�
		���� �� override �Ͽ� ����� �� �ֽ��ϴ�.
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
		OnTriggerExit ���� �Լ����� �����˴ϴ�. �ش� �Լ����� �������� �浹�� ����
		�ൿ�� ������ �� ���˴ϴ�.
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