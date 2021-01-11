#include "ChipsSystem/Components/ColliderComponents/SphereCollider.h"
#include "ChipsSystem/Components/BaiscComponents/Rigidbody.h"
#include "ChipsSystem/Manager/PhysxManager.h"
#include "ChipsSystem/BasicFrame/GameObject.h"
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
	SphereCollider::SphereCollider() : ACollider("SphereCollider")
	{
	}

	float SphereCollider::GetRadius()
	{
		return m_shapeInfo.w;
	}

	VOID SphereCollider::SetRadius(float _radius)
	{
		_radius = Mathf::Clamp(_radius, 0.0f, Mathf::Abs(_radius));

#if defined(DEBUG) | defined(_DEBUG)
		m_scaleMatrix = XMMatrixScaling(_radius, _radius, _radius);
#endif

		m_shapeInfo = XMFLOAT4(0.0f, 0.0f, 0.0f, _radius);
		m_sphereGeometry.radius = _radius;
		ResetShape();
	}

	VOID SphereCollider::InitShape()
	{
		m_isLoaded = true;	

#if defined(DEBUG) | defined(_DEBUG)
		MeshData meshData;
		MeshGenerator::CreateSphere(0.5f, 15, 15, meshData);

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

		m_shapeInfo = XMFLOAT4(0.0f, 0.0f, 0.0f, 0.5f);
		m_sphereGeometry.radius = 0.5f;

		m_sphereGeometry = PxSphereGeometry(0.5f);
		m_shape = PhysxManager::GetInstance()->GetPhysics()->createShape(m_sphereGeometry, *m_material);
		m_shape->setLocalPose(m_pxTransform);
		m_rigidbody->AttachShape(m_shape);
	}

	VOID SphereCollider::ResetShape()
	{
		m_rigidbody->DettachShape(m_shape);
		m_shape->release();
		m_shape = PhysxManager::GetInstance()->GetPhysics()->createShape(m_sphereGeometry, *m_material);
		m_shape->setLocalPose(m_pxTransform);
		m_shape->setFlag(physx::PxShapeFlag::eSIMULATION_SHAPE, !m_isTrigger);
		m_shape->setFlag(physx::PxShapeFlag::eTRIGGER_SHAPE, m_isTrigger);
		m_rigidbody->AttachShape(m_shape);
	}
}