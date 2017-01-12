#include "include.h"

int ProcessLoop() {						//循环必须处理的三大过程
	if (ProcessMessage() != 0)return -1; //过程处理如果发生错误返回-1
	if (ClearDrawScreen() != 0)return -1; //如果画面清空错误返回-1

	GetHitKeyStateAll_2();//进行当前按键处理
	return 0;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	ChangeWindowMode(TRUE);//窗口模式
	SetWindowText("东方璃水城");
	if (DxLib_Init() == -1 || SetDrawScreen(DX_SCREEN_BACK) != 0) return -1;//初始化和里画面化
	load();
	first_init();
	while (ProcessLoop() == 0) {//主循环
		switch (func_state) {
		case 0:
			menu_choose();
			graph_menu();
			break;
		case 20://Replay
			replay_choose();
			graph_replay_list();
			break;

		case 30://manual游戏信息
			manual_choose();
			graph_manual();
			break;
		case 31://manual animation
			manual_menu_change();
			graph_manual_menu_change();
			break;
		case 32://manual animation
			manual_manual_change();
			graph_manual_manual_change(-1);
			break;
		case 33://manual animation
			manual_manual_change();
			graph_manual_manual_change(1);
			break;

		case 60://EX模式
			extra_rank_choose();
			graph_extra_rank_select();
			break;
		case 70://练习模式难度选择
			rank_choose();
			graph_rank_select();
			break;
		case 80://正常游戏难度选择
			rank_choose();
			graph_rank_select();
			break;
		case 90://STG开始前进行的初始化 
			func_state = 100;
			init();
			board.init();
			load_stage(stage_count);
			break;
		case 100://通常处理
			graph_back_main();
			ch.round();
			enemy_main();
			enter_main();
			bullet_main();
			board.round();
			music_main();
			open_time_count++;
			back_count++;
			break;
		default:
			printfDx("错误的func_state\n");
			break;
		}
		if (func_state == -1)break;//如果按下quit则跳出循环
		ScreenFlip();//里外画面翻转
	}

	DxLib_End();//DX Library终止处理
	return 0;
}