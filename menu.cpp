#include "include.h"

void menu_choose() {
	if (stateKey[KEY_INPUT_UP] % 30 == 1) {
		choose--;
		if (choose < 0)
			choose = 6;
	}
	if (stateKey[KEY_INPUT_DOWN] % 30 == 1) {
		choose++;
		if (choose > 6)
			choose = 0;
	}
	if (stateKey[KEY_INPUT_Z] % 30 == 1)
		menu_shot();
	if (stateKey[KEY_INPUT_ESCAPE] % 30 == 1 || stateKey[KEY_INPUT_X] % 30 == 1)
		choose = 6;
}

void menu_shot()
{
	switch (choose)
	{
	case 0:func_state = 80; open_time_count = 0; choose = 1; break;
	case 1:func_state = 60; open_time_count = 0; choose = 1; break;
	case 2:func_state = 70; open_time_count = 0; choose = 1; break;
	case 3:func_state = 20; open_time_count = 0; choose = 0; replay_choose_page = 0; break;
	case 5:func_state = 30; open_time_count = 0; choose = 0; choose_t = 0; break;
	case 6:func_state = -1; break;
	default:break;
	}
}

void rank_choose()
{
	if (stateKey[KEY_INPUT_UP] % 30 == 1 || stateKey[KEY_INPUT_LEFT] % 30 == 1) {
		choose--;
		if (choose < 0)
			choose = 3;
	}
	if (stateKey[KEY_INPUT_DOWN] % 30 == 1 || stateKey[KEY_INPUT_RIGHT] % 30 == 1) {
		choose++;
		if (choose > 3)
			choose = 0;
	}
	if (stateKey[KEY_INPUT_Z] == 1) {
		func_state = 90;
		open_time_count = 0;
		return;
	}
	if (stateKey[KEY_INPUT_ESCAPE] % 30 == 1 || stateKey[KEY_INPUT_X] % 30 == 1)
	{
		if (func_state == 80)
			choose = 0;
		else if (func_state == 60)
			choose = 2;
		func_state = 0;
		open_time_count = 0;
	}
}

void extra_rank_choose()
{
	if (stateKey[KEY_INPUT_ESCAPE] % 30 == 1 || stateKey[KEY_INPUT_X] % 30 == 1)
	{
		func_state = 0;
		choose = 1;
		open_time_count = 0;
	}
}

void replay_choose()
{
	if (stateKey[KEY_INPUT_UP] % 30 == 1) {
		choose--;
		if (choose < 0)
			choose = 19;
	}
	if (stateKey[KEY_INPUT_DOWN] % 30 == 1) {
		choose++;
		if (choose > 19)
			choose = 0;
	}
	if (stateKey[KEY_INPUT_ESCAPE] % 30 == 1 || stateKey[KEY_INPUT_X] % 30 == 1)
	{
		func_state = 0;
		choose = 3;
		open_time_count = 0;
	}
}

void manual_choose()
{
	open_time_count++;
	if (choose_t == 0)
	{
		if (stateKey[KEY_INPUT_UP] % 30 == 1) {
			choose--;
			if (choose < 0)
				choose = 6;
		}
		if (stateKey[KEY_INPUT_DOWN] % 30 == 1) {
			choose++;
			if (choose > 6)
				choose = 0;
		}
		if (stateKey[KEY_INPUT_Z] % 30 == 1)
		{
			func_state = 31;
			open_time_count = 0;
		}
		if (stateKey[KEY_INPUT_ESCAPE] % 30 == 1 || stateKey[KEY_INPUT_X] % 30 == 1)
		{
			choose = 5;
			func_state = 0;
		}
	}
	else
	{
		if (stateKey[KEY_INPUT_UP] % 30 == 1) {
			func_state = 32;
			open_time_count = 0;
		}
		if (stateKey[KEY_INPUT_DOWN] % 30 == 1) {
			func_state = 33;
			open_time_count = 0;
		}
		if (stateKey[KEY_INPUT_ESCAPE] % 30 == 1 || stateKey[KEY_INPUT_X] % 30 == 1)
		{
			choose_t = 0;
		}
	}
}