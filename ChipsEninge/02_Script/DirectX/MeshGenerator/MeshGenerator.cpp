#include "DirectX/MeshGenerator/MeshGenerator.h"

VOID MeshGenerator::CreateBox(float _width, float _height, float _depth, MeshData& _meshData)
{
	Vertex36 v[24];

	float w2 = 0.5f*_width;
	float h2 = 0.5f*_height;
	float d2 = 0.5f*_depth;

	// Fill in the front face vertex data.
	InitVertex36(v[0], -w2, -h2, -d2, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f);
	InitVertex36(v[1], -w2, +h2, -d2, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f);
	InitVertex36(v[2], +w2, +h2, -d2, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f);
	InitVertex36(v[3], +w2, -h2, -d2, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f);

	// Fill in the back face vertex data.
	InitVertex36(v[4], -w2, -h2, +d2, 0.0f, 0.0f, 1.0f, -1.0f, 0.0f, 0.0f, 1.0f, 1.0f);
	InitVertex36(v[5], +w2, -h2, +d2, 0.0f, 0.0f, 1.0f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f);
	InitVertex36(v[6], +w2, +h2, +d2, 0.0f, 0.0f, 1.0f, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f);
	InitVertex36(v[7], -w2, +h2, +d2, 0.0f, 0.0f, 1.0f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f);

	// Fill in the top face vertex data.
	InitVertex36(v[8], -w2, +h2, -d2, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f);
	InitVertex36(v[9], -w2, +h2, +d2, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f);
	InitVertex36(v[10], +w2, +h2, +d2, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f);
	InitVertex36(v[11], +w2, +h2, -d2, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f);

	// Fill in the bottom face vertex data.
	InitVertex36(v[12], -w2, -h2, -d2, 0.0f, -1.0f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f, 1.0f);
	InitVertex36(v[13], +w2, -h2, -d2, 0.0f, -1.0f, 0.0f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f);
	InitVertex36(v[14], +w2, -h2, +d2, 0.0f, -1.0f, 0.0f, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f);
	InitVertex36(v[15], -w2, -h2, +d2, 0.0f, -1.0f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f);

	// Fill in the left face vertex data.
	InitVertex36(v[16], -w2, -h2, +d2, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f, 1.0f);
	InitVertex36(v[17], -w2, +h2, +d2, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f);
	InitVertex36(v[18], -w2, +h2, -d2, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f);
	InitVertex36(v[19], -w2, -h2, -d2, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f);

	// Fill in the right face vertex data.
	InitVertex36(v[20], +w2, -h2, -d2, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f);
	InitVertex36(v[21], +w2, +h2, -d2, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f);
	InitVertex36(v[22], +w2, +h2, +d2, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f);
	InitVertex36(v[23], +w2, -h2, +d2, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f);

	_meshData.Vertices.assign(&v[0], &v[24]);

	UINT i[36];

	// Fill in the front face index data
	i[0] = 0; i[1] = 1; i[2] = 2;
	i[3] = 0; i[4] = 2; i[5] = 3;

	// Fill in the back face index data
	i[6] = 4; i[7] = 5; i[8] = 6;
	i[9] = 4; i[10] = 6; i[11] = 7;

	// Fill in the top face index data
	i[12] = 8; i[13] = 9; i[14] = 10;
	i[15] = 8; i[16] = 10; i[17] = 11;

	// Fill in the bottom face index data
	i[18] = 12; i[19] = 13; i[20] = 14;
	i[21] = 12; i[22] = 14; i[23] = 15;

	// Fill in the left face index data
	i[24] = 16; i[25] = 17; i[26] = 18;
	i[27] = 16; i[28] = 18; i[29] = 19;

	// Fill in the right face index data
	i[30] = 20; i[31] = 21; i[32] = 22;
	i[33] = 20; i[34] = 22; i[35] = 23;

	_meshData.Indices.assign(&i[0], &i[36]);
}

