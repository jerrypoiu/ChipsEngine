#include "ObjRenderer.h"
#include "ChipsSystem/Global/Global.h"
#include "ChipsSystem/BasicFrame/GameObject.h"
#include "ChipsSystem/Camera/Camera.h"
#include "ChipsSystem/Components/BaiscComponents/Transform.h"
#include "ChipsSystem/Etc/Mathf.h"
#include "ChipsSystem/Etc/Debug.h"
#include "DirectX/Effects/RenderStates.h"
#include "DirectX/Effects/Effects.h"

namespace ChipsFrame
{
	ObjRenderer::ObjRenderer() : Component("MeshRenderer"), m_isLoaded(false)
	{
	}

	VOID ObjRenderer::LoadMesh(string _meshFilePath)
	{
		if (m_isLoaded)
			return;

		m_isLoaded = true;
		int _vertexCount, _textureCount, _normalCount, _faceCount;
		ReadFileCounts(_meshFilePath, _vertexCount, _textureCount, _normalCount, _faceCount);
		LoadDataStructures(_meshFilePath, _vertexCount, _textureCount, _normalCount, _faceCount);
		InitGemometryBuffer();
	}

	VOID ObjRenderer::LoadTexture(const string _fileName)
	{
		wstring ws(_fileName.begin(), _fileName.end());
		DirectX::ScratchImage image;
		DirectX::LoadFromDDSFile(ws.c_str(), DirectX::DDS_FLAGS_NONE, nullptr, image);
		DirectX::CreateShaderResourceView(Global::g_d3dDevice, image.GetImages(), image.GetImageCount(), image.GetMetadata(), &m_meshSRV);
	}

	VOID ObjRenderer::SetTextureTiling(float _x, float _y)
	{
		XMMATRIX texScale = XMMatrixScaling(_x, _y, 1.0f);
		XMStoreFloat4x4(&m_texTransform, texScale);
	}

	VOID ObjRenderer::ReadFileCounts(string _filename, int& _vertexCount, int& _textureCount, int& _normalCount, int& _faceCount)
	{
		ifstream fin;
		char input;
		_vertexCount = 0;
		_textureCount = 0;
		_normalCount = 0;
		_faceCount = 0;

		fin.open(_filename);

		if (fin.fail() == true)
		{
			Debug::ErrorMessage("check your mesh file or path", "Mesh load error");
		}

		fin.get(input);
		while (!fin.eof())
		{
			if (input == 'v')
			{
				fin.get(input);
				if (input == ' ') { _vertexCount++; }
				if (input == 't') { _textureCount++; }
				if (input == 'n') { _normalCount++; }
			}

			if (input == 'f')
			{
				fin.get(input);
				if (input == ' ') { _faceCount++; }
			}

			while (input != '\n')
			{
				fin.get(input);
			}

			fin.get(input);
		}
		fin.close();
	}

