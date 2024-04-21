/*
* 开发日志：
* 1，创建项目，导入素材
* 2. 设计项目框架（设计类）
*/

#include <iostream>
#include "ChessGame.h"


int main() {
	Chess chess(13,24,24,37.5);
	Man man;
	AI ai;
	ChessGame game(&man, &ai, &chess);
	game.play();
	return 0;
}