VOID MeshGenerator::CreateSphere(float _radius, UINT _sliceCount, UINT _stackCount, MeshData& _meshData)
{
	_meshData.Vertices.clear();
	_meshData.Indices.clear();
	//
	// Compute the vertices stating at the top pole and moving down the stacks.
	//

	// Poles: note that there will be texture coordinate distortion as there is
	// not a unique point on the texture map to assign to the pole when mapping
	// a rectangular texture onto a sphere.
	Vertex36 topVertex;
	InitVertex36(topVertex, 0.0f, +_radius, 0.0f, 0.0f, +1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f);
	Vertex36 bottomVertex;
	InitVertex36(bottomVertex, 0.0f, -_radius, 0.0f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f);

	_meshData.Vertices.push_back(topVertex);

	const float XM_PI = 3.141592f;
	const float XM_2PI = 6.283185307f;
	float phiStep = XM_PI / _stackCount;
	float thetaStep = 2.0f*XM_PI / _sliceCount;

	// Compute vertices for each stack ring (do not count the poles as rings).
	for (UINT i = 1; i <= _stackCount - 1; ++i)
	{
		float phi = i * phiStep;

		// Vertices of ring.
		for (UINT j = 0; j <= _sliceCount; ++j)
		{
			float theta = j * thetaStep;

			Vertex36 v;

			// spherical to cartesian
			v.pos.x = _radius * sinf(phi)*cosf(theta);
			v.pos.y = _radius * cosf(phi);
			v.pos.z = _radius * sinf(phi)*sinf(theta);

			// Partial derivative of P with respect to theta
			v.tangent.x = -_radius * sinf(phi)*sinf(theta);
			v.tangent.y = 0.0f;
			v.tangent.z = +_radius * sinf(phi)*cosf(theta);

			XMVECTOR T = XMLoadFloat3(&v.tangent);
			XMStoreFloat3(&v.tangent, XMVector3Normalize(T));

			XMVECTOR p = XMLoadFloat3(&v.pos);
			XMStoreFloat3(&v.normal, XMVector3Normalize(p));

			v.tex.x = theta / XM_2PI;
			v.tex.y = phi / XM_PI;

			_meshData.Vertices.push_back(v);
		}
	}

	_meshData.Vertices.push_back(bottomVertex);

	//
	// Compute indices for top stack.  The top stack was written first to the vertex buffer
	// and connects the top pole to the first ring.
	//

	for (UINT i = 1; i <= _sliceCount; ++i)
	{
		_meshData.Indices.push_back(0);
		_meshData.Indices.push_back(i + 1);
		_meshData.Indices.push_back(i);
	}

	//
	// Compute indices for inner stacks (not connected to poles).
	//

	// Offset the indices to the index of the first vertex in the first ring.
	// This is just skipping the top pole vertex.
	UINT baseIndex = 1;
	UINT ringVertexCount = _sliceCount + 1;
	for (UINT i = 0; i < _stackCount - 2; ++i)
	{
		for (UINT j = 0; j < _sliceCount; ++j)
		{
			_meshData.Indices.push_back(baseIndex + i * ringVertexCount + j);
			_meshData.Indices.push_back(baseIndex + i * ringVertexCount + j + 1);
			_meshData.Indices.push_back(baseIndex + (i + 1)*ringVertexCount + j);
			
			_meshData.Indices.push_back(baseIndex + (i + 1)*ringVertexCount + j);
			_meshData.Indices.push_back(baseIndex + i * ringVertexCount + j + 1);
			_meshData.Indices.push_back(baseIndex + (i + 1)*ringVertexCount + j + 1);
		}
	}

	//
	// Compute indices for bottom stack.  The bottom stack was written last to the vertex buffer
	// and connects the bottom pole to the bottom ring.
	//

	// South pole vertex was added last.
	UINT southPoleIndex = (UINT)_meshData.Vertices.size() - 1;

	// Offset the indices to the index of the first vertex in the last ring.
	baseIndex = southPoleIndex - ringVertexCount;

	for (UINT i = 0; i < _sliceCount; ++i)
	{
		_meshData.Indices.push_back(southPoleIndex);
		_meshData.Indices.push_back(baseIndex + i);
		_meshData.Indices.push_back(baseIndex + i + 1);
	}
}

