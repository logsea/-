#include "include.h"

void graph_back00() {
	SetDrawArea(32, 16, 416, 464);//�軭���ܥ��ꥢ���O��
	DrawGraph(FIELD_X, back_count % 700 + FIELD_Y - 700, img_back[0], FALSE);
	DrawGraph(FIELD_X, back_count % 700 + FIELD_Y, img_back[0], FALSE);
	SetDrawArea(0, 0, 640, 480);//���ꥢ�����
}

void graph_back_main() {
	graph_back00();
}