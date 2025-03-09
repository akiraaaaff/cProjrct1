#ifndef ANIMATION_H
#define ANIMATION_H

#include<graphics.h>
#include <vector>
#include "Graphics.h"

class Animation
{
public:
	Animation(LPCTSTR path, int num, int interval) {

		interval_ms = interval;

		TCHAR path_file[256];
		for (size_t i = 0; i < num; i++)
		{
			_stprintf_s(path_file, path, i);

			IMAGE* frame = new IMAGE();
			loadimage(frame, path_file);
			frame_list.push_back(frame);
		}
	}

	~Animation() {
		for (size_t i = 0; i < frame_list.size(); i++) {
			delete frame_list[i];
		}
	}

	void play(int x, int y, int delta) {

		timer += delta;
		if (timer >= interval_ms) {
			idx_frame = (idx_frame + 1) % frame_list.size();
			timer = 0;
		}

		putimage_alpha(x, y, frame_list[idx_frame]);
	}

private:
	int timer = 0;     // 动画计时器
	int idx_frame = 0; // 动画帧引索
	int interval_ms = 0;
	std::vector<IMAGE*> frame_list;
};

#endif // ANIMATION_H