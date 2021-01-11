#ifndef DIRECTX_EFFECTS_RENDERSTATE_H
#define DIRECTX_EFFECTS_RENDERSTATE_H

class RenderStates
{
public:
	static void InitAll(ID3D11Device* device);
	static void DestroyAll();

	static ID3D11RasterizerState* WireframeRS;
	static ID3D11RasterizerState* NoCullRS;

	static ID3D11BlendState* AlphaToCoverageBS;
	static ID3D11BlendState* TransparentBS;
};

#endif //DIRECTX_EFFECTS_RENDERSTATE_H