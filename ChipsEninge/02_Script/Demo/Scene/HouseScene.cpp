#include "Demo/Scene/HouseScene.h"
#include "ChipsEninge.h"

using namespace ChipsEngine;

//Reflection Probe 추가
//Fbx 다시 찍기

namespace Demo
{
	HouseScene::HouseScene(string _name) : Scene(_name)
	{

	}

	VOID HouseScene::Awake()
	{
#pragma region Sky
		GameObject* sky = new GameObject("sky");
		sky->AddComponent<SkyRenderer>();
		sky->GetComponent<SkyRenderer>()->LoadTexture("01_Asset/Texture/Skybox/BlueSunset.dds");
		sky->GetComponent<SkyRenderer>()->SetSkyRotationY(0.0f);
		Application::GetScene()->AddGameObject(sky);
#pragma endregion

#pragma region Person
		GameObject* Mannequin = new GameObject("Mannequin");
		Mannequin->AddComponent<Animator>();
		Mannequin->GetComponent<Animator>()->LoadAnimationClip("HeadShake", "01_Asset/Animation/Sitting Idle.fbx");
		Mannequin->AddComponent<SkinRenderer>();
		Mannequin->GetComponent<SkinRenderer>()->SetRimLightRendering(true);
		Mannequin->GetComponent<SkinRenderer>()->SetAnimator(Mannequin->GetComponent<Animator>());
		Mannequin->GetComponent<SkinRenderer>()->LoadMesh("01_Asset/Model/Mannequin.fbx");
		Mannequin->GetComponent<SkinRenderer>()->AddDiffuseTexture("01_Asset/Texture/Mannequin/MannequinD.dds");
		Mannequin->GetComponent<SkinRenderer>()->AddSpecularTexture("01_Asset/Texture/Mannequin/MannequinS.dds");
		Mannequin->GetTransform()->SetWorldPosition(4.3f, 1.2f, 0.0f);
		Mannequin->GetTransform()->SetWorldRotation(0.0f, -130.0f, 0.0f);
		Mannequin->GetTransform()->SetWorldScale(0.01f, 0.01f, 0.01f);
		Application::GetScene()->AddGameObject(Mannequin);
#pragma endregion

#pragma region House
		GameObject* house = new GameObject("house");

		GameObject* House_Wall = new GameObject("House_Wall");
		House_Wall->AddComponent<FbxRenderer>();
		House_Wall->GetComponent<FbxRenderer>()->LoadMesh("01_Asset/Model/House/House.fbx", 0);
		House_Wall->GetComponent<FbxRenderer>()->AddDiffuseTexture("01_Asset/Texture/Furniture/House_Chair.dds");
		House_Wall->GetComponent<FbxRenderer>()->AddSpecularTexture("01_Asset/Texture/Furniture/House_Chair_Roughness.dds");
		House_Wall->GetComponent<FbxRenderer>()->SetTextureTiling(0.2f, 0.2f);
		House_Wall->GetComponent<FbxRenderer>()->SetAmbient(XMFLOAT4(0.6f, 0.6f, 0.6f, 1.0f));
		House_Wall->GetTransform()->SetParent(house->GetTransform());
		Application::GetScene()->AddGameObject(House_Wall);

		GameObject* House_Windows_Ceiling_Frame = new GameObject("House_Windows_Ceiling_Frame");
		House_Windows_Ceiling_Frame->AddComponent<FbxRenderer>();
		House_Windows_Ceiling_Frame->GetComponent<FbxRenderer>()->LoadMesh("01_Asset/Model/House/House.fbx", 1);
		House_Windows_Ceiling_Frame->GetComponent<FbxRenderer>()->AddDiffuseTexture("01_Asset/Texture/House/House_Windows_Ceiling_Frame.dds");
		House_Windows_Ceiling_Frame->GetComponent<FbxRenderer>()->AddNormalTexture("01_Asset/Texture/House/House_Windows_Ceiling_Frame_Normals.dds");
		House_Windows_Ceiling_Frame->GetTransform()->SetParent(house->GetTransform());
		House_Windows_Ceiling_Frame->GetTransform()->SetLocalPosition(0.0f, 0.0f, -0.05f);
		Application::GetScene()->AddGameObject(House_Windows_Ceiling_Frame);
 
		GameObject* House_Floor_01 = new GameObject("House_Floor_01");
		House_Floor_01->AddComponent<FbxRenderer>();
		House_Floor_01->GetComponent<FbxRenderer>()->LoadMesh("01_Asset/Model/House/House.fbx", 2);
		House_Floor_01->GetComponent<FbxRenderer>()->AddDiffuseTexture("01_Asset/Texture/House/House_Floor_01.dds");
		House_Floor_01->GetComponent<FbxRenderer>()->AddNormalTexture("01_Asset/Texture/House/House_Floor_01_Normals.dds");
		House_Floor_01->GetComponent<FbxRenderer>()->AddSpecularTexture("01_Asset/Texture/House/House_Floor_01_Roughness.dds.dds");
		House_Floor_01->GetComponent<FbxRenderer>()->SetReflect(XMFLOAT4(0.1f, 0.1f, 0.1f, 1.0f));
		House_Floor_01->GetTransform()->SetParent(house->GetTransform());
		Application::GetScene()->AddGameObject(House_Floor_01);

		GameObject* House_Floor_02 = new GameObject("House_Floor_02");
		House_Floor_02->AddComponent<FbxRenderer>();
		House_Floor_02->GetComponent<FbxRenderer>()->LoadMesh("01_Asset/Model/House/House.fbx", 4);
		House_Floor_02->GetComponent<FbxRenderer>()->AddDiffuseTexture("01_Asset/Texture/Furniture/House_Chair.dds");
		House_Floor_02->GetComponent<FbxRenderer>()->AddSpecularTexture("01_Asset/Texture/Furniture/House_Chair_Roughness.dds");
		House_Floor_02->GetComponent<FbxRenderer>()->SetTextureTiling(0.2f, 0.2f);
		House_Floor_02->GetComponent<FbxRenderer>()->SetAmbient(XMFLOAT4(0.5f, 0.5f, 0.5f, 1.0f));
		House_Floor_02->GetTransform()->SetParent(house->GetTransform());
		House_Floor_02->GetTransform()->SetLocalPosition(0.0f, 0.0f, 1.75f);
		Application::GetScene()->AddGameObject(House_Floor_02);

		GameObject* House_Floor_03 = new GameObject("House_Floor_03");
		House_Floor_03->AddComponent<FbxRenderer>();
		House_Floor_03->GetComponent<FbxRenderer>()->LoadMesh("01_Asset/Model/House/House.fbx", 4);
		House_Floor_03->GetComponent<FbxRenderer>()->AddDiffuseTexture("01_Asset/Texture/Furniture/House_Chair.dds");
		House_Floor_03->GetComponent<FbxRenderer>()->AddSpecularTexture("01_Asset/Texture/Furniture/House_Chair_Roughness.dds");
		House_Floor_03->GetComponent<FbxRenderer>()->SetTextureTiling(0.2f, 0.2f);
		House_Floor_03->GetComponent<FbxRenderer>()->SetAmbient(XMFLOAT4(0.5f, 0.5f, 0.5f, 1.0f));
		House_Floor_03->GetTransform()->SetParent(house->GetTransform());
		House_Floor_03->GetTransform()->SetLocalPosition(0.0f, 6.00f, 1.75f);
		Application::GetScene()->AddGameObject(House_Floor_03);

		GameObject* House_Windows_Frame = new GameObject("House_Windows_Frame");
		House_Windows_Frame->AddComponent<FbxRenderer>();
		House_Windows_Frame->GetComponent<FbxRenderer>()->LoadMesh("01_Asset/Model/House/House.fbx", 5);
		House_Windows_Frame->GetComponent<FbxRenderer>()->AddDiffuseTexture("01_Asset/Texture/House/House_Wall.dds");
		House_Windows_Frame->GetTransform()->SetParent(house->GetTransform());
		House_Windows_Frame->GetTransform()->SetLocalPosition(-1.175f, -4.75f, 2.92f);
		Application::GetScene()->AddGameObject(House_Windows_Frame);

		GameObject* House_Windows_Black = new GameObject("House_Windows_Black");
		House_Windows_Black->AddComponent<FbxRenderer>();
		House_Windows_Black->GetComponent<FbxRenderer>()->LoadMesh("01_Asset/Model/House/House.fbx", 6);
		House_Windows_Black->GetComponent<FbxRenderer>()->AddDiffuseTexture("01_Asset/Texture/House/House_Windows_Black.dds");
		House_Windows_Black->GetComponent<FbxRenderer>()->SetMakeShadow(false);
		House_Windows_Black->GetTransform()->SetParent(house->GetTransform());
		House_Windows_Black->GetTransform()->SetLocalPosition(-1.175f, -4.75f, 2.92f);
		Application::GetScene()->AddGameObject(House_Windows_Black);

		GameObject* House_Wallpaper = new GameObject("House_Wallpaper");
		House_Wallpaper->AddComponent<FbxRenderer>();
		House_Wallpaper->GetComponent<FbxRenderer>()->LoadMesh("01_Asset/Model/House/House.fbx", 8);
		House_Wallpaper->GetComponent<FbxRenderer>()->AddDiffuseTexture("01_Asset/Texture/House/House_Wallpaper.dds");
		House_Wallpaper->GetComponent<FbxRenderer>()->SetAmbient(XMFLOAT4(0.8f, 0.8f, 0.8f, 1.0f));
		House_Wallpaper->GetComponent<FbxRenderer>()->SetSpecular(XMFLOAT4(0.8f, 0.8f, 0.8f, 64.0f));
		House_Wallpaper->GetTransform()->SetParent(house->GetTransform());
		House_Wallpaper->GetTransform()->SetLocalPosition(-3.825f, -2.00f, 1.25f);
		Application::GetScene()->AddGameObject(House_Wallpaper);

		GameObject* House_Wallpaper_01 = new GameObject("House_Wallpaper_01");
		House_Wallpaper_01->AddComponent<FbxRenderer>();
		House_Wallpaper_01->GetComponent<FbxRenderer>()->LoadMesh("01_Asset/Model/House/House.fbx", 9);
		House_Wallpaper_01->GetComponent<FbxRenderer>()->AddDiffuseTexture("01_Asset/Texture/House/House_Wallpaper_01.dds");
		House_Wallpaper_01->GetComponent<FbxRenderer>()->SetAmbient(XMFLOAT4(0.5f, 0.5f, 0.5f, 1.0f));
		House_Wallpaper_01->GetTransform()->SetParent(house->GetTransform());
		Application::GetScene()->AddGameObject(House_Wallpaper_01);

		GameObject* House_Windows_Ceiling_Glass = new GameObject("House_Windows_Ceiling_Glass");
		House_Windows_Ceiling_Glass->AddComponent<FbxRenderer>();
		House_Windows_Ceiling_Glass->GetComponent<FbxRenderer>()->LoadMesh("01_Asset/Model/House/House.fbx", 10);
		House_Windows_Ceiling_Glass->GetComponent<FbxRenderer>()->AddDiffuseTexture("01_Asset/Texture/House/House_Windows_Glass.dds");
		House_Windows_Ceiling_Glass->GetComponent<FbxRenderer>()->SetMakeShadow(false);
		House_Windows_Ceiling_Glass->GetTransform()->SetParent(house->GetTransform());
		House_Windows_Ceiling_Glass->GetTransform()->SetLocalPosition(2.50f, -0.80f, 2.60f);
		Application::GetScene()->AddGameObject(House_Windows_Ceiling_Glass);

		GameObject* House_Ceiling = new GameObject("House_Ceiling");
		House_Ceiling->AddComponent<PlaneRenderer>();
		House_Ceiling->GetComponent<PlaneRenderer>()->AddDiffuseTexture("01_Asset/Texture/House/House_Wall.dds");
		House_Ceiling->GetTransform()->SetParent(house->GetTransform());
		House_Ceiling->GetTransform()->SetLocalScale(2000.0f, 1000.0f, 1600.0f);
		House_Ceiling->GetTransform()->SetLocalRotation(90.0f, 0.0f, 0.0f);
		House_Ceiling->GetTransform()->SetLocalPosition(0.0f, 2.80f, 2.80f);
		Application::GetScene()->AddGameObject(House_Ceiling);

		GameObject* House_Left_Wall = new GameObject("House_Left_Wall");
		House_Left_Wall->AddComponent<PlaneRenderer>();
		House_Left_Wall->GetComponent<PlaneRenderer>()->AddDiffuseTexture("01_Asset/Texture/House/House_Wall.dds");
		House_Left_Wall->GetTransform()->SetParent(house->GetTransform());
		House_Left_Wall->GetTransform()->SetLocalScale(1000.0f, 1000.0f, 1500.0f);
		House_Left_Wall->GetTransform()->SetLocalRotation(90.0f, 0.0f, -90.0f);
		House_Left_Wall->GetTransform()->SetLocalPosition(4.00f, 2.80f, 2.80f);
		Application::GetScene()->AddGameObject(House_Left_Wall);

		GameObject* House_Right_Wall = new GameObject("House_Right_Wall");
		House_Right_Wall->AddComponent<PlaneRenderer>();
		House_Right_Wall->GetComponent<PlaneRenderer>()->AddDiffuseTexture("01_Asset/Texture/House/House_Wall.dds");
		House_Right_Wall->GetTransform()->SetParent(house->GetTransform());
		House_Right_Wall->GetTransform()->SetLocalScale(1000.0f, 1000.0f, 1500.0f);
		House_Right_Wall->GetTransform()->SetLocalRotation(90.0f, 0.0f, 90.0f);
		House_Right_Wall->GetTransform()->SetLocalPosition(-3.885f, 2.80f, 2.80f);
		Application::GetScene()->AddGameObject(House_Right_Wall);

		//GameObject* House_Ground = new GameObject("House_Ground");
		//House_Ground->AddComponent<PlaneRenderer>();
		//House_Ground->GetComponent<PlaneRenderer>()->AddDiffuseTexture("01_Asset/Texture/House/House_Wall.dds");
		//House_Ground->GetComponent<PlaneRenderer>()->SetAmbient(XMFLOAT4(0.1f, 0.1f, 0.1f, 1.0f));
		//House_Ground->GetTransform()->SetParent(house->GetTransform());
		//House_Ground->GetTransform()->SetLocalScale(5000.0f, 1000.0f, 5000.0f);
		//House_Ground->GetTransform()->SetLocalRotation(90.0f, 0.0f, 0.0f);
		//House_Ground->GetTransform()->SetLocalPosition(0.0f, 0.0f, -0.5f);
		//Application::GetScene()->AddGameObject(House_Ground);

		Application::GetScene()->AddGameObject(house);
#pragma endregion

#pragma region Furniture
		GameObject* furniture = new GameObject("furniture");

		GameObject* House_Books_01 = new GameObject("House_Books_01");
		House_Books_01->AddComponent<FbxRenderer>();
		House_Books_01->GetComponent<FbxRenderer>()->LoadMesh("01_Asset/Model/Furniture/House_Books_01.fbx");
		House_Books_01->GetComponent<FbxRenderer>()->AddDiffuseTexture("01_Asset/Texture/Furniture/House_Bookshelf_Books.dds");
		House_Books_01->GetComponent<FbxRenderer>()->SetAmbient(XMFLOAT4(0.5f, 0.5f, 0.5f, 1.0f));
		House_Books_01->GetTransform()->SetParent(furniture->GetTransform());
		House_Books_01->GetTransform()->SetLocalRotation(0.0f, 0.0f, 90.0f);
		House_Books_01->GetTransform()->SetLocalPosition(0.0f, 0.93f, 1.80f);
		Application::GetScene()->AddGameObject(House_Books_01);		
		
		GameObject* House_Books_02 = new GameObject("House_Books_02");
		House_Books_02->AddComponent<FbxRenderer>();
		House_Books_02->GetComponent<FbxRenderer>()->LoadMesh("01_Asset/Model/Furniture/House_Books_02.fbx");
		House_Books_02->GetComponent<FbxRenderer>()->AddDiffuseTexture("01_Asset/Texture/Furniture/House_Books_02.dds");
		House_Books_02->GetComponent<FbxRenderer>()->SetAmbient(XMFLOAT4(0.5f, 0.5f, 0.5f, 1.0f));
		House_Books_02->GetTransform()->SetParent(furniture->GetTransform());
		House_Books_02->GetTransform()->SetLocalRotation(0.0f, 0.0f, 90.0f);
		House_Books_02->GetTransform()->SetLocalPosition(2.85f, -2.50f, 0.75f);		
		Application::GetScene()->AddGameObject(House_Books_02);
		
		GameObject* House_DinningTable = new GameObject("House_DinningTable");
		House_DinningTable->AddComponent<FbxRenderer>();
		House_DinningTable->GetComponent<FbxRenderer>()->LoadMesh("01_Asset/Model/Furniture/House_DinningTable.fbx");
		House_DinningTable->GetComponent<FbxRenderer>()->AddDiffuseTexture("01_Asset/Texture/Furniture/House_DinningTable.dds");
		House_DinningTable->GetComponent<FbxRenderer>()->AddNormalTexture("01_Asset/Texture/Furniture/House_DinningTable_Normals.dds");
		House_DinningTable->GetComponent<FbxRenderer>()->AddSpecularTexture("01_Asset/Texture/Furniture/House_DinningTable_Roughness.dds");
		House_DinningTable->GetComponent<FbxRenderer>()->SetAmbient(XMFLOAT4(0.5f, 0.5f, 0.5f, 1.0f));
		House_DinningTable->GetTransform()->SetParent(furniture->GetTransform());
		House_DinningTable->GetTransform()->SetLocalPosition(1.2f, -2.50f, 0.69f);
		Application::GetScene()->AddGameObject(House_DinningTable);		
		
		GameObject* House_Bookshelf_Books = new GameObject("House_Bookshelf_Books");
		House_Bookshelf_Books->AddComponent<FbxRenderer>();
		House_Bookshelf_Books->GetComponent<FbxRenderer>()->LoadMesh("01_Asset/Model/Furniture/House_Bookshelf.fbx");
		House_Bookshelf_Books->GetComponent<FbxRenderer>()->AddDiffuseTexture("01_Asset/Texture/Furniture/House_Bookshelf_Books.dds");
		House_Bookshelf_Books->GetTransform()->SetParent(furniture->GetTransform());
		House_Bookshelf_Books->GetTransform()->SetLocalPosition(-2.0f, 0.07f, 2.0f);
		House_Bookshelf_Books->GetComponent<FbxRenderer>()->SetAmbient(XMFLOAT4(0.5f, 0.5f, 0.5f, 1.0f));
		Application::GetScene()->AddGameObject(House_Bookshelf_Books);

		GameObject* House_Bookshelf_Wood = new GameObject("House_Bookshelf_Wood");
		House_Bookshelf_Wood->AddComponent<FbxRenderer>();
		House_Bookshelf_Wood->GetComponent<FbxRenderer>()->LoadMesh("01_Asset/Model/Furniture/House_Bookshelf.fbx", 1);
		House_Bookshelf_Wood->GetComponent<FbxRenderer>()->AddDiffuseTexture("01_Asset/Texture/Furniture/House_Bookshelf_Wood.dds");
		House_Bookshelf_Wood->GetComponent<FbxRenderer>()->AddNormalTexture("01_Asset/Texture/Furniture/House_Bookshelf_Wood_Normals.dds");
		House_Bookshelf_Wood->GetComponent<FbxRenderer>()->AddSpecularTexture("01_Asset/Texture/Furniture/House_Bookshelf_Wood_Roughness.dds");
		House_Bookshelf_Wood->GetTransform()->SetParent(House_Bookshelf_Books->GetTransform());
		House_Bookshelf_Wood->GetTransform()->SetLocalPosition(0.025f, 0.0f, 0.023f);
		House_Bookshelf_Wood->GetComponent<FbxRenderer>()->SetAmbient(XMFLOAT4(0.65f, 0.65f, 0.65f, 1.0f));
		Application::GetScene()->AddGameObject(House_Bookshelf_Wood);

		GameObject* House_Bookshelf_Black = new GameObject("House_Bookshelf_Black");
		House_Bookshelf_Black->AddComponent<FbxRenderer>();
		House_Bookshelf_Black->GetComponent<FbxRenderer>()->LoadMesh("01_Asset/Model/Furniture/House_Bookshelf.fbx", 2);
		House_Bookshelf_Black->GetComponent<FbxRenderer>()->AddDiffuseTexture("01_Asset/Texture/Furniture/House_Bookshelf_Black.dds");
		House_Bookshelf_Black->GetComponent<FbxRenderer>()->AddSpecularTexture("01_Asset/Texture/Furniture/House_Bookshelf_Black_Roughness.dds");
		House_Bookshelf_Black->GetTransform()->SetParent(House_Bookshelf_Books->GetTransform());
		House_Bookshelf_Black->GetTransform()->SetLocalPosition(-0.025f, 0.04f, -0.017f);
		House_Bookshelf_Black->GetComponent<FbxRenderer>()->SetAmbient(XMFLOAT4(0.5f, 0.5f, 0.5f, 1.0f));
		Application::GetScene()->AddGameObject(House_Bookshelf_Black);		
		
		GameObject* House_Bowl = new GameObject("House_Bowl");
		House_Bowl->AddComponent<FbxRenderer>();
		House_Bowl->GetComponent<FbxRenderer>()->LoadMesh("01_Asset/Model/Furniture/House_Bowl.fbx");
		House_Bowl->GetComponent<FbxRenderer>()->AddDiffuseTexture("01_Asset/Texture/Furniture/House_Bowl.dds");
		House_Bowl->GetComponent<FbxRenderer>()->AddNormalTexture("01_Asset/Texture/Furniture/House_Bowl_Normals.dds");
		House_Bowl->GetComponent<FbxRenderer>()->AddSpecularTexture("01_Asset/Texture/Furniture/House_Bowl_Roughness.dds");
		House_Bowl->GetComponent<FbxRenderer>()->SetAmbient(XMFLOAT4(0.5f, 0.5f, 0.5f, 1.0f));
		House_Bowl->GetTransform()->SetParent(furniture->GetTransform());
		House_Bowl->GetTransform()->SetLocalRotation(0.0f, 0.0f, 90.0f);
		House_Bowl->GetTransform()->SetLocalPosition(0.0f, 0.6f, 1.85f);
		Application::GetScene()->AddGameObject(House_Bowl);		
		
		GameObject* House_Box = new GameObject("House_Box");
		House_Box->AddComponent<FbxRenderer>();
		House_Box->GetComponent<FbxRenderer>()->LoadMesh("01_Asset/Model/Furniture/House_Box.fbx");
		House_Box->GetComponent<FbxRenderer>()->AddDiffuseTexture("01_Asset/Texture/Furniture/House_Box.dds");
		House_Box->GetComponent<FbxRenderer>()->AddNormalTexture("01_Asset/Texture/Furniture/House_Box_Normals.dds");
		House_Box->GetComponent<FbxRenderer>()->AddSpecularTexture("01_Asset/Texture/Furniture/House_Box_Roughness.dds");
		House_Box->GetComponent<FbxRenderer>()->SetAmbient(XMFLOAT4(0.5f, 0.5f, 0.5f, 1.0f));
		House_Box->GetTransform()->SetParent(furniture->GetTransform());
		House_Box->GetTransform()->SetLocalPosition(0.0f, 0.75f, 1.87f);
		Application::GetScene()->AddGameObject(House_Box);		
		
		GameObject* House_Carpet = new GameObject("House_Carpet");
		House_Carpet->AddComponent<FbxRenderer>();
		House_Carpet->GetComponent<FbxRenderer>()->LoadMesh("01_Asset/Model/Furniture/House_Carpet.fbx");
		House_Carpet->GetComponent<FbxRenderer>()->AddDiffuseTexture("01_Asset/Texture/Furniture/House_Carpet.dds");
		House_Carpet->GetComponent<FbxRenderer>()->AddNormalTexture("01_Asset/Texture/Furniture/House_Carpet_Normals.dds");
		House_Carpet->GetComponent<FbxRenderer>()->SetAmbient(XMFLOAT4(0.5f, 0.5f, 0.5f, 1.0f));
		House_Carpet->GetTransform()->SetParent(furniture->GetTransform());
		House_Carpet->GetTransform()->SetLocalRotation(0.0f, 0.0f, 90.0f);
		House_Carpet->GetTransform()->SetLocalPosition(-2.0f, -2.48f, 0.0f);
		Application::GetScene()->AddGameObject(House_Carpet);		
		
		GameObject* House_Chair1 = new GameObject("House_Chair1");
		House_Chair1->AddComponent<FbxRenderer>();
		House_Chair1->GetComponent<FbxRenderer>()->LoadMesh("01_Asset/Model/Furniture/House_Chair.fbx");
		House_Chair1->GetComponent<FbxRenderer>()->AddDiffuseTexture("01_Asset/Texture/Furniture/House_Chair.dds");
		House_Chair1->GetComponent<FbxRenderer>()->AddSpecularTexture("01_Asset/Texture/Furniture/House_Chair_Roughness.dds");
		House_Chair1->GetComponent<FbxRenderer>()->SetAmbient(XMFLOAT4(0.5f, 0.5f, 0.5f, 1.0f));
		House_Chair1->GetComponent<FbxRenderer>()->SetReflect(XMFLOAT4(0.1f, 0.1f, 0.1f, 1.0f));
		House_Chair1->GetTransform()->SetParent(furniture->GetTransform());
		House_Chair1->GetTransform()->SetLocalRotation(0.0f, 0.0f, -90.0f);
		House_Chair1->GetTransform()->SetLocalPosition(3.3f, -2.48f, 0.0f);
		Application::GetScene()->AddGameObject(House_Chair1);

		GameObject* House_Chair2 = new GameObject("House_Chair2");
		House_Chair2->AddComponent<FbxRenderer>();
		House_Chair2->GetComponent<FbxRenderer>()->LoadMesh("01_Asset/Model/Furniture/House_Chair.fbx");
		House_Chair2->GetComponent<FbxRenderer>()->AddDiffuseTexture("01_Asset/Texture/Furniture/House_Chair.dds");
		House_Chair2->GetComponent<FbxRenderer>()->AddSpecularTexture("01_Asset/Texture/Furniture/House_Chair_Roughness.dds");
		House_Chair2->GetComponent<FbxRenderer>()->SetAmbient(XMFLOAT4(0.5f, 0.5f, 0.5f, 1.0f));
		House_Chair2->GetComponent<FbxRenderer>()->SetReflect(XMFLOAT4(0.1f, 0.1f, 0.1f, 1.0f));
		House_Chair2->GetTransform()->SetParent(furniture->GetTransform());
		House_Chair2->GetTransform()->SetLocalRotation(0.0f, 0.0f, 8.0f);
		House_Chair2->GetTransform()->SetLocalPosition(2.5f, -1.8f, 0.0f);
		Application::GetScene()->AddGameObject(House_Chair2);

		GameObject* House_Chair3 = new GameObject("House_Chair3");
		House_Chair3->AddComponent<FbxRenderer>();
		House_Chair3->GetComponent<FbxRenderer>()->LoadMesh("01_Asset/Model/Furniture/House_Chair.fbx");
		House_Chair3->GetComponent<FbxRenderer>()->AddDiffuseTexture("01_Asset/Texture/Furniture/House_Chair.dds");
		House_Chair3->GetComponent<FbxRenderer>()->AddSpecularTexture("01_Asset/Texture/Furniture/House_Chair_Roughness.dds");
		House_Chair3->GetComponent<FbxRenderer>()->SetAmbient(XMFLOAT4(0.5f, 0.5f, 0.5f, 1.0f));
		House_Chair3->GetComponent<FbxRenderer>()->SetReflect(XMFLOAT4(0.1f, 0.1f, 0.1f, 1.0f));
		House_Chair3->GetTransform()->SetParent(furniture->GetTransform());
		House_Chair3->GetTransform()->SetLocalRotation(0.0f, 0.0f, 188.0f);
		House_Chair3->GetTransform()->SetLocalPosition(1.8f, -3.1f, 0.0f);
		Application::GetScene()->AddGameObject(House_Chair3);		
		
		GameObject* House_Cupboard_White = new GameObject("House_Cupboard_White");
		House_Cupboard_White->AddComponent<FbxRenderer>();
		House_Cupboard_White->GetComponent<FbxRenderer>()->LoadMesh("01_Asset/Model/Furniture/House_Cupboard.fbx", 1);
		House_Cupboard_White->GetComponent<FbxRenderer>()->AddDiffuseTexture("01_Asset/Texture/Furniture/House_Cupboard_White.dds");
		House_Cupboard_White->GetComponent<FbxRenderer>()->AddSpecularTexture("01_Asset/Texture/Furniture/House_Cupboard_White_Roghness.dds");
		House_Cupboard_White->GetComponent<FbxRenderer>()->SetTextureTiling(2.0f, 2.0f);
		House_Cupboard_White->GetComponent<FbxRenderer>()->SetAmbient(XMFLOAT4(0.5f, 0.5f, 0.5f, 1.0f));
		House_Cupboard_White->GetTransform()->SetParent(furniture->GetTransform());
		House_Cupboard_White->GetTransform()->SetLocalPosition(2.5f, 0.0f, 0.0f);
		Application::GetScene()->AddGameObject(House_Cupboard_White);

		GameObject* House_Cupboard_Metal = new GameObject("House_Cupboard_Metal");
		House_Cupboard_Metal->AddComponent<FbxRenderer>();
		House_Cupboard_Metal->GetComponent<FbxRenderer>()->LoadMesh("01_Asset/Model/Furniture/House_Cupboard.fbx", 0);
		House_Cupboard_Metal->GetComponent<FbxRenderer>()->AddDiffuseTexture("01_Asset/Texture/Furniture/House_Lamp_02_Metal_01.dds");
		House_Cupboard_Metal->GetComponent<FbxRenderer>()->AddSpecularTexture("01_Asset/Texture/Furniture/House_Lamp_02_Metal_01_Roughness.dds");
		House_Cupboard_Metal->GetComponent<FbxRenderer>()->SetTextureTiling(3.0f, 3.0f);
		House_Cupboard_Metal->GetComponent<FbxRenderer>()->SetAmbient(XMFLOAT4(0.5f, 0.5f, 0.5f, 1.0f));
		House_Cupboard_Metal->GetComponent<FbxRenderer>()->SetSpecular(XMFLOAT4(0.5f, 0.5f, 0.5f, 64.0f));
		House_Cupboard_Metal->GetTransform()->SetParent(furniture->GetTransform());
		House_Cupboard_Metal->GetTransform()->SetLocalPosition(2.5f, 0.0f, 0.0f);
		Application::GetScene()->AddGameObject(House_Cupboard_Metal);		
		
		GameObject* House_Cupboard_01_White = new GameObject("House_Cupboard_01_White");
		House_Cupboard_01_White->AddComponent<FbxRenderer>();
		House_Cupboard_01_White->GetComponent<FbxRenderer>()->LoadMesh("01_Asset/Model/Furniture/House_Cupboard_01.fbx", 0);
		House_Cupboard_01_White->GetComponent<FbxRenderer>()->AddDiffuseTexture("01_Asset/Texture/Furniture/House_Cupboard_01_White.dds");
		House_Cupboard_01_White->GetComponent<FbxRenderer>()->AddSpecularTexture("01_Asset/Texture/Furniture/House_Cupboard_01_Fridge_Roughness.dds");
		House_Cupboard_01_White->GetComponent<FbxRenderer>()->SetTextureTiling(2.0f, 2.0f);
		House_Cupboard_01_White->GetComponent<FbxRenderer>()->SetAmbient(XMFLOAT4(0.5f, 0.5f, 0.5f, 1.0f));
		House_Cupboard_01_White->GetTransform()->SetParent(furniture->GetTransform());
		House_Cupboard_01_White->GetTransform()->SetLocalPosition(2.34f, 2.84f, 0.0f);
		Application::GetScene()->AddGameObject(House_Cupboard_01_White);

		GameObject* House_Cupboard_01_Fridge = new GameObject("House_Cupboard_01_Fridge");
		House_Cupboard_01_Fridge->AddComponent<FbxRenderer>();
		House_Cupboard_01_Fridge->GetComponent<FbxRenderer>()->LoadMesh("01_Asset/Model/Furniture/House_Cupboard_01.fbx", 1);
		House_Cupboard_01_Fridge->GetComponent<FbxRenderer>()->AddDiffuseTexture("01_Asset/Texture/Furniture/House_Cupboard_01_Fridge.dds");
		House_Cupboard_01_Fridge->GetComponent<FbxRenderer>()->AddSpecularTexture("01_Asset/Texture/Furniture/House_Cupboard_01_Fridge_Roughness.dds");
		House_Cupboard_01_Fridge->GetComponent<FbxRenderer>()->SetTextureTiling(2.0f, 2.0f);
		House_Cupboard_01_Fridge->GetComponent<FbxRenderer>()->SetAmbient(XMFLOAT4(0.5f, 0.5f, 0.5f, 1.0f));
		House_Cupboard_01_Fridge->GetTransform()->SetParent(furniture->GetTransform());
		House_Cupboard_01_Fridge->GetTransform()->SetLocalPosition(1.15f, -0.25f, 1.0f);
		Application::GetScene()->AddGameObject(House_Cupboard_01_Fridge);

		GameObject* House_Cupboard_01_Fridge_Metal = new GameObject("House_Cupboard_01_Fridge_Metal");
		House_Cupboard_01_Fridge_Metal->AddComponent<FbxRenderer>();
		House_Cupboard_01_Fridge_Metal->GetComponent<FbxRenderer>()->LoadMesh("01_Asset/Model/Furniture/House_Cupboard_01.fbx", 2);
		House_Cupboard_01_Fridge_Metal->GetComponent<FbxRenderer>()->AddDiffuseTexture("01_Asset/Texture/Furniture/House_Cupboard_01_Fridge.dds");
		House_Cupboard_01_Fridge_Metal->GetComponent<FbxRenderer>()->AddSpecularTexture("01_Asset/Texture/Furniture/House_Cupboard_01_Fridge_Roughness.dds");
		House_Cupboard_01_Fridge_Metal->GetComponent<FbxRenderer>()->SetTextureTiling(2.0f, 2.0f);
		House_Cupboard_01_Fridge_Metal->GetComponent<FbxRenderer>()->SetAmbient(XMFLOAT4(0.5f, 0.5f, 0.5f, 1.0f));
		House_Cupboard_01_Fridge_Metal->GetComponent<FbxRenderer>()->SetSpecular(XMFLOAT4(0.8f, 0.8f, 0.8f, 36.0f));
		House_Cupboard_01_Fridge_Metal->GetTransform()->SetParent(furniture->GetTransform());
		House_Cupboard_01_Fridge_Metal->GetTransform()->SetLocalPosition(2.36f, 2.8f, -0.1f);
		Application::GetScene()->AddGameObject(House_Cupboard_01_Fridge_Metal);

		GameObject* House_Cupboard_01_Light = new GameObject("House_Cupboard_01_Light");
		House_Cupboard_01_Light->AddComponent<FbxRenderer>();
		House_Cupboard_01_Light->GetComponent<FbxRenderer>()->LoadMesh("01_Asset/Model/Furniture/House_Cupboard_01.fbx", 3);
		House_Cupboard_01_Light->GetComponent<FbxRenderer>()->AddDiffuseTexture("01_Asset/Texture/Furniture/House_Cupboard_01_Light.dds");
		House_Cupboard_01_Light->GetComponent<FbxRenderer>()->SetAmbient(XMFLOAT4(15.0f, 15.0f, 15.0f, 1.0f));
		House_Cupboard_01_Light->GetComponent<FbxRenderer>()->SetDiffuse(XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f));
		House_Cupboard_01_Light->GetComponent<FbxRenderer>()->SetSpecular(XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f));
		House_Cupboard_01_Light->GetTransform()->SetParent(furniture->GetTransform());
		House_Cupboard_01_Light->GetTransform()->SetLocalPosition(2.35f, 2.45f, 2.46f);
		Application::GetScene()->AddGameObject(House_Cupboard_01_Light);		
		
		GameObject* House_Lamp_01_Metal = new GameObject("House_Lamp_01_Metal");
		House_Lamp_01_Metal->AddComponent<FbxRenderer>();
		House_Lamp_01_Metal->GetComponent<FbxRenderer>()->LoadMesh("01_Asset/Model/Furniture/House_Lamp_01.fbx", 2);
		House_Lamp_01_Metal->GetComponent<FbxRenderer>()->AddDiffuseTexture("01_Asset/Texture/Furniture/House_Lamp_01_Metal.dds");
		House_Lamp_01_Metal->GetComponent<FbxRenderer>()->AddNormalTexture("01_Asset/Texture/Furniture/House_Lamp_01_Metal_Normals.dds");
		House_Lamp_01_Metal->GetComponent<FbxRenderer>()->AddSpecularTexture("01_Asset/Texture/Furniture/House_Lamp_01_Metal_Roughness.dds");
		House_Lamp_01_Metal->GetComponent<FbxRenderer>()->SetTextureTiling(2.0f, 2.0f);
		House_Lamp_01_Metal->GetComponent<FbxRenderer>()->SetAmbient(XMFLOAT4(0.25f, 0.25f, 0.25f, 1.0f));
		House_Lamp_01_Metal->GetComponent<FbxRenderer>()->SetSpecular(XMFLOAT4(0.5f, 0.5f, 0.5f, 64.0f));
		House_Lamp_01_Metal->GetComponent<FbxRenderer>()->SetMakeShadow(false);
		House_Lamp_01_Metal->GetTransform()->SetParent(furniture->GetTransform());
		House_Lamp_01_Metal->GetTransform()->SetLocalPosition(-1.9f, -2.6f, 2.4925f);
		Application::GetScene()->AddGameObject(House_Lamp_01_Metal);

		GameObject* House_Lamp_01_Emission = new GameObject("House_Lamp_01_Emission");
		House_Lamp_01_Emission->AddComponent<FbxRenderer>();
		House_Lamp_01_Emission->GetComponent<FbxRenderer>()->LoadMesh("01_Asset/Model/Furniture/House_Lamp_01.fbx", 1);
		House_Lamp_01_Emission->GetComponent<FbxRenderer>()->AddDiffuseTexture("01_Asset/Texture/Furniture/House_Lamp_01_Emission.dds");
		House_Lamp_01_Emission->GetComponent<FbxRenderer>()->SetAmbient(XMFLOAT4(8.0f, 8.0f, 8.0f, 1.0f));
		House_Lamp_01_Emission->GetComponent<FbxRenderer>()->SetDiffuse(XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f));
		House_Lamp_01_Emission->GetComponent<FbxRenderer>()->SetSpecular(XMFLOAT4(1.0f, 1.0f, 1.0f, 32.0f));
		House_Lamp_01_Emission->GetComponent<FbxRenderer>()->SetReflect(XMFLOAT4(0.1f, 0.1f, 0.1f, 1.0f));
		House_Lamp_01_Emission->GetComponent<FbxRenderer>()->SetMakeShadow(false);
		House_Lamp_01_Emission->GetTransform()->SetParent(furniture->GetTransform());
		House_Lamp_01_Emission->GetTransform()->SetLocalPosition(-1.9f, -2.6f, 1.95f);
		Application::GetScene()->AddGameObject(House_Lamp_01_Emission);		
		
		GameObject* House_Sofa_Legs = new GameObject("House_Sofa_Legs");
		House_Sofa_Legs->AddComponent<FbxRenderer>();
		House_Sofa_Legs->GetComponent<FbxRenderer>()->LoadMesh("01_Asset/Model/Furniture/House_Sofa.fbx", 0);
		House_Sofa_Legs->GetComponent<FbxRenderer>()->AddDiffuseTexture("01_Asset/Texture/Furniture/House_Lamp_01_Metal.dds");
		House_Sofa_Legs->GetComponent<FbxRenderer>()->AddNormalTexture("01_Asset/Texture/Furniture/House_Lamp_01_Metal_Normals.dds");
		House_Sofa_Legs->GetComponent<FbxRenderer>()->AddSpecularTexture("01_Asset/Texture/Furniture/House_Lamp_01_Metal_Roughness.dds");
		House_Sofa_Legs->GetComponent<FbxRenderer>()->SetTextureTiling(2.0f, 2.0f);
		House_Sofa_Legs->GetComponent<FbxRenderer>()->SetAmbient(XMFLOAT4(0.25f, 0.25f, 0.25f, 1.0f));
		House_Sofa_Legs->GetComponent<FbxRenderer>()->SetSpecular(XMFLOAT4(0.5f, 0.5f, 0.5f, 64.0f));
		House_Sofa_Legs->GetTransform()->SetParent(furniture->GetTransform());
		House_Sofa_Legs->GetTransform()->SetLocalRotation(0.0f, 0.0f, 90.0f);
		House_Sofa_Legs->GetTransform()->SetLocalPosition(-2.9f, -3.525f, 0.25f);
		Application::GetScene()->AddGameObject(House_Sofa_Legs);

		GameObject* House_Sofa_Cloth = new GameObject("House_Sofa_Cloth");
		House_Sofa_Cloth->AddComponent<FbxRenderer>();
		House_Sofa_Cloth->GetComponent<FbxRenderer>()->LoadMesh("01_Asset/Model/Furniture/House_Sofa.fbx", 2);
		House_Sofa_Cloth->GetComponent<FbxRenderer>()->AddDiffuseTexture("01_Asset/Texture/Furniture/House_Sofa_Cloth.dds");
		House_Sofa_Cloth->GetComponent<FbxRenderer>()->AddNormalTexture("01_Asset/Texture/Furniture/House_Sofa_Cloth_Normals.dds");
		House_Sofa_Cloth->GetComponent<FbxRenderer>()->SetTextureTiling(25.0f, 25.0f);
		House_Sofa_Cloth->GetComponent<FbxRenderer>()->SetAmbient(XMFLOAT4(0.5f, 0.5f, 0.5f, 1.0f));
		House_Sofa_Cloth->GetComponent<FbxRenderer>()->SetSpecular(XMFLOAT4(0.5f, 0.5f, 0.5f, 64.0f));
		House_Sofa_Cloth->GetTransform()->SetParent(furniture->GetTransform());
		House_Sofa_Cloth->GetTransform()->SetLocalRotation(0.0f, 0.0f, 90.0f);
		House_Sofa_Cloth->GetTransform()->SetLocalPosition(-2.9f, -2.49f, -0.008f);
		Application::GetScene()->AddGameObject(House_Sofa_Cloth);

		GameObject* House_Sofa_Pillows = new GameObject("House_Sofa_Pillows");
		House_Sofa_Pillows->AddComponent<FbxRenderer>();
		House_Sofa_Pillows->GetComponent<FbxRenderer>()->LoadMesh("01_Asset/Model/Furniture/House_Sofa.fbx", 3);
		House_Sofa_Pillows->GetComponent<FbxRenderer>()->AddDiffuseTexture("01_Asset/Texture/Furniture/House_Sofa_Pillows.dds");
		House_Sofa_Pillows->GetComponent<FbxRenderer>()->AddNormalTexture("01_Asset/Texture/Furniture/House_Sofa_Pillows_Normals.dds");
		House_Sofa_Pillows->GetComponent<FbxRenderer>()->SetTextureTiling(25.0f, 25.0f);
		House_Sofa_Pillows->GetComponent<FbxRenderer>()->SetAmbient(XMFLOAT4(0.5f, 0.5f, 0.5f, 1.0f));
		House_Sofa_Pillows->GetComponent<FbxRenderer>()->SetSpecular(XMFLOAT4(0.5f, 0.5f, 0.5f, 64.0f));
		House_Sofa_Pillows->GetTransform()->SetParent(furniture->GetTransform());
		House_Sofa_Pillows->GetTransform()->SetLocalRotation(0.0f, 0.0f, 90.0f);
		House_Sofa_Pillows->GetTransform()->SetLocalPosition(-2.9f, -2.49f, -0.008f);
		Application::GetScene()->AddGameObject(House_Sofa_Pillows);

		GameObject* House_Lampattach = new GameObject("House_Lampattach");
		House_Lampattach->AddComponent<FbxRenderer>();
		House_Lampattach->GetComponent<FbxRenderer>()->LoadMesh("01_Asset/Model/Furniture/House_Lampattach.fbx", 1);
		House_Lampattach->GetComponent<FbxRenderer>()->AddDiffuseTexture("01_Asset/Texture/House/House_Wall.dds");
		House_Lampattach->GetComponent<FbxRenderer>()->SetAmbient(XMFLOAT4(0.5f, 0.5f, 0.5f, 1.0f));
		House_Lampattach->GetComponent<FbxRenderer>()->SetDiffuse(XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f));
		House_Lampattach->GetComponent<FbxRenderer>()->SetReflect(XMFLOAT4(0.f, 0.1f, 0.1f, 1.0f));
		House_Lampattach->GetTransform()->SetParent(furniture->GetTransform());
		House_Lampattach->GetTransform()->SetLocalPosition(2.15f, -2.6f, 2.49f);
		Application::GetScene()->AddGameObject(House_Lampattach);

		GameObject* House_Lampattach_Line = new GameObject("House_Lampattach_Line");
		House_Lampattach_Line->AddComponent<FbxRenderer>();
		House_Lampattach_Line->GetComponent<FbxRenderer>()->LoadMesh("01_Asset/Model/Furniture/House_Lampattach.fbx");
		House_Lampattach_Line->GetComponent<FbxRenderer>()->AddDiffuseTexture("01_Asset/Texture/Furniture/House_Lampattach_Line.dds");
		House_Lampattach_Line->GetComponent<FbxRenderer>()->AddSpecularTexture("01_Asset/Texture/Furniture/House_Cupboard_01_Fridge_Roughness.dds");
		House_Lampattach_Line->GetComponent<FbxRenderer>()->SetTextureTiling(20.0f, 20.0f);
		House_Lampattach_Line->GetComponent<FbxRenderer>()->SetAmbient(XMFLOAT4(0.5f, 0.5f, 0.5f, 1.0f));
		House_Lampattach_Line->GetComponent<FbxRenderer>()->SetSpecular(XMFLOAT4(2.0f, 2.0f, 2.0f, 16.0f));
		House_Lampattach_Line->GetTransform()->SetParent(furniture->GetTransform());
		House_Lampattach_Line->GetTransform()->SetLocalPosition(2.15f, -2.6f, 2.49f);
		Application::GetScene()->AddGameObject(House_Lampattach_Line);		
		
		GameObject* House_Lamp_02_Metal_01 = new GameObject("House_Lamp_02_Metal_01");
		House_Lamp_02_Metal_01->AddComponent<FbxRenderer>();
		House_Lamp_02_Metal_01->GetComponent<FbxRenderer>()->LoadMesh("01_Asset/Model/Furniture/House_Lamp_02.fbx", 1);
		House_Lamp_02_Metal_01->GetComponent<FbxRenderer>()->AddDiffuseTexture("01_Asset/Texture/Furniture/House_Lamp_02_Metal_01.dds");
		House_Lamp_02_Metal_01->GetComponent<FbxRenderer>()->AddSpecularTexture("01_Asset/Texture/Furniture/House_Lamp_02_Metal_01_Roughness.dds");
		House_Lamp_02_Metal_01->GetComponent<FbxRenderer>()->SetTextureTiling(3.0f, 3.0f);
		House_Lamp_02_Metal_01->GetComponent<FbxRenderer>()->SetAmbient(XMFLOAT4(0.5f, 0.5f, 0.5f, 1.0f));
		House_Lamp_02_Metal_01->GetComponent<FbxRenderer>()->SetSpecular(XMFLOAT4(0.5f, 0.5f, 0.5f, 64.0f));
		House_Lamp_02_Metal_01->GetTransform()->SetParent(furniture->GetTransform());
		House_Lamp_02_Metal_01->GetTransform()->SetLocalPosition(2.568f, -2.6f, 1.85f);
		Application::GetScene()->AddGameObject(House_Lamp_02_Metal_01);

		GameObject* House_Lamp_02_Metal_02 = new GameObject("House_Lamp_02_Metal_02");
		House_Lamp_02_Metal_02->AddComponent<FbxRenderer>();
		House_Lamp_02_Metal_02->GetComponent<FbxRenderer>()->LoadMesh("01_Asset/Model/Furniture/House_Lamp_02.fbx", 2);
		House_Lamp_02_Metal_02->GetComponent<FbxRenderer>()->AddDiffuseTexture("01_Asset/Texture/Furniture/House_Lamp_02_Metal_01.dds");
		House_Lamp_02_Metal_02->GetComponent<FbxRenderer>()->AddSpecularTexture("01_Asset/Texture/Furniture/House_Lamp_02_Metal_01_Roughness.dds");
		House_Lamp_02_Metal_02->GetComponent<FbxRenderer>()->SetTextureTiling(10.0f, 10.0f);
		House_Lamp_02_Metal_02->GetComponent<FbxRenderer>()->SetAmbient(XMFLOAT4(0.5f, 0.5f, 0.5f, 1.0f));
		House_Lamp_02_Metal_02->GetComponent<FbxRenderer>()->SetSpecular(XMFLOAT4(0.5f, 0.5f, 0.5f, 64.0f));
		House_Lamp_02_Metal_02->GetTransform()->SetParent(furniture->GetTransform());
		House_Lamp_02_Metal_02->GetTransform()->SetLocalPosition(2.568f, -2.6f, 1.85f);
		Application::GetScene()->AddGameObject(House_Lamp_02_Metal_02);

		GameObject* House_Lamp_02_Metal_03 = new GameObject("House_Lamp_02_Metal_03");
		House_Lamp_02_Metal_03->AddComponent<FbxRenderer>();
		House_Lamp_02_Metal_03->GetComponent<FbxRenderer>()->LoadMesh("01_Asset/Model/Furniture/House_Lamp_02.fbx", 4);
		House_Lamp_02_Metal_03->GetComponent<FbxRenderer>()->AddDiffuseTexture("01_Asset/Texture/Furniture/House_Lamp_02_Metal_01.dds");
		House_Lamp_02_Metal_03->GetComponent<FbxRenderer>()->AddSpecularTexture("01_Asset/Texture/Furniture/House_Lamp_02_Metal_01_Roughness.dds");
		House_Lamp_02_Metal_03->GetComponent<FbxRenderer>()->SetAmbient(XMFLOAT4(0.5f, 0.5f, 0.5f, 1.0f));
		House_Lamp_02_Metal_03->GetComponent<FbxRenderer>()->SetSpecular(XMFLOAT4(0.5f, 0.5f, 0.5f, 64.0f));
		House_Lamp_02_Metal_03->GetTransform()->SetParent(furniture->GetTransform());
		House_Lamp_02_Metal_03->GetTransform()->SetLocalPosition(2.568f, -2.6f, 1.85f);
		Application::GetScene()->AddGameObject(House_Lamp_02_Metal_03);
		
		GameObject* House_Lamp_02_White = new GameObject("House_Lamp_02_White");
		House_Lamp_02_White->AddComponent<FbxRenderer>();
		House_Lamp_02_White->GetComponent<FbxRenderer>()->LoadMesh("01_Asset/Model/Furniture/House_Lamp_02.fbx", 3);
		House_Lamp_02_White->GetComponent<FbxRenderer>()->AddDiffuseTexture("01_Asset/Texture/House/House_Wall.dds");
		House_Lamp_02_White->GetComponent<FbxRenderer>()->AddSpecularTexture("01_Asset/Texture/Furniture/House_Lamp_02_White_Roughness.dds");
		House_Lamp_02_White->GetComponent<FbxRenderer>()->SetAmbient(XMFLOAT4(0.5f, 0.5f, 0.5f, 1.0f));
		House_Lamp_02_White->GetComponent<FbxRenderer>()->SetSpecular(XMFLOAT4(0.5f, 0.5f, 0.5f, 64.0f));
		House_Lamp_02_White->GetTransform()->SetParent(furniture->GetTransform());
		House_Lamp_02_White->GetTransform()->SetLocalPosition(2.568f, -2.6f, 1.85f);
		Application::GetScene()->AddGameObject(House_Lamp_02_White);

		GameObject* House_Lamp_02_White_01 = new GameObject("House_Lamp_02_White_01");
		House_Lamp_02_White_01->AddComponent<FbxRenderer>();
		House_Lamp_02_White_01->GetComponent<FbxRenderer>()->LoadMesh("01_Asset/Model/Furniture/House_Lamp_02.fbx", 7);
		House_Lamp_02_White_01->GetComponent<FbxRenderer>()->AddDiffuseTexture("01_Asset/Texture/House/House_Wall.dds");
		House_Lamp_02_White_01->GetComponent<FbxRenderer>()->AddSpecularTexture("01_Asset/Texture/Furniture/House_Lamp_02_White_01_Roughness.dds");
		House_Lamp_02_White_01->GetComponent<FbxRenderer>()->SetTextureTiling(2.0f, 2.0f);
		House_Lamp_02_White_01->GetComponent<FbxRenderer>()->SetAmbient(XMFLOAT4(0.5f, 0.5f, 0.5f, 1.0f));
		House_Lamp_02_White_01->GetComponent<FbxRenderer>()->SetSpecular(XMFLOAT4(0.5f, 0.5f, 0.5f, 64.0f));
		House_Lamp_02_White_01->GetTransform()->SetParent(furniture->GetTransform());
		House_Lamp_02_White_01->GetTransform()->SetLocalPosition(2.568f, -2.6f, 1.85f);
		Application::GetScene()->AddGameObject(House_Lamp_02_White_01);

		GameObject* House_Lamp_02_Emission = new GameObject("House_Lamp_02_Emission");
		House_Lamp_02_Emission->AddComponent<FbxRenderer>();
		House_Lamp_02_Emission->GetComponent<FbxRenderer>()->LoadMesh("01_Asset/Model/Furniture/House_Lamp_02.fbx", 6);
		House_Lamp_02_Emission->GetComponent<FbxRenderer>()->AddDiffuseTexture("01_Asset/Texture/Furniture/House_Cupboard_01_Light.dds");
		House_Lamp_02_Emission->GetComponent<FbxRenderer>()->SetAmbient(XMFLOAT4(2.0f, 2.0f, 2.0f, 1.0f));
		House_Lamp_02_Emission->GetComponent<FbxRenderer>()->SetDiffuse(XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f));
		House_Lamp_02_Emission->GetComponent<FbxRenderer>()->SetSpecular(XMFLOAT4(1.0f, 1.0f, 1.0f, 32.0f));
		House_Lamp_02_Emission->GetComponent<FbxRenderer>()->SetReflect(XMFLOAT4(0.1f, 0.1f, 0.1f, 1.0f));
		House_Lamp_02_Emission->GetTransform()->SetParent(furniture->GetTransform());
		House_Lamp_02_Emission->GetTransform()->SetLocalPosition(2.568f, -2.6f, 1.85f);
		Application::GetScene()->AddGameObject(House_Lamp_02_Emission);

		GameObject* House_Lamp_02_Metal_01_2 = new GameObject("House_Lamp_02_Metal_01_2");
		House_Lamp_02_Metal_01_2->AddComponent<FbxRenderer>();
		House_Lamp_02_Metal_01_2->GetComponent<FbxRenderer>()->LoadMesh("01_Asset/Model/Furniture/House_Lamp_02.fbx", 1);
		House_Lamp_02_Metal_01_2->GetComponent<FbxRenderer>()->AddDiffuseTexture("01_Asset/Texture/Furniture/House_Lamp_02_Metal_01.dds");
		House_Lamp_02_Metal_01_2->GetComponent<FbxRenderer>()->AddSpecularTexture("01_Asset/Texture/Furniture/House_Lamp_02_Metal_01_Roughness.dds");
		House_Lamp_02_Metal_01_2->GetComponent<FbxRenderer>()->SetTextureTiling(3.0f, 3.0f);
		House_Lamp_02_Metal_01_2->GetComponent<FbxRenderer>()->SetAmbient(XMFLOAT4(0.5f, 0.5f, 0.5f, 1.0f));
		House_Lamp_02_Metal_01_2->GetComponent<FbxRenderer>()->SetSpecular(XMFLOAT4(0.5f, 0.5f, 0.5f, 64.0f));
		House_Lamp_02_Metal_01_2->GetTransform()->SetParent(furniture->GetTransform());
		House_Lamp_02_Metal_01_2->GetTransform()->SetLocalPosition(1.73f, -2.6f, 1.85f);
		Application::GetScene()->AddGameObject(House_Lamp_02_Metal_01_2);

		GameObject* House_Lamp_02_Metal_02_2 = new GameObject("House_Lamp_02_Metal_02_2");
		House_Lamp_02_Metal_02_2->AddComponent<FbxRenderer>();
		House_Lamp_02_Metal_02_2->GetComponent<FbxRenderer>()->LoadMesh("01_Asset/Model/Furniture/House_Lamp_02.fbx", 2);
		House_Lamp_02_Metal_02_2->GetComponent<FbxRenderer>()->AddDiffuseTexture("01_Asset/Texture/Furniture/House_Lamp_02_Metal_01.dds");
		House_Lamp_02_Metal_02_2->GetComponent<FbxRenderer>()->AddSpecularTexture("01_Asset/Texture/Furniture/House_Lamp_02_Metal_01_Roughness.dds");
		House_Lamp_02_Metal_02_2->GetComponent<FbxRenderer>()->SetTextureTiling(10.0f, 10.0f);
		House_Lamp_02_Metal_02_2->GetComponent<FbxRenderer>()->SetAmbient(XMFLOAT4(0.5f, 0.5f, 0.5f, 1.0f));
		House_Lamp_02_Metal_02_2->GetComponent<FbxRenderer>()->SetSpecular(XMFLOAT4(0.5f, 0.5f, 0.5f, 64.0f));
		House_Lamp_02_Metal_02_2->GetTransform()->SetParent(furniture->GetTransform());
		House_Lamp_02_Metal_02_2->GetTransform()->SetLocalPosition(1.73f, -2.6f, 1.85f);
		Application::GetScene()->AddGameObject(House_Lamp_02_Metal_02_2);

		GameObject* House_Lamp_02_Metal_03_2 = new GameObject("House_Lamp_02_Metal_03_2");
		House_Lamp_02_Metal_03_2->AddComponent<FbxRenderer>();
		House_Lamp_02_Metal_03_2->GetComponent<FbxRenderer>()->LoadMesh("01_Asset/Model/Furniture/House_Lamp_02.fbx", 4);
		House_Lamp_02_Metal_03_2->GetComponent<FbxRenderer>()->AddDiffuseTexture("01_Asset/Texture/Furniture/House_Lamp_02_Metal_01.dds");
		House_Lamp_02_Metal_03_2->GetComponent<FbxRenderer>()->AddSpecularTexture("01_Asset/Texture/Furniture/House_Lamp_02_Metal_01_Roughness.dds");
		House_Lamp_02_Metal_03_2->GetComponent<FbxRenderer>()->SetAmbient(XMFLOAT4(0.5f, 0.5f, 0.5f, 1.0f));
		House_Lamp_02_Metal_03_2->GetComponent<FbxRenderer>()->SetSpecular(XMFLOAT4(0.5f, 0.5f, 0.5f, 64.0f));
		House_Lamp_02_Metal_03_2->GetTransform()->SetParent(furniture->GetTransform());
		House_Lamp_02_Metal_03_2->GetTransform()->SetLocalPosition(1.73f, -2.6f, 1.85f);
		Application::GetScene()->AddGameObject(House_Lamp_02_Metal_03_2);

		GameObject* House_Lamp_02_White_2 = new GameObject("House_Lamp_02_White_2");
		House_Lamp_02_White_2->AddComponent<FbxRenderer>();
		House_Lamp_02_White_2->GetComponent<FbxRenderer>()->LoadMesh("01_Asset/Model/Furniture/House_Lamp_02.fbx", 3);
		House_Lamp_02_White_2->GetComponent<FbxRenderer>()->AddDiffuseTexture("01_Asset/Texture/House/House_Wall.dds");
		House_Lamp_02_White_2->GetComponent<FbxRenderer>()->AddSpecularTexture("01_Asset/Texture/Furniture/House_Lamp_02_White_Roughness.dds");
		House_Lamp_02_White_2->GetComponent<FbxRenderer>()->SetAmbient(XMFLOAT4(0.5f, 0.5f, 0.5f, 1.0f));
		House_Lamp_02_White_2->GetComponent<FbxRenderer>()->SetSpecular(XMFLOAT4(0.5f, 0.5f, 0.5f, 64.0f));
		House_Lamp_02_White_2->GetTransform()->SetParent(furniture->GetTransform());
		House_Lamp_02_White_2->GetTransform()->SetLocalPosition(1.73f, -2.6f, 1.85f);
		Application::GetScene()->AddGameObject(House_Lamp_02_White_2);

		GameObject* House_Lamp_02_White_01_2 = new GameObject("House_Lamp_02_White_01_2");
		House_Lamp_02_White_01_2->AddComponent<FbxRenderer>();
		House_Lamp_02_White_01_2->GetComponent<FbxRenderer>()->LoadMesh("01_Asset/Model/Furniture/House_Lamp_02.fbx", 7);
		House_Lamp_02_White_01_2->GetComponent<FbxRenderer>()->AddDiffuseTexture("01_Asset/Texture/House/House_Wall.dds");
		House_Lamp_02_White_01_2->GetComponent<FbxRenderer>()->AddSpecularTexture("01_Asset/Texture/Furniture/House_Lamp_02_White_01_Roughness.dds");
		House_Lamp_02_White_01_2->GetComponent<FbxRenderer>()->SetTextureTiling(2.0f, 2.0f);
		House_Lamp_02_White_01_2->GetComponent<FbxRenderer>()->SetAmbient(XMFLOAT4(0.5f, 0.5f, 0.5f, 1.0f));
		House_Lamp_02_White_01_2->GetComponent<FbxRenderer>()->SetSpecular(XMFLOAT4(0.5f, 0.5f, 0.5f, 64.0f));
		House_Lamp_02_White_01_2->GetTransform()->SetParent(furniture->GetTransform());
		House_Lamp_02_White_01_2->GetTransform()->SetLocalPosition(1.73f, -2.6f, 1.85f);
		Application::GetScene()->AddGameObject(House_Lamp_02_White_01_2);

		GameObject* House_Lamp_02_Emission_2 = new GameObject("House_Lamp_02_Emission_2");
		House_Lamp_02_Emission_2->AddComponent<FbxRenderer>();
		House_Lamp_02_Emission_2->GetComponent<FbxRenderer>()->LoadMesh("01_Asset/Model/Furniture/House_Lamp_02.fbx", 6);
		House_Lamp_02_Emission_2->GetComponent<FbxRenderer>()->AddDiffuseTexture("01_Asset/Texture/Furniture/House_Cupboard_01_Light.dds");
		House_Lamp_02_Emission_2->GetComponent<FbxRenderer>()->SetAmbient(XMFLOAT4(2.0f, 2.0f, 2.0f, 1.0f));
		House_Lamp_02_Emission_2->GetComponent<FbxRenderer>()->SetDiffuse(XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f));
		House_Lamp_02_Emission_2->GetComponent<FbxRenderer>()->SetSpecular(XMFLOAT4(1.0f, 1.0f, 1.0f, 32.0f));
		House_Lamp_02_Emission_2->GetComponent<FbxRenderer>()->SetReflect(XMFLOAT4(0.1f, 0.1f, 0.1f, 1.0f));
		House_Lamp_02_Emission_2->GetTransform()->SetParent(furniture->GetTransform());
		House_Lamp_02_Emission_2->GetTransform()->SetLocalPosition(1.73f, -2.6f, 1.85f);
		Application::GetScene()->AddGameObject(House_Lamp_02_Emission_2);

		GameObject* House_Lampattach_01 = new GameObject("House_Lampattach_01");
		House_Lampattach_01->AddComponent<FbxRenderer>();
		House_Lampattach_01->GetComponent<FbxRenderer>()->LoadMesh("01_Asset/Model/Furniture/House_Lampattach_01.fbx");
		House_Lampattach_01->GetComponent<FbxRenderer>()->AddDiffuseTexture("01_Asset/Texture/House/House_Wall.dds");
		House_Lampattach_01->GetComponent<FbxRenderer>()->SetAmbient(XMFLOAT4(0.5f, 0.5f, 0.5f, 1.0f));
		House_Lampattach_01->GetComponent<FbxRenderer>()->SetSpecular(XMFLOAT4(0.5f, 0.5f, 0.5f, 64.0f));
		House_Lampattach_01->GetTransform()->SetParent(furniture->GetTransform());
		House_Lampattach_01->GetTransform()->SetLocalRotation(90.0f, 0.0f, 0.0f);
		House_Lampattach_01->GetTransform()->SetLocalPosition(2.4f, 1.5f, 2.5f);
		Application::GetScene()->AddGameObject(House_Lampattach_01);

		GameObject* House_Lamp_03_Black1 = new GameObject("House_Lamp_03_Black1");
		House_Lamp_03_Black1->AddComponent<FbxRenderer>();
		House_Lamp_03_Black1->GetComponent<FbxRenderer>()->LoadMesh("01_Asset/Model/Furniture/House_Lamp_03.fbx", 3);
		House_Lamp_03_Black1->GetComponent<FbxRenderer>()->AddDiffuseTexture("01_Asset/Texture/Furniture/House_Lamp_02_Metal_01.dds");
		House_Lamp_03_Black1->GetComponent<FbxRenderer>()->AddSpecularTexture("01_Asset/Texture/Furniture/House_Lamp_02_Metal_01_Roughness.dds");
		House_Lamp_03_Black1->GetComponent<FbxRenderer>()->SetAmbient(XMFLOAT4(0.5f, 0.5f, 0.5f, 1.0f));
		House_Lamp_03_Black1->GetComponent<FbxRenderer>()->SetSpecular(XMFLOAT4(0.5f, 0.5f, 0.5f, 64.0f));
		House_Lamp_03_Black1->GetTransform()->SetParent(furniture->GetTransform());
		House_Lamp_03_Black1->GetTransform()->SetLocalPosition(2.4f, 1.5f, 2.5f);
		Application::GetScene()->AddGameObject(House_Lamp_03_Black1);

		GameObject* House_Lamp_03_Black2 = new GameObject("House_Lamp_03_Black2");
		House_Lamp_03_Black2->AddComponent<FbxRenderer>();
		House_Lamp_03_Black2->GetComponent<FbxRenderer>()->LoadMesh("01_Asset/Model/Furniture/House_Lamp_03.fbx", 3);
		House_Lamp_03_Black2->GetComponent<FbxRenderer>()->AddDiffuseTexture("01_Asset/Texture/Furniture/House_Lamp_02_Metal_01.dds");
		House_Lamp_03_Black2->GetComponent<FbxRenderer>()->AddSpecularTexture("01_Asset/Texture/Furniture/House_Lamp_02_Metal_01_Roughness.dds");
		House_Lamp_03_Black2->GetComponent<FbxRenderer>()->SetAmbient(XMFLOAT4(0.5f, 0.5f, 0.5f, 1.0f));
		House_Lamp_03_Black2->GetComponent<FbxRenderer>()->SetSpecular(XMFLOAT4(0.5f, 0.5f, 0.5f, 64.0f));
		House_Lamp_03_Black2->GetTransform()->SetParent(furniture->GetTransform());
		House_Lamp_03_Black2->GetTransform()->SetLocalPosition(2.925f, 1.5f, 2.5f);
		Application::GetScene()->AddGameObject(House_Lamp_03_Black2);

		GameObject* House_Lamp_03_Black3 = new GameObject("House_Lamp_03_Black3");
		House_Lamp_03_Black3->AddComponent<FbxRenderer>();
		House_Lamp_03_Black3->GetComponent<FbxRenderer>()->LoadMesh("01_Asset/Model/Furniture/House_Lamp_03.fbx", 3);
		House_Lamp_03_Black3->GetComponent<FbxRenderer>()->AddDiffuseTexture("01_Asset/Texture/Furniture/House_Lamp_02_Metal_01.dds");
		House_Lamp_03_Black3->GetComponent<FbxRenderer>()->AddSpecularTexture("01_Asset/Texture/Furniture/House_Lamp_02_Metal_01_Roughness.dds");
		House_Lamp_03_Black3->GetComponent<FbxRenderer>()->SetAmbient(XMFLOAT4(0.5f, 0.5f, 0.5f, 1.0f));
		House_Lamp_03_Black3->GetComponent<FbxRenderer>()->SetSpecular(XMFLOAT4(0.5f, 0.5f, 0.5f, 64.0f));
		House_Lamp_03_Black3->GetTransform()->SetParent(furniture->GetTransform());
		House_Lamp_03_Black3->GetTransform()->SetLocalPosition(3.45f, 1.5f, 2.5f);
		Application::GetScene()->AddGameObject(House_Lamp_03_Black3);

		GameObject* House_Lamp_03_Line1 = new GameObject("House_Lamp_03_Line1");
		House_Lamp_03_Line1->AddComponent<FbxRenderer>();
		House_Lamp_03_Line1->GetComponent<FbxRenderer>()->LoadMesh("01_Asset/Model/Furniture/House_Lamp_03.fbx", 2);
		House_Lamp_03_Line1->GetComponent<FbxRenderer>()->AddDiffuseTexture("01_Asset/Texture/Furniture/House_Lamp_02_Metal_01.dds");
		House_Lamp_03_Line1->GetComponent<FbxRenderer>()->AddSpecularTexture("01_Asset/Texture/Furniture/House_Lamp_02_Metal_01_Roughness.dds");
		House_Lamp_03_Line1->GetComponent<FbxRenderer>()->SetAmbient(XMFLOAT4(0.5f, 0.5f, 0.5f, 1.0f));
		House_Lamp_03_Line1->GetComponent<FbxRenderer>()->SetSpecular(XMFLOAT4(0.5f, 0.5f, 0.5f, 64.0f));
		House_Lamp_03_Line1->GetTransform()->SetParent(furniture->GetTransform());
		House_Lamp_03_Line1->GetTransform()->SetLocalPosition(2.4f, 1.5f, 2.5f);
		Application::GetScene()->AddGameObject(House_Lamp_03_Line1);

		GameObject* House_Lamp_03_Line2 = new GameObject("House_Lamp_03_Line2");
		House_Lamp_03_Line2->AddComponent<FbxRenderer>();
		House_Lamp_03_Line2->GetComponent<FbxRenderer>()->LoadMesh("01_Asset/Model/Furniture/House_Lamp_03.fbx", 2);
		House_Lamp_03_Line2->GetComponent<FbxRenderer>()->AddDiffuseTexture("01_Asset/Texture/Furniture/House_Lamp_02_Metal_01.dds");
		House_Lamp_03_Line2->GetComponent<FbxRenderer>()->AddSpecularTexture("01_Asset/Texture/Furniture/House_Lamp_02_Metal_01_Roughness.dds");
		House_Lamp_03_Line2->GetComponent<FbxRenderer>()->SetAmbient(XMFLOAT4(0.5f, 0.5f, 0.5f, 1.0f));
		House_Lamp_03_Line2->GetComponent<FbxRenderer>()->SetSpecular(XMFLOAT4(0.5f, 0.5f, 0.5f, 64.0f));
		House_Lamp_03_Line2->GetTransform()->SetParent(furniture->GetTransform());
		House_Lamp_03_Line2->GetTransform()->SetLocalPosition(2.925f, 1.5f, 2.5f);
		Application::GetScene()->AddGameObject(House_Lamp_03_Line2);

		GameObject* House_Lamp_03_Line3 = new GameObject("House_Lamp_03_Line3");
		House_Lamp_03_Line3->AddComponent<FbxRenderer>();
		House_Lamp_03_Line3->GetComponent<FbxRenderer>()->LoadMesh("01_Asset/Model/Furniture/House_Lamp_03.fbx", 2);
		House_Lamp_03_Line3->GetComponent<FbxRenderer>()->AddDiffuseTexture("01_Asset/Texture/Furniture/House_Lamp_02_Metal_01.dds");
		House_Lamp_03_Line3->GetComponent<FbxRenderer>()->AddSpecularTexture("01_Asset/Texture/Furniture/House_Lamp_02_Metal_01_Roughness.dds");
		House_Lamp_03_Line3->GetComponent<FbxRenderer>()->SetAmbient(XMFLOAT4(0.5f, 0.5f, 0.5f, 1.0f));
		House_Lamp_03_Line3->GetComponent<FbxRenderer>()->SetSpecular(XMFLOAT4(0.5f, 0.5f, 0.5f, 64.0f));
		House_Lamp_03_Line3->GetTransform()->SetParent(furniture->GetTransform());
		House_Lamp_03_Line3->GetTransform()->SetLocalPosition(3.45f, 1.5f, 2.5f);
		Application::GetScene()->AddGameObject(House_Lamp_03_Line3);		
		
		GameObject* House_Oven_Metal = new GameObject("House_Oven_Metal");
		House_Oven_Metal->AddComponent<FbxRenderer>();
		House_Oven_Metal->GetComponent<FbxRenderer>()->LoadMesh("01_Asset/Model/Furniture/House_Oven.fbx", 2);
		House_Oven_Metal->GetComponent<FbxRenderer>()->AddDiffuseTexture("01_Asset/Texture/Furniture/House_Oven_Metal.dds");
		House_Oven_Metal->GetComponent<FbxRenderer>()->AddSpecularTexture("01_Asset/Texture/Furniture/House_Cupboard_Metal_Roughness.dds");
		House_Oven_Metal->GetComponent<FbxRenderer>()->SetAmbient(XMFLOAT4(0.5f, 0.5f, 0.5f, 1.0f));
		House_Oven_Metal->GetComponent<FbxRenderer>()->SetSpecular(XMFLOAT4(0.5f, 0.5f, 0.5f, 64.0f));
		House_Oven_Metal->GetTransform()->SetParent(furniture->GetTransform());
		House_Oven_Metal->GetTransform()->SetLocalRotation(0.0f, 0.0f, 90.0f);
		House_Oven_Metal->GetTransform()->SetLocalPosition(0.1575f, 0.734f, 1.57f);
		Application::GetScene()->AddGameObject(House_Oven_Metal);
		
		GameObject* House_Oven_Glass = new GameObject("House_Oven_Glass");
		House_Oven_Glass->AddComponent<FbxRenderer>();
		House_Oven_Glass->GetComponent<FbxRenderer>()->LoadMesh("01_Asset/Model/Furniture/House_Oven.fbx", 0);
		House_Oven_Glass->GetComponent<FbxRenderer>()->AddDiffuseTexture("01_Asset/Texture/Furniture/House_Oven_Glass.dds");
		House_Oven_Glass->GetComponent<FbxRenderer>()->SetAmbient(XMFLOAT4(0.5f, 0.5f, 0.5f, 1.0f));
		House_Oven_Glass->GetTransform()->SetParent(furniture->GetTransform());
		House_Oven_Glass->GetTransform()->SetLocalRotation(0.0f, 0.0f, 90.0f);
		House_Oven_Glass->GetTransform()->SetLocalPosition(0.1575f, 0.734f, 1.55f);
		Application::GetScene()->AddGameObject(House_Oven_Glass);

		GameObject* House_Oven_Handle = new GameObject("House_Oven_Handle");
		House_Oven_Handle->AddComponent<FbxRenderer>();
		House_Oven_Handle->GetComponent<FbxRenderer>()->LoadMesh("01_Asset/Model/Furniture/House_Oven.fbx", 1);
		House_Oven_Handle->GetComponent<FbxRenderer>()->AddDiffuseTexture("01_Asset/Texture/Furniture/House_Oven_Metal.dds");
		House_Oven_Handle->GetComponent<FbxRenderer>()->AddSpecularTexture("01_Asset/Texture/Furniture/House_Cupboard_Metal_Roughness.dds");
		House_Oven_Handle->GetComponent<FbxRenderer>()->SetAmbient(XMFLOAT4(0.5f, 0.5f, 0.5f, 1.0f));
		House_Oven_Handle->GetComponent<FbxRenderer>()->SetSpecular(XMFLOAT4(0.5f, 0.5f, 0.5f, 64.0f));
		House_Oven_Handle->GetTransform()->SetParent(furniture->GetTransform());
		House_Oven_Handle->GetTransform()->SetLocalRotation(0.0f, 0.0f, 90.0f);
		House_Oven_Handle->GetTransform()->SetLocalPosition(0.162f, 0.734f, 1.7175f);
		Application::GetScene()->AddGameObject(House_Oven_Handle);

		GameObject* House_Oven_Metal2 = new GameObject("House_Oven_Metal2");
		House_Oven_Metal2->AddComponent<FbxRenderer>();
		House_Oven_Metal2->GetComponent<FbxRenderer>()->LoadMesh("01_Asset/Model/Furniture/House_Oven.fbx", 2);
		House_Oven_Metal2->GetComponent<FbxRenderer>()->AddDiffuseTexture("01_Asset/Texture/Furniture/House_Oven_Metal.dds");
		House_Oven_Metal2->GetComponent<FbxRenderer>()->AddSpecularTexture("01_Asset/Texture/Furniture/House_Cupboard_Metal_Roughness.dds");
		House_Oven_Metal2->GetComponent<FbxRenderer>()->SetAmbient(XMFLOAT4(0.5f, 0.5f, 0.5f, 1.0f));
		House_Oven_Metal2->GetComponent<FbxRenderer>()->SetSpecular(XMFLOAT4(0.5f, 0.5f, 0.5f, 64.0f));
		House_Oven_Metal2->GetTransform()->SetParent(furniture->GetTransform());
		House_Oven_Metal2->GetTransform()->SetLocalRotation(0.0f, 0.0f, 90.0f);
		House_Oven_Metal2->GetTransform()->SetLocalPosition(0.1575f, 0.734f, 1.57f - 0.504f);
		Application::GetScene()->AddGameObject(House_Oven_Metal2);

		GameObject* House_Oven_Glass2 = new GameObject("House_Oven_Glass2");
		House_Oven_Glass2->AddComponent<FbxRenderer>();
		House_Oven_Glass2->GetComponent<FbxRenderer>()->LoadMesh("01_Asset/Model/Furniture/House_Oven.fbx", 0);
		House_Oven_Glass2->GetComponent<FbxRenderer>()->AddDiffuseTexture("01_Asset/Texture/Furniture/House_Oven_Glass.dds");
		House_Oven_Glass2->GetComponent<FbxRenderer>()->SetAmbient(XMFLOAT4(0.5f, 0.5f, 0.5f, 1.0f));
		House_Oven_Glass2->GetTransform()->SetParent(furniture->GetTransform());
		House_Oven_Glass2->GetTransform()->SetLocalRotation(0.0f, 0.0f, 90.0f);
		House_Oven_Glass2->GetTransform()->SetLocalPosition(0.1575f, 0.734f, 1.55f - 0.504f);
		Application::GetScene()->AddGameObject(House_Oven_Glass2);

		GameObject* House_Oven_Handle2 = new GameObject("House_Oven_Handle2");
		House_Oven_Handle2->AddComponent<FbxRenderer>();
		House_Oven_Handle2->GetComponent<FbxRenderer>()->LoadMesh("01_Asset/Model/Furniture/House_Oven.fbx", 1);
		House_Oven_Handle2->GetComponent<FbxRenderer>()->AddDiffuseTexture("01_Asset/Texture/Furniture/House_Oven_Metal.dds");
		House_Oven_Handle2->GetComponent<FbxRenderer>()->AddSpecularTexture("01_Asset/Texture/Furniture/House_Cupboard_Metal_Roughness.dds");
		House_Oven_Handle2->GetComponent<FbxRenderer>()->SetAmbient(XMFLOAT4(0.5f, 0.5f, 0.5f, 1.0f));
		House_Oven_Handle2->GetComponent<FbxRenderer>()->SetSpecular(XMFLOAT4(0.5f, 0.5f, 0.5f, 64.0f));
		House_Oven_Handle2->GetTransform()->SetParent(furniture->GetTransform());
		House_Oven_Handle2->GetTransform()->SetLocalRotation(0.0f, 0.0f, 90.0f);
		House_Oven_Handle2->GetTransform()->SetLocalPosition(0.162f, 0.734f, 1.7175f - 0.504f);
		Application::GetScene()->AddGameObject(House_Oven_Handle2);		
		
		GameObject* House_Stool1 = new GameObject("House_Stool1");
		House_Stool1->AddComponent<FbxRenderer>();
		House_Stool1->GetComponent<FbxRenderer>()->LoadMesh("01_Asset/Model/Furniture/House_Stool.fbx");
		House_Stool1->GetComponent<FbxRenderer>()->AddDiffuseTexture("01_Asset/Texture/Furniture/House_Chair.dds");
		House_Stool1->GetComponent<FbxRenderer>()->AddSpecularTexture("01_Asset/Texture/Furniture/House_Chair_Roughness.dds");
		House_Stool1->GetComponent<FbxRenderer>()->SetTextureTiling(2.0f, 2.0f);
		House_Stool1->GetComponent<FbxRenderer>()->SetAmbient(XMFLOAT4(0.5f, 0.5f, 0.5f, 1.0f));
		House_Stool1->GetTransform()->SetParent(furniture->GetTransform());
		House_Stool1->GetTransform()->SetLocalRotation(0.0f, 0.0f, 130.0f);
		House_Stool1->GetTransform()->SetLocalPosition(3.0f, -0.7f, 0.0f);
		Application::GetScene()->AddGameObject(House_Stool1);

		GameObject* House_Stool2 = new GameObject("House_Stool2");
		House_Stool2->AddComponent<FbxRenderer>();
		House_Stool2->GetComponent<FbxRenderer>()->LoadMesh("01_Asset/Model/Furniture/House_Stool.fbx");
		House_Stool2->GetComponent<FbxRenderer>()->AddDiffuseTexture("01_Asset/Texture/Furniture/House_Chair.dds");
		House_Stool2->GetComponent<FbxRenderer>()->AddSpecularTexture("01_Asset/Texture/Furniture/House_Chair_Roughness.dds");
		House_Stool2->GetComponent<FbxRenderer>()->SetTextureTiling(2.0f, 2.0f);
		House_Stool2->GetComponent<FbxRenderer>()->SetAmbient(XMFLOAT4(0.5f, 0.5f, 0.5f, 1.0f));
		House_Stool2->GetTransform()->SetParent(furniture->GetTransform());
		House_Stool2->GetTransform()->SetLocalRotation(0.0f, 0.0f, 40.0f);
		House_Stool2->GetTransform()->SetLocalPosition(2.0f, -0.8f, 0.0f);
		Application::GetScene()->AddGameObject(House_Stool2);
				
		GameObject* House_TVCabinet_Metal = new GameObject("House_TVCabinet_Metal");
		House_TVCabinet_Metal->AddComponent<FbxRenderer>();
		House_TVCabinet_Metal->GetComponent<FbxRenderer>()->LoadMesh("01_Asset/Model/Furniture/House_TVCabinet.fbx", 1);
		House_TVCabinet_Metal->GetComponent<FbxRenderer>()->AddDiffuseTexture("01_Asset/Texture/Furniture/House_TVCabinet_Metal.dds");
		House_TVCabinet_Metal->GetComponent<FbxRenderer>()->AddSpecularTexture("01_Asset/Texture/Furniture/House_TVCabinet_Metal_Roghness.dds");
		House_TVCabinet_Metal->GetComponent<FbxRenderer>()->SetAmbient(XMFLOAT4(0.5f, 0.5f, 0.5f, 1.0f));
		House_TVCabinet_Metal->GetComponent<FbxRenderer>()->SetSpecular(XMFLOAT4(0.5f, 0.5f, 0.5f, 64.0f));
		House_TVCabinet_Metal->GetTransform()->SetParent(furniture->GetTransform());
		House_TVCabinet_Metal->GetTransform()->SetLocalPosition(-3.625f, 0.0f, 0.0f);
		Application::GetScene()->AddGameObject(House_TVCabinet_Metal);

		GameObject* House_TVCabinet_Wood = new GameObject("House_TVCabinet_Wood");
		House_TVCabinet_Wood->AddComponent<FbxRenderer>();
		House_TVCabinet_Wood->GetComponent<FbxRenderer>()->LoadMesh("01_Asset/Model/Furniture/House_TVCabinet.fbx", 0);
		House_TVCabinet_Wood->GetComponent<FbxRenderer>()->AddDiffuseTexture("01_Asset/Texture/Furniture/House_TVCabinet_Wood.dds");
		House_TVCabinet_Wood->GetComponent<FbxRenderer>()->AddNormalTexture("01_Asset/Texture/Furniture/House_TVCabinet_Wood_Normals.dds");
		House_TVCabinet_Wood->GetComponent<FbxRenderer>()->AddSpecularTexture("01_Asset/Texture/Furniture/House_TVCabinet_Wood_Roughness.dds");
		House_TVCabinet_Wood->GetComponent<FbxRenderer>()->SetAmbient(XMFLOAT4(0.5f, 0.5f, 0.5f, 1.0f));
		House_TVCabinet_Wood->GetTransform()->SetParent(furniture->GetTransform());
		House_TVCabinet_Wood->GetTransform()->SetLocalPosition(-2.1725f, -0.1f, 0.02f);
		Application::GetScene()->AddGameObject(House_TVCabinet_Wood);		
		
		GameObject* House_Television_Metal_03 = new GameObject("House_Television_Metal_03");
		House_Television_Metal_03->AddComponent<FbxRenderer>();
		House_Television_Metal_03->GetComponent<FbxRenderer>()->LoadMesh("01_Asset/Model/Furniture/House_Television.fbx", 0);
		House_Television_Metal_03->GetComponent<FbxRenderer>()->AddDiffuseTexture("01_Asset/Texture/House/House_Wall.dds");
		House_Television_Metal_03->GetComponent<FbxRenderer>()->AddSpecularTexture("01_Asset/Texture/Furniture/House_TVCabinet_Metal_Roghness.dds");
		House_Television_Metal_03->GetTransform()->SetParent(furniture->GetTransform());
		House_Television_Metal_03->GetTransform()->SetLocalPosition(-1.9f, -0.1f, 0.49f);
		Application::GetScene()->AddGameObject(House_Television_Metal_03);

		GameObject* House_Television_Metal_01 = new GameObject("House_Television_Metal_01");
		House_Television_Metal_01->AddComponent<FbxRenderer>();
		House_Television_Metal_01->GetComponent<FbxRenderer>()->LoadMesh("01_Asset/Model/Furniture/House_Television.fbx", 1);
		House_Television_Metal_01->GetComponent<FbxRenderer>()->AddDiffuseTexture("01_Asset/Texture/Furniture/House_Television_Metal.dds");
		House_Television_Metal_01->GetTransform()->SetParent(furniture->GetTransform());
		House_Television_Metal_01->GetTransform()->SetLocalPosition(-1.9f, -0.13f, 0.83f);
		Application::GetScene()->AddGameObject(House_Television_Metal_01);

		GameObject* House_Television_Metal_02 = new GameObject("House_Television_Metal_02");
		House_Television_Metal_02->AddComponent<FbxRenderer>();
		House_Television_Metal_02->GetComponent<FbxRenderer>()->LoadMesh("01_Asset/Model/Furniture/House_Television.fbx", 3);
		House_Television_Metal_02->GetComponent<FbxRenderer>()->AddDiffuseTexture("01_Asset/Texture/Furniture/House_Television_Metal.dds");
		House_Television_Metal_02->GetTransform()->SetParent(furniture->GetTransform());
		House_Television_Metal_02->GetTransform()->SetLocalPosition(-1.9f, -0.13f, 1.02f);
		Application::GetScene()->AddGameObject(House_Television_Metal_02);

		GameObject* House_Television_Metal_04 = new GameObject("House_Television_Metal_04");
		House_Television_Metal_04->AddComponent<FbxRenderer>();
		House_Television_Metal_04->GetComponent<FbxRenderer>()->LoadMesh("01_Asset/Model/Furniture/House_Television.fbx", 4);
		House_Television_Metal_04->GetComponent<FbxRenderer>()->AddDiffuseTexture("01_Asset/Texture/Furniture/House_Television_Metal.dds");
		House_Television_Metal_04->GetComponent<FbxRenderer>()->SetAmbient(XMFLOAT4(0.8f, 0.8f, 0.8f, 1.0f));
		House_Television_Metal_04->GetTransform()->SetParent(furniture->GetTransform());
		House_Television_Metal_04->GetTransform()->SetLocalPosition(-1.9f, -0.1155f, 0.49f);
		Application::GetScene()->AddGameObject(House_Television_Metal_04);

		GameObject* House_Television_Screen = new GameObject("House_Television_Screen");
		House_Television_Screen->AddComponent<FbxRenderer>();
		House_Television_Screen->GetComponent<FbxRenderer>()->LoadMesh("01_Asset/Model/Furniture/House_Television.fbx", 5);
		House_Television_Screen->GetComponent<FbxRenderer>()->AddDiffuseTexture("01_Asset/Texture/Furniture/House_Oven_Glass.dds");
		House_Television_Screen->GetComponent<FbxRenderer>()->SetAmbient(XMFLOAT4(0.3f, 0.3f, 0.3f, 1.0f));
		House_Television_Screen->GetComponent<FbxRenderer>()->SetReflect(XMFLOAT4(0.1f, 0.1f, 0.1f, 1.0f));
		House_Television_Screen->GetTransform()->SetParent(furniture->GetTransform());
		House_Television_Screen->GetTransform()->SetLocalPosition(-1.9f, -0.115f, 0.49f);
		Application::GetScene()->AddGameObject(House_Television_Screen);
		
		GameObject* House_Speaker_Metal_02 = new GameObject("House_Speaker_Metal_02");
		House_Speaker_Metal_02->AddComponent<FbxRenderer>();
		House_Speaker_Metal_02->GetComponent<FbxRenderer>()->LoadMesh("01_Asset/Model/Furniture/House_Speaker.fbx", 2);
		House_Speaker_Metal_02->GetComponent<FbxRenderer>()->AddDiffuseTexture("01_Asset/Texture/Furniture/House_Oven_Glass.dds");
		House_Speaker_Metal_02->GetComponent<FbxRenderer>()->SetAmbient(XMFLOAT4(0.3f, 0.3f, 0.3f, 1.0f));
		House_Speaker_Metal_02->GetTransform()->SetParent(furniture->GetTransform());
		House_Speaker_Metal_02->GetTransform()->SetLocalPosition(-0.7f, -0.115f, 0.65f);
		Application::GetScene()->AddGameObject(House_Speaker_Metal_02);

		GameObject* House_Speaker_Metal_03 = new GameObject("House_Speaker_Metal_03");
		House_Speaker_Metal_03->AddComponent<FbxRenderer>();
		House_Speaker_Metal_03->GetComponent<FbxRenderer>()->LoadMesh("01_Asset/Model/Furniture/House_Speaker.fbx", 0);
		House_Speaker_Metal_03->GetComponent<FbxRenderer>()->AddDiffuseTexture("01_Asset/Texture/Furniture/House_Television_Metal.dds");
		House_Speaker_Metal_03->GetComponent<FbxRenderer>()->AddSpecularTexture("01_Asset/Texture/Furniture/House_Speaker_Metal.dds");
		House_Speaker_Metal_03->GetComponent<FbxRenderer>()->SetAmbient(XMFLOAT4(0.8f, 0.8f, 0.8f, 1.0f));
		House_Speaker_Metal_03->GetComponent<FbxRenderer>()->SetReflect(XMFLOAT4(0.1f, 0.1f, 0.1f, 1.0f));
		House_Speaker_Metal_03->GetTransform()->SetParent(furniture->GetTransform());
		House_Speaker_Metal_03->GetTransform()->SetLocalPosition(-0.7f, -0.115f, 0.65f);
		Application::GetScene()->AddGameObject(House_Speaker_Metal_03);

		GameObject* House_Speaker_Cloth = new GameObject("House_Speaker_Cloth");
		House_Speaker_Cloth->AddComponent<FbxRenderer>();
		House_Speaker_Cloth->GetComponent<FbxRenderer>()->LoadMesh("01_Asset/Model/Furniture/House_Speaker.fbx", 3);
		House_Speaker_Cloth->GetComponent<FbxRenderer>()->AddDiffuseTexture("01_Asset/Texture/Furniture/House_Oven_Glass.dds");
		House_Speaker_Cloth->GetComponent<FbxRenderer>()->SetAmbient(XMFLOAT4(0.1f, 0.1f, 0.1f, 1.0f));
		House_Speaker_Cloth->GetTransform()->SetParent(furniture->GetTransform());
		House_Speaker_Cloth->GetTransform()->SetLocalPosition(-0.7f, -0.115f, 0.65f);
		Application::GetScene()->AddGameObject(House_Speaker_Cloth);

		GameObject* House_Speaker_Metal_02_2 = new GameObject("House_Speaker_Metal_02_2");
		House_Speaker_Metal_02_2->AddComponent<FbxRenderer>();
		House_Speaker_Metal_02_2->GetComponent<FbxRenderer>()->LoadMesh("01_Asset/Model/Furniture/House_Speaker.fbx", 2);
		House_Speaker_Metal_02_2->GetComponent<FbxRenderer>()->AddDiffuseTexture("01_Asset/Texture/Furniture/House_Oven_Glass.dds");
		House_Speaker_Metal_02_2->GetComponent<FbxRenderer>()->SetAmbient(XMFLOAT4(0.3f, 0.3f, 0.3f, 1.0f));
		House_Speaker_Metal_02_2->GetTransform()->SetParent(furniture->GetTransform());
		House_Speaker_Metal_02_2->GetTransform()->SetLocalPosition(-3.0f, -0.115f, 0.65f);
		Application::GetScene()->AddGameObject(House_Speaker_Metal_02_2);

		GameObject* House_Speaker_Metal_03_2 = new GameObject("House_Speaker_Metal_03_2");
		House_Speaker_Metal_03_2->AddComponent<FbxRenderer>();
		House_Speaker_Metal_03_2->GetComponent<FbxRenderer>()->LoadMesh("01_Asset/Model/Furniture/House_Speaker.fbx", 0);
		House_Speaker_Metal_03_2->GetComponent<FbxRenderer>()->AddDiffuseTexture("01_Asset/Texture/Furniture/House_Television_Metal.dds");
		House_Speaker_Metal_03_2->GetComponent<FbxRenderer>()->AddSpecularTexture("01_Asset/Texture/Furniture/House_Speaker_Metal.dds");
		House_Speaker_Metal_03_2->GetComponent<FbxRenderer>()->SetAmbient(XMFLOAT4(0.8f, 0.8f, 0.8f, 1.0f));
		House_Speaker_Metal_03_2->GetComponent<FbxRenderer>()->SetReflect(XMFLOAT4(0.1f, 0.1f, 0.1f, 1.0f));
		House_Speaker_Metal_03_2->GetTransform()->SetParent(furniture->GetTransform());
		House_Speaker_Metal_03_2->GetTransform()->SetLocalPosition(-3.0f, -0.115f, 0.65f);
		Application::GetScene()->AddGameObject(House_Speaker_Metal_03_2);

		GameObject* House_Speaker_Cloth_2 = new GameObject("House_Speaker_Cloth_2");
		House_Speaker_Cloth_2->AddComponent<FbxRenderer>();
		House_Speaker_Cloth_2->GetComponent<FbxRenderer>()->LoadMesh("01_Asset/Model/Furniture/House_Speaker.fbx", 3);
		House_Speaker_Cloth_2->GetComponent<FbxRenderer>()->AddDiffuseTexture("01_Asset/Texture/Furniture/House_Oven_Glass.dds");
		House_Speaker_Cloth_2->GetComponent<FbxRenderer>()->SetAmbient(XMFLOAT4(0.1f, 0.1f, 0.1f, 1.0f));
		House_Speaker_Cloth_2->GetTransform()->SetParent(furniture->GetTransform());
		House_Speaker_Cloth_2->GetTransform()->SetLocalPosition(-3.0f, -0.115f, 0.65f);
		Application::GetScene()->AddGameObject(House_Speaker_Cloth_2);		
		
		GameObject* House_Wineshelf_Box = new GameObject("House_Wineshelf_Box");
		House_Wineshelf_Box->AddComponent<FbxRenderer>();
		House_Wineshelf_Box->GetComponent<FbxRenderer>()->LoadMesh("01_Asset/Model/Furniture/House_Wineshelf.fbx", 0);
		House_Wineshelf_Box->GetComponent<FbxRenderer>()->AddDiffuseTexture("01_Asset/Texture/House/House_Wall.dds");
		House_Wineshelf_Box->GetComponent<FbxRenderer>()->SetAmbient(XMFLOAT4(0.1f, 0.1f, 0.1f, 1.0f));
		House_Wineshelf_Box->GetTransform()->SetParent(furniture->GetTransform());
		House_Wineshelf_Box->GetTransform()->SetLocalRotation(0.0f, 0.0f, 90.0f);
		House_Wineshelf_Box->GetTransform()->SetLocalPosition(1.322f, -1.415f, 1.0f);
		Application::GetScene()->AddGameObject(House_Wineshelf_Box);

		GameObject* House_Wineshelf_Frame = new GameObject("House_Wineshelf_Frame");
		House_Wineshelf_Frame->AddComponent<FbxRenderer>();
		House_Wineshelf_Frame->GetComponent<FbxRenderer>()->LoadMesh("01_Asset/Model/Furniture/House_Wineshelf.fbx", 3);
		House_Wineshelf_Frame->GetComponent<FbxRenderer>()->AddDiffuseTexture("01_Asset/Texture/Furniture/House_Wineshelf_Frame.dds");
		House_Wineshelf_Frame->GetComponent<FbxRenderer>()->AddSpecularTexture("01_Asset/Texture/Furniture/House_Wineshelf_Frame_Roughness.dds");
		House_Wineshelf_Frame->GetComponent<FbxRenderer>()->SetAmbient(XMFLOAT4(0.5f, 0.5f, 0.5f, 1.0f));
		House_Wineshelf_Frame->GetTransform()->SetParent(furniture->GetTransform());
		House_Wineshelf_Frame->GetTransform()->SetLocalRotation(0.0f, 0.0f, 90.0f);
		House_Wineshelf_Frame->GetTransform()->SetLocalPosition(0.1575f, 0.734f, 0.435f);
		Application::GetScene()->AddGameObject(House_Wineshelf_Frame);

		GameObject* House_Wineshelf_Handle = new GameObject("House_Wineshelf_Handle");
		House_Wineshelf_Handle->AddComponent<FbxRenderer>();
		House_Wineshelf_Handle->GetComponent<FbxRenderer>()->LoadMesh("01_Asset/Model/Furniture/House_Wineshelf.fbx", 4);
		House_Wineshelf_Handle->GetComponent<FbxRenderer>()->AddDiffuseTexture("01_Asset/Texture/Furniture/House_Chair.dds");
		House_Wineshelf_Handle->GetComponent<FbxRenderer>()->AddSpecularTexture("01_Asset/Texture/Furniture/House_Chair_Roughness.dds");
		House_Wineshelf_Handle->GetComponent<FbxRenderer>()->SetAmbient(XMFLOAT4(0.5f, 0.5f, 0.5f, 1.0f));
		House_Wineshelf_Handle->GetTransform()->SetParent(furniture->GetTransform());
		House_Wineshelf_Handle->GetTransform()->SetLocalRotation(0.0f, 0.0f, 90.0f);
		House_Wineshelf_Handle->GetTransform()->SetLocalPosition(0.1575f, 0.734f, 0.435f);
		Application::GetScene()->AddGameObject(House_Wineshelf_Handle);

		GameObject* House_Wineshelf_Wood = new GameObject("House_Wineshelf_Wood");
		House_Wineshelf_Wood->AddComponent<FbxRenderer>();
		House_Wineshelf_Wood->GetComponent<FbxRenderer>()->LoadMesh("01_Asset/Model/Furniture/House_Wineshelf.fbx", 1);
		House_Wineshelf_Wood->GetComponent<FbxRenderer>()->AddDiffuseTexture("01_Asset/Texture/Furniture/House_Wineshelf_Wood.dds");
		House_Wineshelf_Wood->GetComponent<FbxRenderer>()->AddSpecularTexture("01_Asset/Texture/Furniture/House_Wineshelf_Wood_Roughness.dds");
		House_Wineshelf_Wood->GetComponent<FbxRenderer>()->SetAmbient(XMFLOAT4(0.5f, 0.5f, 0.5f, 1.0f));
		House_Wineshelf_Wood->GetTransform()->SetParent(furniture->GetTransform());
		House_Wineshelf_Wood->GetTransform()->SetLocalRotation(0.0f, 0.0f, 90.0f);
		House_Wineshelf_Wood->GetTransform()->SetLocalPosition(-0.01f, 0.734f, 0.1f);
		Application::GetScene()->AddGameObject(House_Wineshelf_Wood);

		//투명도가 있는 물체
		GameObject* House_Wineshelf_Glass = new GameObject("House_Wineshelf_Glass");
		House_Wineshelf_Glass->AddComponent<FbxRenderer>();
		House_Wineshelf_Glass->GetComponent<FbxRenderer>()->LoadMesh("01_Asset/Model/Furniture/House_Wineshelf.fbx", 2);
		House_Wineshelf_Glass->GetComponent<FbxRenderer>()->AddDiffuseTexture("01_Asset/Texture/Furniture/GlassTable.dds");
		House_Wineshelf_Glass->GetComponent<FbxRenderer>()->SetMakeShadow(false);
		House_Wineshelf_Glass->GetComponent<FbxRenderer>()->SetTransparentRendering(true);
		House_Wineshelf_Glass->GetComponent<FbxRenderer>()->SetAmbient(XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f));
		House_Wineshelf_Glass->GetComponent<FbxRenderer>()->SetDiffuse(XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f));
		House_Wineshelf_Glass->GetComponent<FbxRenderer>()->SetSpecular(XMFLOAT4(1.0f, 1.0f, 1.0f, 32.0f));
		House_Wineshelf_Glass->GetComponent<FbxRenderer>()->SetReflect(XMFLOAT4(0.1f, 0.1f, 0.1f, 1.0f));		
		House_Wineshelf_Glass->GetTransform()->SetParent(furniture->GetTransform());
		House_Wineshelf_Glass->GetTransform()->SetLocalRotation(0.0f, 0.0f, 90.0f);
		House_Wineshelf_Glass->GetTransform()->SetLocalPosition(0.1575f, 0.734f, 0.125f);
		Application::GetScene()->AddGameObject(House_Wineshelf_Glass);

		GameObject* House_Lamp_02_Glass_02 = new GameObject("House_Lamp_02_Glass_02");
		House_Lamp_02_Glass_02->AddComponent<FbxRenderer>();
		House_Lamp_02_Glass_02->GetComponent<FbxRenderer>()->LoadMesh("01_Asset/Model/Furniture/House_Lamp_02.fbx", 5);
		House_Lamp_02_Glass_02->GetComponent<FbxRenderer>()->AddDiffuseTexture("01_Asset/Texture/Furniture/GlassTable.dds");
		House_Lamp_02_Glass_02->GetComponent<FbxRenderer>()->AddSpecularTexture("01_Asset/Texture/Furniture/House_Lamp_02_Glass_Roughness.dds");
		House_Lamp_02_Glass_02->GetComponent<FbxRenderer>()->SetTransparentRendering(true);
		House_Lamp_02_Glass_02->GetComponent<FbxRenderer>()->SetAmbient(XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f));
		House_Lamp_02_Glass_02->GetComponent<FbxRenderer>()->SetDiffuse(XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f));
		House_Lamp_02_Glass_02->GetComponent<FbxRenderer>()->SetSpecular(XMFLOAT4(1.0f, 1.0f, 1.0f, 32.0f));
		House_Lamp_02_Glass_02->GetComponent<FbxRenderer>()->SetReflect(XMFLOAT4(0.1f, 0.1f, 0.1f, 1.0f));
		House_Lamp_02_Glass_02->GetTransform()->SetParent(furniture->GetTransform());
		House_Lamp_02_Glass_02->GetTransform()->SetLocalPosition(2.568f, -2.6f, 1.85f);
		Application::GetScene()->AddGameObject(House_Lamp_02_Glass_02);

		GameObject* House_Lamp_02_Glass = new GameObject("House_Lamp_02_Glass");
		House_Lamp_02_Glass->AddComponent<FbxRenderer>();
		House_Lamp_02_Glass->GetComponent<FbxRenderer>()->LoadMesh("01_Asset/Model/Furniture/House_Lamp_02.fbx", 0);
		House_Lamp_02_Glass->GetComponent<FbxRenderer>()->AddDiffuseTexture("01_Asset/Texture/Furniture/GlassTable.dds");
		House_Lamp_02_Glass->GetComponent<FbxRenderer>()->AddSpecularTexture("01_Asset/Texture/Furniture/House_Lamp_02_Glass_Roughness.dds");
		House_Lamp_02_Glass->GetComponent<FbxRenderer>()->SetTransparentRendering(true);
		House_Lamp_02_Glass->GetComponent<FbxRenderer>()->SetAmbient(XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f));
		House_Lamp_02_Glass->GetComponent<FbxRenderer>()->SetDiffuse(XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f));
		House_Lamp_02_Glass->GetComponent<FbxRenderer>()->SetSpecular(XMFLOAT4(1.0f, 1.0f, 1.0f, 32.0f));
		House_Lamp_02_Glass->GetComponent<FbxRenderer>()->SetReflect(XMFLOAT4(0.1f, 0.1f, 0.1f, 1.0f));
		House_Lamp_02_Glass->GetTransform()->SetParent(furniture->GetTransform());
		House_Lamp_02_Glass->GetTransform()->SetLocalPosition(2.568f, -2.6f, 1.85f);
		Application::GetScene()->AddGameObject(House_Lamp_02_Glass);

		GameObject* House_Lamp_02_Glass_02_2 = new GameObject("House_Lamp_02_Glass_02_2");
		House_Lamp_02_Glass_02_2->AddComponent<FbxRenderer>();
		House_Lamp_02_Glass_02_2->GetComponent<FbxRenderer>()->LoadMesh("01_Asset/Model/Furniture/House_Lamp_02.fbx", 5);
		House_Lamp_02_Glass_02_2->GetComponent<FbxRenderer>()->AddDiffuseTexture("01_Asset/Texture/Furniture/GlassTable.dds");
		House_Lamp_02_Glass_02_2->GetComponent<FbxRenderer>()->AddSpecularTexture("01_Asset/Texture/Furniture/House_Lamp_02_Glass_Roughness.dds");
		House_Lamp_02_Glass_02_2->GetComponent<FbxRenderer>()->SetTransparentRendering(true);
		House_Lamp_02_Glass_02_2->GetComponent<FbxRenderer>()->SetAmbient(XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f));
		House_Lamp_02_Glass_02_2->GetComponent<FbxRenderer>()->SetDiffuse(XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f));
		House_Lamp_02_Glass_02_2->GetComponent<FbxRenderer>()->SetSpecular(XMFLOAT4(1.0f, 1.0f, 1.0f, 32.0f));
		House_Lamp_02_Glass_02_2->GetComponent<FbxRenderer>()->SetReflect(XMFLOAT4(0.1f, 0.1f, 0.1f, 1.0f));
		House_Lamp_02_Glass_02_2->GetTransform()->SetParent(furniture->GetTransform());
		House_Lamp_02_Glass_02_2->GetTransform()->SetLocalPosition(1.73f, -2.6f, 1.85f);
		Application::GetScene()->AddGameObject(House_Lamp_02_Glass_02_2);

		GameObject* House_Lamp_02_Glass_2 = new GameObject("House_Lamp_02_Glass_2");
		House_Lamp_02_Glass_2->AddComponent<FbxRenderer>();
		House_Lamp_02_Glass_2->GetComponent<FbxRenderer>()->LoadMesh("01_Asset/Model/Furniture/House_Lamp_02.fbx", 0);
		House_Lamp_02_Glass_2->GetComponent<FbxRenderer>()->AddDiffuseTexture("01_Asset/Texture/Furniture/GlassTable.dds");
		House_Lamp_02_Glass_2->GetComponent<FbxRenderer>()->AddSpecularTexture("01_Asset/Texture/Furniture/House_Lamp_02_Glass_Roughness.dds");
		House_Lamp_02_Glass_2->GetComponent<FbxRenderer>()->SetTransparentRendering(true);
		House_Lamp_02_Glass_2->GetComponent<FbxRenderer>()->SetAmbient(XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f));
		House_Lamp_02_Glass_2->GetComponent<FbxRenderer>()->SetDiffuse(XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f));
		House_Lamp_02_Glass_2->GetComponent<FbxRenderer>()->SetSpecular(XMFLOAT4(1.0f, 1.0f, 1.0f, 32.0f));
		House_Lamp_02_Glass_2->GetComponent<FbxRenderer>()->SetReflect(XMFLOAT4(0.1f, 0.1f, 0.1f, 1.0f));
		House_Lamp_02_Glass_2->GetTransform()->SetParent(furniture->GetTransform());
		House_Lamp_02_Glass_2->GetTransform()->SetLocalPosition(1.73f, -2.6f, 1.85f);
		Application::GetScene()->AddGameObject(House_Lamp_02_Glass_2);

		GameObject* House_GlassTable = new GameObject("House_GlassTable");
		House_GlassTable->AddComponent<FbxRenderer>();
		House_GlassTable->GetComponent<FbxRenderer>()->LoadMesh("01_Asset/Model/Furniture/House_GlassTable.fbx");
		House_GlassTable->GetComponent<FbxRenderer>()->AddDiffuseTexture("01_Asset/Texture/Furniture/GlassTable.dds");
		House_GlassTable->GetComponent<FbxRenderer>()->AddSpecularTexture("01_Asset/Texture/Furniture/House_Chair_Roughness.dds");
		House_GlassTable->GetComponent<FbxRenderer>()->SetTransparentRendering(true);
		House_GlassTable->GetComponent<FbxRenderer>()->SetAmbient(XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f));
		House_GlassTable->GetComponent<FbxRenderer>()->SetDiffuse(XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f));
		House_GlassTable->GetComponent<FbxRenderer>()->SetSpecular(XMFLOAT4(1.0f, 1.0f, 1.0f, 32.0f));
		House_GlassTable->GetComponent<FbxRenderer>()->SetReflect(XMFLOAT4(0.1f, 0.1f, 0.1f, 1.0f));
		House_GlassTable->GetTransform()->SetParent(furniture->GetTransform());
		House_GlassTable->GetTransform()->SetLocalRotation(0.0f, 0.0f, 90.0f);
		House_GlassTable->GetTransform()->SetLocalPosition(-1.9f, -2.6f, 0.2f);
		Application::GetScene()->AddGameObject(House_GlassTable);

		GameObject* House_Windows_Glass = new GameObject("House_Windows_Glass");
		House_Windows_Glass->AddComponent<FbxRenderer>();
		House_Windows_Glass->GetComponent<FbxRenderer>()->LoadMesh("01_Asset/Model/House/House.fbx", 7);
		House_Windows_Glass->GetComponent<FbxRenderer>()->AddDiffuseTexture("01_Asset/Texture/Furniture/GlassTable.dds");
		House_Windows_Glass->GetComponent<FbxRenderer>()->SetMakeShadow(false);
		House_Windows_Glass->GetComponent<FbxRenderer>()->SetTransparentRendering(true);
		House_Windows_Glass->GetComponent<FbxRenderer>()->SetAmbient(XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f));
		House_Windows_Glass->GetComponent<FbxRenderer>()->SetDiffuse(XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f));
		House_Windows_Glass->GetComponent<FbxRenderer>()->SetSpecular(XMFLOAT4(1.0f, 1.0f, 1.0f, 32.0f));
		House_Windows_Glass->GetComponent<FbxRenderer>()->SetReflect(XMFLOAT4(0.1f, 0.1f, 0.1f, 1.0f));
		House_Windows_Glass->GetTransform()->SetParent(house->GetTransform());
		House_Windows_Glass->GetTransform()->SetLocalPosition(-3.26f, -4.75f, 1.90f);
		Application::GetScene()->AddGameObject(House_Windows_Glass);
		house->GetTransform()->SetWorldScale(0.01f, 0.01f, 0.01f);
		house->GetTransform()->SetWorldRotation(-90.0f, 0.0f, 130.0f);

		furniture->GetTransform()->SetWorldRotation(-90.0f, 0.0f, 130.0f);
		furniture->GetTransform()->SetWorldScale(0.01f, 0.01f, 0.01f);
		Application::GetScene()->AddGameObject(furniture);
