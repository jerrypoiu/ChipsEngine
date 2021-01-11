#ifndef DEMO_SCENE_STARTSCENE_H
#define DEMO_SCENE_STARTSCENE_H
#include "ChipsSystem/BasicFrame/Scene.h"

namespace Demo
{
	class StartScene : public ChipsEngine::Scene
	{
	public:
		StartScene(string _name);
	private:
		virtual VOID Awake() override;
		virtual VOID Update() override;
	};
}

#endif //DEMO_SCENE_STARTSCENE_H