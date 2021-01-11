#include <fbxsdk/scene/geometry/fbxmesh.h>
#include "FbxLoader.h"
#include "ChipsSystem/Etc/Debug.h"
#include "ChipsSystem/Etc/StringLib.h"
#include "ChipsSystem/Etc/Mathf.h"

namespace ChipsEngine
{
	FbxLoader::FbxLoader()
	{
		m_manager = FbxManager::Create();
		m_ios = FbxIOSettings::Create(m_manager, IOSROOT);
		m_manager->SetIOSettings(m_ios);
		m_positions = nullptr;
		m_indexWeightPair = nullptr;
	}

	VOID FbxLoader::LoadFbx(string _fileName, vector<Vertex36>& _vertexs, vector<UINT>& _indexs, int _meshIndex, bool _isSkeleton)
	{
#pragma region Read meta file
		//Meta 파일 로드
		ifstream meshLoadFile;
		meshLoadFile.open(_fileName + to_string(_meshIndex) + ".meta", std::ios::binary);

		if (meshLoadFile.is_open())
		{
			string str;
			vector<string> values;
			getline(meshLoadFile, str);
			values = StringLib::Split(str);
			int vertexSize = stoi(values[0]);
			int indexSize = stoi(values[1]);
			for (int i = 0; i < vertexSize; i++)
			{
				Vertex36 vertex;
				getline(meshLoadFile, str);
				values = StringLib::Split(str);
				vertex.pos = XMFLOAT3(stof(values[0]), stof(values[1]), stof(values[2]));

				getline(meshLoadFile, str);
				values = StringLib::Split(str);
				vertex.normal = XMFLOAT3(stof(values[0]), stof(values[1]), stof(values[2]));

				getline(meshLoadFile, str);
				values = StringLib::Split(str);
				vertex.tangent = XMFLOAT3(stof(values[0]), stof(values[1]), stof(values[2]));

				getline(meshLoadFile, str);
				values = StringLib::Split(str);
				vertex.tex = XMFLOAT2(stof(values[0]), stof(values[1]));

				getline(meshLoadFile, str);
				values = StringLib::Split(str);
				vertex.matNum = stoi(values[0]);

				getline(meshLoadFile, str);
				values = StringLib::Split(str);
				vertex.weights = XMFLOAT4(stof(values[0]), stof(values[1]), stof(values[2]), stof(values[3]));

				getline(meshLoadFile, str);
				values = StringLib::Split(str);
				vertex.BoneIndices = DirectX::XMUINT4((UINT)stoi(values[0]), (UINT)stoi(values[1]), (UINT)stoi(values[2]), (UINT)stoi(values[3]));

				_vertexs.emplace_back(vertex);
			}

			for (int i = 0; i < indexSize; i++)
			{
				getline(meshLoadFile, str);
				_indexs.emplace_back(std::stoi(str));
			}

			meshLoadFile.close();

			if (_isSkeleton)
			{
				m_bindSkeletonMatrix.clear();

				meshLoadFile.open(_fileName + ".smeta", std::ios::binary);
				if (meshLoadFile.is_open())
				{
					string str;
					vector<string> values;
					getline(meshLoadFile, str);
					int boneCount = stoi(str);
					
					for (int i = 0; i < boneCount; i++)
					{
						XMFLOAT4X4 tempM = XMFLOAT4X4();

						getline(meshLoadFile, str);
						values = StringLib::Split(str);
						tempM.m[0][0] = stof(values[0]);
						tempM.m[0][1] = stof(values[1]);
						tempM.m[0][2] = stof(values[2]);
						tempM.m[0][3] = stof(values[3]);

						getline(meshLoadFile, str);
						values = StringLib::Split(str);
						tempM.m[1][0] = stof(values[0]);
						tempM.m[1][1] = stof(values[1]);
						tempM.m[1][2] = stof(values[2]);
						tempM.m[1][3] = stof(values[3]);

						getline(meshLoadFile, str);
						values = StringLib::Split(str);
						tempM.m[2][0] = stof(values[0]);
						tempM.m[2][1] = stof(values[1]);
						tempM.m[2][2] = stof(values[2]);
						tempM.m[2][3] = stof(values[3]);

						getline(meshLoadFile, str);
						values = StringLib::Split(str);
						tempM.m[3][0] = stof(values[0]);
						tempM.m[3][1] = stof(values[1]);
						tempM.m[3][2] = stof(values[2]);
						tempM.m[3][3] = stof(values[3]);

						m_bindSkeletonMatrix.push_back(tempM);
					}
				}
				meshLoadFile.close();
			}
			
			return;
		}
#pragma endregion

		//Meta 파일이 없을 시 FBX 직접 Load
		m_scene = FbxScene::Create(m_manager, "");
		m_importer = FbxImporter::Create(m_manager, "");
		m_importer->Initialize(_fileName.c_str(), -1, m_manager->GetIOSettings());
		m_importer->Import(m_scene);

		FbxAxisSystem sceneAxisSystem = m_scene->GetGlobalSettings().GetAxisSystem();
		FbxAxisSystem ourAxisSystem(FbxAxisSystem::DirectX);
		ourAxisSystem.ConvertScene(m_scene);

		FbxGeometryConverter geometryConverter(m_manager);
		geometryConverter.Triangulate(m_scene, true);
		m_indexMapping.clear();

		FbxNode* rootNode = m_scene->GetRootNode();

		if (rootNode)
		{
			FbxNode* childNode = rootNode->GetChild(_meshIndex);
			FbxMesh* fbxMesh = childNode->GetMesh();

			if (childNode->GetNodeAttribute() && childNode->GetNodeAttribute()->GetAttributeType() == FbxNodeAttribute::eMesh)
			{
				ProcessControlPoints(fbxMesh);
				ReadSkeleton(fbxMesh, _isSkeleton);

				unsigned int triCount = fbxMesh->GetPolygonCount();
				unsigned int vertexCount = 0;

				for (unsigned int i = 0; i < triCount; ++i)
				{
					for (unsigned int j = 0; j < 3; ++j)
					{
						int controlPointIndex = fbxMesh->GetPolygonVertex(i, j);

						XMFLOAT3& position = m_positions[controlPointIndex];
						XMFLOAT3 normal = ReadNormal(fbxMesh, controlPointIndex, vertexCount);
						//XMFLOAT3 binormal = ReadBinormal(fbxMesh, controlPointIndex, vertexCount);				
						//XMFLOAT3 tangent = ReadTangent(fbxMesh, controlPointIndex, vertexCount);				
						XMFLOAT3 tangent = XMFLOAT3(0, 0, 0);
						XMFLOAT2 uv = ReadUV(fbxMesh, controlPointIndex, fbxMesh->GetTextureUVIndex(i, j));
						uv.y = 1.0f - uv.y;

						vertexCount++;
						InsertVertex(position, normal, uv, tangent, _vertexs, _indexs, m_indexWeightPair[controlPointIndex], controlPointIndex);
					}
				}
			}
			ReadMatNum(fbxMesh, _vertexs, _indexs);
			CalculateTangent(_vertexs, _indexs);
		}

		#pragma region Write meta file
				//Meta 파일 생성
				ofstream meshSaveFile;
				meshSaveFile.open(_fileName + to_string(_meshIndex) + ".meta", std::ios::binary);
		
				if (meshSaveFile.is_open())
				{
					meshSaveFile << to_string(_vertexs.size()) << "," << to_string(_indexs.size()) << endl;
		
					for(auto& element : _vertexs)
					{
						string str;
		
						str = to_string(element.pos.x) + "," + to_string(element.pos.y) + "," + to_string(element.pos.z);
						meshSaveFile << str << endl;
		
						str = to_string(element.normal.x) + "," + to_string(element.normal.y) + "," + to_string(element.normal.z);
						meshSaveFile << str << endl;
		
						str = to_string(element.tangent.x) + "," + to_string(element.tangent.y) + "," + to_string(element.tangent.z);
						meshSaveFile << str << endl;
		
						str = to_string(element.tex.x) + "," + to_string(element.tex.y);
						meshSaveFile << str << endl;
		
						str = to_string(element.matNum);
						meshSaveFile << str << endl;

						str = to_string(element.weights.x) + "," + to_string(element.weights.y) + "," + to_string(element.weights.z) + "," + to_string(element.weights.w);
						meshSaveFile << str << endl;

						str = to_string(element.BoneIndices.x) + "," + to_string(element.BoneIndices.y) + "," + to_string(element.BoneIndices.z) + "," + to_string(element.BoneIndices.w);
						meshSaveFile << str << endl;
					}
		
					for (auto& element : _indexs)
					{
						meshSaveFile << element << endl;
					}
		
					meshSaveFile.close();
				}

				if (_isSkeleton)
				{
					meshSaveFile.open(_fileName + ".smeta", std::ios::binary);

					meshSaveFile << to_string(m_bindSkeletonMatrix.size()) << endl;

					for (auto& element : m_bindSkeletonMatrix)
					{
						string str;
						str = to_string(element.m[0][0]) + "," + to_string(element.m[0][1]) + "," + to_string(element.m[0][2]) + "," + to_string(element.m[0][3]);
						meshSaveFile << str << endl;

						str = to_string(element.m[1][0]) + "," + to_string(element.m[1][1]) + "," + to_string(element.m[1][2]) + "," + to_string(element.m[1][3]);
						meshSaveFile << str << endl;

						str = to_string(element.m[2][0]) + "," + to_string(element.m[2][1]) + "," + to_string(element.m[2][2]) + "," + to_string(element.m[2][3]);
						meshSaveFile << str << endl;

						str = to_string(element.m[3][0]) + "," + to_string(element.m[3][1]) + "," + to_string(element.m[3][2]) + "," + to_string(element.m[3][3]);
						meshSaveFile << str << endl;
					}

					meshSaveFile.close();
				}
		#pragma endregion

		m_importer->Destroy();
		m_scene->Destroy();
		SAFE_DELETE_ARRAY(m_positions);
		SAFE_DELETE_ARRAY(m_indexWeightPair);
		m_indexMapping.clear();
		m_skeleton.m_joints.clear();	
}

