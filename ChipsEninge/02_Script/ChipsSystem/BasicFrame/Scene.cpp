#include "ChipsSystem/Global/Global.h"
#include "ChipsSystem/BasicFrame/Scene.h"
#include "ChipsSystem/BasicFrame/GameObject.h"
#include "ChipsSystem/Etc/Input.h"
#include "ChipsSystem/Manager/ScheduleManager.h"
#include "ChipsSystem/Manager/LightManager.h"
#include "ChipsSystem/Manager/PhysxManager.h"
#include "ChipsSystem/Manager/ParticleManager.h"
#include "ChipsSystem/Manager/GraphicManager.h"
#include "ChipsSystem/Manager/TextManager.h"
#include "ChipsSystem/Manager/UIManager.h"
#include "ChipsSystem/Camera/Camera.h"
#include "ChipsSystem/Etc/Debug.h"
#include "ChipsSystem/Time/Time.h"

namespace ChipsEngine
{
	Scene::Scene(string _name) : m_name(_name), m_sceneAwake([]() {})
	{
		Debug::Log("Scene Create " + m_name, LOG_TYPE::CREATE_LOG);
		m_objects.resize(0);
	}

	Scene::Scene(string _name, SceneAwake _sceneAwake) : m_name(_name), m_sceneAwake(_sceneAwake)
	{
		Debug::Log("Scene Create " + m_name, LOG_TYPE::CREATE_LOG);
		m_objects.resize(0);
	}

	VOID Scene::AddGameObject(GameObject* _obj)
	{
		IEngineFrame* obj = _obj;
		obj->_Awake_();
		m_objects.emplace_back(obj, [](IEngineFrame* obj) {obj->_Release_(); });
	}

	VOID Scene::RemoveGameObject(GameObject* _obj)
	{
		for (auto it = m_objects.begin(); it != m_objects.end(); it++)
		{
			if (it->get() == _obj)
			{
				m_objects.remove(*it);
				return;
			}
		}
	}

	VOID Scene::RemoveGameObject(string _name)
	{
		RemoveGameObject(FindGameObject(_name));
	}

	GameObject* const Scene::FindGameObject(string _name)
	{
		for (auto const& _obj : m_objects)
		{
			GameObject* obj = static_cast<GameObject*>(_obj.get());
			if (obj->GetName() == _name)
			{
				return obj;
			}
		}
		return nullptr;
	}

	VOID Scene::_Awake_()
	{
		LightManager::GetInstance()->Awake();
		TextManager::GetInstance()->Awake();
		UIManager::GetInstance()->Awake();
		ParticleManager::GetInstance()->Awake();
		PhysxManager::GetInstance()->Awake();
		m_sceneAwake();
		Awake();
	}

	VOID Scene::_Update_()
	{
		Update();
		
		for (auto const& object : m_objects)
		{
			object->_Update_();
		}

		ScheduleManager::GetInstance()->Update();
		ParticleManager::GetInstance()->Update();
		LightManager::GetInstance()->Update();
		Input::Update(Global::g_mouse, Global::g_hwnd);
	}

	VOID Scene::_FixedUpdate_()
	{
		FixedUpdate();

		PhysxManager::GetInstance()->FixedUpdate();
		
		for (auto const& object : m_objects)
		{
			object->_FixedUpdate_();
		}

	}

	VOID Scene::_Render_()
	{
		Camera::GetInstance()->ConstructFrustum();
		LightManager::GetInstance()->Render();
		GraphicManager::GetInstance()->PreSettingToPostProcessing();

		for (auto const& object : m_objects)
		{
			object->_Render_();
		}
		ParticleManager::GetInstance()->Render();
		
		TextManager::GetInstance()->Render();
		GraphicManager::GetInstance()->Render();
		UIManager::GetInstance()->Render();
		PhysxManager::GetInstance()->Render();

		//렌더링 스텐드바이 모드 관련
		HRESULT hr;
		if (Global::g_standByMode)
		{
			hr = Global::g_swapChain->Present(0, DXGI_PRESENT_TEST);

			if (hr == DXGI_STATUS_OCCLUDED)
				return;

			Global::g_standByMode = false; // 스텐바이 모드 해제
		}
		
		hr = Global::g_swapChain->Present(0, 0);

		if (hr == DXGI_STATUS_OCCLUDED)
		{
			Global::g_standByMode = true; // 스텐바이 모드 진입
		}
	}

	VOID Scene::_Release_()
	{
		Debug::Log("Scene Delete " + m_name, LOG_TYPE::DELETE_LOG);
		m_objects.clear();
		ScheduleManager::GetInstance()->Clear();
		PhysxManager::GetInstance()->Clear();
		LightManager::GetInstance()->Clear();
		ParticleManager::GetInstance()->Clear();
		TextManager::GetInstance()->Clear();
		UIManager::GetInstance()->Clear();
		this->~Scene();
	}

	VOID Scene::Awake()
	{
	}

	VOID Scene::Update()
	{

	}

	VOID Scene::FixedUpdate()
	{

	}
}