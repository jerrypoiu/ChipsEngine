#ifndef CHIPSSYSTEM_BASICFRAME_GAMEOBJECT_H
#define CHIPSSYSTEM_BASICFRAME_GAMEOBJECT_H
#include "ChipsSystem/Etc/ChipsCallbacks.h"
#include "ChipsSystem/Components/BaiscComponents/Rigidbody.h"

namespace ChipsEngine
{
	class Transform;
	class GameObject;

	using SmartComponent = unique_ptr<IEngineFrame, function<void(IEngineFrame*)>>;
	using Components = list<SmartComponent>;
	using TriggerColliders = list <GameObject*>;

	/*
	1. ���� ���� ���� ��� �Ǵ� ������ ���������� �����ϸ� ���ذ� ����.
	2. GameObject�� �̸�, �±�, ���̾�, Transform, Rigidbody(Static)�� �ʼ��� ������ �ִ�.
	3. Tag�� ��쿡�� ��Ÿ�� �߿� SetTag�� ���Ͽ� ������ �� ������, �̸��� Layer�� ������ �� ����.
	   �̸�, Tag, Layer�� �浹ó�� ��� ������Ʈ �ĺ������� ���� �� �ִ�.
	   Ư�� Layer�� Ư�� ���̾�� �浹 �ùķ��̼��� ���� ���θ� ������ �� �ִ�.
	4. SetActive�� ���Ͽ� Ȱ��ȭ�� ������ �� �ִ�.
	5. GameObject�� ����� ���� ������, GameObject�� ����� ���ϰ� �ʹٸ�, Component�� �ٿ��� �Ѵ�.
	   GameObject�� ����� �������� �ʴ� ������, ����ڿ��� Component �߽��� ��� ���� �� ���߽�Ű�� �����̴�.
	6. ����ڵ��� AddComponent, RemoveComponent, GetComponent�� ������Ʈ���� �߰�, ����, �޾ƿ��⸦ ������ �� �ִ�.
	*/
	class GameObject final : public IEngineFrame
	{
	private:
		friend class ChipsEventCallback;
	private:
		bool		 m_isActive;
		string		 m_name;
		string		 m_tag;
		PxU32        m_layer;
		Transform*	 m_transfrom;
		Rigidbody*	 m_rigidbody;
		Components	 m_components;
		TriggerColliders m_triggerColliders;
		const type_info& m_transformType;
		const type_info& m_rigidbodyType;
	private:
		GameObject(const GameObject&) = delete;
		GameObject(const GameObject&&) = delete;
		GameObject& operator=(const GameObject&) = delete;
		GameObject& operator=(const GameObject&&) = delete;
	public:
		explicit GameObject(string _name, string _layer = "Default", string _tag = "");
	private:
		virtual ~GameObject() = default;
	public:
		inline VOID SetTag(string _tag)
		{
			m_tag = _tag;
		}
		inline VOID SetActive(bool _isActive)
		{
			m_isActive = _isActive;
		}
	public:
		inline const string GetName() const
		{
			return m_name;
		}
		inline PxU32 GetLayer()
		{
			return m_layer;
		}
		inline const string GetTag() const
		{
			return m_tag;
		}
		inline bool GetActive() const
		{
			return m_isActive;
		}
	public:
		template <typename T>
		VOID AddComponent()
		{
			if (m_rigidbody != nullptr && m_rigidbodyType == typeid(T))
			{
				static_cast<IEngineFrame*>(m_rigidbody)->_Awake_();
				return;
			}
			else if(m_transfrom != nullptr && m_transformType == typeid(T))
			{
				return;
			}

			AComponent* component = new T();
			component->SetOwner(this);
			IEngineFrame* engineFrame = component;
			engineFrame->_Awake_();
			m_components.emplace_front(engineFrame, [](IEngineFrame* comp) {comp->_Release_(); });
		}
		VOID RemoveComponent(AComponent* _component);
		VOID RemoveComponent(string _componentType);
		template <typename T>
		VOID const RemoveComponent()
		{
			const type_info& _info_T = typeid(T);

			if (m_rigidbodyType == typeid(T))
			{
				Debug::Log("WARNING : You can't remove \"Rigidbody\" Compoenet.", LOG_TYPE::WARING_LOG);
				return;
			}
			else if (m_transformType == typeid(T))
			{
				Debug::Log("WARNING : You can't remove \"Transform\" Compoenet.", LOG_TYPE::WARING_LOG);
				return;
			}

			for (auto it = m_components.begin(); it != m_components.end(); it++)
			{
				if (typeid(*it->get()) == _info_T)
				{
					m_components.remove(*it);
					return;
				}
			}
		}
	public:
		inline Transform* const GetTransform()
		{
			return m_transfrom;
		}
		template <typename T>
		T* const GetComponent()
		{
			const type_info& _info_T = typeid(T);
			for (auto it = m_components.begin(); it != m_components.end(); it++)
			{
				if (typeid(*it->get()) == _info_T)
				{
					return static_cast<T*>(it->get());
				}
			}
			return nullptr;
		}
	private:
		virtual VOID _Awake_() final;
		virtual VOID _Update_() final;
		virtual VOID _FixedUpdate_() final;
		virtual VOID _Render_() final;
		virtual VOID _Release_() final;
	private:
		virtual VOID OnCollisionEnter(GameObject* _coll) final;
		virtual VOID OnCollisionStay(GameObject* _coll) final;
		virtual VOID OnCollisionExit(GameObject* _coll) final;
		virtual VOID OnTriggerEnter(GameObject* _coll) final;
		virtual VOID OnTriggerExit(GameObject* _coll) final;
	};
}
#endif //CHIPSSYSTEM_BASICFRAME_GAMEOBJECT_H