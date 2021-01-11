// stdafx.h : 자주 사용하지만 자주 변경되지는 않는
// 표준 시스템 포함 파일 또는 프로젝트 특정 포함 파일이 들어 있는
// 포함 파일입니다.
//
#pragma once
#pragma warning(disable:4316)

#pragma comment (lib, "fmodex_vc.lib")
#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // 거의 사용되지 않는 내용을 Windows 헤더에서 제외합니다.
// Windows 헤더 파일
#include <Windows.h>
#include <windows.h>

// C 런타임 헤더 파일입니다.
#include <math.h>
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h> 
#include <crtdbg.h>
#include <string.h>

// 여기서 프로그램에 필요한 추가 헤더를 참조합니다.
#pragma once
#include <mmsystem.h>
#include <DirectXMath.h>
#include <DirectXColors.h>
#include <d3d11.h>
#include <d3dcompiler.h>
#include <d3d11sdklayers.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <iterator>
#include <vector>
#include <list>
#include <map>
#include <set>
#include <memory>
#include <typeinfo>
#include <functional>
#include <random>
#include <thread>
#include <future>
#include <numeric>
#include <utility>
#include "DirectX/DirectXTex/DirectXTex.h"
#include "DirectX/DirectX11Effect/d3dx11effect.h"
#include "DirectX/DirectXToolKit/SpriteBatch.h"
#include "DirectX/DirectXToolKit/SpriteFont.h"
#include "DirectX/DirectXToolKit/SimpleMath.h"
#include "PhysXSDK/PhysX/include/PxPhysics.h"
#include "PhysXSDK/PhysX/include/PxPhysicsAPI.h"
#include "PhysXSDK/PhysX/include/PxScene.h"
#include "PhysXSDK/PhysX/include/PxSceneDesc.h"
#include "PhysXSDK/PhysX/include/PxRigidBody.h"
#include "PhysXSDK/PhysX/include/PxShape.h"
#include "PhysXSDK/PhysX/include/PxPhysicsAPI.h"
#include "PhysXSDK/PhysX/include/PxRigidBody.h"
#include "PhysXSDK/PhysX/include/PxQueryReport.h"
#include "PhysXSDK/PhysX/include/task/PxCpuDispatcher.h"
#include "PhysXSDK/PhysX/include/pvd/PxPvdTransport.h"
#include "PhysXSDK/PhysX/include/pvd/PxPvdSceneClient.h"
#include "PhysXSDK/PhysX/include/task/PxTask.h"
#include "PhysXSDK/PhysX/include/PxFiltering.h"
#include "PhysXSDK/PhysX/include/characterkinematic/PxController.h"
#include "PhysXSDK/PhysX/include/characterkinematic/PxCapsuleController.h"
#include "PhysXSDK/PhysX/include/vehicle/PxVehicleSDK.h"
#include "PhysXSDK/PhysX/include/vehicle/PxVehicleDrive4W.h"
#include "PhysXSDK/PhysX/include/vehicle/PxVehicleWheels.h"
#include "PhysXSDK/PhysX/include/vehicle/PxVehicleUtilSetup.h"
#include "PhysXSDK/PhysX/include/characterkinematic/PxControllerManager.h"
#include "PhysXSDK/PhysX/include/geometry/PxSphereGeometry.h"
#include "PhysXSDK/PhysX/include/geometry/PxBoxGeometry.h"
#include "PhysXSDK/PhysX/include/geometry/PxCapsuleGeometry.h"
#include "PhysXSDK/PhysX/include/geometry/PxTriangleMesh.h"
#include "PhysXSDK/PhysX/include/geometry/PxConvexMesh.h"
#include "PhysXSDK/PhysX/include/geometry/PxPlaneGeometry.h"
#include "PhysXSDK/PhysX/include/extensions/PxExtensionsAPI.h"
#include "PhysXSDK/PhysX/include/extensions/PxDefaultSimulationFilterShader.h"
#include "PhysXSDK/PhysX/include/cudamanager/PxCudaContextManager.h"
#include "PhysXSDK/PhysX/include/foundation/PxMathUtils.h"
#include "PhysXSDK/PhysX/include/cooking/PxCooking.h"
#include "PhysXSDK/PhysX/include/cooking/PxBVH33MidphaseDesc.h"
#include "PhysXSDK/PxShared/include/foundation/PxMath.h"
#include "PhysXSDK/PxShared/include/foundation/PxVec3.h"
#include "PhysXSDK/PxShared/include/foundation/PxVec4.h"
#include "TinyXml2/tinyxml2.h"
#include "Fmod/fmod.hpp"

