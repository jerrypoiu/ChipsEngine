#include "Demo/Scene/StartScene.h"
#include "ChipsEninge.h"

using namespace ChipsEngine;

namespace Demo
{
	StartScene::StartScene(string _name) : Scene(_name)
	{

	}

	VOID StartScene::Awake()
	{
#pragma region Car
		GameObject* car = new GameObject("car");
		car->AddComponent<Rigidbody>();
		car->AddComponent<BoxCollider>();
		car->GetComponent<BoxCollider>()->SetBoxSize(5.4f, 2.3f, 1.6f);
		car->AddComponent<FbxRenderer>();
		car->GetComponent<FbxRenderer>()->SetRimLightRendering(true);
		car->GetComponent<FbxRenderer>()->LoadMesh("01_Asset/Model/RaceC.fbx");
		car->GetComponent<FbxRenderer>()->AddDiffuseTexture("01_Asset/Texture/RaceC/RaceC.dds");
		car->GetComponent<FbxRenderer>()->AddNormalTexture("01_Asset/Texture/RaceC/RaceCN.dds");
		car->GetComponent<FbxRenderer>()->AddSpecularTexture("01_Asset/Texture/RaceC/RaceCS.dds");

		car->GetComponent<FbxRenderer>()->AddDiffuseTexture("01_Asset/Texture/RaceC/RaceCChassi.dds");
		car->GetComponent<FbxRenderer>()->AddNormalTexture("01_Asset/Texture/RaceC/RaceCChassiN.dds");
		car->GetComponent<FbxRenderer>()->AddSpecularTexture("01_Asset/Texture/RaceC/RaceCChassiS.dds");

		car->GetComponent<FbxRenderer>()->AddDiffuseTexture("01_Asset/Texture/RaceC/RaceCWindows.dds");
		car->GetComponent<FbxRenderer>()->AddNormalTexture("01_Asset/Texture/RegularC/RegularCWindowsN.dds");
		car->GetComponent<FbxRenderer>()->AddSpecularTexture("01_Asset/Texture/RaceC/RaceCWindowsS.dds");
		car->GetComponent<FbxRenderer>()->AddMaterial();
		car->GetComponent<FbxRenderer>()->AddMaterial();
		car->GetComponent<FbxRenderer>()->SetReflect(XMFLOAT4(0.1f, 0.1f, 0.1f, 1.0f), 0);
		car->GetComponent<FbxRenderer>()->SetReflect(XMFLOAT4(0.1f, 0.1f, 0.1f, 1.0f), 1);
		car->GetComponent<FbxRenderer>()->SetReflect(XMFLOAT4(0.25f, 0.25f, 0.25f, 1.0f), 2);
		car->GetTransform()->SetWorldRotation(-90.0f, 0.0f, 0.0f);
		car->GetTransform()->SetWorldPosition(0.0f, 1.5f, 0.0f);
		Application::GetScene()->AddGameObject(car);

		GameObject* wheel1 = new GameObject("wheel");
		wheel1->AddComponent<FbxRenderer>();
		wheel1->GetComponent<FbxRenderer>()->LoadMesh("01_Asset/Model/RaceC.fbx", 2);
		wheel1->GetComponent<FbxRenderer>()->AddDiffuseTexture("01_Asset/Texture/RaceC/RaceC.dds");
		wheel1->GetComponent<FbxRenderer>()->AddNormalTexture("01_Asset/Texture/RaceC/RaceCN.dds");
		wheel1->GetComponent<FbxRenderer>()->AddDiffuseTexture("01_Asset/Texture/RaceC/RaceCChassi.dds");
		wheel1->GetComponent<FbxRenderer>()->AddNormalTexture("01_Asset/Texture/RaceC/RaceCChassiN.dds");
		wheel1->GetComponent<FbxRenderer>()->SetReflect(XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f), 0);
		wheel1->GetTransform()->SetWorldPosition(1.615f, 1.1f, -0.95f);
		wheel1->GetTransform()->SetWorldRotation(-90.0f, 0.0f, 0.0f);
		wheel1->GetTransform()->SetParent(car->GetTransform());
		Application::GetScene()->AddGameObject(wheel1);

