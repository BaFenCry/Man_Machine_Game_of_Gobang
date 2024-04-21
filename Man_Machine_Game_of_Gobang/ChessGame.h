#pragma once
//添加数据成员
#include "Man.h"
#include "AI.h"

class ChessGame
{
public:
	ChessGame(Man* man, AI* ai, Chess* chess);
	void play(); //开始对局
private:
	Man* man;
	AI* ai;
	Chess* chess;
};