#pragma endregion

#pragma region UI
		UIManager::GetInstance()->SetConstantSize(true);

		GameObject* textUI = new GameObject("textUI");
		textUI->AddComponent<TextUIRenderer>();
		textUI->AddComponent<UIButton>();
		textUI->GetComponent<UIButton>()->SetUIRenderer(textUI->GetComponent<TextUIRenderer>());
		textUI->GetComponent<TextUIRenderer>()->SetText("ChipsEngine");
		textUI->GetComponent<TextUIRenderer>()->SetPivot(0.0f, 0.0f);
		textUI->GetComponent<TextUIRenderer>()->SetAnchorPoint(0.0f, 0.0f);
		textUI->GetTransform()->SetWorldScale(0.5f, 0.5f, 0.0f);
		Application::GetScene()->AddGameObject(textUI);

		GameObject* fpsUI = new GameObject("fpsUI");
		fpsUI->AddComponent<TextUIRenderer>();
		fpsUI->GetComponent<TextUIRenderer>()->SetPivot(1.0f, 0.0f);
		fpsUI->GetComponent<TextUIRenderer>()->SetAnchorPoint(1.0f, 0.0f);
		fpsUI->GetTransform()->SetWorldScale(0.5f, 0.5f, 0.0f);
		Application::GetScene()->AddGameObject(fpsUI);