using namespace std::placeholders;
using namespace DirectX::Colors;
using std::cout;
using std::endl;
using std::string;
using std::wstring;
using std::map;
using std::multimap;
using std::list;
using std::bind;
using std::move;
using std::next;
using std::sort;
using std::to_string;
using std::vector;
using std::unique_ptr;
using std::function;
using std::mem_fn;
using std::ifstream;
using std::ofstream;
using std::thread;
using std::async;
using std::wstring;
using std::future;
using std::pair;
using std::stof;
using std::make_pair;
using std::random_device;
using std::default_random_engine;
using std::uniform_int_distribution;
using std::uniform_real_distribution;
using std::bernoulli_distribution;
using std::initializer_list;
using DirectX::XMVECTOR;
using DirectX::XMFLOAT4X4;
using DirectX::XMFLOAT3;
using DirectX::XMFLOAT4;
using DirectX::XMFLOAT2;
using DirectX::XMMATRIX;
using DirectX::XMVECTORF32;
using DirectX::XMVectorSet;
using DirectX::XMVector3Transform;
using DirectX::XMMatrixIdentity;
using DirectX::XMMatrixPerspectiveFovLH;
using DirectX::XMVector3Normalize;
using DirectX::XMVector3Length;
using DirectX::XMVectorSubtract;
using DirectX::XMVector3Cross;
using DirectX::XMVectorReplicate;
using DirectX::XMVectorSet;
using DirectX::XMVectorMultiplyAdd;
using DirectX::XMMatrixRotationAxis;
using DirectX::XMMatrixRotationY;
using DirectX::XMMatrixRotationZ;
using DirectX::XMVectorGetX;
using DirectX::XMVector3Dot;
using DirectX::XMMatrixRotationRollPitchYaw;
using DirectX::XMMatrixAffineTransformation;
using DirectX::XMLoadFloat3;
using DirectX::XMStoreFloat3;
using DirectX::XMMatrixScaling;
using DirectX::XMVector3Project;
using DirectX::XMConvertToRadians;
using DirectX::XMMatrixTranspose;
using DirectX::XMMatrixRotationQuaternion;
using DirectX::XMQuaternionMultiply;
using DirectX::XMQuaternionRotationMatrix;
using DirectX::XMQuaternionRotationNormal;
using DirectX::XMMatrixLookAtLH;
using DirectX::XMMatrixOrthographicOffCenterLH;
using DirectX::XMQuaternionRotationRollPitchYaw;
using DirectX::XMVectorGetX;
using DirectX::SpriteBatch;
using DirectX::SpriteFont;

using physx::PxDefaultAllocator;
using physx::PxDefaultErrorCallback;
using physx::PxFoundation;
using physx::PxCooking;
using physx::PxPhysics;
using physx::PxTolerancesScale;
using physx::PxSceneDesc;
using physx::PxCpuDispatcher;
using physx::PxLightCpuTask;
using physx::PxDefaultCpuDispatcher;
using physx::PxCudaContextManagerDesc;
using physx::PxCudaContextManager;
using physx::PxPvd;
using physx::PxPvdTransport;
using physx::PxSceneFlag;
using physx::PxSceneQueryUpdateMode;
using physx::PxScene;
using physx::PxShape;
using physx::PxPlane;
using physx::PxVec3;
using physx::PxQuat;
using physx::PxF32;
using physx::PxRigidStatic;
using physx::PxRigidDynamic;
using physx::PxTransform;
using physx::PxMaterial;
using physx::PxSphereGeometry;
using physx::PxBoxGeometry;
using physx::PxCapsuleGeometry;
using physx::PxPlaneGeometry;
using physx::PxTriangleMeshGeometry;
using physx::PxTriangleMesh;
using physx::PxTriangleMeshDesc;
using physx::PxFilterFlags;
using physx::PxFilterObjectAttributes;
using physx::PxFilterData;
using physx::PxPairFlags;
using physx::PxU32;
using physx::PxPvdInstrumentationFlag;
using physx::PxDefaultMemoryOutputStream;
using physx::PxTriangleMeshCookingResult;
using physx::PxDefaultMemoryInputData;
using physx::PxCookingParams;
using physx::PxMeshPreprocessingFlag;
using physx::PxMeshCookingHint;
using physx::PxBVH33MidphaseDesc;
using physx::PxPvdSceneClient;
using physx::PxPvdSceneFlag;
using physx::PxFilterFlag;
using physx::PxPairFlag;
using physx::PxMeshScale;
using physx::PxSimulationEventCallback;
using physx::PxSimulationFilterCallback;
using physx::PxConstraintInfo;
using physx::PxActor;
using physx::PxContactPairHeader;
using physx::PxTriggerPair;
using physx::PxRigidBody;
using physx::PxContactPair;
using physx::PxControllerManager;
using physx::PxController;
using physx::PxControllerFilters;
using physx::PxCapsuleController;
using physx::PxCapsuleControllerDesc;
using physx::PxVehicleWheelsSimData;
using physx::PxVehicleDriveSimData4W;
using physx::PxVehicleDrive4W;
using physx::PxVehicleWheelData;
using physx::PxVehicleDrive4WWheelOrder;
using physx::PxVehicleTireData;
using physx::PxVehicleSuspensionData;
using physx::PxVehicleDifferential4WData;
using physx::PxVehicleEngineData;
using physx::PxVehicleGearsData;
using physx::PxVehicleClutchData;
using physx::PxVehicleAckermannGeometryData;
using physx::PxVehicleChassisData;
using physx::PxConvexMesh;
using physx::PxConvexMeshDesc;
using physx::PxConvexMeshGeometry;
using physx::PxFilterObjectIsTrigger;
using physx::PxTransformFromPlaneEquation;
using physx::PxDefaultCpuDispatcherCreate;
using physx::PxDefaultSimulationFilterShader;
using physx::PxCreatePvd;
using physx::PxDefaultPvdSocketTransportCreate;

