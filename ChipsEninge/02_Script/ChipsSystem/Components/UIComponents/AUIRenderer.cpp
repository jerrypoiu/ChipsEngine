#include "ChipsSystem/Components/UIComponents/AUIRenderer.h"
#include "ChipsSystem/Manager/UIManager.h"
#include "ChipsSystem/Etc/Mathf.h"

namespace ChipsEngine
{
	AUIRenderer::AUIRenderer(string _componentType) : AComponent(_componentType), m_layer(0)
	{
	}

	VOID AUIRenderer::SetLayer(UINT _layer)
	{
		m_layer = _layer;
		UIManager::GetInstance()->SortLayer();
	}

	VOID AUIRenderer::SetColor(XMVECTOR _color)
	{
		m_color = _color;
	}

	VOID AUIRenderer::SetColor(float _r, float _g, float _b, float _a)
	{
		m_color.m128_f32[0] = _r;
		m_color.m128_f32[1] = _g;
		m_color.m128_f32[2] = _b;
		m_color.m128_f32[3] = _a;
	}

	VOID AUIRenderer::SetAnchorPoint(float _x, float _y)
	{
		m_anchorPoint = XMFLOAT2(Mathf::Clamp(_x, 0.0f, 1.0f), Mathf::Clamp(_y, 0.0f, 1.0f));
	}
	VOID AUIRenderer::SetAnchorPoint(XMFLOAT2 _anchorPoint)
	{
		m_anchorPoint = XMFLOAT2(Mathf::Clamp(_anchorPoint.x, 0.0f, 1.0f), Mathf::Clamp(_anchorPoint.y, 0.0f, 1.0f));
	}

	VOID AUIRenderer::SetPivot(XMFLOAT2 _pivot)
	{
		m_pivot = XMFLOAT2(Mathf::Clamp(_pivot.x, 0.0f, 1.0f), Mathf::Clamp(_pivot.y, 0.0f, 1.0f));
	}
	
	VOID AUIRenderer::SetPivot(float _x, float _y)
	{
		m_pivot = XMFLOAT2(Mathf::Clamp(_x, 0.0f, 1.0f), Mathf::Clamp(_y, 0.0f, 1.0f));
	}

	XMVECTOR AUIRenderer::GetColor()
	{
		return m_color;
	}
}