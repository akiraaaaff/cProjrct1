#include<graphics.h>

// 检测指定棋子的玩家是否获胜
bool CheckWin(char c) {

}

// 检测当前是否出现平局
bool CheckDraw() {

}

// 绘制棋盘网格
void DrawBoard() {

}

// 绘制棋子
void DrawPiece() {

}

// 绘制提示信息
void DrawTipText() {

}

int main() {

    initgraph(600, 600);

    bool running = true;

    ExMessage msg;

    BeginBatchDraw();

    while (running)
    {
        while (peekmessage(&msg))
        {
        }

        if (CheckWin('x')) {
            MessageBox(GetHWnd(), _T("x 玩家获胜"), _T("游戏结束"), MB_OK);
            running = false;
        }
        else if (CheckWin('o')) {
            MessageBox(GetHWnd(), _T("o 玩家获胜"), _T("游戏结束"), MB_OK);
            running = false;
        }
        else if (CheckDraw()) {
            MessageBox(GetHWnd(), _T("平局！"), _T("游戏结束"), MB_OK);
            running = false;
        }

        cleardevice();

        DrawBoard();
        DrawPiece();
        DrawTipText();

        FlushBatchDraw();
    }

    EndBatchDraw();

    return 0;
}