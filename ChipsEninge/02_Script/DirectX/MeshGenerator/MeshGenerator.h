#ifndef DIRECTX_MESHGENERATOR_MESHGENERATOR_H
#define DIRECTX_MESHGENERATOR_MESHGENERATOR_H
#include "ChipsSystem/Etc/Singleton.h"

struct MeshData
{
	std::vector<Vertex36> Vertices;
	std::vector<UINT> Indices;
};

class MeshGenerator 
{
private:
	MeshGenerator() = delete;
	~MeshGenerator() = delete;
	MeshGenerator(MeshGenerator&) = delete;
	void operator=(MeshGenerator&) = delete;
	MeshGenerator(MeshGenerator&&) = delete;
	void operator=(MeshGenerator&&) = delete;
public:
	static VOID CreateBox(float _width, float _height, float _depth, MeshData& _meshData);
	static VOID CreateSphere(float _radius, UINT _sliceCount, UINT _stackCount, MeshData& _meshData);
	static VOID CreateCylinder(float _bottomRadius, float _topRadius, float _height, UINT _sliceCount, UINT _stackCount, MeshData& _meshData);
	static VOID CreateCapsule(float _radius, float _halfHeight, MeshData& _meshData);
	static VOID CreateGrid(float _width, float _depth, UINT _m, UINT _n, MeshData& _meshData);
	static VOID CreateFullscreenQuad(MeshData& _meshData);
private:
	static VOID Subdivide(MeshData& _meshData);
	static VOID BuildCylinderTopCap(float _bottomRadius, float _topRadius, float _height, UINT _sliceCount, UINT _stackCount, MeshData& _meshData);
	static VOID BuildCylinderBottomCap(float _bottomRadius, float _topRadius, float _height, UINT _sliceCount, UINT _stackCount, MeshData& _meshData);
};

#endif //DIRECTX_MESHGENERATOR_MESHGENERATOR_H