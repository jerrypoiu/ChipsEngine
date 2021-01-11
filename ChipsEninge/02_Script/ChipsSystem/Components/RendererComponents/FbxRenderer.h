#ifndef CHIPSSYSTEM_COMPONENETS_RENDERERCOMPONENETS_FBXRENDERER_H
#define CHIPSSYSTEM_COMPONENETS_RENDERERCOMPONENETS_FBXRENDERER_H
#include "DirectX/Effects/LightHelper.h"
#include "ChipsSystem/Components/RendererComponents/AMeshRenderer.h"
#include "DirectX/MeshGenerator/MeshGenerator.h"

namespace ChipsEngine
{
	/*
	.fbx 파일을 렌더링하는 컴포넌트이다.
	애니메이션이 적용되지 않는 파일을 렌더링할 때 사용한다.
	유니티의 MeshRenderer와 용도가 같다.
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