#pragma endregion

#pragma region Particle
		GameObject* dust1 = new GameObject("dust1");
		dust1->AddComponent<ParticleRenderer>();
		dust1->GetComponent<ParticleRenderer>()->LoadTexture("01_Asset/Texture/Particle/DustWhite.dds");
		dust1->GetComponent<ParticleRenderer>()->SetColor(XMFLOAT3(0.05f, 0.05f, 0.05f));
		dust1->GetComponent<ParticleRenderer>()->SetRandomizePosition(1.0f);
		dust1->GetComponent<ParticleRenderer>()->SetSpread(0.0f);
		dust1->GetComponent<ParticleRenderer>()->SetSpeed(0.025f);
		dust1->GetComponent<ParticleRenderer>()->SetFadeTime(18.0f);
		dust1->GetComponent<ParticleRenderer>()->SetDeleteTime(18.0f);
		dust1->GetComponent<ParticleRenderer>()->SetCreateIntervalTime(0.18f);
		dust1->GetComponent<ParticleRenderer>()->SetFrustumCulling(false);
		dust1->GetTransform()->SetWorldPosition(3.5f, 0.7f, -2.5f);
		dust1->GetTransform()->SetWorldRotation(30.0f, -45.0f, 0.0f);
		dust1->GetTransform()->SetParent(furniture->GetTransform());
		dust1->GetTransform()->Translate(1.5f, 0.0f, -3.0f);
		dust1->GetTransform()->Translate(0.0f, -0.5f, 0.0f, false);
		Application::GetScene()->AddGameObject(dust1);

		GameObject* dust2 = new GameObject("dust2");
		dust2->AddComponent<ParticleRenderer>();
		dust2->GetComponent<ParticleRenderer>()->LoadTexture("01_Asset/Texture/Particle/DustWhite.dds");
		dust2->GetComponent<ParticleRenderer>()->SetColor(XMFLOAT3(0.05f, 0.05f, 0.05f));
		dust2->GetComponent<ParticleRenderer>()->SetRandomizePosition(1.0f);
		dust2->GetComponent<ParticleRenderer>()->SetSpread(0.0f);
		dust2->GetComponent<ParticleRenderer>()->SetSpeed(0.00625f);
		dust2->GetComponent<ParticleRenderer>()->SetFadeTime(72.0f);
		dust2->GetComponent<ParticleRenderer>()->SetDeleteTime(72.0f);
		dust2->GetComponent<ParticleRenderer>()->SetCreateIntervalTime(0.72f);
		dust2->GetComponent<ParticleRenderer>()->SetFrustumCulling(false);
		dust2->GetTransform()->SetWorldPosition(3.5f, 0.7f, -2.5f);
		dust2->GetTransform()->SetWorldRotation(30.0f, -45.0f, 0.0f);
		dust2->GetTransform()->SetParent(furniture->GetTransform());
		dust2->GetTransform()->Translate(-2.5f, 0.0f, -3.0f);
		dust2->GetTransform()->Translate(0.0f, -0.5f, 0.0f, false);
		Application::GetScene()->AddGameObject(dust2);