		GameObject* wheel2 = new GameObject("wheel");
		wheel2->AddComponent<FbxRenderer>();
		wheel2->GetComponent<FbxRenderer>()->LoadMesh("01_Asset/Model/RaceC.fbx", 2);
		wheel2->GetComponent<FbxRenderer>()->AddDiffuseTexture("01_Asset/Texture/RaceC/RaceC.dds");
		wheel2->GetComponent<FbxRenderer>()->AddNormalTexture("01_Asset/Texture/RaceC/RaceCN.dds");
		wheel2->GetComponent<FbxRenderer>()->AddDiffuseTexture("01_Asset/Texture/RaceC/RaceCChassi.dds");
		wheel2->GetComponent<FbxRenderer>()->AddNormalTexture("01_Asset/Texture/RaceC/RaceCChassiN.dds");
		wheel2->GetComponent<FbxRenderer>()->SetReflect(XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f), 0);
		wheel2->GetTransform()->SetWorldPosition(-1.515f, 1.1f, -0.95f);
		wheel2->GetTransform()->SetWorldRotation(-90.0f, 0.0f, 0.0f);
		wheel2->GetTransform()->SetParent(car->GetTransform());
		Application::GetScene()->AddGameObject(wheel2);

		GameObject* wheel3 = new GameObject("wheel");
		wheel3->AddComponent<FbxRenderer>();
		wheel3->GetComponent<FbxRenderer>()->LoadMesh("01_Asset/Model/RaceC.fbx", 2);
		wheel3->GetComponent<FbxRenderer>()->AddDiffuseTexture("01_Asset/Texture/RaceC/RaceC.dds");
		wheel3->GetComponent<FbxRenderer>()->AddNormalTexture("01_Asset/Texture/RaceC/RaceCN.dds");
		wheel3->GetComponent<FbxRenderer>()->AddDiffuseTexture("01_Asset/Texture/RaceC/RaceCChassi.dds");
		wheel3->GetComponent<FbxRenderer>()->AddNormalTexture("01_Asset/Texture/RaceC/RaceCChassiN.dds");
		wheel3->GetComponent<FbxRenderer>()->SetReflect(XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f), 0);
		wheel3->GetTransform()->SetWorldPosition(1.615f, 1.1f, 0.95f);
		wheel3->GetTransform()->SetWorldRotation(-90.0f, 0.0f, 0.0f);
		wheel3->GetTransform()->SetParent(car->GetTransform());
		Application::GetScene()->AddGameObject(wheel3);

		GameObject* wheel4 = new GameObject("wheel");
		wheel4->AddComponent<FbxRenderer>();
		wheel4->GetComponent<FbxRenderer>()->LoadMesh("01_Asset/Model/RaceC.fbx", 2);
		wheel4->GetComponent<FbxRenderer>()->AddDiffuseTexture("01_Asset/Texture/RaceC/RaceC.dds");
		wheel4->GetComponent<FbxRenderer>()->AddNormalTexture("01_Asset/Texture/RaceC/RaceCN.dds");
		wheel4->GetComponent<FbxRenderer>()->AddDiffuseTexture("01_Asset/Texture/RaceC/RaceCChassi.dds");
		wheel4->GetComponent<FbxRenderer>()->AddNormalTexture("01_Asset/Texture/RaceC/RaceCChassiN.dds");
		wheel4->GetComponent<FbxRenderer>()->SetReflect(XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f), 0);
		wheel4->GetTransform()->SetWorldPosition(-1.515f, 1.1f, 0.95f);
		wheel4->GetTransform()->SetWorldRotation(-90.0f, 0.0f, 0.0f);
		wheel4->GetTransform()->SetParent(car->GetTransform());
		Application::GetScene()->AddGameObject(wheel4);

		car->GetTransform()->SetWorldRotation(-90.0f, 0, -70.0f);
#pragma endregion		

#pragma region Racer
		GameObject* racer = new GameObject("Racer");
		racer->AddComponent<Animator>();
		racer->GetComponent<Animator>()->LoadAnimationClip("HeadShake", "01_Asset/Animation/HeadShake.fbx", 92);
		//racer->GetComponent<Animator>()->LoadAnimationClip("Idle", "01_Asset/Animation/Idle.fbx", 92);
		racer->AddComponent<SkinRenderer>();
		racer->GetComponent<SkinRenderer>()->SetRimLightRendering(true);
		racer->GetComponent<SkinRenderer>()->SetAnimator(racer->GetComponent<Animator>());
		racer->GetComponent<SkinRenderer>()->LoadMesh("01_Asset/Model/Mannequin.fbx");
		racer->GetComponent<SkinRenderer>()->AddDiffuseTexture("01_Asset/Texture/Mannequin/MannequinD.dds");
		racer->GetComponent<SkinRenderer>()->AddSpecularTexture("01_Asset/Texture/Mannequin/MannequinS.dds");
		racer->GetTransform()->SetWorldPosition(2.0f, 1.95f, -2.0f);
		racer->GetTransform()->SetWorldRotation(0.0f, 180.0f, 0.0f);
		racer->GetTransform()->SetWorldScale(0.01f, 0.01f, 0.01f);
		Application::GetScene()->AddGameObject(racer);
