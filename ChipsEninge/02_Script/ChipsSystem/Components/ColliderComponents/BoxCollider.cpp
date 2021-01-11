#include "ChipsSystem/Components/ColliderComponents/BoxCollider.h"
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
	BoxCollider::BoxCollider() : ACollider("BoxCollider")
	{
	}

	VOID BoxCollider::SetBoxSize(float _x, float _y, float _z)
	{
		float sizeX = Mathf::Clamp(_x, 0.0f, Mathf::Abs(_x));
		float sizeY = Mathf::Clamp(_y, 0.0f, Mathf::Abs(_y));
		float sizeZ = Mathf::Clamp(_z, 0.0f, Mathf::Abs(_z));

	#if defined(DEBUG) | defined(_DEBUG)
		m_scaleMatrix = XMMatrixScaling(sizeX, sizeY, sizeZ);
	#endif

		m_shapeInfo = XMFLOAT4(sizeX, sizeY, sizeZ, 0.0f);
		ResetShape();
	}

	VOID BoxCollider::SetBoxSize(XMFLOAT3 _boxSize)
	{
		SetBoxSize(_boxSize.x, _boxSize.y, _boxSize.z);
	}

	XMFLOAT3 BoxCollider::GetBoxSize()
	{
		return XMFLOAT3(m_shapeInfo.x, m_shapeInfo.y, m_shapeInfo.z);
	}

	VOID BoxCollider::InitShape()
	{
		m_isLoaded = true;

#if defined(DEBUG) | defined(_DEBUG)
		MeshData meshData;
		MeshGenerator::CreateBox(1.0f, 1.0f, 1.0f, meshData);

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

		m_shapeInfo = XMFLOAT4(1.0f, 1.0f, 1.0f, 0.0f);
		m_boxGeometry = PxBoxGeometry(0.5f, 0.5f, 0.5f);
		m_shape = PhysxManager::GetInstance()->GetPhysics()->createShape(m_boxGeometry, *m_material);
		m_shape->setLocalPose(m_pxTransform);
		m_rigidbody->AttachShape(m_shape);
	}

	VOID BoxCollider::ResetShape()
	{
		m_rigidbody->DettachShape(m_shape);
		m_shape->release();

		m_boxGeometry = PxBoxGeometry(m_shapeInfo.x * 0.5f, m_shapeInfo.y * 0.5f, m_shapeInfo.z * 0.5f);
		m_shape = PhysxManager::GetInstance()->GetPhysics()->createShape(m_boxGeometry, *m_material);
		m_shape->setLocalPose(m_pxTransform);
		m_shape->setFlag(physx::PxShapeFlag::eSIMULATION_SHAPE, !m_isTrigger);
		m_shape->setFlag(physx::PxShapeFlag::eTRIGGER_SHAPE, m_isTrigger);
		m_rigidbody->AttachShape(m_shape);
	}
}