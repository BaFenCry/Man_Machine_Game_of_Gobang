#pragma once

#include <graphics.h>
#include <iostream>
#include <vector>
#include <math.h>
#include "tools.h"
#include <conio.h>
#include <mmsystem.h>
#pragma comment(lib,"winmm.lib")

using namespace std;
//落子位置
struct ChessPos {
	int row, col;
	ChessPos(int row_=0,int col_=0):row(row_),col(col_){}
};

enum {
	CHESS_WHITE = -1, //白棋
	CHESS_BLACK = 1   //黑棋
};

class Chess
{
public:
	//构造函数
	Chess(int gradeSize, int margin_x, int margin_y, float chessSize);
	void init(); //棋盘初始化，
	int getGradeSize(); //获取棋盘大小（13*13,15*15，,19*19）
	bool clickBoard(int x, int y, ChessPos* pos); //判断点击是否有效
	void chessDown(ChessPos* pos); //落子功能（落子位置和种类）
	int getChessData(int row,int col);  //获取棋盘某位置的信息
	bool checkOver();//检查棋局是否结束
	bool checkWin();  //检查时候胜利
private:
	IMAGE chessBlackImg;  //黑棋棋子图片
	IMAGE chessWhiteImg;  //白棋棋子图片
	int margin_x;//棋盘左部距图片左部长度
	int margin_y;//棋盘顶部距图片顶部长度
	int gradeSize; //棋盘大小（13，15,17,19）
	float chessSize;//棋子大小=棋盘方格大小
	vector<vector<int>> chessMap; //棋局存储，0表示空白，-1表示白子，1表示黑子

	//表示现在该谁落子（Man or AI）
	bool playerFlag; //true:黑子走，false：白子走
	//更新游戏数据
	void updateGameMap(ChessPos* pos);
	ChessPos lastPos;

};

