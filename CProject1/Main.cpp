#include<graphics.h>
#include "Player.h"
#include "Graphics.h"
#include "Enemy.h"
#include "Sound.h"

void TryGenerateEnemy(std::vector<Enemy*>& enemy_list) {
	const int INTERVAL = 10;
	static int counter = 0;
	if ((++counter) % INTERVAL == 0)
		enemy_list.push_back(new Enemy());
}

void UpdateBullets(std::vector<Bullet>& bullet_list, const Player& player) {

	const double RADIAL_SPEED = 0.0045;                        // 径向波动速度
	const double TANGENT_SPEED = 0.0055;                       // 切向波动速度
	double radian_interval = 2 * 3.14159 / bullet_list.size(); // 子弹之间的弧度间隔
	POINT player_position = player.GetPosition();
	double radius = 100 + 25 * sin(GetTickCount() * RADIAL_SPEED);
	for (size_t i = 0; i < bullet_list.size(); i++)
	{
		double radian = GetTickCount() * TANGENT_SPEED + radian_interval * i; // 子弹当前所在弧度值
		bullet_list[i].position.x = player_position.x + player.FRAME_WIDTH / 2 + (int)(radius * sin(radian));
		bullet_list[i].position.y = player_position.y + player.FRAME_HEIGHT / 2 + (int)(radius * cos(radian));
	}
}

// 绘制玩家得分
void DrawPlayerScore(int score) {

	static TCHAR text[64];
	_stprintf_s(text, _T("当前玩家得分:%d"), score);
	setbkmode(TRANSPARENT);
	settextcolor(RGB(255, 85, 185));
	outtextxy(10, 10, text);
}

int main() {

	// 初始化
	initgraph(WINDOW_WIDTH, WINDOW_HEIGHT);

	bool running = true;

	int score = 0;
	Player player;
	ExMessage msg;
	IMAGE img_background;
	std::vector<Enemy*> enemy_list;
	std::vector<Bullet> bullet_list(3);

	loadsound();
	loadimage(&img_background, _T("img/background.png"));
	mciSendString(_T("play bgm repeat from 0"), NULL, 0, NULL);

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
		UpdateBullets(bullet_list, player);
		TryGenerateEnemy(enemy_list);
		for (Enemy* enemy : enemy_list)
			enemy->Move(player);

		// 检测敌人和玩家的碰撞
		for (Enemy* enemy : enemy_list)
		{
			if (enemy->CheckPlayerCollision(player)) {

				static TCHAR text[128];
				_stprintf_s(text, _T("最终得分:%d！"), score);
				MessageBox(GetHWnd(), text, _T("游戏结束"), MB_OK);
				running = false;
				break;
			}
		}

		// 检测子弹和敌人的碰撞
		for (Enemy* enemy : enemy_list)
		{
			for (const Bullet& bullet : bullet_list)
			{
				if (enemy->CheckBulletCollision(bullet)) {
					enemy->Hurt();
					mciSendString(_T("play hit from 0"), NULL, 0, NULL);
				}
			}
		}

		// 移除生命值归零的敌人
		for (int i = enemy_list.size() - 1; i >= 0; i--)
		{
			if (!enemy_list[i]->CheckAlive()) {
				delete enemy_list[i];  // 释放内存
				std::swap(enemy_list[i], enemy_list.back());  // 交换到最后
				enemy_list.pop_back();  // 删除最后一个（O(1) 操作）
				score++;
			}
		}

		// 绘制画面
		cleardevice();

		putimage(0, 0, &img_background);
		player.Draw(1000 / 144);
		for (Enemy* enemy : enemy_list)
			enemy->Draw(1000 / 144);
		for (const Bullet& bullet : bullet_list)
			bullet.Draw();
		DrawPlayerScore(score);

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