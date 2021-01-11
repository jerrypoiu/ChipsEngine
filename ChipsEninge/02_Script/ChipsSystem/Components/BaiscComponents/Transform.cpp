#include "ChipsSystem/Components/BaiscComponents/Transform.h"
#include "ChipsSystem/BasicFrame/AComponent.h"
#include "ChipsSystem/BasicFrame/GameObject.h"
#include "ChipsSystem/Etc/Mathf.h"
#include "ChipsSystem/Time/Time.h"

namespace ChipsEngine
{
	Transform::Transform() : AComponent("Transform"), m_parent(nullptr)
	{
		m_worldTranslationMatrix = XMMatrixIdentity();
		m_worldRotationMatrix = XMMatrixIdentity();
		m_worldScaleMatrix = XMMatrixIdentity();

		m_worldMatrix = m_worldScaleMatrix * m_worldRotationMatrix * m_worldTranslationMatrix;

		m_localTranslationMatrix = XMMatrixIdentity();
		m_localRotationMatrix = XMMatrixIdentity();
		m_localScaleMatrix = XMMatrixIdentity();

		m_worldUpVector = XMVECTOR();
		m_worldUpVector.m128_f32[1] = 1.0f;

		SetWorldPosition(0.0f, 0.0f, 0.0f);
		SetWorldRotation(0.0f, 0.0f, 0.0f);
		SetWorldScale(1.0f, 1.0f, 1.0f);

		SetLocalPosition(0.0f, 0.0f, 0.0f);
		SetLocalRotation(0.0f, 0.0f, 0.0f);
		SetLocalScale(1.0f, 1.0f, 1.0f);
	}

#pragma region Set World XMFLOAT3
	VOID Transform::SetWorldPosition(float _x, float _y, float _z)
	{
		SetWorldPosition(XMFLOAT3(_x, _y, _z));
	}
					   
	VOID Transform::SetWorldPosition(XMFLOAT3 _position)
	{
		m_worldPosition = _position;
		m_worldTranslationMatrix.r[3].m128_f32[0] = _position.x;
		m_worldTranslationMatrix.r[3].m128_f32[1] = _position.y;
		m_worldTranslationMatrix.r[3].m128_f32[2] = _position.z;

		if (m_parent != nullptr)
		{
			UpdateLocalTranslationMatrix();
		}
	}
					   
	VOID Transform::SetWorldRotation(float _x, float _y, float _z)
	{
		SetWorldRotation(XMFLOAT3(_x, _y, _z));
	}
					   
	VOID Transform::SetWorldRotation(XMFLOAT3 _rotation)
	{
		m_worldRotation = _rotation;
		m_worldRotationMatrix = XMMatrixRotationRollPitchYaw(m_worldRotation.x * DEGREES_TO_RADIANS,
															 m_worldRotation.y * DEGREES_TO_RADIANS,
															 m_worldRotation.z * DEGREES_TO_RADIANS);

		if (m_parent != nullptr)
		{
			UpdateLocalRotationMatrix();
		}
	}														 
					   
	VOID Transform::SetWorldScale(float _x, float _y, float _z)
	{
		SetWorldScale(XMFLOAT3(_x, _y, _z));
	}
					   
	VOID Transform::SetWorldScale(XMFLOAT3 _scale)
	{
		if (_scale.x < 0)
			_scale.x = 0;

		if (_scale.y < 0)
			_scale.y = 0;

		if (_scale.z < 0)
			_scale.z = 0;

		m_worldScale = _scale;
		m_worldScaleMatrix.r[0].m128_f32[0] = _scale.x;
		m_worldScaleMatrix.r[1].m128_f32[1] = _scale.y;
		m_worldScaleMatrix.r[2].m128_f32[2] = _scale.z;

		if (m_parent != nullptr)
		{
			UpdateLocalScaleMatrix();
		}
	}
#pragma endregion

#pragma region Set Local XMFLOAT3
	VOID Transform::SetLocalPosition(float _x, float _y, float _z)
	{
		SetLocalPosition(XMFLOAT3(_x, _y, _z));
	}

	VOID Transform::SetLocalPosition(XMFLOAT3 _position)
	{
		if (m_parent == nullptr)
		{
			SetWorldPosition(_position.x, _position.y, _position.z);
		}
		else
		{
			m_localPosition = _position;
			m_localTranslationMatrix.r[3].m128_f32[0] = _position.x;
			m_localTranslationMatrix.r[3].m128_f32[1] = _position.y;
			m_localTranslationMatrix.r[3].m128_f32[2] = _position.z;
		}
	}

