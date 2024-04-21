#include "ChessGame.h"


ChessGame::ChessGame(Man* man, AI* ai, Chess* chess)
{
	this->man = man;
	this->ai = ai;
	this->chess = chess;
	man->init(chess);
	ai->init(chess);
}

//开始游戏 
void ChessGame::play()
{

	chess->init();
	while (1) {
		man->go();//人先走棋
		if (chess->checkOver(                         )) { //检查游戏是否结束
			chess->init();
			continue;
		}
		ai->go(); //ai走棋
		if (chess->checkOver()) {
			chess->init();
			continue;
		}
	}
}
