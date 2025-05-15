#pragma once
#pragma once

#include "Scene.h"
#include "SceneManager.h"

#include<iostream>

extern SceneManager scene_manager;

class SelectorScene :public Scene
{
public:
	SelectorScene() = default;
	~SelectorScene() = default;

	void on_enter() {
		std::cout << "进入角色选择场景" << std::endl;
	}

	void on_update() {
		std::cout << "角色选择场景正在运行" << std::endl;
	}

	void on_draw() {
		outtextxy(10, 10, _T("角色选择场景绘图内容"));
	}

	void on_input(const ExMessage& msg) {
		if (msg.message == WM_KEYDOWN) {
			scene_manager.swith_to(SceneManager::SceneType::Game);
		}
	}

	void on_exit() {
		std::cout << "角色选择场景退出" << std::endl;
	}

private:

};