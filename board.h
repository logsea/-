#pragma once
#include "global.h"

class bd
{
private:
	int img[4];//0-3:board
	int lifespell_img[6];
	long long highest_point, point;
	int life, spell_card;
	int life_piece, spell_piece;
	int max_point,point_energe;
	int graze_num, graze_energe;
	int rank;
public:
	void init();
	void round();
	void graph();
};

GLOBAL bd board;