using FMOD::System;
using FMOD::Sound;
using FMOD::Channel;
using FMOD::System_Create;

namespace DX_Frame
{
	class Object;
	using AnimEvent = function<void(void)>;
	using ButtonEvent = function<void(void)>;
	using CollisionEvent = function<void(Object*)>;
}

#define D3DFMT_3DVERTEX (D3DFVF_XYZ | D3DFVF_TEX1)
#define D3DFMT_2DVERTEX (D3DFVF_XYZRHW | D3DFVF_TEX1)
//#define D3DFMT_UIVERTEX (D3DFVF_XYZRHW | D3DFVF_DIFFUSE)

#define SAFE_DELETE(x) if(x != nullptr) {delete x; x = nullptr;}
#define SAFE_DELETE_ARRAY(x) if(x != nullptr) {delete []x; x = nullptr;}
#define SAFE_RELEASE(x) if(x != nullptr) {x->Release(); x = nullptr;}

#define PVD_HOST "127.0.0.1"
#define DEGREES_TO_RADIANS 0.01745329251f
#define RADIANS_TO_DEGRESS 57.2957795131f

struct Basic32
{
	XMFLOAT3 pos;
	XMFLOAT3 normal;
	XMFLOAT2 tex;
};

struct VertexToPost
{
	XMFLOAT3 pos;
	XMFLOAT2 tex;
};

struct Vertex36
{
	XMFLOAT3 pos;
	XMFLOAT3 normal;
	XMFLOAT2 tex;
	XMFLOAT3 tangent;
	int matNum = 0;
	XMFLOAT4 weights;
	DirectX::XMUINT4 BoneIndices;
};

void InitVertex36(Vertex36& _vertex36, 
				float _posX, float _posY, float _posZ, 
				float _normalX, float  _normalY, float _normalZ, 
				float _tangentX, float  _tangentY, float _tangentZ,	
				float _texX, float _texY,
				int _matNum = 0,
				float _weight1 = 0.0f, float _weight2 = 0.0f, float _weight3 = 0.0f, float _weight4 = 0.0f,
				UINT _BoneIndices1 = 0, UINT _BoneIndices2 = 0, UINT _BoneIndices3 = 0, UINT _BoneIndices4 = 0);

struct Particle
{
	XMFLOAT3 InitialPos;
	XMFLOAT3 InitialVel;
	XMFLOAT2 Size;
	float Age;
	unsigned int Type;
};

class InputLayoutDesc
{
public:
	static const D3D11_INPUT_ELEMENT_DESC Pos[1];
	static const D3D11_INPUT_ELEMENT_DESC Basic32[3];
	static const D3D11_INPUT_ELEMENT_DESC VertexToPost[2];
	static const D3D11_INPUT_ELEMENT_DESC Vertex36[7];
	static const D3D11_INPUT_ELEMENT_DESC Particle[5];
};

class InputLayouts
{
public:
	static void InitAll(ID3D11Device* device);
	static void DestroyAll();

	static ID3D11InputLayout* Pos;
	static ID3D11InputLayout* Vertex36;
	static ID3D11InputLayout* VertexToPost;
	static ID3D11InputLayout* Particle;
};

struct COLOR_RGB
{
	int red, blue, green;
};

struct OBJECT_VERTEX
{
	float x, y, z;
	float tu, tv;
};

struct OBJECT_INDEX
{
	unsigned short _0, _1, _2;
};

struct UI_VERTRX
{
	float x, y, z, rhw;
	float tu, tv;
};

enum class DIRECTION_ENUM : char
{
	FOWORD, BACK, STOP
};

