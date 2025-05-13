#ifndef OUTGAME_H
#define OUTGAME_H

#include <windef.h>
#include "Button.h"
#include "Window.h"

class OutGame
{
public:
	OutGame() {

		RECT region_btn_start_game, region_btn_quit_game;

		region_btn_start_game.left = (WINDOW_WIDTH - BUTTON_WIDTH) / 2;
		region_btn_start_game.right = region_btn_start_game.left + BUTTON_WIDTH;
		region_btn_start_game.top = 430;
		region_btn_start_game.bottom = region_btn_start_game.top + BUTTON_HEIGHT;

		region_btn_quit_game.left = (WINDOW_WIDTH - BUTTON_WIDTH) / 2;
		region_btn_quit_game.right = region_btn_quit_game.left + BUTTON_WIDTH;
		region_btn_quit_game.top = 550;
		region_btn_quit_game.bottom = region_btn_quit_game.top + BUTTON_HEIGHT;

		btn_start_game = new StaetGameButton(region_btn_start_game,
			_T("img/ui_start_idle.png"), _T("img/ui_start_hovered.png"), _T("img/ui_start_pushed.png"));

		btn_quit_game = new QuitGameButton(region_btn_quit_game,
			_T("img/ui_quit_idle.png"), _T("img/ui_quit_hovered.png"), _T("img/ui_quit_pushed.png"));

		loadimage(&img_menu, _T("img/menu.png"));
	}

	~OutGame() {
		delete btn_start_game;
		delete btn_quit_game;
	}

	void ProcessEvent(const ExMessage& msg) {
		btn_start_game->ProcessEvent(msg);
		btn_quit_game->ProcessEvent(msg);
	}

	void Draw() {
		putimage(0, 0, &img_menu);
		btn_start_game->Draw();
		btn_quit_game->Draw();
	}

private:
	StaetGameButton* btn_start_game;
	QuitGameButton* btn_quit_game;
	IMAGE img_menu;
};

#endif // OUTGAME_H