	VOID ObjRenderer::LoadDataStructures(string _filename, int _vertexCount, int _textureCount, int _normalCount, int _faceCount)
	{
		struct VertexType
		{
			float x, y, z;
		};

		struct FaceType
		{
			int vIndex1, vIndex2, vIndex3;
			int tIndex1, tIndex2, tIndex3;
			int nIndex1, nIndex2, nIndex3;
		};

		vector<VertexType> vertices(_vertexCount);
		vector<VertexType> texcoords(_textureCount);
		vector<VertexType> normals(_normalCount);
		vector<FaceType> faces(_faceCount);
		ifstream fin(_filename);
		char input = '\0';
		char input2 = '\0';
		int vertexIndex = 0;
		int texcoordIndex = 0;
		int normalIndex = 0;
		int faceIndex = 0;
		int vIndex = 0;
		int tIndex = 0;
		int nIndex = 0;

		if (fin.fail() == true)
		{
			Debug::ErrorMessage("check your mesh file or path", "Mesh load error");
		}

		fin.get(input);
		while (!fin.eof())
		{
			if (input == 'v')
			{
				fin.get(input);

				if (input == ' ')
				{
					fin >> vertices[vertexIndex].x >> vertices[vertexIndex].y >> vertices[vertexIndex].z;
					vertices[vertexIndex].z = vertices[vertexIndex].z * -1.0f;
					vertexIndex++;
				}

				if (input == 't')
				{
					fin >> texcoords[texcoordIndex].x >> texcoords[texcoordIndex].y;
					texcoords[texcoordIndex].y = 1.0f - texcoords[texcoordIndex].y;
					texcoordIndex++;
				}

				if (input == 'n')
				{
					fin >> normals[normalIndex].x >> normals[normalIndex].y >> normals[normalIndex].z;
					normals[normalIndex].z = normals[normalIndex].z * -1.0f;
					normalIndex++;
				}
			}

			if (input == 'f')
			{
				fin.get(input);
				if (input == ' ')
				{
					fin >> faces[faceIndex].vIndex3 >> input2 >> faces[faceIndex].tIndex3 >> input2 >> faces[faceIndex].nIndex3
						>> faces[faceIndex].vIndex2 >> input2 >> faces[faceIndex].tIndex2 >> input2 >> faces[faceIndex].nIndex2
						>> faces[faceIndex].vIndex1 >> input2 >> faces[faceIndex].tIndex1 >> input2 >> faces[faceIndex].nIndex1;
					faceIndex++;
				}
			}

			while (input != '\n')
			{
				fin.get(input);
			}

			fin.get(input);
		}
		fin.close();

		//MeshData »ý¼º
		Vertex32 vertex;
		for (int i = 0; i < faceIndex; i++)
		{
			vIndex = faces[i].vIndex1 - 1;
			tIndex = faces[i].tIndex1 - 1;
			nIndex = faces[i].nIndex1 - 1;

			vertex.pos.x = vertices[vIndex].x;
			vertex.pos.y = vertices[vIndex].y; 
			vertex.pos.z = vertices[vIndex].z;
			vertex.normal.x = normals[nIndex].x; 
			vertex.normal.y = normals[nIndex].y;
			vertex.normal.z = normals[nIndex].z;
			vertex.yex.x = texcoords[tIndex].x;  
			vertex.yex.y = texcoords[tIndex].y;
			m_meshData.Vertices.push_back(vertex);

			vIndex = faces[i].vIndex2 - 1;
			tIndex = faces[i].tIndex2 - 1;
			nIndex = faces[i].nIndex2 - 1;

			vertex.pos.x = vertices[vIndex].x;
			vertex.pos.y = vertices[vIndex].y;
			vertex.pos.z = vertices[vIndex].z;
			vertex.normal.x = normals[nIndex].x;
			vertex.normal.y = normals[nIndex].y;
			vertex.normal.z = normals[nIndex].z;
			vertex.yex.x = texcoords[tIndex].x;
			vertex.yex.y = texcoords[tIndex].y;
			m_meshData.Vertices.push_back(vertex);

			vIndex = faces[i].vIndex3 - 1;
			tIndex = faces[i].tIndex3 - 1;
			nIndex = faces[i].nIndex3 - 1;

			vertex.pos.x = vertices[vIndex].x;
			vertex.pos.y = vertices[vIndex].y;
			vertex.pos.z = vertices[vIndex].z;
			vertex.normal.x = normals[nIndex].x;
			vertex.normal.y = normals[nIndex].y;
			vertex.normal.z = normals[nIndex].z;
			vertex.yex.x = texcoords[tIndex].x;
			vertex.yex.y = texcoords[tIndex].y;
			m_meshData.Vertices.push_back(vertex);
		}
	}

