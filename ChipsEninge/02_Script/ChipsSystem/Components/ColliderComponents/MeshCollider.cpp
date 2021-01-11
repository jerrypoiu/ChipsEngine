#include "ChipsSystem/Components/ColliderComponents/MeshCollider.h"
#include "ChipsSystem/BasicFrame/GameObject.h"
#include "ChipsSystem/Components/BaiscComponents/Rigidbody.h"
#include "ChipsSystem/Manager/PhysxManager.h"
#include "ChipsSystem/Etc/Mathf.h"
#include "ChipsSystem/Etc/Debug.h"

#if defined(DEBUG) | defined(_DEBUG)
#include "ChipsSystem/Camera/Camera.h"
#include "ChipsSystem/Global/Global.h"
#include "DirectX/Effects/Effects.h"
#include "DirectX/Effects/RenderStates.h"
#include "DirectX/MeshGenerator/MeshGenerator.h"
#endif

namespace ChipsEngine
{
	MeshCollider::MeshCollider() : ACollider("MeshCollider")
	{
		m_shapeInfo = XMFLOAT4(1.0f, 1.0f, 1.0f, 0.0f);
	}

	XMFLOAT3 MeshCollider::GetMeshScale()
	{
		return XMFLOAT3(m_shapeInfo.x, m_shapeInfo.y, m_shapeInfo.z);
	}
	
	VOID MeshCollider::SetMeshScale(float _x, float _y, float _z)
	{
		if (m_isLoaded == false)
		{
			Debug::Log("WARNING : You tried to modify the size without loading the mesh. \"" + GetGameObject()->GetName() + "\" GameObject.", LOG_TYPE::WARING_LOG);
			return;
		}

		float sizeX = Mathf::Clamp(_x, 0.0f, Mathf::Abs(_x));
		float sizeY = Mathf::Clamp(_y, 0.0f, Mathf::Abs(_y));
		float sizeZ = Mathf::Clamp(_z, 0.0f, Mathf::Abs(_z));

#if defined(DEBUG) | defined(_DEBUG)
		m_scaleMatrix = XMMatrixScaling(sizeX, sizeY, sizeZ);
#endif

		m_shapeInfo = XMFLOAT4(sizeX, sizeY, sizeZ, 0.0f);

		ResetShape();
	}

	VOID MeshCollider::SetMeshScale(XMFLOAT3 _meshScale)
	{
		SetMeshScale(_meshScale.x, _meshScale.y, _meshScale.z);
	}
	
