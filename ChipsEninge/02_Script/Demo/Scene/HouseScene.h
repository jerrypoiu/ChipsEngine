#ifndef DEMO_SCENE_HOUSESCENE_H
#define DEMO_SCENE_HOUSESCENE_H
#include "ChipsSystem/BasicFrame/Scene.h"

namespace Demo
{
	class HouseScene : public ChipsEngine::Scene
	{
	public:
		HouseScene(string _name);
	private:
		virtual VOID Awake() override;
		virtual VOID Update() override;
	};
}

#endif //DEMO_SCENE_HOUSESCENE_H