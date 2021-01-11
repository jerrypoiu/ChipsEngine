#ifndef CHIPSSYSTEM_COMPONENETS_RENDERERCOMPONENETS_SKINRENDERER_H
#define CHIPSSYSTEM_COMPONENETS_RENDERERCOMPONENETS_SKINRENDERER_H

#include "DirectX/Effects/LightHelper.h"
#include "ChipsSystem/Components/RendererComponents/AMeshRenderer.h"
#include "DirectX/MeshGenerator/MeshGenerator.h"

//FBX Loader 수정

namespace ChipsEngine
{
	class Animator;

	/*
	.fbx 파일을 렌더링하는 컴포넌트이다.
	애니메이션이 적용되는 파일을 렌더링할 때 사용한다.
	유니티의 SkinnedMeshRenderer와 용도가 같다.
	*/
	class SkinRenderer final : public AMeshRenderer
	{
	private:
		MeshData m_meshData;
		Animator* m_animator;
		vector<XMMATRIX> m_finalTransforms;
		vector<XMMATRIX> m_boneTransforms;
	public:
		SkinRenderer();
	protected:
		virtual ~SkinRenderer() = default;
	public:
		inline MeshData GetMeshData()
		{
			return m_meshData;
		}
		VOID LoadMesh(string _meshFilePath, int _meshIndex = 0);
	public:
		VOID SetAnimator(Animator* _animator);
		inline Animator* GetAnimator()
		{
			return m_animator;
		}
		inline vector<XMMATRIX>& GetFinalTransforms()
		{
			return m_finalTransforms;
		}
		inline vector<XMMATRIX>& GetBoneTransforms()
		{
			return m_boneTransforms;
		}

	private:
		virtual VOID InitGemometryBuffer() final;
		virtual VOID SetShaderSkinningValues() final;
		virtual VOID SetShaderSkinningShadowValues() final;
	};
}

#endif //CHIPSSYSTEM_COMPONENETS_RENDERERCOMPONENETS_SKINRENDERER_H