#pragma once

#include "Scene.h"

#include<iostream>

class MenuScene :public Scene
{
public:
	MenuScene() = default;
	~MenuScene() = default;

	void on_enter() {
		std::cout << "进入主菜单" << std::endl;
	}

	void on_update() {
		std::cout << "主菜单正在运行" << std::endl;
	}

	void on_draw() {
		outtextxy(10, 10, _T("主菜单绘图内容"));
	}

	void on_input(const Scene& msg) {}

	void on_exit() {
		std::cout << "主菜单退出" << std::endl;
	}

private:

};