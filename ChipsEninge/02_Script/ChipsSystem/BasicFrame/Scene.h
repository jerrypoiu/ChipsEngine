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
	1. GameObjcet 들이 활동하는 무대의 개념이다.
	2. 연극에서의 씬이라고 생각하면 이해가 편하다.
	3. 사용자들은 Scene을 상속받아 자신만의 Scene을 꾸미거나, 람다식을 사용한 생성방법을 통하여 간단한 씬을 바로 테스트해볼 수 있다.
	4. Scene의 이름, GameObject 추가, 삭제, 찾기 등의 기능을 기본적으로 제공한다.
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
		// GameObject 추가
		VOID AddGameObject(GameObject* _obj);
		// GameObject 삭제 (직접 삭제)
		VOID RemoveGameObject(GameObject* _obj);
		// GameObject 샂게 (Object 이름으로 삭제)
		VOID RemoveGameObject(string _name);
		// GameObject 찾기 (Object 이름으로 찾기)
		GameObject* const FindGameObject(string _name);
	private:
		// _Awake_, _Update_, _FixedUpdate_, _Render_, _Release_의 함수들은 private으로 override(final)되어 있어, 기본적인 씬의 작동이 구현되어 있다.
		// 해당 부분은 사용자가 직접 수정할 수 없다.
		virtual VOID _Awake_() final;
		virtual VOID _Update_() final;
		virtual VOID _FixedUpdate_() final;
		virtual VOID _Render_() final;
		virtual VOID _Release_() final;
	private:
		// 사용자에게는 Awake, Update, FixedUpdate 가상함수들이 제공된다. Render와 Release는 사용자가 추가적인 구현을 제공해 줄 수 없다.
		// 해당 함수들은 사용자들이 Scene에 대한 추가적인 구현을 제공하고 싶을 때, override하여 사용할 수 있다.
		//	ex_) Awake에서는 GameObject를 생성하고, Update에서 Input을 체크...
		virtual VOID Awake();
		virtual VOID Update();
		virtual VOID FixedUpdate();
	};
}
#endif //CHIPSSYSTEM_BASICFRAME_SCENE_H