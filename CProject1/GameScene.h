#pragma once

#include "Scene.h"
#include "SceneManager.h"

#include<iostream>

extern SceneManager scene_manager;

class GameScene :public Scene
{
public:
	GameScene() = default;
	~GameScene() = default;

	void on_enter() {
		std::cout << "进入游戏场景" << std::endl;
	}

	void on_update() {
		std::cout << "游戏场景正在运行" << std::endl;
	}

	void on_draw() {
		outtextxy(10, 10, _T("游戏场景绘图内容"));
	}

	void on_input(const ExMessage& msg) {
		if (msg.message == WM_KEYDOWN) {
			scene_manager.swith_to(SceneManager::SceneType::Menu);
		}
	}

	void on_exit() {
		std::cout << "游戏场景退出" << std::endl;
	}

private:

};