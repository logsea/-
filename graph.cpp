#include "include.h"

void graph_menu()
{
	DrawGraph(0, 0, image_board[0], FALSE);
	DrawGraph(0, 0, image_board[1], TRUE);
	DrawGraph(460, 420, image_board[2], TRUE);
	for (int i = 0; i < 7; i++)
	{
		if (choose != i)
			DrawGraph(20, 204 + 32 * i, img_menu[0][i], TRUE);
		else
			DrawGraph(20, 204 + 32 * i, img_menu[1][i], TRUE);
	}
}

void graph_rank_select()
{
	DrawGraph(0, 0, image_board[0], FALSE);
	DrawGraph(0, 0, image_board[3], TRUE);
	for (int i = 0; i < 4; i++)
	{
		DrawGraph(240 + 160 * (i - choose), 200 + 75 * (i - choose), rank_menu[i], TRUE);
	}
}

void graph_extra_rank_select()
{
	DrawGraph(0, 0, image_board[0], FALSE);
	DrawGraph(0, 0, image_board[3], TRUE);
	DrawGraph(240, 200, rank_menu[4], TRUE);
}

void graph_replay_list()
{
	DrawGraph(0, 0, image_board[0], FALSE);
	DrawGraph(200, 0, image_board[4], TRUE);
	DrawGraph(20, 60, image_board[5], TRUE);
	int debug = ChangeFont("M+ 1mn light");
	int color1 = GetColor(255, 255, 255);
	int color2 = GetColor(0, 0, 0);
	for (int i = 0; i < 20; i++)
	{
		if (choose == i)
			DrawFormatString(10, 100 + 18 * i, color2, "No.%2d  --------  --/--/--  --:--  -------  -------  ---  ---\\%", i+1);
		else
			DrawFormatString(10, 100 + 18 * i, color1, "No.%2d  --------  --/--/--  --:--  -------  -------  ---  ---\\%", i+1);
		DrawFormatString(0, 460, color1, "Debug = %d", debug);
	}
}

void graph_manual()
{
	DrawGraph(0, 0, image_board[0], FALSE);
	if (choose_t == 0)
	{
		for (int i = 0; i < 7; i++)
		{
			if (choose == i)
			{
				DrawGraph(100, 50 + 40 * i, manual_menu[(open_time_count / 8) % 6][i],TRUE);
			}
			else
			{
				DrawGraph(100, 50 + 40 * i, manual_menu[0][i], TRUE);
			}
		}
	}
	else
	{
		DrawGraph(100, 50, manual_text[choose_t],TRUE);
	}
}

void graph_manual_menu_change()
{
	DrawGraph(0, 0, image_board[0], FALSE);
	if (open_time_count == 32)
	{
		func_state = 30;
		choose_t = choose + 2;
		return;
	}
	else
	{
		for (int i = 0; i < 7; i++)
		{
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255-7*open_time_count);
			DrawGraph(100, 50 + 40 * i+4*open_time_count, manual_menu[0][i], TRUE);
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, 7 * open_time_count);
			DrawGraph(100 + (32 - open_time_count) * 4, 50, manual_text[choose+2], TRUE);
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
		}
	}
}

void graph_manual_manual_change(int chg)
{
	DrawGraph(0, 0, image_board[0], FALSE);
	int bef = choose_t;
	int aft = choose_t + chg;
	if (aft < 2)aft = 8;
	if (aft > 8)aft = 2;
	if (open_time_count == 32)
	{
		func_state = 30;
		choose_t = aft;
		return;
	}
	else
	{
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255 - 7 * open_time_count);
		DrawGraph(100, 50 - (open_time_count) * 4 * chg, manual_text[bef], TRUE);
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 7 * open_time_count);
		DrawGraph(100, 50 + (32 - open_time_count) * 4 * chg, manual_text[aft], TRUE);
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
	}
}