#include "DirectX/Effects/Effect.h"

Effect::Effect(ID3D11Device* _device, const std::wstring& _filename)
	: m_fX(0)
{
	std::ifstream fin(_filename, std::ios::binary);

	fin.seekg(0, std::ios_base::end);
	int size = (int)fin.tellg();
	fin.seekg(0, std::ios_base::beg);
	std::vector<char> compiledShader(size);

	fin.read(&compiledShader[0], size);
	fin.close();
	
	/*if (SUCCEEDED(D3DX11CreateEffectFromMemory(&compiledShader[0], size, 0, _device, &m_fX)))
	{

	}*/
}

Effect::~Effect()
{
	SAFE_RELEASE(m_fX);
}