	VOID FbxLoader::LoadAnimation(string _fileName)
	{
#pragma region Read meta file
		//Meta 파일 로드
		ifstream meshLoadFile;
		meshLoadFile.open(_fileName + ".ameta", std::ios::binary);

		if (meshLoadFile.is_open())
		{
			if (meshLoadFile.is_open())
			{
				string str;
				vector<string> values;
				getline(meshLoadFile, str);
				values = StringLib::Split(str);
				int animCount = stoi(values[0]);
				int boneCount = stoi(values[1]);

				vector<XMFLOAT4X4> bindSkeletonMatrix;

				m_animationMatrix.clear();
				for (int i = 0; i < animCount; i++)
				{
					bindSkeletonMatrix.clear();

					for (int j = 0; j < boneCount; j++)
					{
						XMFLOAT4X4 tempM = XMFLOAT4X4();

						getline(meshLoadFile, str);
						values = StringLib::Split(str);
						tempM.m[0][0] = stof(values[0]);
						tempM.m[0][1] = stof(values[1]);
						tempM.m[0][2] = stof(values[2]);
						tempM.m[0][3] = stof(values[3]);

						getline(meshLoadFile, str);
						values = StringLib::Split(str);
						tempM.m[1][0] = stof(values[0]);
						tempM.m[1][1] = stof(values[1]);
						tempM.m[1][2] = stof(values[2]);
						tempM.m[1][3] = stof(values[3]);

						getline(meshLoadFile, str);
						values = StringLib::Split(str);
						tempM.m[2][0] = stof(values[0]);
						tempM.m[2][1] = stof(values[1]);
						tempM.m[2][2] = stof(values[2]);
						tempM.m[2][3] = stof(values[3]);

						getline(meshLoadFile, str);
						values = StringLib::Split(str);
						tempM.m[3][0] = stof(values[0]);
						tempM.m[3][1] = stof(values[1]);
						tempM.m[3][2] = stof(values[2]);
						tempM.m[3][3] = stof(values[3]);

						bindSkeletonMatrix.push_back(tempM);
					}
					m_animationMatrix.push_back(bindSkeletonMatrix);
				}
				meshLoadFile.close();
			}
			return;
		}
#pragma endregion

		m_scene = FbxScene::Create(m_manager, "");
		m_importer = FbxImporter::Create(m_manager, "");
		m_importer->Initialize(_fileName.c_str(), -1, m_manager->GetIOSettings());
		m_importer->Import(m_scene);

		FbxAxisSystem sceneAxisSystem = m_scene->GetGlobalSettings().GetAxisSystem();
		FbxAxisSystem ourAxisSystem(FbxAxisSystem::DirectX);
		ourAxisSystem.ConvertScene(m_scene);

		FbxGeometryConverter geometryConverter(m_manager);
		geometryConverter.Triangulate(m_scene, true);
		m_indexMapping.clear();

		FbxNode* rootNode = m_scene->GetRootNode();

		if (rootNode)
		{
			FbxNode* childNode = rootNode->GetChild(0);
			FbxMesh* fbxMesh = childNode->GetMesh();

			if (childNode->GetNodeAttribute() && childNode->GetNodeAttribute()->GetAttributeType() == FbxNodeAttribute::eMesh)
			{
				ProcessControlPoints(fbxMesh);
				ReadAnimation(fbxMesh);
			}
		}

#pragma region Write meta file
		//Meta 파일 생성
		if (m_animationMatrix.size() > 0)
		{
			ofstream meshSaveFile;
			meshSaveFile.open(_fileName + ".ameta", std::ios::binary);

			meshSaveFile << to_string(m_animationMatrix.size()) << "," << to_string(m_animationMatrix[0].size()) << endl;

			for (auto& vec : m_animationMatrix)
			{
				for (auto& element : vec)
				{
					string str;
					str = to_string(element.m[0][0]) + "," + to_string(element.m[0][1]) + "," + to_string(element.m[0][2]) + "," + to_string(element.m[0][3]);
					meshSaveFile << str << endl;

					str = to_string(element.m[1][0]) + "," + to_string(element.m[1][1]) + "," + to_string(element.m[1][2]) + "," + to_string(element.m[1][3]);
					meshSaveFile << str << endl;

					str = to_string(element.m[2][0]) + "," + to_string(element.m[2][1]) + "," + to_string(element.m[2][2]) + "," + to_string(element.m[2][3]);
					meshSaveFile << str << endl;

					str = to_string(element.m[3][0]) + "," + to_string(element.m[3][1]) + "," + to_string(element.m[3][2]) + "," + to_string(element.m[3][3]);
					meshSaveFile << str << endl;
				}
			}
			meshSaveFile.close();
		}
#pragma endregion

		m_importer->Destroy();
		m_scene->Destroy();
	}

