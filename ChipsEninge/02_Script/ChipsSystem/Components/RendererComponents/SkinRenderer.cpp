#include "ChipsSystem/Components/BaiscComponents/Animator.h"
#include "ChipsSystem/Components/RendererComponents/SkinRenderer.h"
#include "ChipsSystem/Global/Global.h"
#include "ChipsSystem/Etc/FbxLoader.h"
#include "DirectX/MeshGenerator/MeshGenerator.h"
#include "DirectX/Effects/Effects.h"

namespace ChipsEngine
{
	SkinRenderer::SkinRenderer() : AMeshRenderer("SkinRenderer"), m_animator(nullptr)
	{
		for (int i = 0; i < 96; i++)
		{
			m_finalTransforms.emplace_back(XMMATRIX());
			m_boneTransforms.emplace_back(XMMATRIX());
		}
	}

	VOID SkinRenderer::SetAnimator(Animator* _animator)
	{
		if (_animator == nullptr)
			return;

		m_animator = _animator;
		m_animator->m_skinRenderer = this;
	}

	VOID SkinRenderer::LoadMesh(string _meshFilePath, int _meshIndex)
	{
		if (m_isLoaded)
			return;

		m_isLoaded = true;
		
		FbxLoader::GetInstance()->LoadFbx(_meshFilePath, m_meshData.Vertices, m_meshData.Indices, _meshIndex, true);
		vector<XMFLOAT4X4> smatrix = FbxLoader::GetInstance()->GetSkeletonMatrix();
		UINT count = smatrix.size();
		for (UINT i = 0; i < count; i++)
		{		
			m_boneTransforms[i] = XMLoadFloat4x4(&smatrix[i]);
		}
		
		InitGemometryBuffer();
	}

	VOID SkinRenderer::InitGemometryBuffer()
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

	VOID SkinRenderer::SetShaderSkinningValues()
	{
		if (m_isLoaded)
		{
			Effects::StandardShaderFX->SetUseSkinning(true);
			Effects::StandardShaderFX->SetBoneTransforms(&m_finalTransforms[0], m_finalTransforms.size());
		}
		else
		{
			Effects::StandardShaderFX->SetUseSkinning(false);
		}
	}

	VOID SkinRenderer::SetShaderSkinningShadowValues()
	{
		if (m_isLoaded)
		{
			Effects::BuildShadowMapFX->SetUseSkinning(true);
			Effects::BuildShadowMapFX->SetBoneTransforms(&m_finalTransforms[0], m_finalTransforms.size());
		}
		else
		{
			Effects::BuildShadowMapFX->SetUseSkinning(false);
		}
	}
}