VOID MeshGenerator::CreateCylinder(float _bottomRadius, float _topRadius, float _height, UINT _sliceCount, UINT _stackCount, MeshData& _meshData)
{
	_meshData.Vertices.clear();
	_meshData.Indices.clear();

	//
	// Build Stacks.
	// 
	const float XM_PI = 3.141592f;
	float stackHeight = _height / _stackCount;

	// Amount to increment radius as we move up each stack level from bottom to top.
	float radiusStep = (_topRadius - _bottomRadius) / _stackCount;

	UINT ringCount = _stackCount + 1;

	// Compute vertices for each stack ring starting at the bottom and moving up.
	for (UINT i = 0; i < ringCount; ++i)
	{
		float y = -0.5f*_height + i * stackHeight;
		float r = _bottomRadius + i * radiusStep;

		// vertices of ring
		float dTheta = 2.0f*XM_PI / _sliceCount;
		for (UINT j = 0; j <= _sliceCount; ++j)
		{
			Vertex36 vertex;

			float c = cosf(j*dTheta);
			float s = sinf(j*dTheta);

			vertex.pos = XMFLOAT3(r*c, y, r*s);

			vertex.tex.x = (float)j / _sliceCount;
			vertex.tex.y = 1.0f - (float)i / _stackCount;

			// This is unit length.
			vertex.tangent = XMFLOAT3(-s, 0.0f, c);

			float dr = _bottomRadius - _topRadius;
			XMFLOAT3 bitangent(dr*c, -_height, dr*s);

			XMVECTOR T = XMLoadFloat3(&vertex.tangent);
			XMVECTOR B = XMLoadFloat3(&bitangent);
			XMVECTOR N = XMVector3Normalize(XMVector3Cross(T, B));
			XMStoreFloat3(&vertex.normal, N);

			_meshData.Vertices.push_back(vertex);
		}
	}

	// Add one because we duplicate the first and last vertex per ring
	// since the texture coordinates are different.
	UINT ringVertexCount = _sliceCount + 1;

	// Compute indices for each stack.
	for (UINT i = 0; i < _stackCount; ++i)
	{
		for (UINT j = 0; j < _sliceCount; ++j)
		{
			_meshData.Indices.push_back(i*ringVertexCount + j);
			_meshData.Indices.push_back((i + 1)*ringVertexCount + j);
			_meshData.Indices.push_back((i + 1)*ringVertexCount + j + 1);

			_meshData.Indices.push_back(i*ringVertexCount + j);
			_meshData.Indices.push_back((i + 1)*ringVertexCount + j + 1);
			_meshData.Indices.push_back(i*ringVertexCount + j + 1);
		}
	}

	BuildCylinderTopCap(_bottomRadius, _topRadius, _height, _sliceCount, _stackCount, _meshData);
	BuildCylinderBottomCap(_bottomRadius, _topRadius, _height, _sliceCount, _stackCount, _meshData);
}

VOID MeshGenerator::BuildCylinderTopCap(float _bottomRadius, float _topRadius, float _height, UINT _sliceCount, UINT _stackCount, MeshData& _meshData)
{
	UINT baseIndex = (UINT)_meshData.Vertices.size();
	
	const float XM_PI = 3.141592f;
	float y = 0.5f*_height;
	float dTheta = 2.0f*XM_PI / _sliceCount;

	// Duplicate cap ring vertices because the texture coordinates and normals differ.
	for (UINT i = 0; i <= _sliceCount; ++i)
	{
		float x = _topRadius * cosf(i*dTheta);
		float z = _topRadius * sinf(i*dTheta);

		// Scale down by the height to try and make top cap texture coord area
		// proportional to base.
		float u = x / _height + 0.5f;
		float v = z / _height + 0.5f;

		Vertex36 vertex;
		InitVertex36(vertex, x, y, z, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, u, v);
		_meshData.Vertices.push_back(vertex);
	}

	// Cap center vertex.
	Vertex36 vertex;
	InitVertex36(vertex, 0.0f, y, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.5f, 0.5f);
	_meshData.Vertices.push_back(vertex);

	// Index of center vertex.
	UINT centerIndex = (UINT)_meshData.Vertices.size() - 1;

	for (UINT i = 0; i < _sliceCount; ++i)
	{
		_meshData.Indices.push_back(centerIndex);
		_meshData.Indices.push_back(baseIndex + i + 1);
		_meshData.Indices.push_back(baseIndex + i);
	}
}

