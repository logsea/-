#pragma once
#include "global.h"
/*
//��config��ص��ļ�
typedef struct {
	int left, up, right, down, shot, bom, slow, start, change;
}configpad_t;

typedef struct {
	int key[16];
}pad_t;

GLOBAL configpad_t configpad;

//�����ֱ�����״̬�ı���
GLOBAL pad_t pad;
*/
//void key_ini();
int GetHitKeyStateAll_2();
int CheckStateKey(unsigned char);
//void input_pad_or_key(int*, int);
//void GetHitPadStateAll();
//int CheckStatePad(unsigned int);