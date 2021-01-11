#ifndef CHIPSSYSTEM_COMPONENTS_BASICCOMPONENTS_TRANSFORM_H
#define CHIPSSYSTEM_COMPONENTS_BASICCOMPONENTS_TRANSFORM_H
#include "ChipsSystem/BasicFrame/AComponent.h"

namespace ChipsEngine
{
	/*
	 Position, Rotation, Scale 관련된 기능이 포함된 컴퍼넌트이다. 
	 모든 GameObject 에 기본적으로 포함된다.
	 Local과 World Matrix를 따로 두었고, 필요에 따라 각 Matrix를 업데이트는 방식으로 연산량을 최소화 시켰다.
	*/
	class Transform final : public AComponent
	{
	private:
#pragma region SceneGraph
		Transform* m_parent;
		vector<Transform*> m_children;
#pragma endregion
#pragma region XMMATRIX
		XMMATRIX m_worldMatrix;
		XMMATRIX m_worldTranslationMatrix;
		XMMATRIX m_worldRotationMatrix;
		XMMATRIX m_worldScaleMatrix;
		XMMATRIX m_localTranslationMatrix;
		XMMATRIX m_localRotationMatrix;
		XMMATRIX m_localScaleMatrix;
#pragma endregion
#pragma region XMFLOAT3
		XMFLOAT3 m_worldPosition;
		XMFLOAT3 m_worldRotation;
		XMFLOAT3 m_worldScale;
		XMFLOAT3 m_localPosition;
		XMFLOAT3 m_localRotation;
		XMFLOAT3 m_localScale;
#pragma endregion
		XMVECTOR m_worldUpVector;
	public:
		Transform();
	protected:
		~Transform() override = default;
	public:
#pragma region GetVector
		inline XMVECTOR GetRight()
		{
			return m_worldRotationMatrix.r[0];
		}
		inline XMVECTOR GetUp()
		{
			return m_worldRotationMatrix.r[1];
		}
		inline XMVECTOR GetForward()
		{
			return m_worldRotationMatrix.r[2];
		}
#pragma endregion
	public:
#pragma region GetLocalMatrix
		XMMATRIX GetLocalTranslationMatrix();
		XMMATRIX GetLocalRotationMatrix();
		XMMATRIX GetLocalScaleMatrix();
#pragma endregion
#pragma region GetWorldMatrix
		XMMATRIX GetWorldTranslationMatrix();
		XMMATRIX GetWorldRotationMatrix();
		XMMATRIX GetWorldScaleMatrix();		
		XMMATRIX GetWorldMatrix();
#pragma endregion
	public:
#pragma region SceneGraph Functions
		inline Transform* GetParent()
		{
			return m_parent;
		}
		inline Transform* GetChild(int _index)
		{
			return m_children[_index];
		}
		inline vector<Transform*>& GetChildren()
		{
			return m_children;
		}
		inline int GetChildrenCount()
		{
			return m_children.size();
		}
		VOID SetParent(Transform* _parentTransform);
		VOID AddChild(Transform* _childTransform);
		VOID DeleteChild(Transform* _deleteTransform);
#pragma endregion
	public:
#pragma region GetWorldXMFLOAT3
		inline XMFLOAT3 GetWorldPosition()
		{
			return m_worldPosition;
		}
		inline XMFLOAT3 GetWorldRotation()
		{
			return m_worldRotation;
		}
		inline XMFLOAT3 GetWorldScale()
		{
			return m_worldScale;
		}
#pragma endregion
#pragma region GetLocalXMFLOAT3
		inline XMFLOAT3 GetLocalPosition()
		{
			if (m_parent == nullptr)
			{
				return GetWorldPosition();
			}
			else
			{
				return m_localPosition;
			}
		}
		inline XMFLOAT3 GetLocalRotation()
		{
			if (m_parent == nullptr)
			{
				return GetWorldRotation();
			}
			else
			{
				return m_localRotation;
			}
		}
		inline XMFLOAT3 GetLocalScale()
		{
			if (m_parent == nullptr)
			{
				return GetWorldScale();
			}
			else
			{
				return m_localScale;
			}
		}
#pragma endregion
	public:
#pragma region SetWorldXMFLOAT3
		VOID SetWorldPosition(float _x, float _y, float _z);
		VOID SetWorldPosition(XMFLOAT3 _position);
		VOID SetWorldRotation(float _x, float _y, float _z);
		VOID SetWorldRotation(XMFLOAT3 _rotation);
		VOID SetWorldScale(float _x, float _y, float _z);
		VOID SetWorldScale(XMFLOAT3 _scale);
#pragma endregion
#pragma region SetLocalXMFLOAT3
		VOID SetLocalPosition(float _x, float _y, float _z);
		VOID SetLocalPosition(XMFLOAT3 _position);
		VOID SetLocalRotation(float _x, float _y, float _z);
		VOID SetLocalRotation(XMFLOAT3 _rotation);
		VOID SetLocalScale(float _x, float _y, float _z);
		VOID SetLocalScale(XMFLOAT3 _scale);
#pragma endregion
	public:
#pragma region Linear Transform
		VOID Translate(float _x, float _y, float _z, bool _isLocalOperate = true);
		VOID Translate(XMFLOAT3 _transAmount, bool _isLocalOperate = true);
		VOID Rotate(float _x, float _y, float _z, bool _isLocalOperate = true);
		VOID Rotate(XMFLOAT3 _rotateAmount, bool _isLocalOperate = true);
		VOID RotateAround(XMFLOAT3 _point, XMFLOAT3 _angle);
		VOID LootAt(XMFLOAT3 _target);
		VOID MoveTo(XMFLOAT3 _destination, float _percent);
		VOID RotateTo(XMFLOAT3 _destination, float _percent);
#pragma endregion
	private:
#pragma region UpdateLocalMatrix
		VOID UpdateLocalTranslationMatrix();
		VOID UpdateLocalRotationMatrix();
		VOID UpdateLocalScaleMatrix();
		VOID UpdateLocalMatrix();
#pragma endregion
#pragma region UpdateWorldMatrix
		VOID UpdateWorldTranslationMatrix();
		VOID UpdateWorldRotationMatrix();
		VOID UpdateWorldScaleMatrix();
		VOID UpdateWorldMatrix();
#pragma endregion
	private:
		virtual VOID Awake() final; 
		virtual	VOID Start() final;
		virtual VOID Update() final;
		virtual VOID FixedUpdate() final;
		virtual VOID Render() final;
		virtual VOID Release() final;
	};
}
#endif //CHIPSSYSTEM_COMPONENTS_BASICCOMPONENTS_TRANSFORM_H
