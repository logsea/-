#include "include.h"

void bd::init()
{
	highest_point = 0; point = 0;
	life = 3; spell_card = 3;
	life_piece = 0; spell_piece = 0;
	point_energe = 0;
	graze_num = 0; graze_energe = 0;
	rank = choose;
	switch (rank)
	{
	case 0: max_point = 5000; break;
	case 1: max_point = 10000; break;
	case 2: max_point = 20000; break;
	case 3: max_point = 20000; break;
	default:max_point = 0; break;
	}
	img[0] = LoadGraph("dat/img/board/10.png");
	img[1] = LoadGraph("dat/img/board/11.png");
	img[2] = LoadGraph("dat/img/board/12.png");
	img[3] = LoadGraph("dat/img/board/20.png");
	LoadDivGraph("dat/img/item/lifespell.png", 6, 2, 3, 15, 17, lifespell_img);
}

void bd::graph()
{
	DrawGraph(0, 0, img[0], FALSE);
	DrawGraph(0, 16, img[1], FALSE);
	DrawGraph(0, 464, img[2], FALSE);
	DrawGraph(416, 0, img[3], FALSE);

	//point
	int printpoint = point;
	for (int i = 0; i < 12; i++)
	{
		int outnum = printpoint % 10;
		printpoint /= 10;
		DrawGraph(597 - 9 * i, 77, ascii[16 + outnum], TRUE);
	}
	printpoint = highest_point;
	for (int i = 0; i < 12; i++)
	{
		int outnum = printpoint % 10;
		printpoint /= 10;
		DrawGraph(597 - 9 * i, 54, ascii[16 + outnum], TRUE);
	}

	//life_spell
	for (int i = 0; i < life; i++)
		DrawGraph(498 + 12 * i, 109, lifespell_img[4], TRUE);
	if (life_piece != 0)
		DrawGraph(498 + 12 * life, 109, lifespell_img[(life_piece - 1) * 2], TRUE);
	for (int i = 0; i < spell_card; i++)
		DrawGraph(498 + 12 * i, 129, lifespell_img[5], TRUE);
	if (spell_piece != 0)
		DrawGraph(498 + 12 * life, 129, lifespell_img[((int)((((double)spell_piece / 5.0) * 2))) * 2 + 1], TRUE);

	//power_graze_perpoint
	DrawGraph(498 + 9 * 8, 170, ascii[16 + 0], TRUE);
	DrawGraph(498 + 9 * 7, 170, ascii[16 + 0], TRUE);
	DrawGraph(498 + 9 * 6, 170, ascii[16 - 2], TRUE);
	DrawGraph(498 + 9 * 5, 170, ascii[16 + 5], TRUE);
	DrawGraph(498 + 9 * 4, 170, ascii[16 - 1], TRUE);
	int printpower = ch.ret_power();
	for (int i = 0; i < 4; i++)
	{
		if(i==2)
			DrawGraph(525 - 9 * i, 170, ascii[16 - 2], TRUE);
		else
		{
			int outnum = printpower % 10;
			printpower /= 10;
			DrawGraph(525 - 9 * i, 170, ascii[16 + outnum], TRUE);
		}
	}
	int printgraze = graze_num;
	for (int i = 0; i < 6; i++)
	{
		int outnum = printgraze % 10;
		printgraze /= 10;
		DrawGraph(570 - 9 * i, 192, ascii[16 + outnum], TRUE);
		if (printgraze == 0)break;
	}
	printpoint = max_point;
	for (int i = 0; i < 6; i++)
	{
		int outnum = printpoint % 10;
		printpoint /= 10;
		DrawGraph(570 - 9 * i, 219, ascii[16 + outnum], TRUE);
		if (printpoint == 0)break;
	}
}

void bd::round()
{
	graph();
}