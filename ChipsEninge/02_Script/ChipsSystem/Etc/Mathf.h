#ifndef CHIPSSYSTEM_ETC_MATHF_H
#define CHIPSSYSTEM_ETC_MATHF_H
#include "ChipsSystem/Components/BaiscComponents/Transform.h"
#include "ChipsSystem/Camera/Camera.h"

namespace ChipsEngine
{
	/*
	기본적인 수학 함수들을 제공한다.
	✓ Abs
	✓ Clamp
	✓ Pow
	✓ Sqrt
	✓ Lerp
	✓ Random
	✓ Dot	✓ DecomposeRollPitchYawZXYMatrix	✓ Inverse	✓ InverseTranspose
	*/
	class Mathf final
	{
	private:
		Mathf() = delete;
		~Mathf() = delete;
		Mathf(Mathf&) = delete;
		void operator=(Mathf&) = delete;
		Mathf(Mathf&&) = delete;
		void operator=(Mathf&&) = delete;
	public:
		static int Abs(int _value)
		{
			return (_value < 0) ? -_value : _value;
		}
		static float Abs(float _value)
		{
			return (_value < 0) ? -_value : _value;
		}
		static int Clamp(int _value, int _min, int _max)
		{
			if (_value < _min)
			{
				_value = _min;
			}
			else if (_value > _max)
			{
				_value = _max;
			}
			return _value;
		}
		static float Clamp(float _value, float _min, float _max)
		{
			if (_value < _min)
			{
				_value = _min;
			}
			else if (_value > _max)
			{
				_value = _max;
			}
			return _value;
		}
		static int Pow(int _value)
		{
			return _value * _value;
		}
		static float Pow(float _value)
		{
			return _value * _value;
		}
		static float Sqrt(float _value)
		{
			return sqrtf(_value);
		}
		static float Lerp(float _value, float _goal, float _amount)
		{
			return float(_value + ((_goal - _value) * _amount));
		}
		static float Random(float _min, float _max)
		{
			return _min + ((float)(rand()) / (float)RAND_MAX) *(_max - _min);
		}
		static float Dot(XMVECTOR _vector1, XMVECTOR _vector2)
		{
			float result = (_vector1.m128_f32[0] * _vector2.m128_f32[0]) 
				+ (_vector1.m128_f32[1] * _vector2.m128_f32[1]) 
				+ (_vector1.m128_f32[2] * _vector2.m128_f32[2]);

			return result;
		}
		static VOID DecomposeRollPitchYawZXYMatrix(XMMATRIX _matrix, float& _x, float& _y, float& _z)
		{
			_x = (float)asin(-_matrix.r[2].m128_f32[1]);

			double threshold = 0.001;

			double test = cos(_x);

			if (test > threshold)
			{
				_z = (float)atan2(_matrix.r[0].m128_f32[1], _matrix.r[1].m128_f32[1]);

				_y = (float)atan2(_matrix.r[2].m128_f32[0], _matrix.r[2].m128_f32[2]);

			}
			else
			{
				_z = atan2(-_matrix.r[1].m128_f32[0], _matrix.r[0].m128_f32[0]);

				_y = 0.0;
			}
		}
		static bool CheckFrustumCulling(Transform* _objectTransform, float _radius)
		{
			//XMVECTOR objectPosition = _objectTransform->GetWorldMatrix().r[3];
			//XMVECTOR cameraPosition = Camera::GetInstance()->GetTransform()->GetWorldMatrix().r[3];
			//XMVECTOR vec1 = XMVectorSubtract(objectPosition, cameraPosition);
			//vec1 = XMVector3Normalize(vec1);
			//XMVECTOR vec2 = Camera::GetInstance()->GetTransform()->GetWorldRotationMatrix().r[2];
			//vec2 = XMVector3Normalize(vec2);
			//return (0 > vec1.m128_f32[0] * vec2.m128_f32[0] + vec1.m128_f32[1] * vec2.m128_f32[1] + vec1.m128_f32[2] * vec2.m128_f32[2]);
			
			//float dist = DirectX::XMVectorGetX(DirectX::XMPlaneDotCoord(planes[0], ));


			XMFLOAT3 pos = _objectTransform->GetWorldPosition();

			for (int i = 0; i < 6; i++)
			{
				if (DirectX::XMVectorGetX(DirectX::XMPlaneDotCoord(Camera::GetInstance()->GetFrustumPlanes()[i], XMVectorSet(pos.x, pos.y, pos.z, 1.0f))) < -_radius)
					return true;
			}

			return false;
		}
		static XMMATRIX InverseTranspose(XMMATRIX M)
		{
			XMMATRIX A = M;
			A.r[3] = XMVectorSet(0.0f, 0.0f, 0.0f, 1.0f);

			XMVECTOR det = XMMatrixDeterminant(A);

			return XMMatrixTranspose(XMMatrixInverse(&det, A));
		}
		static XMMATRIX Inverse(XMMATRIX M)
		{
			XMMATRIX A = M;
			A.r[3] = XMVectorSet(0.0f, 0.0f, 0.0f, 1.0f);

			XMVECTOR det = XMMatrixDeterminant(A);
			return XMMatrixInverse(nullptr, A);
		}
	};
}

#endif //CHIPSSYSTEM_ETC_MATHF_H