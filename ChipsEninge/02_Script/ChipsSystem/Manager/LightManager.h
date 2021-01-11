#ifndef CHIPSSYSTEM_MANAGER_LIGHTMANAGER_H
#define CHIPSSYSTEM_MANAGER_LIGHTMANAGER_H
#include "DirectX/Effects/LightHelper.h"
#include "ChipsSystem/Etc/Singleton.h"
#include "ChipsSystem/Components/RendererComponents/AMeshRenderer.h"
#include "ChipsSystem/Components/LightComponents/DirectionalLight.h"
#include "ChipsSystem/Components/LightComponents/PointLight.h"
#include "ChipsSystem/Components/LightComponents/SpotLight.h"
#include <array>

namespace ChipsEngine
{
	using BuildShadowMapFunction = function<void(void)>;

	/*
	그림자 맵의 사용 여부와 범위를 지정할 수 있다.
	*/
	class LightManager final : public Singletone<LightManager>
	{
		friend AMeshRenderer;
		friend DirectionalLight;		
		friend PointLight;
		friend SpotLight;
	private:
		const int m_spotLightMaxCount;
		const int m_pointLightMaxCount;
		const int m_directionalLightMaxCount;
	private:
		float m_radius;
		bool m_isMakeShadow;
		int m_directionalLightCount;
		UINT m_width;
		UINT m_height;
		XMFLOAT3 m_center;
		XMVECTOR m_lightPos;
		XMMATRIX m_t;
		XMMATRIX m_lightView;
		XMMATRIX m_lightProj;
		XMMATRIX m_shadowTransform;
		D3D11_VIEWPORT m_viewport;
		ID3D11ShaderResourceView* m_depthMapSRV;
		ID3D11DepthStencilView* m_depthMapDSV;
		list<AMeshRenderer*> m_meshRenderers;
		vector<int*> m_spotLightsIndexs;
		vector<int*> m_pointLightsIndexs;
		vector<SpotLightData> m_spotLights;
		vector<PointLightData> m_pointLights;
		vector<DirectionalLightData> m_directionalLights;
	public: 
		LightManager();
		~LightManager() = default;
	public:
		inline VOID SetMakeShadow(bool _active)
		{
			m_isMakeShadow = _active;
		}
		inline bool GetMakeShadow()
		{
			return m_isMakeShadow;
		}
		VOID SetShadowBoundary(float _boundary)
		{
			m_radius = _boundary;
		}
		inline float GetShadowBoundary()
		{
			return m_radius;
		}
	private:
		VOID LoadSRVandDSV();
		VOID AddMeshRenderer(AMeshRenderer* _meshRenderer);
		VOID RemoveMeshRenderer(AMeshRenderer* _meshRenderer);
	private:
		inline XMMATRIX GetShadowTransform()
		{
			return m_shadowTransform;
		}
		inline XMMATRIX GetLightView()
		{
			return m_lightView;
		}
		inline XMMATRIX GetLightProj()
		{
			return m_lightProj;
		}
	private:
		VOID CreateSpotLight(int* _index);
		VOID CreatePointLight(int* _index);
		DirectionalLightData* GetDirectionalLight();
	private:
		VOID RemoveSpotLight(int _index);
		VOID RemovePointLight(int _index);
	public:
		VOID Awake();
		VOID Update();
		VOID Render();
		VOID Clear();
	};
}

#endif //CHIPSSYSTEM_MANAGER_LIGHTMANAGER_H