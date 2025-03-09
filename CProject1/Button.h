#ifndef BUTTON_H
#define BUTTON_H

#include <windef.h>
#include <graphics.h>
#include "State.h"

const int BUTTON_WIDTH = 192;
const int BUTTON_HEIGHT = 75;

class Button
{
public:
	Button(RECT rect, LPCTSTR path_img_idle, LPCTSTR path_img_hovered, LPCTSTR path_img_pushed) {

		region = rect;

		loadimage(&img_idle, path_img_idle);
		loadimage(&img_hovered, path_img_hovered);
		loadimage(&img_pushed, path_img_pushed);
	}

	~Button() = default;

	void ProcessEvent(const ExMessage& msg) {
		switch (msg.message)
		{
		case WM_MOUSEMOVE:
			if (status == Status::Idle && CheckCursorHit(msg.x, msg.y))
				status = Status::Hovered;
			else if (status == Status::Hovered && !CheckCursorHit(msg.x, msg.y))
				status = Status::Idle;
			break;
		case WM_LBUTTONDOWN:
			if (CheckCursorHit(msg.x, msg.y))
				status = Status::Pushed;
			break;
		case WM_LBUTTONUP:
			if (status == Status::Pushed)
			{
				OnClick();
			}
			break;
		}
	}

	void Draw() {
		switch (status)
		{
		case Button::Status::Idle:
			putimage(region.left, region.top, &img_idle);
			break;
		case Button::Status::Hovered:
			putimage(region.left, region.top, &img_hovered);
			break;
		case Button::Status::Pushed:
			putimage(region.left, region.top, &img_pushed);
			break;
		}
	}

protected:
	virtual void OnClick() = 0;

private:
	enum class Status
	{
		Idle = 0,
		Hovered,
		Pushed
	};

private:
	RECT region;
	IMAGE img_idle;
	IMAGE img_hovered;
	IMAGE img_pushed;
	Status status = Status::Idle;

private:
	// 检测鼠标点击
	bool CheckCursorHit(int x, int y) {
		return x >= region.left && x <= region.right
			&& y >= region.top && y <= region.bottom;
	}
};

// 游戏开始按钮
class StaetGameButton :public Button
{
public:
	StaetGameButton(RECT rect, LPCTSTR path_img_idle, LPCTSTR path_img_hovered, LPCTSTR path_img_pushed)
		:Button(rect, path_img_idle, path_img_hovered, path_img_pushed) {}
	~StaetGameButton() = default;

protected:
	void OnClick() {
		is_game_started = true;
		mciSendString(_T("play bgm repeat from 0"), NULL, 0, NULL);
	}
};

// 退出开始按钮
class QuitGameButton :public Button
{
public:
	QuitGameButton(RECT rect, LPCTSTR path_img_idle, LPCTSTR path_img_hovered, LPCTSTR path_img_pushed)
		:Button(rect, path_img_idle, path_img_hovered, path_img_pushed) {}
	~QuitGameButton() = default;

protected:
	void OnClick() {
		running = false;
	}
};

#endif // BUTTON_H
