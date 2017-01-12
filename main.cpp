#include "include.h"

int ProcessLoop() {						//ѭ�����봦����������
	if (ProcessMessage() != 0)return -1; //���̴�������������󷵻�-1
	if (ClearDrawScreen() != 0)return -1; //���������մ��󷵻�-1

	GetHitKeyStateAll_2();//���е�ǰ��������
	return 0;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	ChangeWindowMode(TRUE);//����ģʽ
	SetWindowText("������ˮ��");
	if (DxLib_Init() == -1 || SetDrawScreen(DX_SCREEN_BACK) != 0) return -1;//��ʼ�����ﻭ�滯
	load();
	first_init();
	while (ProcessLoop() == 0) {//��ѭ��
		switch (func_state) {
		case 0:
			menu_choose();
			graph_menu();
			break;
		case 20://Replay
			replay_choose();
			graph_replay_list();
			break;

		case 30://manual��Ϸ��Ϣ
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

		case 60://EXģʽ
			extra_rank_choose();
			graph_extra_rank_select();
			break;
		case 70://��ϰģʽ�Ѷ�ѡ��
			rank_choose();
			graph_rank_select();
			break;
		case 80://������Ϸ�Ѷ�ѡ��
			rank_choose();
			graph_rank_select();
			break;
		case 90://STG��ʼǰ���еĳ�ʼ�� 
			func_state = 100;
			init();
			board.init();
			load_stage(stage_count);
			break;
		case 100://ͨ������
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
			printfDx("�����func_state\n");
			break;
		}
		if (func_state == -1)break;//�������quit������ѭ��
		ScreenFlip();//���⻭�淭ת
	}

	DxLib_End();//DX Library��ֹ����
	return 0;
}