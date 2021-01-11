#ifndef CHIPSSYSTEM_COMPONENTS_RENDERERCOMPONENTS_SKYRENDERER_H
#define CHIPSSYSTEM_COMPONENTS_RENDERERCOMPONENTS_SKYRENDERER_H
#include "ChipsSystem/BasicFrame/AComponent.h"

namespace ChipsEngine
{
	/*
	�ϴ��� �������ϴ� ������Ʈ�̴�.
	Yaw �����̼� ����� �����Ѵ�.
	*/
	class SkyRenderer final : public AComponent
	{
	private:
		float m_skyRotate;
		UINT m_indexCount;
		ID3D11Buffer* m_vertexBuffer;
		ID3D11Buffer* m_indexBuffer;
		ID3D11ShaderResourceView* m_cubeMapSRV;
	public:
		SkyRenderer();
	protected:
		~SkyRenderer() override = default;
	public:
		VOID LoadTexture(const string _fileName);
		inline VOID SetSkyRotationY(float _angleY)
		{
			m_skyRotate = _angleY;
		}
		inline float GetSkyRotationY()
		{
			return m_skyRotate;
		}
	private:
		VOID InitGemometryBuffer();
	private:
		virtual VOID Awake() final;
		virtual VOID Start() final;
		virtual VOID Update() final;
		virtual VOID FixedUpdate() final;
		virtual VOID Render() final;
		virtual VOID Release() final;
	};
}

#endif //CHIPSSYSTEM_COMPONENTS_RENDERERCOMPONENTS_SKYRENDERER_H