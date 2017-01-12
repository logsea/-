#include "include.h"

void load_stage(int stg)
{
	char fname[32];
	char readyname[6][32] = { "dat/csv/storyH0.csv","","","","","" };
	strcpy_s(fname, readyname[stg]);
	int n, num, i, fp;
	int input[64];
	char inputc[64];

	fp = FileRead_open(fname);//�����ļ�
	if (fp == NULL) {
		printfDx("read error\n");
		return;
	}
	for (i = 0; i<2; i++)//�����ʼ������
		while (FileRead_getc(fp) != '\n');

	n = 0, num = 0;
	while (1) {
		for (i = 0; i<64; i++) {
			inputc[i] = input[i] = FileRead_getc(fp);//����1���ַ� 
			if (inputc[i] == '/') {//�����б��
				while (FileRead_getc(fp) != '\n');//ѭ��һֱ������
				i = -1;//���ü�����
				continue;
			}
			if (input[i] == ',' || input[i] == '\n') {//����Ƕ��Ż��߻���
				inputc[i] = '\0';//�����˵�����������Ϊ�ַ���
				break;
			}
			if (input[i] == EOF) {//��������ļ�β
				goto EXFILE;//��ֹ
			}
		}
		switch (num) {
		case 0: enemy_order[n].cnt = atoi(inputc); break;
		case 1: enemy_order[n].pattern = atoi(inputc); break;
		case 2: enemy_order[n].knd = atoi(inputc); break;
		case 3: enemy_order[n].x = atof(inputc); break;
		case 4: enemy_order[n].y = atof(inputc); break;
		case 5: enemy_order[n].sp = atof(inputc); break;
		case 6: enemy_order[n].bltime = atoi(inputc); break;
		case 7: enemy_order[n].blknd = atoi(inputc); break;
		case 8: enemy_order[n].col = atoi(inputc); break;
		case 9: enemy_order[n].hp = atoi(inputc); break;
		case 10:enemy_order[n].blknd2 = atoi(inputc); break;
		case 11:enemy_order[n].wait = atoi(inputc); break;
		case 12:enemy_order[n].item_n[0] = atoi(inputc); break;
		case 13:enemy_order[n].item_n[1] = atoi(inputc); break;
		case 14:enemy_order[n].item_n[2] = atoi(inputc); break;
		case 15:enemy_order[n].item_n[3] = atoi(inputc); break;
		case 16:enemy_order[n].item_n[4] = atoi(inputc); break;
		case 17:enemy_order[n].item_n[5] = atoi(inputc); break;
		}
		num++;
		if (num == 18) {
			num = 0;
			n++;
		}
	}
EXFILE:
	FileRead_close(fp);
}