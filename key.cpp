#include "include.h"

/*
void key_ini() {

	//��������
	configpad.down = 0;
	configpad.left = 1;
	configpad.right = 2;
	configpad.up = 3;
	configpad.bom = 4;
	configpad.shot = 5;
	configpad.slow = 11;
	configpad.start = 13;
	configpad.change = 6;
}
*/

int GetHitKeyStateAll_2() {
	char GetHitKeyStateAll_Key[256];
	GetHitKeyStateAll(GetHitKeyStateAll_Key);
	for (int i = 0; i<256; i++) 
	{
		if (GetHitKeyStateAll_Key[i] == 1)
		{
			stateKey[i]++;
		}
		else                            stateKey[i] = 0;
	}
	return 0;
}

int CheckStateKey(unsigned char Handle) {
	return stateKey[Handle];
}

/*
//�Ѳ���1�Ͳ���2�нϴ��һ����������1
void input_pad_or_key(int *p, int k) {
	*p = *p>k ? *p : k;
}

//ͬʱ����ֱ��ͼ�������ĺ���
void GetHitPadStateAll() {
	int i, PadInput, mul = 1;
	PadInput = GetJoypadInputState(DX_INPUT_PAD1);//����ֱ�������״̬
	for (i = 0; i<16; i++) {
		if (PadInput & mul)  pad.key[i]++;
		else                pad.key[i] = 0;
		mul *= 2;
	}
	input_pad_or_key(&pad.key[configpad.left], CheckStateKey(KEY_INPUT_LEFT));
	input_pad_or_key(&pad.key[configpad.up], CheckStateKey(KEY_INPUT_UP));
	input_pad_or_key(&pad.key[configpad.right], CheckStateKey(KEY_INPUT_RIGHT));
	input_pad_or_key(&pad.key[configpad.down], CheckStateKey(KEY_INPUT_DOWN));
	input_pad_or_key(&pad.key[configpad.shot], CheckStateKey(KEY_INPUT_Z));
	input_pad_or_key(&pad.key[configpad.bom], CheckStateKey(KEY_INPUT_X));
	input_pad_or_key(&pad.key[configpad.slow], CheckStateKey(KEY_INPUT_LSHIFT));
	input_pad_or_key(&pad.key[configpad.start], CheckStateKey(KEY_INPUT_ESCAPE));
	input_pad_or_key(&pad.key[configpad.change], CheckStateKey(KEY_INPUT_LCONTROL));
}

//���ش�����ֱ��İ�����Ŷ�Ӧ������״̬���������-1��ʾ�������
int CheckStatePad(unsigned int Handle) {
	if (0 <= Handle && Handle<Playpad_Key_Max) {
		return pad.key[Handle];
	}
	else {
		printfDx("��CheckStatePad�����˴���ļ�ֵ\n");
		return -1;
	}
}
*/