	VOID FbxLoader::LoadNode(FbxNode* node, FbxMesh** _fbxMesh)
	{
		FbxNodeAttribute* nodeAttribute = node->GetNodeAttribute();
		if (nodeAttribute)
		{
			if (nodeAttribute->GetAttributeType() == FbxNodeAttribute::eMesh)
			{
				*_fbxMesh = node->GetMesh();
			}
		}

		const int childCount = node->GetChildCount();

		for (int i = 0; i < childCount; ++i)
		{
			LoadNode(node->GetChild(i), _fbxMesh);
		}
	}

	VOID FbxLoader::ProcessControlPoints(FbxMesh* _fbxMesh)
	{
		unsigned int count = _fbxMesh->GetControlPointsCount();
		m_positions = new XMFLOAT3[count];

		for (unsigned int i = 0; i < count; i++)
		{
			m_positions[i].x = static_cast<float>(_fbxMesh->GetControlPointAt(i).mData[0]);
			m_positions[i].y = static_cast<float>(_fbxMesh->GetControlPointAt(i).mData[1]);
			m_positions[i].z = static_cast<float>(_fbxMesh->GetControlPointAt(i).mData[2]);
		}
	}

	VOID FbxLoader::ProcessSkeletonHierarchy(FbxNode* _inRootNode)
	{
		for (int childIndex = 0; childIndex < _inRootNode->GetChildCount(); ++childIndex)
		{
			FbxNode* currNode = _inRootNode->GetChild(childIndex);
			ProcessSkeletonHierarchyRecursively(currNode, 0, 0, -1);
		}
	}

