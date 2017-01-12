#pragma once
#include "global.h"

//角色
class ch_c 
{
	friend class cshot_c;
	friend class shot_c;
	friend class bullet_c;
private:
	int flag;       //flag
	int cnt;        //计数变量
	int power;      //power
	int point;      //点数
	int score;      //分数
	int num;        //残机数
	int mutekicnt;  //无敌状态与计数变量
	int shot_mode;  //射击模式
	int img;        //图像
	int slow;       //是否缓慢移动
	double x, y;     //坐标
	int shot_cnt;   //射击的计数器

	int shot0num[2];
	int shot0pos_x[4];
	int shot0pos_y[4];
	int img_cshot[2];
	int img_ch[2][12];//自机图片
	int shot_sound;
	int se_flag;
public:
	void round();//循环周期调用的函数
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
	int flag, power, cnt, knd;//flag、power、计数器、种类
	double x, y, angle, spd;//坐标、角度、速度
public:
	int out_judge_cshot(int);
	void enemy_death_judge(int);
};

GLOBAL cshot_c cshot[CSHOT_MAX];