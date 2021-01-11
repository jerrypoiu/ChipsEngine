#ifndef CHIPSSYSTEM_MANAGER_BUILDMANAGER_H
#define CHIPSSYSTEM_MANAGER_BUILDMANAGER_H
#include "ChipsSystem/Etc/Singleton.h"
#include "ChipsSystem/Global/Global.h"

namespace ChipsEngine
{
	/*
	BackGround 에서도 작동하기 기능이 구현되어 있다.
	위 기능은 SetIsRunInBackGround 함수로 설정할 수 있다.
	*/
	class BuildManager final : public Singletone<BuildManager>
	{
	private:
		bool m_isRunInBackGround;
		bool m_isInBackGround;
	public:
		BuildManager();
		~BuildManager() = default;
	public:
		inline bool GetIsRunInBackGround()
		{
			return m_isRunInBackGround;
		}
		inline VOID SetIsRunInBackGround(bool _isRunInBackGround)
		{
			m_isRunInBackGround = _isRunInBackGround;
		}
		inline bool GetIsInBackGround()
		{
			return m_isInBackGround;
		}
		inline VOID SetIsInBackGround(bool _paused)
		{
			m_isInBackGround = _paused;
		}
	};
}
#endif//CHIPSSYSTEM_MANAGER_GraphicManager_H