#ifndef CHIPSSYSTEM_BASICFRAME_SCENE_H
#define CHIPSSYSTEM_BASICFRAME_SCENE_H
#include "ChipsSystem/BasicFrame/GameObject.h"

namespace ChipsEngine
{
	using SmartObject = unique_ptr<IEngineFrame, function<void(IEngineFrame*)>>;
	using Objects = list<SmartObject>;

	using SceneAwake = function<void(void)>;

#define SCENE_AWAKE_DECL []()

	/*
	1. GameObjcet ���� Ȱ���ϴ� ������ �����̴�.
	2. ���ؿ����� ���̶�� �����ϸ� ���ذ� ���ϴ�.
	3. ����ڵ��� Scene�� ��ӹ޾� �ڽŸ��� Scene�� �ٹ̰ų�, ���ٽ��� ����� ��������� ���Ͽ� ������ ���� �ٷ� �׽�Ʈ�غ� �� �ִ�.
	4. Scene�� �̸�, GameObject �߰�, ����, ã�� ���� ����� �⺻������ �����Ѵ�.
	*/
	class Scene : public IEngineFrame
	{
	private:
		string  m_name;
		Objects	m_objects;
		SceneAwake m_sceneAwake;
	private:
		Scene(const Scene&) = delete;
		Scene(const Scene&&) = delete;
		Scene& operator=(const Scene&) = delete;
		Scene& operator=(const Scene&&) = delete;
	public:
		Scene(string _name);
		Scene(string _name, SceneAwake _sceneAwake);
	protected:
		~Scene() = default;
	public:
		inline string GetName() const
		{
			return m_name;
		}
	public:
		// GameObject �߰�
		VOID AddGameObject(GameObject* _obj);
		// GameObject ���� (���� ����)
		VOID RemoveGameObject(GameObject* _obj);
		// GameObject ���� (Object �̸����� ����)
		VOID RemoveGameObject(string _name);
		// GameObject ã�� (Object �̸����� ã��)
		GameObject* const FindGameObject(string _name);
	private:
		// _Awake_, _Update_, _FixedUpdate_, _Render_, _Release_�� �Լ����� private���� override(final)�Ǿ� �־�, �⺻���� ���� �۵��� �����Ǿ� �ִ�.
		// �ش� �κ��� ����ڰ� ���� ������ �� ����.
		virtual VOID _Awake_() final;
		virtual VOID _Update_() final;
		virtual VOID _FixedUpdate_() final;
		virtual VOID _Render_() final;
		virtual VOID _Release_() final;
	private:
		// ����ڿ��Դ� Awake, Update, FixedUpdate �����Լ����� �����ȴ�. Render�� Release�� ����ڰ� �߰����� ������ ������ �� �� ����.
		// �ش� �Լ����� ����ڵ��� Scene�� ���� �߰����� ������ �����ϰ� ���� ��, override�Ͽ� ����� �� �ִ�.
		//	ex_) Awake������ GameObject�� �����ϰ�, Update���� Input�� üũ...
		virtual VOID Awake();
		virtual VOID Update();
		virtual VOID FixedUpdate();
	};
}
#endif //CHIPSSYSTEM_BASICFRAME_SCENE_H