VOID MeshGenerator::BuildCylinderBottomCap(float _bottomRadius, float _topRadius, float _height, UINT _sliceCount, UINT _stackCount, MeshData& _meshData)
{
	// 
	// Build bottom cap.
	//

	UINT baseIndex = (UINT)_meshData.Vertices.size();
	const float XM_PI = 3.141592f;
	float y = -0.5f*_height;

	// vertices of ring
	float dTheta = 2.0f*XM_PI / _sliceCount;
	for (UINT i = 0; i <= _sliceCount; ++i)
	{
		float x = _bottomRadius * cosf(i*dTheta);
		float z = _bottomRadius * sinf(i*dTheta);

		// Scale down by the height to try and make top cap texture coord area
		// proportional to base.
		float u = x / _height + 0.5f;
		float v = z / _height + 0.5f;

		Vertex36 vertex;
		InitVertex36(vertex, x, y, z, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f, 0.0f, u, v);
		_meshData.Vertices.push_back(vertex);
	}

	// Cap center vertex.
	Vertex36 vertex;
	InitVertex36(vertex, 0.0f, y, 0.0f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.5f, 0.5f);
	_meshData.Vertices.push_back(vertex);

	// Cache the index of center vertex.
	UINT centerIndex = (UINT)_meshData.Vertices.size() - 1;

	for (UINT i = 0; i < _sliceCount; ++i)
	{
		_meshData.Indices.push_back(centerIndex);
		_meshData.Indices.push_back(baseIndex + i);
		_meshData.Indices.push_back(baseIndex + i + 1);
	}
}

VOID MeshGenerator::CreateCapsule(float _radius, float _halfHeight, MeshData& _meshData)
{
	MeshData sphere1;
	CreateSphere(_radius, 15, 15, sphere1);
	for (auto& vertex : sphere1.Vertices)
	{
		vertex.pos.y += _halfHeight;
		_meshData.Vertices.emplace_back(vertex);
	}
	for (auto& index : sphere1.Indices)
	{
		_meshData.Indices.emplace_back(index);
	}

	UINT count = _meshData.Vertices.size();

	MeshData sphere2;
	CreateSphere(_radius, 15, 15, sphere2);
	for (auto& vertex : sphere2.Vertices)
	{
		vertex.pos.y -= _halfHeight;
		_meshData.Vertices.emplace_back(vertex);
	}
	for (auto& index : sphere2.Indices)
	{
		_meshData.Indices.emplace_back(index + count);
	}

	count = _meshData.Vertices.size();

	MeshData cylinder;
	CreateCylinder(_radius, _radius, _halfHeight * 2, 15, 5, cylinder);
	for (auto& vertex : cylinder.Vertices)
	{
		_meshData.Vertices.emplace_back(vertex);
	}
	for (auto& index : cylinder.Indices)
	{
		_meshData.Indices.emplace_back(index + count);
	}
}

VOID MeshGenerator::CreateGrid(float _width, float _depth, UINT _m, UINT _n, MeshData& _meshData)
{
	UINT vertexCount = _m * _n;
	UINT faceCount = (_m - 1)*(_n - 1) * 2;

	//
	// Create the vertices.
	//

	float halfWidth = 0.5f*_width;
	float halfDepth = 0.5f*_depth;

	float dx = _width / (_n - 1);
	float dz = _depth / (_m - 1);

	float du = 1.0f / (_n - 1);
	float dv = 1.0f / (_m - 1);

	_meshData.Vertices.resize(vertexCount);
	for (UINT i = 0; i < _m; ++i)
	{
		float z = halfDepth - i * dz;
		for (UINT j = 0; j < _n; ++j)
		{
			float x = -halfWidth + j * dx;

			_meshData.Vertices[i*_n + j].pos = XMFLOAT3(x, 0.0f, z);
			_meshData.Vertices[i*_n + j].normal = XMFLOAT3(0.0f, 1.0f, 0.0f);
			_meshData.Vertices[i*_n + j].tangent = XMFLOAT3(1.0f, 0.0f, 0.0f);

			// Stretch texture over grid.
			_meshData.Vertices[i*_n + j].tex.x = j * du;
			_meshData.Vertices[i*_n + j].tex.y = i * dv;
		}
	}

	//
	// Create the indices.
	//

	_meshData.Indices.resize(faceCount * 3); // 3 indices per face

	// Iterate over each quad and compute indices.
	UINT k = 0;
	for (UINT i = 0; i < _m - 1; ++i)
	{
		for (UINT j = 0; j < _n - 1; ++j)
		{
			_meshData.Indices[k] = i * _n + j;
			_meshData.Indices[k + 1] = i * _n + j + 1;
			_meshData.Indices[k + 2] = (i + 1)*_n + j;
			
			_meshData.Indices[k + 3] = (i + 1)*_n + j;
			_meshData.Indices[k + 4] = i * _n + j + 1;
			_meshData.Indices[k + 5] = (i + 1)*_n + j + 1;

			k += 6; // next quad
		}
	}
}

