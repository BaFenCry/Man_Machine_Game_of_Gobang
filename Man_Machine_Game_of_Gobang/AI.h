#pragma once

#include "Chess.h"

class AI
{
public:
	void init(Chess *chess);  //AI��ʼ��
	void go();
private:
	Chess* chess;
	//map<int, int> score;
	vector<vector<int>> scoreMap;
	void calculateScore();
	ChessPos think();
};

