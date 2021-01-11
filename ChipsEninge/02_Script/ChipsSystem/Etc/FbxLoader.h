#ifndef CHIPSSYSTEM_ETC_FBXLOADER_H
#define CHIPSSYSTEM_ETC_FBXLOADER_H
#include <fbxsdk.h>
#include "ChipsSystem/Etc/Singleton.h"

namespace ChipsEngine
{
	using namespace fbxsdk;
	/*
	FbxRenderer, Animator 컴포넌트를 사용할 때, .Fbx 파일을 로드하고 meta 파일을 만드는 역할을 한다. 
	meta 파일의 목적은 fbx 파일을 빠르게 읽게 하기 위함이다.
	FbxLoader 는 FbxRenderer, Animator 내부에서 알아서 호출함으로, 사용자가 직접 호출할 경우는 없다.
	*/
	class FbxLoader : public Singletone<FbxLoader>
	{
	private:
		struct BlendingIndexWeightPair
		{
			vector<UINT> m_blendingIndex;
			vector<float> m_blendingWeight;
			BlendingIndexWeightPair()
			{
				m_blendingIndex.reserve(4);
				m_blendingWeight.reserve(4);
			}
		};
		struct Keyframe
		{
			FbxLongLong m_frameNum;
			FbxAMatrix m_globalTransform;
			Keyframe* m_next;

			Keyframe() :
				m_next(nullptr)
			{}
		};
		struct Joint
		{
			std::string m_name;
			int m_parentIndex;
			FbxAMatrix m_globalBindposeInverse;
			Keyframe* m_animation;
			FbxNode* m_node;

			Joint() :
				m_node(nullptr),
				m_animation(nullptr)
			{
				m_globalBindposeInverse.SetIdentity();
				m_parentIndex = -1;
			}

			~Joint()
			{
				while (m_animation)
				{
					Keyframe* temp = m_animation->m_next;
					delete m_animation;
					m_animation = temp;
				}
			}
		};
		struct Skeleton
		{
			std::vector<Joint> m_joints;
		};
	private:
		fbxsdk::FbxManager*    m_manager;
		fbxsdk::FbxIOSettings* m_ios;
		fbxsdk::FbxImporter*   m_importer;
		fbxsdk::FbxScene*      m_scene;
		XMFLOAT3*			   m_positions;
		Skeleton			   m_skeleton;
		int					   m_animationLength;
		string				   m_animationName;
		vector<XMFLOAT4X4>     m_bindSkeletonMatrix;
		vector<vector<XMFLOAT4X4>> m_animationMatrix;
		BlendingIndexWeightPair* m_indexWeightPair;
		map<string, unsigned int> m_indexMapping;
	public:
		FbxLoader();
		~FbxLoader() = default;
	public:
		VOID LoadFbx(string _fileName, vector<Vertex36>& _vertexs, vector<UINT>& _indexs, int _meshIndex, bool _isSkeleton = false);
		VOID LoadAnimation(string _fileName);
		inline vector<XMFLOAT4X4> GetSkeletonMatrix()
		{
			return m_bindSkeletonMatrix;
		}
		inline vector<vector<XMFLOAT4X4>> GetAnimationMatrix()
		{
			return m_animationMatrix;
;		}
	private:
		VOID LoadNode(FbxNode* node, FbxMesh** _fbxMesh);
		VOID ProcessControlPoints(FbxMesh* _fbxMesh);
		VOID ProcessSkeletonHierarchy(FbxNode* _inRootNode);
		VOID ProcessSkeletonHierarchyRecursively(FbxNode* _inNode, int _inDepth, int _myIndex, int _inParentIndex);
		UINT FindJointIndexUsingName(const string& _inJointName);
		FbxAMatrix GetGeometryTransformation(FbxNode* _inNode);
		XMFLOAT3 ReadNormal(const FbxMesh* _fbxMesh, int controlPointIndex, int vertexCounter);
		XMFLOAT3 ReadBinormal(const FbxMesh* _fbxMesh, int controlPointIndex, int vertexCounter);
		XMFLOAT3 ReadTangent(const FbxMesh* _fbxMesh, int controlPointIndex, int vertexCounter);
		XMFLOAT2 ReadUV(const FbxMesh* _fbxMesh, int controlPointIndex, int indexCounter);
		VOID ReadMatNum(const FbxMesh* _fbxMesh, vector<Vertex36>& _vertexs, vector<UINT>& _indexs);
		VOID ReadSkeleton(FbxMesh* _fbxMesh, bool _isSkeleton);
		VOID ReadAnimation(FbxMesh* _fbxMesh);
		VOID CalculateTangent(vector<Vertex36>& _vertexs, vector<UINT>& _indexs);
		VOID InsertVertex(const XMFLOAT3& _pos, const XMFLOAT3& _normal, const XMFLOAT2& _uv, const XMFLOAT3& _tangent, vector<Vertex36>& _vectors, vector<UINT>& _indexs, BlendingIndexWeightPair& _indexWeightPair, int _index);
		string HashFunc(const XMFLOAT3& _pos, const XMFLOAT3& _normal, const XMFLOAT2& _uv, const XMFLOAT3& _tangent, int _index);
	};
}

#endif CHIPSSYSTEM_ETC_SINGLETON_H