#pragma endregion

#pragma region Graphic Setting
		GraphicManager::GetInstance()->SetLimitFps(60);
		GraphicManager::GetInstance()->SetScreenResolution(1280.0f, 720.0f);
		GraphicManager::GetInstance()->SetPostProcessing(true);
		GraphicManager::GetInstance()->SetSSAA(false);
		GraphicManager::GetInstance()->SetSSAO(true);
		GraphicManager::GetInstance()->SetBloom(true, true, 1.0f);
		GraphicManager::GetInstance()->LoadLutTexture("01_Asset/Texture/Lut/LUT_Fall.dds");
		GraphicManager::GetInstance()->SetLUT(true, 0.25f);
		GraphicManager::GetInstance()->SetGamma(true, 1.2f);
		GraphicManager::GetInstance()->SetCinematicLine(true, 0.08f);
#pragma endregion

#pragma region Audio
		GameObject* sound = new GameObject("Sound");
		sound->AddComponent<AudioSource>();
		sound->GetComponent<AudioSource>()->CreateAudio("Background", "01_Asset/Audio/lenaPark.mp3", false, AUDIO_LOOP_TYPE::AUDIO_LOOP_TYPE_LOOP, AUDIO_SOUND_TYPE::AUDIO_SOUND_TYPE_2D);
		sound->GetComponent<AudioSource>()->SetVolume(1.0f);
		Application::GetScene()->AddGameObject(sound);
