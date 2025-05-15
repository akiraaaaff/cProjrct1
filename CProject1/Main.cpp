#include<graphics.h>
#include "Scene.h"
#include "MenuScene.h"
#include "SelectorScene.h"
#include "GameScene.h"
#include "SceneManager.h"

Scene* menu_scene = nullptr;
Scene* selector_scene = nullptr;
Scene* game_scene = nullptr;
SceneManager scene_manager;

int main() {

	ExMessage msg;
	const int FPS = 60;

	initgraph(1280, 720, EW_SHOWCONSOLE);

	BeginBatchDraw();

	menu_scene = new MenuScene();
	selector_scene = new SelectorScene();
	game_scene = new GameScene();
	scene_manager.set_current_scene(menu_scene);

	while (true)
	{
		DWORD start_time = GetTickCount();

		while (peekmessage(&msg))
		{
			scene_manager.on_input(msg);
		}

		scene_manager.on_update();

		cleardevice();
		scene_manager.on_draw();
		FlushBatchDraw();

		DWORD end_time = GetTickCount();
		DWORD delta_time = end_time - start_time;

		if (delta_time < 1000 / FPS)
		{
			Sleep(1000 / 60 - delta_time);
		}
	}

	EndBatchDraw();

	return 0;
}