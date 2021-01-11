#include "ChipsSystem/Components/RendererComponents/FbxRenderer.h"
#include "ChipsSystem/Global/Global.h"
#include "DirectX/MeshGenerator/MeshGenerator.h"
#include "ChipsSystem/Etc/FbxLoader.h"

namespace ChipsEngine
{
	FbxRenderer::FbxRenderer() : AMeshRenderer("FbxRenderer")
	{
	}

	VOID FbxRenderer::LoadMesh(string _meshFilePath, int _meshIndex)
	{
		if (m_isLoaded)
			return;

		m_isLoaded = true;
		FbxLoader::GetInstance()->LoadFbx(_meshFilePath, m_meshData.Vertices, m_meshData.Indices, _meshIndex);
		InitGemometryBuffer();
	}

	VOID FbxRenderer::InitGemometryBuffer()
	{
		if (m_isLoaded == false)
			return;

		D3D11_BUFFER_DESC vbd;
		vbd.Usage = D3D11_USAGE_IMMUTABLE;
		vbd.ByteWidth = sizeof(Vertex36) * m_meshData.Vertices.size();
		vbd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		vbd.CPUAccessFlags = 0;
		vbd.MiscFlags = 0;
		vbd.StructureByteStride = 0;

		D3D11_SUBRESOURCE_DATA vinitData;
		vinitData.pSysMem = &m_meshData.Vertices[0];

		Global::g_d3dDevice->CreateBuffer(&vbd, &vinitData, &m_vertexBuffer);

		m_indexCount = m_meshData.Indices.size();

		D3D11_BUFFER_DESC ibd;
		ibd.Usage = D3D11_USAGE_IMMUTABLE;
		ibd.ByteWidth = sizeof(UINT) * m_indexCount;
		ibd.BindFlags = D3D11_BIND_INDEX_BUFFER;
		ibd.CPUAccessFlags = 0;
		ibd.StructureByteStride = 0;
		ibd.MiscFlags = 0;

		D3D11_SUBRESOURCE_DATA iinitData;
		iinitData.pSysMem = &m_meshData.Indices[0];

		Global::g_d3dDevice->CreateBuffer(&ibd, &iinitData, &m_indexBuffer);
	}
}