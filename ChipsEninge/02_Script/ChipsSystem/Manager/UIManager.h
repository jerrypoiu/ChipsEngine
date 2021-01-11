#ifndef CHIPSSYSTEM_MANAGER_UIMANAGER_H
#define CHIPSSYSTEM_MANAGER_UIMANAGER_H
#include "ChipsSystem/Components/UIComponents/AUIRenderer.h"
#include "ChipsSystem/Etc/Singleton.h"
#include "ChipsSystem/Global/Global.h"

namespace ChipsEngine
{
	using UIRenderComponent = pair<AUIRenderer*, function<VOID(VOID)>>;

	/*
	ConstantSize 이 기능이 구현되어 있고, UI 의 정상적인 작동을 위해
	존재하는 Manager 이기에 다양한 기능을 제공하지는 않다.
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