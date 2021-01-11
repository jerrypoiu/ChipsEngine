#include "ChipsSystem/Components/ColliderComponents/SphereCollider.h"
#include "ChipsSystem/Global/Global.h"
#include "ChipsSystem/Etc/Mathf.h"
#include "DirectX/MeshGenerator/MeshGenerator.h"

namespace ChipsEngine
{
	SphereCollider::SphereCollider() : ACollider("SphereCollider")
	{
	}

	float SphereCollider::GetRadius()
	{
		return GetCollisionInfoSecondValue().w;
	}

	VOID SphereCollider::SetRadius(float _radius)
	{
		float value = _radius * 2.0f;
		SetCollisionInfoSecondValue(XMFLOAT4(value, value, value, _radius));
	}

#ifdef _DEBUG
	VOID SphereCollider::InitGemometryBuffer()
	{
		m_isLoaded = true;
		MeshData meshData;
		MeshGenerator::CreateSphere(0.5f, 30, 30, meshData);

		vector<Basic32> vertices(meshData.Vertices.size());
		for (UINT i = 0; i < meshData.Vertices.size(); ++i)
		{
			vertices[i].pos = meshData.Vertices[i].pos;
			vertices[i].normal = meshData.Vertices[i].normal;
			vertices[i].tex = meshData.Vertices[i].tex;
		}

		D3D11_BUFFER_DESC vbd;
		vbd.Usage = D3D11_USAGE_IMMUTABLE;
		vbd.ByteWidth = sizeof(Basic32) * vertices.size();
		vbd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		vbd.CPUAccessFlags = 0;
		vbd.MiscFlags = 0;
		vbd.StructureByteStride = 0;

		D3D11_SUBRESOURCE_DATA vinitData;
		vinitData.pSysMem = &vertices[0];

		Global::g_d3dDevice->CreateBuffer(&vbd, &vinitData, &m_vertexBuffer);

		m_indexCount = meshData.Indices.size();

		D3D11_BUFFER_DESC ibd;
		ibd.Usage = D3D11_USAGE_IMMUTABLE;
		ibd.ByteWidth = sizeof(UINT) * m_indexCount;
		ibd.BindFlags = D3D11_BIND_INDEX_BUFFER;
		ibd.CPUAccessFlags = 0;
		ibd.StructureByteStride = 0;
		ibd.MiscFlags = 0;

		std::vector<UINT> indices16;
		indices16.assign(meshData.Indices.begin(), meshData.Indices.end());

		D3D11_SUBRESOURCE_DATA iinitData;
		iinitData.pSysMem = &indices16[0];

		Global::g_d3dDevice->CreateBuffer(&ibd, &iinitData, &m_indexBuffer);
	}
#endif

	VOID SphereCollider::Init()
	{
		ACollider::Init();
		SetCollisionInfoSecondValue(XMFLOAT4(1.0f, 1.0f, 1.0f, 0.5f));
		SetCollisionShpae(COLLISION_SHAPE::SPHERE);
	}
}