	VOID FbxLoader::ProcessSkeletonHierarchyRecursively(FbxNode* _inNode, int _inDepth, int _myIndex, int _inParentIndex)
	{
		if (_inNode->GetNodeAttribute()
			&& _inNode->GetNodeAttribute()->GetAttributeType()
			&& _inNode->GetNodeAttribute()->GetAttributeType() == FbxNodeAttribute::eSkeleton)
		{
			Joint currJoint;
			currJoint.m_parentIndex = _inParentIndex;
			currJoint.m_name = _inNode->GetName();
			m_skeleton.m_joints.push_back(currJoint);
		}
		for (int i = 0; i < _inNode->GetChildCount(); i++)
		{
			ProcessSkeletonHierarchyRecursively(_inNode->GetChild(i), _inDepth + 1, m_skeleton.m_joints.size(), _myIndex);
		}
	}

	UINT FbxLoader::FindJointIndexUsingName(const string& _inJointName)
	{
		for (unsigned int i = 0; i < m_skeleton.m_joints.size(); ++i)
		{
			if (m_skeleton.m_joints[i].m_name == _inJointName)
			{
				return i;
			}
		}

		return -1;
	}

	fbxsdk::FbxAMatrix FbxLoader::GetGeometryTransformation(FbxNode* _inNode)
	{
		const FbxVector4 lT = _inNode->GetGeometricTranslation(FbxNode::eSourcePivot);
		const FbxVector4 lR = _inNode->GetGeometricRotation(FbxNode::eSourcePivot);
		const FbxVector4 lS = _inNode->GetGeometricScaling(FbxNode::eSourcePivot);

		return FbxAMatrix(lT, lR, lS);
	}

	XMFLOAT3 FbxLoader::ReadNormal(const FbxMesh* mesh, int controlPointIndex, int vertexCounter)
	{
		if (mesh->GetElementNormalCount() < 1)
			return XMFLOAT3();

		const FbxGeometryElementNormal* vertexNormal = mesh->GetElementNormal(0);
		XMFLOAT3 result;

		switch (vertexNormal->GetMappingMode())
		{
		case FbxGeometryElement::eByControlPoint:
			switch (vertexNormal->GetReferenceMode())
			{
			case FbxGeometryElement::eDirect:
			{
				result.x = static_cast<float>(vertexNormal->GetDirectArray().GetAt(controlPointIndex).mData[0]);
				result.y = static_cast<float>(vertexNormal->GetDirectArray().GetAt(controlPointIndex).mData[1]);
				result.z = static_cast<float>(vertexNormal->GetDirectArray().GetAt(controlPointIndex).mData[2]);
			}
			break;

			case FbxGeometryElement::eIndexToDirect:
			{
				int index = vertexNormal->GetIndexArray().GetAt(controlPointIndex);
				result.x = static_cast<float>(vertexNormal->GetDirectArray().GetAt(index).mData[0]);
				result.y = static_cast<float>(vertexNormal->GetDirectArray().GetAt(index).mData[1]);
				result.z = static_cast<float>(vertexNormal->GetDirectArray().GetAt(index).mData[2]);
			}
			break;
			default:
				return XMFLOAT3{ 0,0,0 };
			}
			break;

		case FbxGeometryElement::eByPolygonVertex:
			switch (vertexNormal->GetReferenceMode())
			{
			case FbxGeometryElement::eDirect:
			{
				result.x = static_cast<float>(vertexNormal->GetDirectArray().GetAt(vertexCounter).mData[0]);
				result.y = static_cast<float>(vertexNormal->GetDirectArray().GetAt(vertexCounter).mData[1]);
				result.z = static_cast<float>(vertexNormal->GetDirectArray().GetAt(vertexCounter).mData[2]);
			}
			break;
			case FbxGeometryElement::eIndexToDirect:
			{
				int index = vertexNormal->GetIndexArray().GetAt(vertexCounter);
				result.x = static_cast<float>(vertexNormal->GetDirectArray().GetAt(index).mData[0]);
				result.y = static_cast<float>(vertexNormal->GetDirectArray().GetAt(index).mData[1]);
				result.z = static_cast<float>(vertexNormal->GetDirectArray().GetAt(index).mData[2]);
			}
			break;
			default:
				return XMFLOAT3{ 0,0,0 };
			}
			break;
		}

		return result;
	}

