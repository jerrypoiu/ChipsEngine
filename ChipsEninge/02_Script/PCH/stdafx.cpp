#include "stdafx.h"
#include "DirectX/Effects/Effects.h"

#ifdef _DEBUG
#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")
#define new new(_CLIENT_BLOCK,__FILE__,__LINE)
#endif

void InitVertex36(Vertex36& _vertex36, 
				float _posX, float _posY, float _posZ, 
				float _normalX, float  _normalY, float _normalZ, 
				float _tangentX, float  _tangentY, float _tangentZ, 
				float _texX, float _texY,
				int _matNum,
				float _weight1, float _weight2, float _weight3, float _weight4,
				UINT _BoneIndices1, UINT _BoneIndices2, UINT _BoneIndices3, UINT _BoneIndices4)
{
	_vertex36.pos.x = _posX;
	_vertex36.pos.y = _posY;
	_vertex36.pos.z = _posZ;
	_vertex36.normal.x = _normalX;
	_vertex36.normal.y = _normalY;
	_vertex36.normal.z = _normalZ;
	_vertex36.tangent.x = _tangentX;
	_vertex36.tangent.y = _tangentY;
	_vertex36.tangent.z = _tangentZ;
	_vertex36.tex.x = _texX;
	_vertex36.tex.y = _texY;
	_vertex36.matNum = _matNum;
	_vertex36.weights.x = _weight1;
	_vertex36.weights.y = _weight2;
	_vertex36.weights.z = _weight3;
	_vertex36.weights.w = _weight4;
	_vertex36.BoneIndices.x = _BoneIndices1;
	_vertex36.BoneIndices.y = _BoneIndices2;
	_vertex36.BoneIndices.z = _BoneIndices3;
	_vertex36.BoneIndices.w = _BoneIndices4;
}

const D3D11_INPUT_ELEMENT_DESC InputLayoutDesc::Pos[1] =
{
	{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 }
};

const D3D11_INPUT_ELEMENT_DESC InputLayoutDesc::Basic32[3] =
{
	{"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
	{"NORMAL",   0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0},
	{"TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 24, D3D11_INPUT_PER_VERTEX_DATA, 0}
};

const D3D11_INPUT_ELEMENT_DESC InputLayoutDesc::VertexToPost[2] =
{
	{"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
	{"TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0}
};

const D3D11_INPUT_ELEMENT_DESC InputLayoutDesc::Vertex36[7] =
{
	{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0,  D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "NORMAL",   0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT,    0, 24, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "TANGENT",  0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 32, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "MATNUM",   0, DXGI_FORMAT_R32_SINT,        0, 44, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "WEIGHTS",  0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 48, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "BONEINDICES",  0, DXGI_FORMAT_R32G32B32A32_UINT, 0, 64, D3D11_INPUT_PER_VERTEX_DATA, 0 }
};

const D3D11_INPUT_ELEMENT_DESC InputLayoutDesc::Particle[5] =
{
	{"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0,  0, D3D11_INPUT_PER_VERTEX_DATA, 0},
	{"VELOCITY", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0},
	{"SIZE",     0, DXGI_FORMAT_R32G32_FLOAT,    0, 24, D3D11_INPUT_PER_VERTEX_DATA, 0},
	{"AGE",      0, DXGI_FORMAT_R32_FLOAT,       0, 32, D3D11_INPUT_PER_VERTEX_DATA, 0},
	{"TYPE",     0, DXGI_FORMAT_R32_UINT,        0, 36, D3D11_INPUT_PER_VERTEX_DATA, 0},
};

ID3D11InputLayout* InputLayouts::Pos = 0;
ID3D11InputLayout* InputLayouts::Vertex36 = 0;
ID3D11InputLayout* InputLayouts::VertexToPost = 0;
ID3D11InputLayout* InputLayouts::Particle = 0;

void InputLayouts::InitAll(ID3D11Device* device)
{
	D3DX11_PASS_DESC passDesc;
	
	//
	//Pos
	//
	Effects::SkyFX->SkyTech->GetPassByIndex(0)->GetDesc(&passDesc);
	device->CreateInputLayout(InputLayoutDesc::Pos, 1, passDesc.pIAInputSignature, passDesc.IAInputSignatureSize, &Pos);

	//
	// Standard
	//
	Effects::StandardShaderFX->StandardTech->GetPassByIndex(0)->GetDesc(&passDesc);
	device->CreateInputLayout(InputLayoutDesc::Vertex36, 7, passDesc.pIAInputSignature,passDesc.IAInputSignatureSize, &Vertex36);

	//
	// PostProcessing
	//
	Effects::PostProcessingFX->PostProcessingTech->GetPassByIndex(0)->GetDesc(&passDesc);
	device->CreateInputLayout(InputLayoutDesc::VertexToPost, 2, passDesc.pIAInputSignature,passDesc.IAInputSignatureSize, &VertexToPost);

	//
	// Particle
	//
	Effects::ParticleFX->StreamOutTech->GetPassByIndex(0)->GetDesc(&passDesc);
	device->CreateInputLayout(InputLayoutDesc::Particle, 5, passDesc.pIAInputSignature, passDesc.IAInputSignatureSize, &Particle);
}

void InputLayouts::DestroyAll()
{
	SAFE_RELEASE(Pos);
	SAFE_RELEASE(Vertex36);
	SAFE_RELEASE(Particle);
	SAFE_RELEASE(VertexToPost);
}