#pragma endregion
		
#pragma region Light
		GameObject* light1 = new GameObject("Light1");
		light1->AddComponent<DirectionalLight>();
		light1->GetComponent<DirectionalLight>()->SetAmbient(XMFLOAT4(0.2f, 0.2f, 0.2f, 1.0f));
		light1->GetComponent<DirectionalLight>()->SetDiffuse(XMFLOAT4(0.8f, 0.8f, 0.8f, 1.0f));
		light1->GetComponent<DirectionalLight>()->SetSpecular(XMFLOAT4(0.8f, 0.8f, 0.8f, 1.0f));
		light1->GetTransform()->LootAt(XMFLOAT3(-0.57735f, -0.85f, 0.57735f));
		Application::GetScene()->AddGameObject(light1);

		GameObject* light2 = new GameObject("Light2");
		light2->AddComponent<DirectionalLight>();
		light2->GetComponent<DirectionalLight>()->SetAmbient(XMFLOAT4(0.2f, 0.2f, 0.2f, 1.0f));
		light2->GetComponent<DirectionalLight>()->SetDiffuse(XMFLOAT4(0.3f, 0.3f, 0.3f, 1.0f));
		light2->GetComponent<DirectionalLight>()->SetSpecular(XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f));
		light2->GetTransform()->LootAt(XMFLOAT3(0.707f, -0.707f, 0.0f));
		Application::GetScene()->AddGameObject(light2);

		GameObject* light3 = new GameObject("Light3");
		light3->AddComponent<DirectionalLight>();
		light3->GetComponent<DirectionalLight>()->SetAmbient(XMFLOAT4(0.1f, 0.1f, 0.1f, 1.0f));
		light3->GetComponent<DirectionalLight>()->SetDiffuse(XMFLOAT4(0.1f, 0.1f, 0.1f, 1.0f));
		light3->GetComponent<DirectionalLight>()->SetSpecular(XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f));
		light3->GetTransform()->LootAt(XMFLOAT3(-1.0f, 0.0, 1.0f));
		Application::GetScene()->AddGameObject(light3);
