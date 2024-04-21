#include "Chess.h"

Chess::Chess(int gradeSize, int margin_x, int margin_y, float chessSize)
{
	this->gradeSize = gradeSize;
	this->margin_x = margin_x;
	this->margin_y = margin_y;
	this->chessSize = chessSize;
	playerFlag = CHESS_BLACK;
	for (int i = 0; i < gradeSize; ++i) {
		vector<int> row;
		for (int j = 0; j < gradeSize; ++j) {
			row.push_back(0);
		}
		chessMap.push_back(row);
	}
}

void Chess::init()
{
	//创建游戏窗口
	initgraph(500, 497,1);
	//显示棋盘图片
	loadimage(0,"res/棋盘2.jpg");
	//播放开始提示音
	mciSendString("paly res.start.wav",0,0,0);
	//加载白棋和黑棋
	loadimage(&chessWhiteImg, "res/white.png", chessSize, chessSize, true);
	loadimage(&chessBlackImg, "res/black.png", chessSize, chessSize, true);
	//清理棋盘，即chessMap设置为0
	for (int i = 0; i < gradeSize; ++i) {
		for (int j = 0; j < gradeSize; ++j) {
			chessMap[i][j] = 0;
		}
	}
	bool playerFlay = true;
}

bool Chess::clickBoard(int x, int y, ChessPos* pos)
{
	ChessPos p[4];  //分别表示棋盘上四个位置：左上，右上，右下，左下
	pair<int, int> posInMap[4]; //表示四个位置的具体坐标
	p[0].row = (y - margin_y) / chessSize;
	p[0].col = (x - margin_x) / chessSize;
	posInMap[0] = make_pair(margin_x + (int)(chessSize * p[0].col), margin_y + (int)(chessSize * p[0].row));
	p[1].row = p[0].row + 1;
	p[1].col = p[0].col;
	posInMap[1] = make_pair(margin_x + (int)(chessSize * p[1].col), margin_y + (int)(chessSize * p[1].row));
	p[2].row = p[0].row + 1;
	p[2].col = p[0].col + 1;
	posInMap[2] = make_pair(margin_x + (int)(chessSize * p[2].col), margin_y + (int)(chessSize * p[2].row));
	p[3].row = p[0].row;
	p[3].col = p[0].col+1;
	posInMap[3] = make_pair(margin_x + (int)(chessSize * p[3].col), margin_y + (int)(chessSize * p[3].row));
	int offset = chessSize * 0.4;

	for (int i = 0; i < 4; ++i) {
		int len = sqrt((x - posInMap[i].first) * (x - posInMap[i].first) + (y - posInMap[i].second) * (y - posInMap[i].second));
		if (len < offset && chessMap[p[i].row][p[i].col]==0) {
			pos->row = p[i].row;
			pos->col = p[i].col;
			cout << pos->row << " " << pos->col << endl;
			return true;
		}
	}
	return false;
}

void Chess::chessDown(ChessPos* pos)
{
	int x = margin_x + pos->col * chessSize;
	int y = margin_y + pos->row * chessSize;
	IMAGE* img;
	if (!playerFlag) img = &chessWhiteImg;
	else img = &chessBlackImg;
	putimagePNG(x - chessSize / 2, y - chessSize / 2, img);
	updateGameMap(pos);
}

int Chess::getGradeSize()
{
	return gradeSize;
}

int Chess::getChessData(int row,int col)
{
	return chessMap[row][col];
}

bool Chess::checkOver()
{
	if (checkWin()) {
		Sleep(1500);
		if (playerFlag==false) {  //playerFlag表示下一步走棋的棋手，上一步走棋棋手赢得游戏
			mciSendString("play res/不错.mp3", 0, 0, 0);
			loadimage(0, "res/胜利.jpg");
		}
		else {
			mciSendString("play res/失败.mp3", 0, 0, 0);
			loadimage(0, "res/失败.jpg");
		}
		_getch(); //暂停
		return true;
	}
	return false;
}

bool Chess::checkWin()
{
	
	return false;
}

void Chess::updateGameMap(ChessPos* pos)
{
	chessMap[pos->row][pos->col] = playerFlag ? CHESS_BLACK : CHESS_WHITE;
	playerFlag = !playerFlag; //交换走棋执行权
}
