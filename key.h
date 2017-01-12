#pragma once
#include "global.h"
/*
//和config相关的文件
typedef struct {
	int left, up, right, down, shot, bom, slow, start, change;
}configpad_t;

typedef struct {
	int key[16];
}pad_t;

GLOBAL configpad_t configpad;

//保存手柄输入状态的变量
GLOBAL pad_t pad;
*/
//void key_ini();
int GetHitKeyStateAll_2();
int CheckStateKey(unsigned char);
//void input_pad_or_key(int*, int);
//void GetHitPadStateAll();
//int CheckStatePad(unsigned int);