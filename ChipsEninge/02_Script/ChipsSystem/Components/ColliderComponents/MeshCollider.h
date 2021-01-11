#ifndef CHIPSSYSTEM_COMPONENETS_COLLIDERCOMPONENETS_MESHCOLLIDER_H
#define CHIPSSYSTEM_COMPONENETS_COLLIDERCOMPONENETS_MESHCOLLIDER_H
#include "ChipsSystem/Components/ColliderComponents/ACollider.h"
#include "ChipsSystem/Components/RendererComponents/FbxRenderer.h"

namespace ChipsEngine
{
	/*
	Mesh (����ȭ���� ����) ����� Collider �� ������Ʈ�� �߰���Ű�� ������Ʈ�̴�.
	*/
	class MeshCollider final : public ACollider
	{
	private:
		PxTolerancesScale m_scale;
		PxTriangleMesh* m_triangleMesh;
		PxTriangleMeshDesc m_triangleMeshDesc;
		PxTriangleMeshGeometry m_triangleMeshGeometry;
	public:
		MeshCollider();
	protected:
		virtual ~MeshCollider() = default;
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

#endif //CHIPSSYSTEM_COMPONENETS_COLLIDERCOMPONENETS_MESHCOLLIDER_H