	XMFLOAT3 FbxLoader::ReadBinormal(const FbxMesh* mesh, int controlPointIndex, int vertexCounter)
	{
		if (mesh->GetElementBinormalCount() < 1)
			return XMFLOAT3();

		const FbxGeometryElementBinormal* vertexNormal = mesh->GetElementBinormal(0);
		XMFLOAT3 result;

		switch (vertexNormal->GetMappingMode())
		{
		case FbxGeometryElement::eByControlPoint:
			switch (vertexNormal->GetReferenceMode())
			{
			case FbxGeometryElement::eDirect:
			{
				result.x = static_cast<float>(vertexNormal->GetDirectArray().GetAt(controlPointIndex).mData[0]);
				result.y = static_cast<float>(vertexNormal->GetDirectArray().GetAt(controlPointIndex).mData[1]);
				result.z = static_cast<float>(vertexNormal->GetDirectArray().GetAt(controlPointIndex).mData[2]);
			}
			break;

			case FbxGeometryElement::eIndexToDirect:
			{
				int index = vertexNormal->GetIndexArray().GetAt(controlPointIndex);
				result.x = static_cast<float>(vertexNormal->GetDirectArray().GetAt(index).mData[0]);
				result.y = static_cast<float>(vertexNormal->GetDirectArray().GetAt(index).mData[1]);
				result.z = static_cast<float>(vertexNormal->GetDirectArray().GetAt(index).mData[2]);
			}
			break;
			default:
				return XMFLOAT3{ 0,0,0 };
			}
			break;

		case FbxGeometryElement::eByPolygonVertex:
			switch (vertexNormal->GetReferenceMode())
			{
			case FbxGeometryElement::eDirect:
			{
				result.x = static_cast<float>(vertexNormal->GetDirectArray().GetAt(vertexCounter).mData[0]);
				result.y = static_cast<float>(vertexNormal->GetDirectArray().GetAt(vertexCounter).mData[1]);
				result.z = static_cast<float>(vertexNormal->GetDirectArray().GetAt(vertexCounter).mData[2]);
			}
			break;
			case FbxGeometryElement::eIndexToDirect:
			{
				int index = vertexNormal->GetIndexArray().GetAt(vertexCounter);
				result.x = static_cast<float>(vertexNormal->GetDirectArray().GetAt(index).mData[0]);
				result.y = static_cast<float>(vertexNormal->GetDirectArray().GetAt(index).mData[1]);
				result.z = static_cast<float>(vertexNormal->GetDirectArray().GetAt(index).mData[2]);
			}
			break;
			default:
				return XMFLOAT3{ 0,0,0 };
			}
			break;
		}

		return result;
	}

	XMFLOAT3 FbxLoader::ReadTangent(const FbxMesh* mesh, int controlPointIndex, int vertexCounter)
	{
		if (mesh->GetElementTangentCount() < 1)
			return XMFLOAT3();

		const FbxGeometryElementTangent* vertexTangent = mesh->GetElementTangent(0);
		XMFLOAT3 result = XMFLOAT3();

		switch (vertexTangent->GetMappingMode())
		{
		case FbxGeometryElement::eByControlPoint:
			switch (vertexTangent->GetReferenceMode())
			{
			case FbxGeometryElement::eDirect:
			{
				result.x = static_cast<float>(vertexTangent->GetDirectArray().GetAt(controlPointIndex).mData[0]);
				result.y = static_cast<float>(vertexTangent->GetDirectArray().GetAt(controlPointIndex).mData[1]);
				result.z = static_cast<float>(vertexTangent->GetDirectArray().GetAt(controlPointIndex).mData[2]);
			}
			break;

			case FbxGeometryElement::eIndexToDirect:
			{
				int index = vertexTangent->GetIndexArray().GetAt(controlPointIndex);
				result.x = static_cast<float>(vertexTangent->GetDirectArray().GetAt(index).mData[0]);
				result.y = static_cast<float>(vertexTangent->GetDirectArray().GetAt(index).mData[1]);
				result.z = static_cast<float>(vertexTangent->GetDirectArray().GetAt(index).mData[2]);
			}
			break;
			}
			break;

		case FbxGeometryElement::eByPolygonVertex:
			switch (vertexTangent->GetReferenceMode())
			{
			case FbxGeometryElement::eDirect:
			{
				result.x = static_cast<float>(vertexTangent->GetDirectArray().GetAt(vertexCounter).mData[0]);
				result.y = static_cast<float>(vertexTangent->GetDirectArray().GetAt(vertexCounter).mData[1]);
				result.z = static_cast<float>(vertexTangent->GetDirectArray().GetAt(vertexCounter).mData[2]);
			}
			break;
			case FbxGeometryElement::eIndexToDirect:
			{
				int index = vertexTangent->GetIndexArray().GetAt(vertexCounter);
				result.x = static_cast<float>(vertexTangent->GetDirectArray().GetAt(index).mData[0]);
				result.y = static_cast<float>(vertexTangent->GetDirectArray().GetAt(index).mData[1]);
				result.z = static_cast<float>(vertexTangent->GetDirectArray().GetAt(index).mData[2]);
			}
			break;
			}
			break;
		}

		return result;
	}

