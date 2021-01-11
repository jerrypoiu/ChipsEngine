#ifndef DEPRECATED_OBJRENDERER_H
#define DEPRECATED_OBJRENDERER_H
#include "DirectX/Effects/LightHelper.h"
#include "ChipsSystem/BasicFrame/Component.h"
#include "DirectX/MeshGenerator/MeshGenerator.h"

namespace ChipsFrame
{
	class ObjRenderer final : public Component
	{
	private:
		bool m_isLoaded;
		UINT m_indexCount;
		MeshData m_meshData;
		Material	  m_material;
		ID3D11Buffer* m_vertexBuffer;
		ID3D11Buffer* m_indexBuffer;
		XMFLOAT4X4	  m_texTransform;
		ID3DX11EffectTechnique* m_tech;
		ID3D11ShaderResourceView* m_meshSRV;
	public:
		ObjRenderer();
	protected:
		virtual ~ObjRenderer() = default;
	public:
		VOID LoadMesh(string _meshFilePath);
		VOID LoadTexture(const string _fileName);
		VOID SetTextureTiling(float _x, float _y);
		inline VOID SetMaterial(Material _material)
		{
			m_material = _material;
		}
		inline VOID SetAmbient(XMFLOAT4 _ambient)
		{
			m_material.Ambient = _ambient;
		}
		inline VOID SetDiffuse(XMFLOAT4 _diffuse)
		{
			m_material.Diffuse = _diffuse;
		}
		inline VOID SetSpecular(XMFLOAT4 _specular)
		{
			m_material.Specular = _specular;
		}
		inline VOID SetReflect(XMFLOAT4 _reflect)
		{
			m_material.Reflect = _reflect;
		}
	private:
		VOID BuildMaterial();
		VOID ReadFileCounts(string _filename, int& _vertexCount, int& _textureCount, int& _normalCount, int& _faceCount);
		VOID LoadDataStructures(string _filename, int vertexCount, int _textureCount, int _normalCount, int _faceCount);
		VOID InitGemometryBuffer();
	private:
		virtual VOID Init() final;
		virtual VOID Update() final;
		virtual VOID Render() final;
		virtual VOID Release() final;
	};
}

#endif //DEPRECATED_OBJRENDERER_H