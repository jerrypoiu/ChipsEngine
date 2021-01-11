#ifndef CHIPSSYSTEM_COMPONENETS_RENDERERCOMPONENETS_FBXRENDERER_H
#define CHIPSSYSTEM_COMPONENETS_RENDERERCOMPONENETS_FBXRENDERER_H
#include "DirectX/Effects/LightHelper.h"
#include "ChipsSystem/Components/RendererComponents/AMeshRenderer.h"
#include "DirectX/MeshGenerator/MeshGenerator.h"

namespace ChipsEngine
{
	/*
	.fbx ������ �������ϴ� ������Ʈ�̴�.
	�ִϸ��̼��� ������� �ʴ� ������ �������� �� ����Ѵ�.
	����Ƽ�� MeshRenderer�� �뵵�� ����.
	*/
	class FbxRenderer final : public AMeshRenderer
	{
	private:
		MeshData m_meshData;
	public:
		FbxRenderer();
	protected:
		virtual ~FbxRenderer() = default;
	public:		
	 	inline MeshData GetMeshData()
		{
			return m_meshData;
		}
		virtual VOID LoadMesh(string _meshFilePath, int _meshIndex = 0);
	private:
		virtual VOID InitGemometryBuffer() override;
	};
}

#endif //CHIPSSYSTEM_COMPONENETS_RENDERERCOMPONENETS_MESHRENDERER_H