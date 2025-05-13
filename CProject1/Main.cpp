#include<graphics.h>
#include "OutGame.h"
#include "InGame.h"
#include "Sound.h"
#include "Window.h"
#include "Player.h"
#include "Enemy.h"

int main() {

	// 初始化
	initgraph(WINDOW_WIDTH, WINDOW_HEIGHT);

	ExMessage msg;
	OutGame out_game_state;
	InGame in_game_state;

	loadsound();

	BeginBatchDraw();

	while (running)
	{
		DWORD start_time = GetTickCount();

		// 读取操作
		while (peekmessage(&msg))
		{
			if (is_game_started)
			{
				in_game_state.ProcessEvent(msg);
			}
			else
			{
				out_game_state.ProcessEvent(msg);
			}
		}

		if (is_game_started)
		{
			// 处理数据
			in_game_state.Update();
		}

		// 绘制画面
		cleardevice();

		if (is_game_started)
		{
			in_game_state.Draw();
		}
		else
		{
			out_game_state.Draw();
		}

		FlushBatchDraw();

		// 锁帧
		DWORD end_time = GetTickCount();
		DWORD delta_time = end_time - start_time;

		if (delta_time < 1000 / 60)
		{
			Sleep(1000 / 60 - delta_time);
		}
	}

	// 释放资源
	EndBatchDraw();

	return 0;
}