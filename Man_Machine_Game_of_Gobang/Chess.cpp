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
	//������Ϸ����
	initgraph(500, 497,1);
	//��ʾ����ͼƬ
	loadimage(0,"res/����2.jpg");
	//���ſ�ʼ��ʾ��
	mciSendString("paly res.start.wav",0,0,0);
	//���ذ���ͺ���
	loadimage(&chessWhiteImg, "res/white.png", chessSize, chessSize, true);
	loadimage(&chessBlackImg, "res/black.png", chessSize, chessSize, true);
	//�������̣���chessMap����Ϊ0
	for (int i = 0; i < gradeSize; ++i) {
		for (int j = 0; j < gradeSize; ++j) {
			chessMap[i][j] = 0;
		}
	}
	bool playerFlay = true;
}

bool Chess::clickBoard(int x, int y, ChessPos* pos)
{
	ChessPos p[4];  //�ֱ��ʾ�������ĸ�λ�ã����ϣ����ϣ����£�����
	pair<int, int> posInMap[4]; //��ʾ�ĸ�λ�õľ�������
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
			//cout << pos->row << " " << pos->col << endl;
			return true;
		}
	}
	return false;
}

void Chess::chessDown(ChessPos* pos)
{
	mciSendString("play res/down7.wav", 0, 0, 0);
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
		if (playerFlag==false) {  //playerFlag��ʾ��һ����������֣���һ����������Ӯ����Ϸ
			mciSendString("play res/����.mp3", 0, 0, 0);
			loadimage(0, "res/ʤ��.jpg");
		}
		else {
			mciSendString("play res/ʧ��.mp3", 0, 0, 0);
			loadimage(0, "res/ʧ��.jpg");
		}
		_getch(); //��ͣ
		return true;
	}
	return false;
}

bool Chess::checkWin()
{
	int row = lastPos.row;
	int col = lastPos.col;

	for (int i = 0; i < 5; i++)
	{
		// ˮƽ����
		if (col - i >= 0 &&
			col - i + 4 < gradeSize &&
			chessMap[row][col - i] == chessMap[row][col - i + 1] &&
			chessMap[row][col - i] == chessMap[row][col - i + 2] &&
			chessMap[row][col - i] == chessMap[row][col - i + 3] &&
			chessMap[row][col - i] == chessMap[row][col - i + 4])
			return true;
	}

	// ��ֱ����
	for (int i = 0; i < 5; i++)
	{
		if (row - i >= 0 &&
			row - i + 4 < gradeSize &&
			chessMap[row - i][col] == chessMap[row - i + 1][col] &&
			chessMap[row - i][col] == chessMap[row - i + 2][col] &&
			chessMap[row - i][col] == chessMap[row - i + 3][col] &&
			chessMap[row - i][col] == chessMap[row - i + 4][col])
			return true;
	}

	// ���µ�����
	for (int i = 0; i < 5; i++)
	{
		if (row + i < gradeSize &&
			row + i - 4 >= 0 &&
			col - i >= 0 &&
			col - i + 4 < gradeSize &&
			chessMap[row + i][col - i] == chessMap[row + i - 1][col - i + 1] &&
			chessMap[row + i][col - i] == chessMap[row + i - 2][col - i + 2] &&
			chessMap[row + i][col - i] == chessMap[row + i - 3][col - i + 3] &&
			chessMap[row + i][col - i] == chessMap[row + i - 4][col - i + 4])
			return true;
	}

	// ���ϵ�����
	for (int i = 0; i < 5; i++)
	{
		if (row - i >= 0 &&
			row - i + 4 < gradeSize &&
			col - i >= 0 &&
			col - i + 4 < gradeSize &&
			chessMap[row - i][col - i] == chessMap[row - i + 1][col - i + 1] &&
			chessMap[row - i][col - i] == chessMap[row - i + 2][col - i + 2] &&
			chessMap[row - i][col - i] == chessMap[row - i + 3][col - i + 3] &&
			chessMap[row - i][col - i] == chessMap[row - i + 4][col - i + 4])
			return true;
	}

	return false;
}

void Chess::updateGameMap(ChessPos* pos)
{
	lastPos = *pos;
	chessMap[pos->row][pos->col] = playerFlag ? CHESS_BLACK : CHESS_WHITE;
	playerFlag = !playerFlag; //��������ִ��Ȩ
}
