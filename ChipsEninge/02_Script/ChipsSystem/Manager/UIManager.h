#ifndef CHIPSSYSTEM_MANAGER_UIMANAGER_H
#define CHIPSSYSTEM_MANAGER_UIMANAGER_H
#include "ChipsSystem/Components/UIComponents/AUIRenderer.h"
#include "ChipsSystem/Etc/Singleton.h"
#include "ChipsSystem/Global/Global.h"

namespace ChipsEngine
{
	using UIRenderComponent = pair<AUIRenderer*, function<VOID(VOID)>>;

	/*
	ConstantSize �� ����� �����Ǿ� �ְ�, UI �� �������� �۵��� ����
	�����ϴ� Manager �̱⿡ �پ��� ����� ���������� �ʴ�.
	*/
	class UIManager final : public Singletone<UIManager>
	{
		friend AUIRenderer;
	private:
		bool m_isConstantSize;
		list<UIRenderComponent> m_uiRenderers;
	public:
		UIManager();
		~UIManager() = default;
	private:
		VOID SortLayer();
	public:
		inline VOID SetConstantSize(bool _isConstantSize)
		{
			m_isConstantSize = _isConstantSize;
		}
		VOID AddUIRenderer(UIRenderComponent _uiRenderer);
	public:
		inline bool GetIsConstantSize()
		{
			return m_isConstantSize;
		}
	public:
		VOID Awake();
		VOID Render();
		VOID Clear();
	};
}
#endif //CHIPSSYSTEM_MANAGER_UIMANAGER_H