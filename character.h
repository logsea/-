#pragma once
#include "global.h"

//��ɫ
class ch_c 
{
	friend class cshot_c;
	friend class shot_c;
	friend class bullet_c;
private:
	int flag;       //flag
	int cnt;        //��������
	int power;      //power
	int point;      //����
	int score;      //����
	int num;        //�л���
	int mutekicnt;  //�޵�״̬���������
	int shot_mode;  //���ģʽ
	int img;        //ͼ��
	int slow;       //�Ƿ����ƶ�
	double x, y;     //����
	int shot_cnt;   //����ļ�����

	int shot0num[2];
	int shot0pos_x[4];
	int shot0pos_y[4];
	int img_cshot[2];
	int img_ch[2][12];//�Ի�ͼƬ
	int shot_sound;
	int se_flag;
public:
	void round();//ѭ�����ڵ��õĺ���
	void init();
	void calc_ch();
	void move();
	void shot_main();
	void calc_shot();
	void enter_shot();
	void ch0_shot_pattern();
	void ch1_shot_pattern();
	int search_shot();
	void graph_main();
	void graph_shot();
	void graph_ch();
	void music_play();
	int ret_power();
	
	void cshot_hit_main();
};

GLOBAL ch_c ch;

class cshot_c
{
	friend class ch_c;
private:
	int flag, power, cnt, knd;//flag��power��������������
	double x, y, angle, spd;//���ꡢ�Ƕȡ��ٶ�
public:
	int out_judge_cshot(int);
	void enemy_death_judge(int);
};

GLOBAL cshot_c cshot[CSHOT_MAX];