	XMFLOAT2 FbxLoader::ReadUV(const FbxMesh* mesh, int controlPointIndex, int indexCounter)
	{
		if (mesh->GetElementUVCount() < 1)
			return XMFLOAT2(0, 0);

		const FbxGeometryElementUV* vertexUv = mesh->GetElementUV(0);
		XMFLOAT2 result;

		switch (vertexUv->GetMappingMode())
		{
		case FbxGeometryElement::eByControlPoint:
			switch (vertexUv->GetReferenceMode())
			{
			case FbxGeometryElement::eDirect:
			{
				result.x = static_cast<float>(vertexUv->GetDirectArray().GetAt(controlPointIndex).mData[0]);
				result.y = static_cast<float>(vertexUv->GetDirectArray().GetAt(controlPointIndex).mData[1]);
			}
			break;

			case FbxGeometryElement::eIndexToDirect:
			{
				int index = vertexUv->GetIndexArray().GetAt(controlPointIndex);
				result.x = static_cast<float>(vertexUv->GetDirectArray().GetAt(index).mData[0]);
				result.y = static_cast<float>(vertexUv->GetDirectArray().GetAt(index).mData[1]);
			}
			break;
			default:
				return XMFLOAT2{ 0,0 };
			}
			break;

		case FbxGeometryElement::eByPolygonVertex:
			switch (vertexUv->GetReferenceMode())
			{
			case FbxGeometryElement::eDirect:
			case FbxGeometryElement::eIndexToDirect:
			{
				result.x = static_cast<float>(vertexUv->GetDirectArray().GetAt(indexCounter).mData[0]);
				result.y = static_cast<float>(vertexUv->GetDirectArray().GetAt(indexCounter).mData[1]);
			}
			break;
			default:
				return XMFLOAT2{ 0,0 };
			}
			break;
		}

		return result;
	}

	VOID FbxLoader::ReadMatNum(const FbxMesh* mesh, vector<Vertex36>& _vertexs, vector<UINT>& _indexs)
	{
		FbxLayerElementArrayTemplate<int>* pLockableArray = &mesh->GetLayer(0)->GetMaterials()->GetIndexArray();
		mesh->GetMaterialIndices(&pLockableArray);

		int maxCount = pLockableArray->GetCount();
		int j = 0;

		for (int i = 0; i < maxCount; i++)
		{
			_vertexs[_indexs[j++]].matNum = (*pLockableArray)[i];
			_vertexs[_indexs[j++]].matNum = (*pLockableArray)[i];
			_vertexs[_indexs[j++]].matNum = (*pLockableArray)[i];
		}
	}

	VOID FbxLoader::ReadSkeleton(FbxMesh* _fbxMesh, bool _isSkeleton)
	{
		FbxAMatrix geometryTransformation;
		geometryTransformation = GetGeometryTransformation(_fbxMesh->GetNode());

		UINT count = _fbxMesh->GetControlPointsCount();
		
		m_indexWeightPair = new BlendingIndexWeightPair[count];

		if (_isSkeleton)
		{
			ProcessSkeletonHierarchy(m_scene->GetRootNode());

			int numDeformers = _fbxMesh->GetDeformerCount();
			FbxSkin* skin = (FbxSkin*)_fbxMesh->GetDeformer(0, FbxDeformer::eSkin);

			if (skin != nullptr)
			{
				int boneCount = skin->GetClusterCount();
				//뼈 갯수가 13개 차이남.

				for (int boneIndex = 0; boneIndex < boneCount; boneIndex++)
				{
					FbxCluster* cluster = skin->GetCluster(boneIndex);
					FbxNode* bone = cluster->GetLink();

					UINT currJointIndex = FindJointIndexUsingName(bone->GetName());

					//Get JointMatrix
					FbxAMatrix transformMatrix;
					FbxAMatrix transformLinkMatrix;
					FbxAMatrix globalBindposeInverseMatrix;

					cluster->GetTransformMatrix(transformMatrix);	
					cluster->GetTransformLinkMatrix(transformLinkMatrix);	

					globalBindposeInverseMatrix = transformLinkMatrix.Inverse() * transformMatrix * geometryTransformation;
					m_skeleton.m_joints[currJointIndex].m_globalBindposeInverse = globalBindposeInverseMatrix;
					m_skeleton.m_joints[currJointIndex].m_node = bone;


					//Get Weight, Index
					double* boneVertexWeights = cluster->GetControlPointWeights();
					int* boneVertexIndices = cluster->GetControlPointIndices();

					int numBoneVertexIndices = cluster->GetControlPointIndicesCount();
					for (int boneVertexIndex = 0; boneVertexIndex < numBoneVertexIndices; boneVertexIndex++)
					{
						m_indexWeightPair[boneVertexIndices[boneVertexIndex]].m_blendingIndex.push_back(currJointIndex);
						m_indexWeightPair[boneVertexIndices[boneVertexIndex]].m_blendingWeight.push_back((float)boneVertexWeights[boneVertexIndex]);
					}				
				}

				//Adding Dummy joints
				for (UINT i = 0; i < count; i++)
				{
					for (UINT j = m_indexWeightPair[i].m_blendingWeight.size(); j < 4; j++)
					{
						m_indexWeightPair[i].m_blendingIndex.push_back(0);
						m_indexWeightPair[i].m_blendingWeight.push_back(0.0f);
					}
				}
			
				m_bindSkeletonMatrix.clear();

				//Make m_bindSkeletonMatrix
				UINT count = m_skeleton.m_joints.size();
				for (UINT i = 0; i < count; i++)
				{
					XMFLOAT4X4 tempM = XMFLOAT4X4();

					FbxAMatrix finalMatrix;
					if (m_skeleton.m_joints[i].m_globalBindposeInverse)
					{
						finalMatrix = m_skeleton.m_joints[i].m_globalBindposeInverse.Transpose();
					}

					fbxsdk::FbxVector4 tempV = finalMatrix.GetColumn(0);
					tempM.m[0][0] = (float)tempV.mData[0];
					tempM.m[0][1] = (float)tempV.mData[1];
					tempM.m[0][2] = (float)tempV.mData[2];
					tempM.m[0][3] = (float)tempV.mData[3];

					tempV = finalMatrix.GetColumn(1);
					tempM.m[1][0] = (float)tempV.mData[0];
					tempM.m[1][1] = (float)tempV.mData[1];
					tempM.m[1][2] = (float)tempV.mData[2];
					tempM.m[1][3] = (float)tempV.mData[3];

					tempV = finalMatrix.GetColumn(2);
					tempM.m[2][0] = (float)tempV.mData[0];
					tempM.m[2][1] = (float)tempV.mData[1];
					tempM.m[2][2] = (float)tempV.mData[2];
					tempM.m[2][3] = (float)tempV.mData[3];

					tempV = finalMatrix.GetColumn(3);
					tempM.m[3][0] = (float)tempV.mData[0];
					tempM.m[3][1] = (float)tempV.mData[1];
					tempM.m[3][2] = (float)tempV.mData[2];
					tempM.m[3][3] = (float)tempV.mData[3];

					m_bindSkeletonMatrix.push_back(tempM);
				}
			}
			else
			{
				for (UINT i = 0; i < count; i++)
				{
					for (int j = 0; j < 4; j++)
					{
						m_indexWeightPair[i].m_blendingIndex.push_back(0);
						m_indexWeightPair[i].m_blendingWeight.push_back(0.0f);
					}
				}
			}
		}
		else
		{
			for (UINT i = 0; i < count; i++)
			{
				for (int j = 0; j < 4; j++)
				{
					m_indexWeightPair[i].m_blendingIndex.push_back(0);
					m_indexWeightPair[i].m_blendingWeight.push_back(0.0f);
				}
			}
		}
	}

