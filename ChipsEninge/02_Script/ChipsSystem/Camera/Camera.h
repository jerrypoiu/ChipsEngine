#ifndef CHIPSSYSTEM_CAMERA_CAMERA_H
#define	CHIPSSYSTEM_CAMERA_CAMERA_H
#include "ChipsSystem/Etc/Singleton.h"

namespace ChipsEngine
{
	class Transform;

	/*
	1. 메인 카메라를 의미하는 클래스이다.
	   싱글톤으로 구현되어 있어, 어디서든 쉽게 접근이 가능하다.
	2. Transform 이 기본적으로 포함되어 있다.
	   Camera 는 추가적인 Component 들은 포함될 수 없다.
	3. SetLens 함수를 통하여 fovY, nearZ, farZ 를 설정할 수 있다.
	*/
	class Camera final : public Singletone<Camera>
	{
	private:
		float m_nearZ;
		float m_farZ;
		float m_aspect;
		float m_fovY;
		float m_nearWindowHeight;
		float m_farWindowHeight;
		Transform* m_transform;
		XMMATRIX m_proj;
		XMVECTOR m_planes[6];
	public:
		Camera();
		~Camera() = default;
	public:
		Transform* GetTransform()
		{
			return m_transform;
		}

		inline float GetNearZ() const
		{
			return m_nearZ;
		}
		inline float GetFarZ() const
		{
			return m_farZ;
		}
		inline float GetAspect() const
		{
			return m_aspect;
		}
		inline float GetFovY() const
		{
			return m_fovY;
		}
		inline float GetFovX() const
		{
			float halfWidth = 0.5f*GetNearWindowWidth();
			return 2.0f*atan(halfWidth / m_nearZ);
		}

		inline float GetNearWindowWidth() const
		{
			return m_aspect * m_nearWindowHeight;
		}
		inline float GetNearWindowHeight() const
		{
			return m_nearWindowHeight;
		}
		inline float GetFarWindowWidth() const
		{
			return m_aspect * m_farWindowHeight;
		}
		inline float GetFarWindowHeight() const
		{
			return m_farWindowHeight;
		}

		VOID SetLens(float _fovY, float _near, float _far);
		VOID ConstructFrustum();
		inline XMVECTOR* GetFrustumPlanes()
		{
			return m_planes;
		}
		
		XMMATRIX View();
		inline XMMATRIX Proj() const
		{
			return m_proj;

		}
	};
}
#endif//CHIPSSYSTEM_CAMERA_CAMERA_H