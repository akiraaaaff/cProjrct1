#include<graphics.h>
#include "Player.h"
#include "Graphics.h"
#include "Enemy.h"

void TryGenerateEnemy(std::vector<Enemy*>& enemy_list) {
	const int INTERVAL = 100;
	static int counter = 0;
	if ((++counter) % INTERVAL == 0)
		enemy_list.push_back(new Enemy());
}

int main() {

	// 初始化
	initgraph(WINDOW_WIDTH, WINDOW_HEIGHT);

	bool running = true;

	Player player;
	ExMessage msg;
	IMAGE img_background;
	std::vector<Enemy*> enemy_list;

	loadimage(&img_background, _T("img/background.png"));

	BeginBatchDraw();

	while (running)
	{
		DWORD start_time = GetTickCount();

		// 读取操作
		while (peekmessage(&msg))
		{
			player.ProcessEvent(msg);
		}

		// 处理数据
		player.Move();
		TryGenerateEnemy(enemy_list);
		for (Enemy* enemy : enemy_list)
			enemy->Move(player);

		// 绘制画面
		cleardevice();

		putimage(0, 0, &img_background);
		player.Draw(1000 / 144);
		for (Enemy* enemy : enemy_list)
			enemy->Draw(1000 / 144);

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