	VOID FbxLoader::ReadAnimation(FbxMesh* _fbxMesh)
	{
		FbxAMatrix geometryTransformation;
		geometryTransformation = GetGeometryTransformation(_fbxMesh->GetNode());

		UINT count = _fbxMesh->GetControlPointsCount();

		ProcessSkeletonHierarchy(m_scene->GetRootNode());

		int numDeformers = _fbxMesh->GetDeformerCount();
		FbxSkin* skin = (FbxSkin*)_fbxMesh->GetDeformer(0, FbxDeformer::eSkin);

		if (skin != nullptr)
		{
			int boneCount = skin->GetClusterCount();
			int frameCount = 0;
			//뼈 갯수가 13개 차이남.

			for (int boneIndex = 0; boneIndex < boneCount; boneIndex++)
			{
				FbxCluster* cluster = skin->GetCluster(boneIndex);
				FbxNode* bone = cluster->GetLink();

				UINT currJointIndex = FindJointIndexUsingName(bone->GetName());

				//Get Animation Information
				FbxAnimStack* currAnimStack = m_scene->GetSrcObject<FbxAnimStack>(0);
				if (currAnimStack == nullptr)
					Debug::ErrorMessage("Animation Load Error", "Animation is not exist.");

				FbxString animStackName = currAnimStack->GetName();
				m_animationName = animStackName.Buffer();

				FbxTakeInfo* takeInfo = m_scene->GetTakeInfo(animStackName);

				FbxTime start = takeInfo->mLocalTimeSpan.GetStart();
				FbxTime end = takeInfo->mLocalTimeSpan.GetStop();

				m_animationLength = (int)(end.GetFrameCount(FbxTime::eFrames24) - start.GetFrameCount(FbxTime::eFrames24) + 1);

				Keyframe tBeforeKeyFrame;
				FbxAMatrix matBeforeMatrix;
				FbxAMatrix matNowMatrix;

				Keyframe** currAnim = &m_skeleton.m_joints[currJointIndex].m_animation;
				frameCount = (int)end.GetFrameCount(FbxTime::eFrames24);
				for (FbxLongLong i = start.GetFrameCount(FbxTime::eFrames24); i <= end.GetFrameCount(FbxTime::eFrames24); ++i)
				{
					FbxTime currTime;
					currTime.SetFrame(i, FbxTime::eFrames24);
					*currAnim = new Keyframe();
					(*currAnim)->m_frameNum = i;

					matNowMatrix = _fbxMesh->GetNode()->EvaluateGlobalTransform(currTime) * geometryTransformation;
					(*currAnim)->m_globalTransform = matNowMatrix.Inverse() * cluster->GetLink()->EvaluateGlobalTransform(currTime);
					currAnim = &((*currAnim)->m_next);
				}
			}
			
#pragma region Insert Bone Matrix
			UINT count = m_skeleton.m_joints.size();
			vector<XMFLOAT4X4> bindSkeletonMatrix;
			bindSkeletonMatrix.reserve(count);
			m_animationMatrix.reserve(m_animationLength);

			for (int animIndex = 0; animIndex < m_animationLength; animIndex++)
			{
				bindSkeletonMatrix.clear();
				for (UINT i = 0; i < count; i++)
				{
					FbxAMatrix finalMatrix;
					if (m_skeleton.m_joints[i].m_animation)
					{
						finalMatrix = m_skeleton.m_joints[i].m_animation->m_globalTransform.Transpose();
						m_skeleton.m_joints[i].m_animation = m_skeleton.m_joints[i].m_animation->m_next;
					}

					XMFLOAT4X4 tempM = XMFLOAT4X4();
					fbxsdk::FbxVector4 tempV = finalMatrix.GetColumn(0);
					tempM.m[0][0] = (float)tempV.mData[0];
					tempM.m[0][1] = (float)tempV.mData[1];
					tempM.m[0][2] = (float)tempV.mData[2];
					tempM.m[0][3] = (float)tempV.mData[3];

					tempV = finalMatrix.GetColumn(1);
					tempM.m[1][0] = (float)tempV.mData[0];
					tempM.m[1][1] = (float)tempV.mData[1];
					tempM.m[1][2] = (float)tempV.mData[2];
					tempM.m[1][3] = (float)tempV.mData[3];

					tempV = finalMatrix.GetColumn(2);
					tempM.m[2][0] = (float)tempV.mData[0];
					tempM.m[2][1] = (float)tempV.mData[1];
					tempM.m[2][2] = (float)tempV.mData[2];
					tempM.m[2][3] = (float)tempV.mData[3];

					tempV = finalMatrix.GetColumn(3);
					tempM.m[3][0] = (float)tempV.mData[0];
					tempM.m[3][1] = (float)tempV.mData[1];
					tempM.m[3][2] = (float)tempV.mData[2];
					tempM.m[3][3] = (float)tempV.mData[3];

					bindSkeletonMatrix.push_back(tempM);
				}
				m_animationMatrix.push_back(bindSkeletonMatrix);
			}
#pragma endregion
		}
	}