VOID MeshGenerator::CreateFullscreenQuad(MeshData& _meshData)
{
	_meshData.Vertices.resize(4);
	_meshData.Indices.resize(6);

	// Position coordinates specified in NDC space.
	InitVertex36(_meshData.Vertices[0], -1.0f, -1.0f, 0.0f, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f);
	InitVertex36(_meshData.Vertices[1], -1.0f, +1.0f, 0.0f, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f);
	InitVertex36(_meshData.Vertices[2], +1.0f, +1.0f, 0.0f, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f);
	InitVertex36(_meshData.Vertices[3], +1.0f, -1.0f, 0.0f, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f);

	_meshData.Indices[0] = 0;
	_meshData.Indices[1] = 1;
	_meshData.Indices[2] = 2;
	
	_meshData.Indices[3] = 0;
	_meshData.Indices[4] = 2;
	_meshData.Indices[5] = 3;
}

VOID MeshGenerator::Subdivide(MeshData& _meshData)
{
	// Save a copy of the input geometry.
	MeshData inputCopy = _meshData;


	_meshData.Vertices.resize(0);
	_meshData.Indices.resize(0);

	//       v1
	//       *
	//      / \
	//     /   \
	//  m0*-----*m1
	//   / \   / \
	//  /   \ /   \
	// *-----*-----*
	// v0    m2     v2

	UINT numTris = inputCopy.Indices.size() / 3;
	for (UINT i = 0; i < numTris; ++i)
	{
		Vertex36 v0 = inputCopy.Vertices[inputCopy.Indices[i * 3 + 0]];
		Vertex36 v1 = inputCopy.Vertices[inputCopy.Indices[i * 3 + 1]];
		Vertex36 v2 = inputCopy.Vertices[inputCopy.Indices[i * 3 + 2]];

		//
		// Generate the midpoints.
		//

		Vertex36 m0, m1, m2;

		// For subdivision, we just care about the position component.  We derive the other
		// vertex components in CreateGeosphere.

		m0.pos = XMFLOAT3(
			0.5f*(v0.pos.x + v1.pos.x),
			0.5f*(v0.pos.y + v1.pos.y),
			0.5f*(v0.pos.z + v1.pos.z));

		m1.pos = XMFLOAT3(
			0.5f*(v1.pos.x + v2.pos.x),
			0.5f*(v1.pos.y + v2.pos.y),
			0.5f*(v1.pos.z + v2.pos.z));

		m2.pos = XMFLOAT3(
			0.5f*(v0.pos.x + v2.pos.x),
			0.5f*(v0.pos.y + v2.pos.y),
			0.5f*(v0.pos.z + v2.pos.z));

		//
		// Add new geometry.
		//

		_meshData.Vertices.push_back(v0); // 0
		_meshData.Vertices.push_back(v1); // 1
		_meshData.Vertices.push_back(v2); // 2
		_meshData.Vertices.push_back(m0); // 3
		_meshData.Vertices.push_back(m1); // 4
		_meshData.Vertices.push_back(m2); // 5
		
		_meshData.Indices.push_back(i * 6 + 0);
		_meshData.Indices.push_back(i * 6 + 3);
		_meshData.Indices.push_back(i * 6 + 5);
		
		_meshData.Indices.push_back(i * 6 + 3);
		_meshData.Indices.push_back(i * 6 + 4);
		_meshData.Indices.push_back(i * 6 + 5);
		
		_meshData.Indices.push_back(i * 6 + 5);
		_meshData.Indices.push_back(i * 6 + 4);
		_meshData.Indices.push_back(i * 6 + 2);
		
		_meshData.Indices.push_back(i * 6 + 3);
		_meshData.Indices.push_back(i * 6 + 1);
		_meshData.Indices.push_back(i * 6 + 4);
	}
}