	VOID Transform::SetLocalRotation(float _x, float _y, float _z)
	{
		SetLocalRotation(XMFLOAT3(_x, _y, _z));
	}

	VOID Transform::SetLocalRotation(XMFLOAT3 _rotation)
	{
		if (m_parent == nullptr)
		{
			SetWorldRotation(_rotation.x, _rotation.y, _rotation.z);
		}
		else
		{
			m_localRotation = _rotation;
			m_localRotationMatrix = XMMatrixRotationRollPitchYaw(_rotation.x * DEGREES_TO_RADIANS,
																 _rotation.y * DEGREES_TO_RADIANS,
																 _rotation.z * DEGREES_TO_RADIANS);
		}
	}
	
	VOID Transform::SetLocalScale(float _x, float _y, float _z)
	{
		SetLocalScale(XMFLOAT3(_x, _y, _z));
	}
	
	VOID Transform::SetLocalScale(XMFLOAT3 _scale)
	{
		if (m_parent == nullptr)
		{
			SetWorldScale(_scale.x, _scale.y, _scale.z);
		}
		else
		{
			if (_scale.x < 0)
				_scale.x = 0;

			if (_scale.y < 0)
				_scale.y = 0;

			if (_scale.z < 0)
				_scale.z = 0;

			m_localScale = _scale;
			m_localScaleMatrix.r[0].m128_f32[0] = _scale.x;
			m_localScaleMatrix.r[1].m128_f32[1] = _scale.y;
			m_localScaleMatrix.r[2].m128_f32[2] = _scale.z;
		}
	}
#pragma endregion

#pragma region Get Matrix
	XMMATRIX Transform::GetWorldTranslationMatrix()
	{
		UpdateWorldTranslationMatrix();
		return m_worldTranslationMatrix;
	}
	
	XMMATRIX Transform::GetWorldRotationMatrix()
	{
		UpdateWorldRotationMatrix();
		return m_worldRotationMatrix;
	}
	
	XMMATRIX Transform::GetWorldScaleMatrix()
	{
		UpdateWorldScaleMatrix();
		return m_worldScaleMatrix;
	}

	XMMATRIX Transform::GetLocalTranslationMatrix()
	{
		if (m_parent == nullptr)
		{
			return GetWorldTranslationMatrix();
		}
		else
		{
			return m_localTranslationMatrix;
		}
	}

	XMMATRIX Transform::GetLocalRotationMatrix()
	{
		if (m_parent == nullptr)
		{
			return GetWorldRotationMatrix();
		}
		else
		{
			return m_localRotationMatrix;
		}
	}

	XMMATRIX Transform::GetLocalScaleMatrix()
	{
		if (m_parent == nullptr)
		{
			return GetWorldScaleMatrix();
		}
		else
		{
			return m_localScaleMatrix;
		}
	}

	XMMATRIX Transform::GetWorldMatrix()
	{
		UpdateWorldMatrix();
		return m_worldMatrix;
	}
#pragma endregion

#pragma region Set Parent, Child
	VOID Transform::SetParent(Transform* _parentTransform)
	{
		if (m_parent != nullptr)
		{
			m_parent->DeleteChild(this);
		}

		m_parent = _parentTransform;
		m_parent->GetChildren().emplace_back(this);

		UpdateLocalMatrix();
		UpdateWorldMatrix();
	}
	
	VOID Transform::AddChild(Transform* _childTransform)
	{
		if (_childTransform->GetParent() != nullptr)
		{
			_childTransform->GetParent()->DeleteChild(_childTransform);
		}

		_childTransform->m_parent = this;
		m_children.emplace_back(_childTransform);

		UpdateLocalMatrix();
		UpdateWorldMatrix();
	}

	VOID Transform::DeleteChild(Transform* _deleteTransform)
	{
		for (auto iter = m_children.begin(); iter != m_children.end(); iter++)
		{
			if ((*iter) == _deleteTransform)
			{
				(*iter)->m_parent = nullptr;
				m_children.erase(iter);
				return;
			}
		}
	}
#pragma endregion

#pragma region Affine
	VOID Transform::Translate(XMFLOAT3 _transAmount, bool _isLocalOperate)
	{
		Translate(_transAmount.x, _transAmount.y, _transAmount.z, _isLocalOperate);
	}

