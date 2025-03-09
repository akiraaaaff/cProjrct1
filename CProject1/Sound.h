#ifndef SOUND_H
#define SOUND_H

# pragma comment(lib,"Winmm.lib")

inline void loadsound() {
	mciSendString(_T("open mus/bgm.mp3 alias bgm"), NULL, 0, NULL);
	mciSendString(_T("open mus/hit.wav alias hit"), NULL, 0, NULL);
}

#endif // SOUND_H