	VOID FbxLoader::CalculateTangent(vector<Vertex36>& _vertexs, vector<UINT>& _indexs)
	{
		for (UINT i = 0; i < _indexs.size(); i += 3)
		{
			Vertex36& vertex0 = _vertexs[_indexs[i]];
			Vertex36& vertex1 = _vertexs[_indexs[i + 1]];
			Vertex36& vertex2 = _vertexs[_indexs[i + 2]];

			XMFLOAT3 e0 = XMFLOAT3(vertex1.pos.x - vertex0.pos.x, vertex1.pos.y - vertex0.pos.y, vertex1.pos.z - vertex0.pos.z);
			XMFLOAT3 e1 = XMFLOAT3(vertex2.pos.x - vertex0.pos.x, vertex2.pos.y - vertex0.pos.y, vertex2.pos.z - vertex0.pos.z);

			XMFLOAT2 v0 = XMFLOAT2(vertex1.tex.x - vertex0.tex.x, vertex1.tex.y - vertex0.tex.y);
			XMFLOAT2 v1 = XMFLOAT2(vertex2.tex.x - vertex0.tex.x, vertex2.tex.y - vertex0.tex.y);

			XMFLOAT3 tangent = XMFLOAT3((v0.x * e0.x + v0.y * e1.x), (v0.x * e0.y + v0.y * e1.y), (v0.x * e0.z + v0.y * e1.z));

			tangent.x /= tangent.x + tangent.y + tangent.z;
			tangent.y /= tangent.x + tangent.y + tangent.z;
			tangent.z /= tangent.x + tangent.y + tangent.z;

			auto isZero = [](XMFLOAT3 _float3) {return _float3.x == 0 && _float3.y == 0 && _float3.z == 0; };
			auto average = [](XMFLOAT3 _one, XMFLOAT3 _two) { return XMFLOAT3((_one.x + _two.x) * 0.5f, (_one.y + _two.y) * 0.5f, (_one.z + _two.z) * 0.5f); };

			vertex0.tangent = isZero(vertex0.tangent) ? tangent : average(vertex0.tangent, tangent);
			vertex1.tangent = isZero(vertex1.tangent) ? tangent : average(vertex1.tangent, tangent);
			vertex2.tangent = isZero(vertex2.tangent) ? tangent : average(vertex2.tangent, tangent);
		}
	}

	VOID FbxLoader::InsertVertex(const XMFLOAT3& _pos, const XMFLOAT3& _normal, const XMFLOAT2& _uv, const XMFLOAT3& _tangent, vector<Vertex36>& _vectors, vector<UINT>& _indexs, BlendingIndexWeightPair& _indexWeightPair, int _index)
	{
		string hadaIndex = HashFunc(_pos, _normal, _uv, _tangent, _index);
		auto lookup = m_indexMapping.find(hadaIndex);
		if (lookup != m_indexMapping.end())
		{
			_indexs.push_back(lookup->second);
		}
		else
		{
			unsigned int index = _vectors.size();
			m_indexMapping[hadaIndex] = index;
			_indexs.push_back(index);
			Vertex36 vertex{ _pos, _normal, _uv, _tangent,  0,
				XMFLOAT4(_indexWeightPair.m_blendingWeight[0], _indexWeightPair.m_blendingWeight[1],
						 _indexWeightPair.m_blendingWeight[2], _indexWeightPair.m_blendingWeight[3]),
				DirectX::XMUINT4(_indexWeightPair.m_blendingIndex[0], _indexWeightPair.m_blendingIndex[1],
								 _indexWeightPair.m_blendingIndex[2], _indexWeightPair.m_blendingIndex[3]) };
			_vectors.push_back(vertex);
		}
	}

	string FbxLoader::HashFunc(const XMFLOAT3& _pos, const XMFLOAT3& _normal, const XMFLOAT2& _uv, const XMFLOAT3& _tangent, int _index)
	{
		string data = to_string(_pos.x) + to_string(_pos.y) + to_string(_pos.z)
			+ to_string(_normal.x) + to_string(_normal.y) + to_string(_normal.z)
			+ to_string(_uv.x) + to_string(_uv.y)
			+ to_string(_tangent.x) + to_string(_tangent.y) + to_string(_tangent.z)
			+ to_string(_index);
		return data;
	}
}