#include "ChipsEninge.h"
#include "Demo/Scene/HouseScene.h"
#include "Demo/Scene/StartScene.h"

using namespace ChipsEngine;

/* 기본 설명
ChipsEngine은 DirectX11기반에 C++을 사용하는 소스 엔진이다.
ChipsEngine의 프레임워크는 CBD를 기반으로 하고 있다.
ChipsEngine은 LDR(Low Dyamic Range), Forward Rendering을 하고 있다.
클래스 구조와 함수 인터페이스가 Unity와 유사하여, Unity 사용자에게 친숙합니다.
프레임워크에 핵심을 이루는 클래스는 IEngineFrame, Application, Scene, GameObject, AComponent이다.
Application은 스트레티지 패턴을 통하여, 현재의 Scene을 게임 실행 중 바꿀 수 있다.
Scene은 다수의 GameObject를 포함할 수 있다. 이는 연극에서의 무대와 개념이 비슷하다.
GameObject는 다수의 AComponent의 자식 클래스들 (세부화된 기능을 가진 Component)을 포함할 수 있다.
개발자는 GameObject에 Component를 추가함으로써, 자신이 원하는 기능, 속성들을 쉽게 추가할 수 있다.
이외에도 BuildManager, GraphicManager, ScheduleManager, UIManager등 다양한 Manager를 통하여, 게임 전반적으로 필요한 세팅을 쉽게 할 수 있다.
*/

/* 핵심 기능
✓ Transform (Scene Graph)
✓ Physics Engine (PhysX) – Rigidbody, Collider
✓ Light System – Directional, Spot, Point, Shadow
✓ Basic Geometric Rendering, Sky Rendering
✓ Mesh, Skin Rendering and Skeletal Animation (FBX SDK)
✓ Particle Rendering
✓ UI Rendering – Text, Image, Button
✓ PostProcessing ("Bloom, SSAO, Blur, DoF, RayMarching, LUT(2D), ..." 총 36개)
✓ 3D Sound (FMOD)
✓ Input System - Keyboard, Mouse
✓ Schedule System – Unity 의 Invoke 기능과 유사.
✓ Debug Rendering
✓ Auto Memory Management 
   ㄴ SmartPointer를 기반으로 구현되었으며, Scene이 변경 되었을 때 혹은 사용자가 Destroy 함수를 호출하였을 때 관련 메모리가 자동으로 삭제됨
      즉, 개발자가 메모리를 직접 해제하지 않아도 알아서 메모리가 해제되며, 특수한 경우에는 직접 해제할 수 있음. 
*/

/* 지원 포멧
✓ 3D : fbx
✓ Texture : dds
✓ Sound : mp3, wav
✓ Font : spritefont
*/

int WINAPI WinMain(HINSTANCE _hInstance, HINSTANCE _prevInstance, PSTR _cmdLine, int _showCmd)
{	
	// Application를 생성하고, 시작 Scene을 지정해주는 부분.
	Application app("ChipsEngine", _hInstance, new Demo::HouseScene("Original"));
	//게임 실행
	app.Run();

	return 0;
}