#include<graphics.h>
#include "Scene.h"
#include "MenuScene.h"

int main() {

	ExMessage msg;
	const int FPS = 60;

	initgraph(1280, 720, EW_SHOWCONSOLE);

	BeginBatchDraw();

	Scene* scene = new MenuScene();
	scene->on_enter();

	while (true)
	{
		DWORD start_time = GetTickCount();

		while (peekmessage(&msg))
		{
			scene->on_input(msg);
		}

		scene->on_update();

		cleardevice();
		scene->on_draw();
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