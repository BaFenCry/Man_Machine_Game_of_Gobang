/*
* ������־��
* 1��������Ŀ�������ز�
* 2. �����Ŀ��ܣ�����ࣩ
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