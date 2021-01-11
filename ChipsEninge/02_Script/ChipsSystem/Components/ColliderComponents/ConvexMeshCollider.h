#ifndef CHIPSSYSTEM_COMPONENETS_COLLIDERCOMPONENETS_CONVEXMESHCOLLIDER_H
#define CHIPSSYSTEM_COMPONENETS_COLLIDERCOMPONENETS_CONVEXMESHCOLLIDER_H
#include "ChipsSystem/Components/ColliderComponents/ACollider.h"
#include "ChipsSystem/Components/RendererComponents/FbxRenderer.h"

namespace ChipsEngine
{
	/*
	Mesh (최적화 된) 모양의 Collider 를 오브젝트에 추가시키는 컴포넌트이다.
	*/
	class ConvexMeshCollider final : public ACollider
	{
	private:
		PxTolerancesScale m_scale;
		PxConvexMesh* m_convexMesh;
		PxConvexMeshDesc m_convexMeshDesc;
		PxConvexMeshGeometry m_convexMeshGeometry;
	public:
		ConvexMeshCollider();
	protected:
		virtual ~ConvexMeshCollider() = default;
	public:
		XMFLOAT3 GetMeshScale();
		VOID SetMeshScale(float _x, float _y, float _z);
		VOID SetMeshScale(XMFLOAT3 _meshScale);
		VOID SetMesh(FbxRenderer* _fbxRenderer);
	private:
		VOID SetDefaultParams();
	private:
		virtual VOID InitShape() override;
		virtual VOID ResetShape() override;
	};
}

#endif //CHIPSSYSTEM_COMPONENETS_COLLIDERCOMPONENETS_CONVEXMESHCOLLIDER_H