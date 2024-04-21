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
//����λ��
struct ChessPos {
	int row, col;
	ChessPos(int row_=0,int col_=0):row(row_),col(col_){}
};

enum {
	CHESS_WHITE = -1, //����
	CHESS_BLACK = 1   //����
};

class Chess
{
public:
	//���캯��
	Chess(int gradeSize, int margin_x, int margin_y, float chessSize);
	void init(); //���̳�ʼ����
	int getGradeSize(); //��ȡ���̴�С��13*13,15*15��,19*19��
	bool clickBoard(int x, int y, ChessPos* pos); //�жϵ���Ƿ���Ч
	void chessDown(ChessPos* pos); //���ӹ��ܣ�����λ�ú����ࣩ
	int getChessData(int row,int col);  //��ȡ����ĳλ�õ���Ϣ
	bool checkOver();//�������Ƿ����
	bool checkWin();  //���ʱ��ʤ��
private:
	IMAGE chessBlackImg;  //��������ͼƬ
	IMAGE chessWhiteImg;  //��������ͼƬ
	int margin_x;//�����󲿾�ͼƬ�󲿳���
	int margin_y;//���̶�����ͼƬ��������
	int gradeSize; //���̴�С��13��15,17,19��
	float chessSize;//���Ӵ�С=���̷����С
	vector<vector<int>> chessMap; //��ִ洢��0��ʾ�հף�-1��ʾ���ӣ�1��ʾ����

	//��ʾ���ڸ�˭���ӣ�Man or AI��
	bool playerFlag; //true:�����ߣ�false��������
	//������Ϸ����
	void updateGameMap(ChessPos* pos);
	ChessPos lastPos;

};

