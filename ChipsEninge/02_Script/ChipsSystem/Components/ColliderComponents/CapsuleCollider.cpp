#include "ChipsSystem/Components/ColliderComponents/CapsuleCollider.h"
#include "ChipsSystem/BasicFrame/GameObject.h"
#include "ChipsSystem/Components/BaiscComponents/Rigidbody.h"
#include "ChipsSystem/Manager/PhysxManager.h"
#include "ChipsSystem/Etc/Mathf.h"

#if defined(DEBUG) | defined(_DEBUG)
#include "ChipsSystem/Camera/Camera.h"
#include "ChipsSystem/Global/Global.h"
#include "DirectX/Effects/Effects.h"
#include "DirectX/Effects/RenderStates.h"
#include "DirectX/MeshGenerator/MeshGenerator.h"
#endif

namespace ChipsEngine
{
	CapsuleCollider::CapsuleCollider() : ACollider("CapsuleCollider")
	{
	}

	VOID CapsuleCollider::SetCapsuleSize(float _raduis, float _halfHeight)
	{		
		float raduis = Mathf::Clamp(_raduis, 0.0f, Mathf::Abs(_raduis));
		float halfHeight = Mathf::Clamp(_halfHeight, 0.0f, Mathf::Abs(_halfHeight));

		m_shapeInfo.x = raduis;
		m_shapeInfo.y = halfHeight;

		m_capsuleGeometry.radius = raduis;
		m_capsuleGeometry.halfHeight = halfHeight;

		ResetShape();
	}

	VOID CapsuleCollider::SetCapsuleSize(XMFLOAT2 _capsuleSize)
	{
		SetCapsuleSize(_capsuleSize.x, _capsuleSize.y);
	}

	XMFLOAT2 CapsuleCollider::GetCapsuleSize()
	{
		return XMFLOAT2(m_shapeInfo.x, m_shapeInfo.y);
	}

	VOID CapsuleCollider::InitShape()
	{
		m_isLoaded = true;

		m_shapeInfo.x = 0.5f;
		m_shapeInfo.y = 0.5f;
		m_capsuleGeometry.radius = 0.5f;
		m_capsuleGeometry.halfHeight = 0.5f;

#if defined(DEBUG) | defined(_DEBUG)
		MeshData meshData;
		MeshGenerator::CreateCapsule(m_shapeInfo.x, m_shapeInfo.y, meshData);

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

		m_capsuleGeometry = PxCapsuleGeometry(0.5f, 0.5f);
		m_shape = PhysxManager::GetInstance()->GetPhysics()->createShape(m_capsuleGeometry, *m_material);
		PxTransform relativePose(PxQuat(physx::PxHalfPi, PxVec3(0, 0, 1)));
		m_shape->setLocalPose(relativePose);
		m_rigidbody->AttachShape(m_shape);
	}

	VOID CapsuleCollider::ResetShape()
	{
		m_rigidbody->DettachShape(m_shape);
		m_shape->release();

#if defined(DEBUG) | defined(_DEBUG)
		SAFE_RELEASE(m_vertexBuffer);
		SAFE_RELEASE(m_indexBuffer);

		MeshData meshData;
		MeshGenerator::CreateCapsule(m_shapeInfo.x, m_shapeInfo.y, meshData);

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
		m_shape = PhysxManager::GetInstance()->GetPhysics()->createShape(m_capsuleGeometry, *m_material);
		PxTransform relativePose(PxQuat(physx::PxHalfPi, PxVec3(0, 0, 1)));
		m_shape->setLocalPose(relativePose);
		m_shape->setFlag(physx::PxShapeFlag::eSIMULATION_SHAPE, !m_isTrigger);
		m_shape->setFlag(physx::PxShapeFlag::eTRIGGER_SHAPE, m_isTrigger);
		m_rigidbody->AttachShape(m_shape);
	}
}