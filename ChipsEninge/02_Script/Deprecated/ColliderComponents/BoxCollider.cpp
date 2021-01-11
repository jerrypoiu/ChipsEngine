#include "ChipsSystem/Components/ColliderComponents/BoxCollider.h"
#include "ChipsSystem/Global/Global.h"
#include "ChipsSystem/Etc/Mathf.h"
#include "DirectX/MeshGenerator/MeshGenerator.h"

namespace ChipsEngine
{
	BoxCollider::BoxCollider() : ACollider("BoxCollider")
	{
	}

	VOID BoxCollider::SetBoxSize(float _x, float _y, float _z)
	{
		float sizeX = Mathf::Abs(_x);
		float sizeY = Mathf::Abs(_y);
		float sizeZ = Mathf::Abs(_z);
		float radius = 0.0f;

		radius = sizeX;

		if (radius < sizeY)
		{
			radius = sizeY;
		}

		if (radius < sizeZ)
		{
			radius = sizeZ;
		}

		SetCollisionInfoSecondValue(XMFLOAT4(sizeX, sizeY, sizeZ, radius));
	}

	VOID BoxCollider::SetBoxSize(XMFLOAT3 _boxSize)
	{
		SetBoxSize(_boxSize.x, _boxSize.y, _boxSize.z);
	}

	XMFLOAT3 BoxCollider::GetBoxSize()
	{
		XMFLOAT4 collisonData = GetCollisionInfoSecondValue();
		return XMFLOAT3(collisonData.x, collisonData.y, collisonData.z);
	}

#ifdef _DEBUG
	VOID BoxCollider::InitGemometryBuffer()
	{
		m_isLoaded = true;
		MeshData meshData;
		MeshGenerator::CreateBox(1.0f, 1.0f, 1.0f, meshData);

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

	VOID BoxCollider::Init()
	{
		ACollider::Init();
		SetCollisionInfoSecondValue(XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f));
		SetCollisionShpae(COLLISION_SHAPE::BOX);
	}
}