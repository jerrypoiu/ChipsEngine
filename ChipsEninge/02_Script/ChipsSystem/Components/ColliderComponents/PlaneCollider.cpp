#include "ChipsSystem/Components/ColliderComponents/PlaneCollider.h"
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
	PlaneCollider::PlaneCollider() : ACollider("PlaneCollider"), m_planeHeight(0.005f)
	{

	}

	VOID PlaneCollider::SetFloorSize(float _x, float _z)
	{	
		float sizeX = Mathf::Clamp(_x, 0.0f, Mathf::Abs(_x));
		float sizeZ = Mathf::Clamp(_z, 0.0f, Mathf::Abs(_z));

#if defined(DEBUG) | defined(_DEBUG)
		m_scaleMatrix = XMMatrixScaling(sizeX, 1.0f, sizeZ);
#endif
		m_shapeInfo = XMFLOAT4(sizeX, m_planeHeight, sizeZ, 0.0f);
		ResetShape();
	}	

	VOID PlaneCollider::SetFloorSize(XMFLOAT2 _planeSize)
	{
		SetFloorSize(_planeSize.x, _planeSize.y);
	}

	XMFLOAT2 PlaneCollider::GetFloorSize()
	{
		return XMFLOAT2(m_shapeInfo.x, m_shapeInfo.z);
	}
	
	VOID PlaneCollider::InitShape()
	{
		m_isLoaded = true;
		
#if defined(DEBUG) | defined(_DEBUG)
		MeshData meshData;
		MeshGenerator::CreateBox(1.0f, 0.005f, 1.0f, meshData);

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

		m_shapeInfo = XMFLOAT4(1.0f, m_planeHeight, 1.0f, 0.0f);
		m_planeGeometry = PxBoxGeometry(0.5f, m_planeHeight, 0.5f);
		m_material->setRestitution(0.0f);
		m_shape = PhysxManager::GetInstance()->GetPhysics()->createShape(m_planeGeometry, *m_material);
		m_shape->setLocalPose(m_pxTransform);
		m_rigidbody->AttachShape(m_shape);
	}

	VOID PlaneCollider::ResetShape()
	{
		m_rigidbody->DettachShape(m_shape);
		m_shape->release();

		m_planeGeometry = PxBoxGeometry(m_shapeInfo.x * 0.5f, m_planeHeight, m_shapeInfo.z * 0.5f);
		m_shape = PhysxManager::GetInstance()->GetPhysics()->createShape(m_planeGeometry, *m_material);
		m_shape->setLocalPose(m_pxTransform);
		m_shape->setFlag(physx::PxShapeFlag::eSIMULATION_SHAPE, !m_isTrigger);
		m_shape->setFlag(physx::PxShapeFlag::eTRIGGER_SHAPE, m_isTrigger);
		m_rigidbody->AttachShape(m_shape);
	}
}