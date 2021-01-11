#include "ChipsSystem/Camera/Camera.h"
#include "ChipsSystem/Manager/GraphicManager.h"
#include "ChipsSystem/Components/BaiscComponents/Transform.h"
#include "ChipsSystem/Global/Global.h"
#include "ChipsSystem/Etc/Mathf.h"

namespace ChipsEngine
{
	Camera::Camera() : m_transform(new Transform())
	{
		SetLens(60.0f, 0.01f, 1000.0f);
		m_transform->GetWorldMatrix();
	}

	XMMATRIX Camera::View()
	{
		XMMATRIX translation = m_transform->GetWorldTranslationMatrix();

		translation.r[3].m128_f32[0] *= -1.0f;
		translation.r[3].m128_f32[1] *= -1.0f;
		translation.r[3].m128_f32[2] *= -1.0f;

		return translation * XMMatrixTranspose(m_transform->GetWorldRotationMatrix());
	}

	VOID Camera::SetLens(float _fovY, float _near, float _far)
	{
		m_fovY = _fovY * DEGREES_TO_RADIANS;
		m_aspect = GraphicManager::GetInstance()->GetWidth() / GraphicManager::GetInstance()->GetHeight();
		m_nearZ = _near;
		m_farZ = _far;

		m_nearWindowHeight = 2.0f * m_nearZ * tanf(0.5f*m_fovY);
		m_farWindowHeight = 2.0f * m_farZ * tanf(0.5f*m_fovY);

		XMMATRIX P = XMMatrixPerspectiveFovLH(m_fovY, m_aspect, m_nearZ, m_farZ);
		m_proj = P;
	}

	VOID Camera::ConstructFrustum()
	{
		XMFLOAT4X4 pMatrix;
		DirectX::XMStoreFloat4x4(&pMatrix, m_proj);
		float zMin = -pMatrix._43 / pMatrix._33;
		float r = m_farZ / (m_farZ - m_nearZ);

		pMatrix._33 = r;
		pMatrix._43 = -r * zMin;
		XMMATRIX newProj = DirectX::XMLoadFloat4x4(&pMatrix);
		XMMATRIX finalMatrix = DirectX::XMMatrixMultiply(View(), newProj);

		XMFLOAT4X4 matrix;
		DirectX::XMStoreFloat4x4(&matrix, finalMatrix);

		float x = (float)(matrix._14 + matrix._13);
		float y = (float)(matrix._24 + matrix._23);
		float z = (float)(matrix._34 + matrix._33);
		float w = (float)(matrix._44 + matrix._43);
		m_planes[0] = XMVectorSet(x, y, z, w);
		m_planes[0] = DirectX::XMPlaneNormalize(m_planes[0]);

		x = (float)(matrix._14 - matrix._13);
		y = (float)(matrix._24 - matrix._23);
		z = (float)(matrix._34 - matrix._33);
		w = (float)(matrix._44 - matrix._43);
		m_planes[1] = XMVectorSet(x, y, z, w);
		m_planes[1] = DirectX::XMPlaneNormalize(m_planes[1]);

		x = (float)(matrix._14 + matrix._11);
		y = (float)(matrix._24 + matrix._21);
		z = (float)(matrix._34 + matrix._31);
		w = (float)(matrix._44 + matrix._41);
		m_planes[2] = XMVectorSet(x, y, z, w);
		m_planes[2] = DirectX::XMPlaneNormalize(m_planes[2]);

		x = (float)(matrix._14 - matrix._11);
		y = (float)(matrix._24 - matrix._21);
		z = (float)(matrix._34 - matrix._31);
		w = (float)(matrix._44 - matrix._41);
		m_planes[3] = XMVectorSet(x, y, z, w);
		m_planes[3] = DirectX::XMPlaneNormalize(m_planes[3]);

		x = (float)(matrix._14 + matrix._12);
		y = (float)(matrix._24 + matrix._22);
		z = (float)(matrix._34 + matrix._32);
		w = (float)(matrix._44 + matrix._42);
		m_planes[4] = XMVectorSet(x, y, z, w);
		m_planes[4] = DirectX::XMPlaneNormalize(m_planes[4]);

		x = (float)(matrix._14 - matrix._12);
		y = (float)(matrix._24 - matrix._22);
		z = (float)(matrix._34 - matrix._32);
		w = (float)(matrix._44 - matrix._42);
		m_planes[5] = XMVectorSet(x, y, z, w);
		m_planes[5] = DirectX::XMPlaneNormalize(m_planes[5]);
;	}
}