#pragma endregion

		BuildManager::GetInstance()->SetIsRunInBackGround(true);
		Camera::GetInstance()->GetTransform()->SetWorldPosition(0.892062f, 1.23061f, -5.75007f);
		Camera::GetInstance()->GetTransform()->SetWorldRotation(-0.699999f, 3.8f, 0.0f);

		ScheduleManager::GetInstance()->AddSchedule("KeyInput",
			SCHEDULE_FUNC_DECL
			{
			   fpsUI->GetComponent<TextUIRenderer>()->SetText(to_string(GraphicManager::GetInstance()->GetCurrentFps()) + "fps");
			});
	}
	VOID HouseScene::Update()
	{
		float speed = 1.0f;

		if (Input::GetMouseButton(0))
		{
			Camera::GetInstance()->GetTransform()->Rotate(Input::GetMouseMove().y * 0.1f, Input::GetMouseMove().x * 0.1f, 0, false);
		}
		if (Input::GetMouseButton(2))
		{
			Camera::GetInstance()->GetTransform()->LootAt(XMFLOAT3(0.0f, 0.0f, 0.0f));
		}

		if (Input::GetKey(VK_SHIFT))
		{
			speed = 10.0f;
		}

		if (Input::GetKey('F'))
		{
			cout << Camera::GetInstance()->GetTransform()->GetWorldPosition().x << " "
				<< Camera::GetInstance()->GetTransform()->GetWorldPosition().y << " "
				<< Camera::GetInstance()->GetTransform()->GetWorldPosition().z << " " << endl;
			cout << Camera::GetInstance()->GetTransform()->GetWorldRotation().x << " "
				<< Camera::GetInstance()->GetTransform()->GetWorldRotation().y << " "
				<< Camera::GetInstance()->GetTransform()->GetWorldRotation().z << " " << endl;
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