	VOID MeshCollider::SetMesh(FbxRenderer* _fbxRenderer)
	{
		MeshData meshData = _fbxRenderer->GetMeshData();

#if defined(DEBUG) | defined(_DEBUG)
		D3D11_BUFFER_DESC vbd;
		vbd.Usage = D3D11_USAGE_IMMUTABLE;
		vbd.ByteWidth = sizeof(Vertex36) * meshData.Vertices.size();
		vbd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		vbd.CPUAccessFlags = 0;
		vbd.MiscFlags = 0;
		vbd.StructureByteStride = 0;

		D3D11_SUBRESOURCE_DATA vinitData;
		vinitData.pSysMem = &meshData.Vertices[0];

		Global::g_d3dDevice->CreateBuffer(&vbd, &vinitData, &m_vertexBuffer);

		m_indexCount = meshData.Indices.size();

		D3D11_BUFFER_DESC ibd;
		ibd.Usage = D3D11_USAGE_IMMUTABLE;
		ibd.ByteWidth = sizeof(UINT) * m_indexCount;
		ibd.BindFlags = D3D11_BIND_INDEX_BUFFER;
		ibd.CPUAccessFlags = 0;
		ibd.StructureByteStride = 0;
		ibd.MiscFlags = 0;

		D3D11_SUBRESOURCE_DATA iinitData;
		iinitData.pSysMem = &meshData.Indices[0];

		Global::g_d3dDevice->CreateBuffer(&ibd, &iinitData, &m_indexBuffer);
#endif
		std::vector<PxVec3> vertices;

		for (auto element : meshData.Vertices)
		{
			vertices.emplace_back(PxVec3(element.pos.x, element.pos.y, element.pos.z));
		}

		std::vector<PxU32> triangels;

		for (auto element : meshData.Indices)
		{
			triangels.emplace_back(PxU32(element));
		}

		m_triangleMeshDesc.setToDefault();
		m_triangleMeshDesc.points.count = vertices.size();
		m_triangleMeshDesc.points.stride = sizeof(PxVec3);
		m_triangleMeshDesc.points.data = &vertices[0];

		m_triangleMeshDesc.triangles.count = triangels.size() / 3;
		m_triangleMeshDesc.triangles.stride = sizeof(PxU32) * 3;
		m_triangleMeshDesc.triangles.data = &triangels[0];

		m_shapeInfo = XMFLOAT4(1.0f, 1.0f, 1.0f, 0.0f);

		SetDefaultParams();

		PxDefaultMemoryOutputStream outBuffer;
		PhysxManager::GetInstance()->GetCooking()->cookTriangleMesh(m_triangleMeshDesc, outBuffer);
		PxDefaultMemoryInputData stream(outBuffer.getData(), outBuffer.getSize());
		m_triangleMesh = PhysxManager::GetInstance()->GetPhysics()->createTriangleMesh(stream);
		m_isLoaded = true;

		if (!m_isLoaded)
			return;

		PxMeshScale scale(PxVec3(1.0f, 1.0f, 1.0f));
		m_triangleMeshGeometry = PxTriangleMeshGeometry(m_triangleMesh, scale);

		if (m_rigidbody->GetKinematic() == false)
		{
			Debug::Log("WARNING : When using MeshCollider, Rigidbody must be kinematic mode. ", LOG_TYPE::WARING_LOG);
			Debug::Log("WARNING : Rigidbody changed to kinematic mode.", LOG_TYPE::WARING_LOG);

			m_rigidbody->SetKinematic(true);
		}

		m_shape = PhysxManager::GetInstance()->GetPhysics()->createShape(m_triangleMeshGeometry, *m_material);
		m_shape->setLocalPose(m_pxTransform);
		m_rigidbody->AttachShape(m_shape);
	}

	VOID MeshCollider::SetDefaultParams()
	{
		PxCookingParams params = PhysxManager::GetInstance()->GetCooking()->getParams();
		params.midphaseDesc = physx::PxMeshMidPhase::eBVH33;
		params.suppressTriangleMeshRemapTable = true;
		params.meshPreprocessParams |= PxMeshPreprocessingFlag::eDISABLE_CLEAN_MESH;
		params.meshPreprocessParams |= PxMeshPreprocessingFlag::eDISABLE_ACTIVE_EDGES_PRECOMPUTE;
		params.midphaseDesc.mBVH33Desc.meshCookingHint = PxMeshCookingHint::eCOOKING_PERFORMANCE;
		params.midphaseDesc.mBVH33Desc.meshSizePerformanceTradeOff = 0.55f;
		PhysxManager::GetInstance()->GetCooking()->setParams(params);
	}

	VOID MeshCollider::InitShape()
	{
	}

	VOID MeshCollider::ResetShape()
	{
		m_rigidbody->DettachShape(m_shape);
		m_shape->release();

		PxMeshScale scale(PxVec3(m_shapeInfo.x, m_shapeInfo.y, m_shapeInfo.z));
		PxTriangleMeshGeometry geom(m_triangleMesh, scale);

		m_shape = PhysxManager::GetInstance()->GetPhysics()->createShape(geom, *m_material);
		m_shape->setLocalPose(m_pxTransform);
		m_shape->setFlag(physx::PxShapeFlag::eSIMULATION_SHAPE, !m_isTrigger);
		m_shape->setFlag(physx::PxShapeFlag::eTRIGGER_SHAPE, m_isTrigger);
		m_rigidbody->AttachShape(m_shape);
	}
}