	VOID ObjRenderer::InitGemometryBuffer()
	{
		vector<Basic32> vertecBufferIn(m_meshData.Vertices.size());
		m_meshData.Indices.resize(m_meshData.Vertices.size());

		for (size_t i = 0; i < m_meshData.Vertices.size(); ++i)
		{
			vertecBufferIn[i].pos = m_meshData.Vertices[i].pos;
			vertecBufferIn[i].normal = m_meshData.Vertices[i].normal;
			vertecBufferIn[i].yex = m_meshData.Vertices[i].yex;
			m_meshData.Indices[i] = i;
		}

		D3D11_BUFFER_DESC vbd;
		vbd.Usage = D3D11_USAGE_IMMUTABLE;
		vbd.ByteWidth = sizeof(Basic32) * vertecBufferIn.size();
		vbd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		vbd.CPUAccessFlags = 0;
		vbd.MiscFlags = 0;
		vbd.StructureByteStride = 0;

		D3D11_SUBRESOURCE_DATA vinitData;
		vinitData.pSysMem = &vertecBufferIn[0];

		Global::g_d3dDevice->CreateBuffer(&vbd, &vinitData, &m_vertexBuffer);

		m_indexCount = m_meshData.Indices.size();

		D3D11_BUFFER_DESC ibd;
		ibd.Usage = D3D11_USAGE_IMMUTABLE;
		ibd.ByteWidth = sizeof(UINT) * m_indexCount;
		ibd.BindFlags = D3D11_BIND_INDEX_BUFFER;
		ibd.CPUAccessFlags = 0;
		ibd.StructureByteStride = 0;
		ibd.MiscFlags = 0;

		std::vector<UINT> indices16;
		indices16.assign(m_meshData.Indices.begin(), m_meshData.Indices.end());

		D3D11_SUBRESOURCE_DATA iinitData;
		iinitData.pSysMem = &indices16[0];

		Global::g_d3dDevice->CreateBuffer(&ibd, &iinitData, &m_indexBuffer);
	}

	VOID ObjRenderer::BuildMaterial()
	{
		m_material.Ambient = XMFLOAT4(0.8f, 0.8f, 0.8f, 1.0f);
		m_material.Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
		m_material.Specular = XMFLOAT4(0.4f, 0.4f, 0.4f, 16.0f);
		m_material.Reflect = XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f);
	}

	VOID ObjRenderer::Init()
	{
		BuildMaterial();
		SetTextureTiling(1.0f, 1.0f);
	}

	VOID ObjRenderer::Update()
	{
	}

	VOID ObjRenderer::Render()
	{
		if (m_isLoaded == false)
			return;

		UINT stride = sizeof(Basic32);
		UINT offset = 0;
		float blendFactor[] = { 0.0f, 0.0f, 0.0f, 0.0f };

		XMMATRIX view = Camera::GetInstance()->View();
		XMMATRIX proj = Camera::GetInstance()->Proj();
		XMMATRIX worldViewProj = GetGameObject()->GetTransform()->GetWorldMatrix() * view * proj;
		XMMATRIX worldInvTranspose = Mathf::InverseTranspose(GetGameObject()->GetTransform()->GetWorldMatrix());

		Global::g_d3dImmediateContext->RSSetState(RenderStates::NoCullRS);
		Global::g_d3dImmediateContext->IASetInputLayout(InputLayouts::Basic32);
		Global::g_d3dImmediateContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
		Global::g_d3dImmediateContext->IASetVertexBuffers(0, 1, &m_vertexBuffer, &stride, &offset);
		Global::g_d3dImmediateContext->IASetIndexBuffer(m_indexBuffer, DXGI_FORMAT_R32_UINT, 0);

		ID3DX11EffectTechnique* activeTexTech = Effects::BasicFX->Light3TexTech;

		D3DX11_TECHNIQUE_DESC techDesc;
		activeTexTech->GetDesc(&techDesc);

		Effects::BasicFX->SetWorld(GetGameObject()->GetTransform()->GetWorldMatrix());
		Effects::BasicFX->SetWorldInvTranspose(worldInvTranspose);
		Effects::BasicFX->SetWorldViewProj(worldViewProj);
		Effects::BasicFX->SetTexTransform(XMLoadFloat4x4(&m_texTransform));
		Effects::BasicFX->SetMaterial(m_material);
		Effects::BasicFX->SetDiffuseMap(m_meshSRV);
		Effects::BasicFX->SetEyePosW(Camera::GetInstance()->GetTransform()->GetWorldPosition());

		for (UINT p = 0; p < techDesc.Passes; ++p)
		{
			activeTexTech->GetPassByIndex(p)->Apply(0, Global::g_d3dImmediateContext);
			Global::g_d3dImmediateContext->OMSetBlendState(RenderStates::TransparentBS, blendFactor, 0xffffffff);
			Global::g_d3dImmediateContext->DrawIndexed(m_indexCount, 0, 0);
		}
	}

	VOID ObjRenderer::Release()
	{
		SAFE_RELEASE(m_vertexBuffer);
		SAFE_RELEASE(m_indexBuffer);
		SAFE_DELETE(m_tech);
		m_meshSRV->Release();
	}
}