	VOID Transform::Translate(float _x, float _y, float _z, bool _isLocalOperate)
	{
		if (_isLocalOperate)
		{
			XMVECTOR position = XMVectorSet(m_worldPosition.x, m_worldPosition.y, m_worldPosition.z, 1.0f);
			XMVECTOR amount = XMVectorSet(_x, _y, _z, 1.0f);
			XMVECTOR moveVector = XMVector3Transform(amount, GetWorldRotationMatrix());
			position.m128_f32[0] = position.m128_f32[0] + moveVector.m128_f32[0];
			position.m128_f32[1] = position.m128_f32[1] + moveVector.m128_f32[1];
			position.m128_f32[2] = position.m128_f32[2] + moveVector.m128_f32[2];
			
			XMMATRIX resultMatrix = DirectX::XMMatrixTranslationFromVector(position);

			SetWorldPosition(resultMatrix.r[3].m128_f32[0], resultMatrix.r[3].m128_f32[1], resultMatrix.r[3].m128_f32[2]);
		}
		else
		{
			SetWorldPosition(m_worldPosition.x + _x, m_worldPosition.y + _y, m_worldPosition.z + _z);
		}
	}

	VOID Transform::Rotate(XMFLOAT3 _rotateAmount, bool _isLocalOperate)
	{
		Rotate(_rotateAmount.x, _rotateAmount.y, _rotateAmount.z, _isLocalOperate);
	}

	VOID Transform::Rotate(float _x, float _y, float _z, bool _isLocalOperate)
	{
		if (_isLocalOperate)
		{
			float radianX = _x * DEGREES_TO_RADIANS;
			float radianY = _y * DEGREES_TO_RADIANS;
			float radianZ = _z * DEGREES_TO_RADIANS;

			XMMATRIX rotationMatrix = XMMatrixRotationRollPitchYaw(radianX, radianY, radianZ) * m_worldRotationMatrix;
			
			float x = 0.0f, y = 0.0f, z = 0.0f;
			Mathf::DecomposeRollPitchYawZXYMatrix(rotationMatrix, x, y, z);
			
			m_worldRotation = XMFLOAT3(x * RADIANS_TO_DEGRESS, y * RADIANS_TO_DEGRESS, z * RADIANS_TO_DEGRESS);
			m_worldRotationMatrix = rotationMatrix;

			if (m_parent != nullptr)
			{
				UpdateLocalRotationMatrix();
			}
		}
		else
		{
			SetWorldRotation(m_worldRotation.x + _x, m_worldRotation.y + _y, m_worldRotation.z + _z);
		}
	}
	
	VOID Transform::RotateAround(XMFLOAT3 _point, XMFLOAT3 _angle)
	{
		if (_point.x == GetWorldPosition().x
			&& _point.y == GetWorldPosition().y
			&& _point.z == GetWorldPosition().z)
			return;

		if (_angle.x == 0 && _angle.y == 0 && _angle.z == 0)
			return;

		XMMATRIX translateMatrix = XMMatrixIdentity();
		translateMatrix.r[3].m128_f32[0] = m_worldPosition.x - _point.x;
		translateMatrix.r[3].m128_f32[1] = m_worldPosition.y - _point.y;
		translateMatrix.r[3].m128_f32[2] = m_worldPosition.z - _point.z;

		XMMATRIX rotationMatrix = XMMatrixRotationRollPitchYaw(_angle.x * DEGREES_TO_RADIANS,
															   _angle.y * DEGREES_TO_RADIANS,
															   _angle.z * DEGREES_TO_RADIANS);

		XMMATRIX result = translateMatrix * rotationMatrix;
		result.r[3].m128_f32[0] = _point.x + result.r[3].m128_f32[0];
		result.r[3].m128_f32[1] = _point.y + result.r[3].m128_f32[1];
		result.r[3].m128_f32[2] = _point.z + result.r[3].m128_f32[2];

		float rotX = _angle.x + GetWorldRotation().x;
		float rotY = _angle.y + GetWorldRotation().y;
		float rotZ = _angle.z + GetWorldRotation().z;

		SetWorldRotation(rotX, rotY, rotZ);
		SetWorldPosition(result.r[3].m128_f32[0], result.r[3].m128_f32[1], result.r[3].m128_f32[2]);
	}