#pragma endregion

#pragma region Env
		GameObject* floor = new GameObject("floor");
		floor->AddComponent<PlaneRenderer>();
		floor->AddComponent<PlaneCollider>();
		floor->GetComponent<PlaneCollider>()->SetFloorSize(10.0f, 10.0f);
		floor->GetComponent<PlaneRenderer>()->AddDiffuseTexture("01_Asset/Texture/Asphalt/Asphalt.dds");
		floor->GetComponent<PlaneRenderer>()->AddNormalTexture("01_Asset/Texture/Asphalt/AsphaltN.dds");
		floor->GetComponent<PlaneRenderer>()->SetTextureTiling(10.0f, 10.0f);
		floor->GetTransform()->SetWorldScale(10.0f, 1.0f, 10.0f);
		Application::GetScene()->AddGameObject(floor);

		GameObject* sky = new GameObject("sky");
		sky->AddComponent<SkyRenderer>();
		sky->GetComponent<SkyRenderer>()->LoadTexture("01_Asset/Texture/Skybox/BlueSunset.dds");
		sky->GetComponent<SkyRenderer>()->SetSkyRotationY(120.0f);
		Application::GetScene()->AddGameObject(sky);
#pragma endregion

#pragma region Graphic Setting
		GraphicManager::GetInstance()->SetLimitFps(60);
		//GraphicManager::GetInstance()->SetScreenResolution(1920.0f / 2.1f, 900.0f);
		GraphicManager::GetInstance()->SetScreenResolution(1920.0f/2, 1080.0f/2);
		GraphicManager::GetInstance()->SetPostProcessing(true);
		GraphicManager::GetInstance()->SetRaymarching(false);
		GraphicManager::GetInstance()->SetSSAA(true);
		//GraphicManager::GetInstance()->SetSSAO(true);
		GraphicManager::GetInstance()->SetBloom(true, true, 0.5f);
		GraphicManager::GetInstance()->LoadLutTexture("01_Asset/Texture/Lut/LUT_Fall.dds");
		GraphicManager::GetInstance()->SetLUT(true, 0.25f);
		GraphicManager::GetInstance()->SetGamma(true, 1.2f);
#pragma endregion

		BuildManager::GetInstance()->SetIsRunInBackGround(true);
		Camera::GetInstance()->GetTransform()->SetWorldPosition(0.0f, 1.5f, 0.0f);
		
		ScheduleManager::GetInstance()->AddSchedule("KeyInput",
			SCHEDULE_FUNC_DECL
			{
			   if (Input::GetKeyDown(VK_SPACE))
			   {
				   car->GetTransform()->SetWorldPosition(0.0f, 2.0f, 0.0f);
			   }
			});
	}
	VOID StartScene::Update()
	{
		float speed = 1.0f;

		if (Input::GetMouseButton(0))
		{
			Camera::GetInstance()->GetTransform()->Rotate(Input::GetMouseMove().y * 0.1f, Input::GetMouseMove().x * 0.1f, 0, false);
		}
		if (Input::GetMouseButton(2))
		{
			Camera::GetInstance()->GetTransform()->LootAt(XMFLOAT3(0.0f, 1.5f, 0.0f));
		}

		if (Input::GetKey(VK_SHIFT))
		{
			speed = 10.0f;
		}

		if (Input::GetKey('W'))
		{
			Camera::GetInstance()->GetTransform()->Translate(0.0f, 0.0f, speed * Time::GetDeltaTime());
		}

		if (Input::GetKey('S'))
		{
			Camera::GetInstance()->GetTransform()->Translate(0.0f, 0.0f, -speed * Time::GetDeltaTime());
		}

		if (Input::GetKey('A'))
		{
			Camera::GetInstance()->GetTransform()->Translate(-speed * Time::GetDeltaTime(), 0.0f, 0.0f);
		}

		if (Input::GetKey('D'))
		{
			Camera::GetInstance()->GetTransform()->Translate(speed * Time::GetDeltaTime(), 0.0f, 0.0f);
		}

		if (Input::GetKey('Q'))
		{
			Camera::GetInstance()->GetTransform()->Translate(0.0f, -1.0f * speed * Time::GetDeltaTime(), 0.0f, false);
		}

		if (Input::GetKey('E'))
		{
			Camera::GetInstance()->GetTransform()->Translate(0.0f, 1.0f * speed * Time::GetDeltaTime(), 0.0f, false);
		}
	}
}