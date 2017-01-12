#include "include.h"

void first_init()
{
	/*
	configpad.down = 0;
	configpad.left = 1;
	configpad.right = 2;
	configpad.up = 3;
	configpad.bom = 4;
	configpad.shot = 5;
	configpad.slow = 11;
	configpad.start = 13;
	configpad.change = 6;
	*/

	func_state = 0;
	choose = 0;
	open_time_count = 0;
	choose_t = 0;
}

//新游戏的初始化
void init() {
	ch.init();
	open_time_count = 0;
	stage_count = 0;
	entered_enemy = 0;
}