	VOID Transform::LootAt(XMFLOAT3 _target)
	{
		if (_target.x == GetWorldPosition().x
			&& _target.y == GetWorldPosition().y
			&& _target.z == GetWorldPosition().z)
			return;

		XMVECTOR worldPosition = XMLoadFloat3(&GetWorldPosition());
		XMVECTOR focusPosition = XMLoadFloat3(&_target);

		XMVECTOR forwardVector = XMVector3Normalize(XMVectorSubtract(focusPosition, worldPosition));
		XMVECTOR rightVector = XMVector3Normalize(XMVector3Cross(m_worldUpVector, forwardVector));
		XMVECTOR upVector = XMVector3Normalize(XMVector3Cross(forwardVector, rightVector));

		XMMATRIX lookAtMatrix = XMMatrixIdentity();
		lookAtMatrix.r[0] = rightVector;
		lookAtMatrix.r[1] = upVector;
		lookAtMatrix.r[2] = forwardVector;

		float x = 0, y = 0, z = 0;
		Mathf::DecomposeRollPitchYawZXYMatrix(lookAtMatrix, x, y, z);

		m_worldRotation = XMFLOAT3(x * RADIANS_TO_DEGRESS, y * RADIANS_TO_DEGRESS, z * RADIANS_TO_DEGRESS);
		m_worldRotationMatrix = lookAtMatrix;

		if (m_parent != nullptr)
		{
			UpdateLocalRotationMatrix();
		}
	}

	VOID Transform::MoveTo(XMFLOAT3 _destination, float _percent)
	{
		_percent = Mathf::Clamp(_percent, 0.0f, 1.0f);

		XMFLOAT3 worldPosition = GetWorldPosition();
		XMFLOAT3 movedPosition;
		movedPosition.x = (worldPosition.x * (1.0f - _percent)) + (_destination.x * _percent);
		movedPosition.y = (worldPosition.y * (1.0f - _percent)) + (_destination.y * _percent);
		movedPosition.z = (worldPosition.z * (1.0f - _percent)) + (_destination.z * _percent);

		SetWorldPosition(movedPosition);
	}

	VOID Transform::RotateTo(XMFLOAT3 _destination, float _percent)
	{
		_percent = Mathf::Clamp(_percent, 0.0f, 1.0f);

		XMFLOAT3 worldRotation = GetWorldRotation();
		XMFLOAT3 movedRotation;
		movedRotation.x = (worldRotation.x * (1.0f - _percent)) + (_destination.x * _percent);
		movedRotation.y = (worldRotation.y * (1.0f - _percent)) + (_destination.y * _percent);
		movedRotation.z = (worldRotation.z * (1.0f - _percent)) + (_destination.z * _percent);

		SetWorldRotation(movedRotation);
	}
#pragma endregion

#pragma region Update Matrix
	VOID Transform::UpdateLocalTranslationMatrix()
	{
		XMMATRIX parentInverseRotationMatrix = XMMatrixTranspose(m_parent->GetWorldRotationMatrix());

		XMMATRIX parentInverseTramslationMatrix = XMMatrixIdentity();
		parentInverseTramslationMatrix.r[3].m128_f32[0] = -m_parent->GetWorldPosition().x;
		parentInverseTramslationMatrix.r[3].m128_f32[1] = -m_parent->GetWorldPosition().y;
		parentInverseTramslationMatrix.r[3].m128_f32[2] = -m_parent->GetWorldPosition().z;

		XMMATRIX worldMatrix = m_worldRotationMatrix * m_worldTranslationMatrix * parentInverseTramslationMatrix * parentInverseRotationMatrix;
		m_localPosition = XMFLOAT3(worldMatrix.r[3].m128_f32[0], worldMatrix.r[3].m128_f32[1], worldMatrix.r[3].m128_f32[2]);
		m_localTranslationMatrix.r[3].m128_f32[0] = m_localPosition.x;
		m_localTranslationMatrix.r[3].m128_f32[1] = m_localPosition.y;
		m_localTranslationMatrix.r[3].m128_f32[2] = m_localPosition.z;
	}

	VOID Transform::UpdateLocalRotationMatrix()
	{
		XMMATRIX parentInverseRotationMatrix = XMMatrixTranspose(m_parent->GetWorldRotationMatrix());

		float localRotX = 0.0f;
		float localRotY = 0.0f;
		float localRotZ = 0.0f;
		XMMATRIX resultRotationMatrix = m_worldRotationMatrix * parentInverseRotationMatrix;
		Mathf::DecomposeRollPitchYawZXYMatrix(resultRotationMatrix, localRotX, localRotY, localRotZ);

		m_localRotation = XMFLOAT3(localRotX * RADIANS_TO_DEGRESS, localRotY * RADIANS_TO_DEGRESS, localRotZ * RADIANS_TO_DEGRESS);
		m_localRotationMatrix = resultRotationMatrix;
	}
	
