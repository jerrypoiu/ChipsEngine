#ifndef CHIPSSYSTEM_COMPONENETS_UICOMPONENTS_AUIREDERER_H
#define CHIPSSYSTEM_COMPONENETS_UICOMPONENTS_AUIREDERER_H
#include "ChipsSystem/BasicFrame/AComponent.h"

namespace ChipsEngine
{
	/*
	ImageUIRenderer, TextUIRenderer 의 부모 클래스이다. 
	스크린 공간에서 UI를 렌더링하기 위한 공통적인 구현 부분을 제공한다. 
	다음과 같은 기능들을 제공한다.
	*기능들*
	✓ Layer
	✓ Color
	✓ AnchorPoint
	✓ Pivot
	*/
	class AUIRenderer abstract : public AComponent
	{
	private:
		UINT m_layer;
		RECT m_rect;
		XMFLOAT2 m_pivot;
		XMFLOAT2 m_anchorPoint;
		XMVECTOR m_color;
	public:
		AUIRenderer(string _componentType);
	protected:
		virtual ~AUIRenderer() = default;
	public:
		inline RECT GetRect()
		{
			return m_rect;
		}
		VOID SetLayer(UINT _layer);
		virtual VOID SetColor(XMVECTOR _color);
		virtual VOID SetColor(float _r, float _g, float _b, float _a = 1.0f);
		VOID SetAnchorPoint(float _x, float _y);
		VOID SetAnchorPoint(XMFLOAT2 _anchorPoint);
		VOID SetPivot(XMFLOAT2 _pivot);
		VOID SetPivot(float _x, float _y);

		inline XMFLOAT2 GetPiviot()
		{
			return m_pivot;
		}
		virtual XMVECTOR GetColor();
		inline UINT GetLayer()
		{
			return m_layer;
		}
		inline XMFLOAT2 GetAnchorPoint()
		{
			return m_anchorPoint;
		}
	protected:
		inline VOID SetRect(RECT _rect)
		{
			m_rect = _rect;
		}
	private:
		virtual VOID RenderUI() abstract;
	private:
		virtual VOID Awake() abstract;
		virtual VOID Start() abstract;
		virtual VOID Update() abstract;
		virtual VOID FixedUpdate() abstract;
		virtual VOID Render() abstract;
		virtual VOID Release() abstract;
	};
}

#endif //CHIPSSYSTEM_COMPONENETS_UICOMPONENTS_AUIREDERER_H