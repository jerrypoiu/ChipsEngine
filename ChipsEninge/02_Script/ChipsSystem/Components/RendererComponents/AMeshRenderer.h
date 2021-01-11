#ifndef CHIPSSYSTEM_COMPONENETS_RENDERERCOMPONENETS_AMESHRERENDERER_H
#define CHIPSSYSTEM_COMPONENETS_RENDERERCOMPONENETS_AMESHRERENDERER_H
#include "ChipsSystem/BasicFrame/AComponent.h"
#include "DirectX/Effects/LightHelper.h"

namespace ChipsEngine
{
	/*
	1. Mesh 형태의 물체를 렌더링 하기위한 다음 PlaneRenderer, BoxRenderer, SphereRenderer, 
	   CylinderRenderer, CapsuleRenderer, FbxRenderer 클래스들의 부모 클래스이다.
	2. 메테리얼과 텍스쳐를 다중으로 사용할 수 있다. 
	   메테리얼의 경우에는 Ambient, Diffuse, Specular, Reflect 를 조정할 수 있다. 
	   사용 가능한 텍스쳐의 종류로는 Diffuse, Normal, Specular 가 있다. 
	3. CartoonStyle, RimLight, Transparent, AlphaClip, TextureTilling 같은 다양한 렌더링 스타일을 지원한다. 
	4. FrustumCulling 기능을 지원한다. 해당 기능을 통하여 화면에 들어오지 않는 객체는 렌더링을 스킵할 수 있다. 
	*/
	class AMeshRenderer abstract : public AComponent
	{
	protected:
		bool m_isLoaded;
		UINT m_indexCount;
		int m_matCount;
		ID3D11Buffer* m_vertexBuffer;
		ID3D11Buffer* m_indexBuffer;
	private:
		bool m_isFrustumCullingActive;
		bool m_isTextureUse;
		bool m_isNormalUse;
		bool m_isReflectUse;
		bool m_isCartoonUse;
		bool m_isUseShadow;
		bool m_isSpecularUse;
		bool m_isAlphaClipUse;
		bool m_isRimLightUse;
		bool m_isMakeShadow;
		float m_frustumRadius;
		vector<Material> m_material;
		XMMATRIX m_texTransform;
		ID3D11BlendState* m_blendState;
		ID3DX11EffectTechnique* m_tech;
		vector<ID3D11ShaderResourceView*> m_diffuseSRV;
		vector<ID3D11ShaderResourceView*> m_normalSRV;
		vector<ID3D11ShaderResourceView*> m_specularSRV;
	public:
		AMeshRenderer(string _componentType);
	protected:
		virtual ~AMeshRenderer() = default;
	public:
		VOID AddMaterial();
		VOID AddMaterial(Material _material);
		VOID AddDiffuseTexture(const string _fileName);
		VOID AddNormalTexture(const string _fileName);
		VOID AddSpecularTexture(const string _fileName);
		VOID SetTextureTiling(float _x, float _y);
		VOID SetTransparentRendering(bool _isActive);
		VOID SetCartoonStyleRendering(bool _active);
		inline VOID SetMakeShadow(bool _active)
		{
			m_isMakeShadow = _active;
		}
		inline VOID SetReceiveShadow(bool _active)
		{
			m_isUseShadow = _active;
		}
		inline VOID SetFrustumCulling(bool _active)
		{
			m_isFrustumCullingActive = _active;
		}
		inline VOID SetFrustumCullingRadius(float _radius)
		{
			m_frustumRadius = _radius;
		}
		inline VOID SetReflectRendering(bool _active)
		{
			m_isReflectUse = _active;
		}
		inline VOID SetSpecularRendering(bool _active)
		{
			m_isSpecularUse = _active;
		}
		inline VOID SetAlphaClipRendering(bool _active)
		{
			m_isAlphaClipUse = _active;
		}
		inline VOID SetRimLightRendering(bool _active)
		{
			m_isRimLightUse = _active;
		}
		inline bool SetMaterial(Material _material, UINT _index = 0)
		{
			if (m_material.size() < _index)
			{		
				return false;
			}

			m_material[_index] = _material;
			return true;
		}
		inline bool SetAmbient(XMFLOAT4 _ambient, UINT _index = 0)
		{
			if (m_material.size() < _index)
			{
				return false;
			}

			m_material[_index].Ambient = _ambient;
			return true;
		}
		inline bool SetDiffuse(XMFLOAT4 _diffuse, UINT _index = 0)
		{
			if (m_material.size() < _index)
			{
				return false;
			}

			m_material[_index].Diffuse = _diffuse;
			return true;
		}
		inline bool SetSpecular(XMFLOAT4 _specular, UINT _index = 0)
		{
			if (m_material.size() < _index)
			{
				return false;
			}

			m_material[_index].Specular = _specular;
			return true;
		}
		inline bool SetReflect(XMFLOAT4 _reflect, UINT _index = 0)
		{
			if (m_material.size() < _index)
			{
				return false;
			}

			m_material[_index].Reflect = _reflect;
			return true;
		}
	public:
		VOID BuildShadowMap();
		VOID WriteLinearDepth();
	private:
		virtual VOID InitGemometryBuffer() abstract;
		virtual VOID SetShaderSkinningValues();
		virtual VOID SetShaderSkinningShadowValues();
	private:
		virtual VOID Awake() final;
		virtual	VOID Start() final;
		virtual VOID Update() final;
		virtual VOID FixedUpdate() final;
		virtual VOID Render() final;
		virtual VOID Release() final;
	};
}
#endif //CHIPSSYSTEM_COMPONENETS_RENDERERCOMPONENETS_AMESHRERENDERER_H