	VOID Transform::UpdateLocalScaleMatrix()
	{
		//크기
		float localScaleX = m_worldScale.x / m_parent->GetWorldScale().x;
		float localScaleY = m_worldScale.y / m_parent->GetWorldScale().y;
		float localScaleZ = m_worldScale.z / m_parent->GetWorldScale().z;

		m_localScale = XMFLOAT3(localScaleX, localScaleY, localScaleZ);
		m_localScaleMatrix.r[0].m128_f32[0] = m_localScale.x;
		m_localScaleMatrix.r[1].m128_f32[1] = m_localScale.y;
		m_localScaleMatrix.r[2].m128_f32[2] = m_localScale.z;
	}

	VOID Transform::UpdateLocalMatrix()
	{
		//크기
		UpdateLocalScaleMatrix();

		//회전
		UpdateLocalRotationMatrix();

		//위치
		UpdateLocalTranslationMatrix();
	}

	VOID Transform::UpdateWorldTranslationMatrix()
	{
		if (m_parent != nullptr)
		{
			XMMATRIX resultMatrix = m_localRotationMatrix * m_localTranslationMatrix * m_parent->GetWorldRotationMatrix() * m_parent->GetWorldTranslationMatrix();

			float worldPosX = resultMatrix.r[3].m128_f32[0];
			float worldPosY = resultMatrix.r[3].m128_f32[1];
			float worldPosZ = resultMatrix.r[3].m128_f32[2];

			m_worldPosition = XMFLOAT3(worldPosX, worldPosY, worldPosZ);
			m_worldTranslationMatrix.r[3].m128_f32[0] = m_worldPosition.x;
			m_worldTranslationMatrix.r[3].m128_f32[1] = m_worldPosition.y;
			m_worldTranslationMatrix.r[3].m128_f32[2] = m_worldPosition.z;
		}

		m_worldMatrix = m_worldScaleMatrix * m_worldRotationMatrix * m_worldTranslationMatrix;
	}

	VOID Transform::UpdateWorldRotationMatrix()
	{
		if (m_parent != nullptr)
		{
			float worldRotX = 0.0f;
			float worldRotY = 0.0f;
			float worldRotZ = 0.0f;
			XMMATRIX resultRotationMatrix = m_localRotationMatrix * m_parent->GetWorldRotationMatrix();
			Mathf::DecomposeRollPitchYawZXYMatrix(resultRotationMatrix, worldRotX, worldRotY, worldRotZ);

			m_worldRotation = XMFLOAT3(worldRotX * RADIANS_TO_DEGRESS, worldRotY * RADIANS_TO_DEGRESS, worldRotZ * RADIANS_TO_DEGRESS);
			m_worldRotationMatrix = resultRotationMatrix;
		}

		m_worldMatrix = m_worldScaleMatrix * m_worldRotationMatrix * m_worldTranslationMatrix;
	}

	VOID Transform::UpdateWorldScaleMatrix()
	{
		if (m_parent != nullptr)
		{
			float worldScaleX = m_localScale.x * m_parent->GetWorldScale().x;
			float worldScaleY = m_localScale.y * m_parent->GetWorldScale().y;
			float worldScaleZ = m_localScale.z * m_parent->GetWorldScale().z;

			m_worldScale = XMFLOAT3(worldScaleX, worldScaleY, worldScaleZ);
			m_worldScaleMatrix.r[0].m128_f32[0] = m_worldScale.x;
			m_worldScaleMatrix.r[1].m128_f32[1] = m_worldScale.y;
			m_worldScaleMatrix.r[2].m128_f32[2] = m_worldScale.z;
		}

		m_worldMatrix = m_worldScaleMatrix * m_worldRotationMatrix * m_worldTranslationMatrix;
	}

	VOID Transform::UpdateWorldMatrix()
	{
		if (m_parent != nullptr)
		{
			//Scale
			UpdateWorldScaleMatrix();

			//Rotation
			UpdateWorldRotationMatrix();

			//Position
			UpdateWorldTranslationMatrix();
		}
	
		m_worldMatrix = m_worldScaleMatrix * m_worldRotationMatrix * m_worldTranslationMatrix;
	}
#pragma endregion

#pragma region IBasicFrame
	VOID Transform::Awake()
	{	}
	
	VOID Transform::Start()
	{
	}

	VOID Transform::Update()
	{
	}

	VOID Transform::FixedUpdate()
	{
	}

	VOID Transform::Render()
	{
	}
	
	VOID Transform::Release()
	{
		m_parent = nullptr;
		m_children.clear();
	}
#pragma endregion
}