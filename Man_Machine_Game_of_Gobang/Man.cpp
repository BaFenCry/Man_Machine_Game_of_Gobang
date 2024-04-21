#include "Man.h"

void Man::init(Chess* chess)
{
	this->chess = chess;
}

void Man::go()
{
	MOUSEMSG msg;
	ChessPos pos(0,0);
	while (1) {
		msg = GetMouseMsg();; //获取鼠标信息
		if (msg.uMsg == WM_LBUTTONDOWN && chess->clickBoard(msg.x,msg.y,&pos)) {
			break;
		}
	}
	chess->chessDown(&pos);
}
