#ifndef ATLAS_H
#define ATLAS_H

#include<graphics.h>
#include <vector>

class Atlas
{
public:
	Atlas(LPCTSTR path, int num) {

		TCHAR path_file[256];
		for (size_t i = 0; i < num; i++)
		{
			_stprintf_s(path_file, path, i);

			IMAGE* frame = new IMAGE();
			loadimage(frame, path_file);
			frame_list.push_back(frame);
		}
	}

	~Atlas() {
		for (size_t i = 0; i < frame_list.size(); i++) {
			delete frame_list[i];
		}
	}

public:
	std::vector<IMAGE*> frame_list;
};

// 这里用 extern 只做声明
extern Atlas* atlas_player_left;
extern Atlas* atlas_player_right;
extern Atlas* atlas_enemy_left;
extern Atlas* atlas_enemy_right;

#endif // ATLAS_H
