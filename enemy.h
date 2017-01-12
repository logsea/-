#pragma once
#include "global.h"

//using shot_bullet_func = void(shot_c::*shot_bullet[SHOT_KND_MAX])();

void enemy_main();
void enter_main();
void bullet_main();

//和敌人相关的结构体
class enemy_c 
{
	friend class enemy_order_c;
	friend class ch_c;
	friend class shot_c;
	friend class cshot_c;
private:
	bool flag;//flag
	//计数器、移动模式、方向、敌人的种类、HP最大值、掉落道具、图像
	int cnt, pattern, muki, knd, hp, hp_max, item_n[6], img, back_col;
	//坐标、速度x分量、速度y分量、速度、角度
	double x, y, vx, vy, sp, ang;
	//弹幕开始时间、弹幕的种类、弹的种类、颜色、状态、待机时间、停止时间
	int bltime, blknd, blknd2, col, state, wtime, wait;
public:
	void round();
	void move();
	void shot();
	bool ret_flag();
	void choose_pattern();
	void graph();

	void pattern0(); void pattern1(); void pattern2(); void pattern3();
	void pattern4(); void pattern5(); void pattern6(); void pattern7();
	void pattern8(); void pattern9(); void pattern10();
};

GLOBAL enemy_c enemy[ENEMY_MAX];
GLOBAL int enemy_img[3][9];

class enemy_order_c 
{
	friend class enemy_c;
	friend void load_stage(int);
private:
	//计数器、移动模式、敌人的种类
	int cnt, pattern, knd;
	//初始化坐标和移动速度
	double x, y, sp;
	//弹幕开始时间、弹幕种类、颜色、体力、子弹的种类、停止时间、物品（6个种类）
	int bltime, blknd, col, hp, blknd2, wait, item_n[6];
public:
	int ret_cnt();
	void enter();
	int num_search();//检查空的敌人编号
};

GLOBAL enemy_order_c enemy_order[ENEMY_ORDER_MAX];
GLOBAL int entered_enemy;

//和子弹相关的结构体
class bullet_c
{
	friend class shot_c;
private:
	//flag、种类、计数器、颜色、状态、保证不消失的最短时间、效果的种类
	int flag, knd, cnt, col, state, till, eff;
	//坐标、角度、速度、基本角度、瞬间记忆速度
	double x, y, angle, spd, base_angle[1], rem_spd[1];
public:
	double bulletatan2();
};

//和射击有关的结构体
class shot_c{
	using shot_bullet_func = void(shot_c::*)();
	friend class enemy_c;
private:
	//flag、种类、计数器、发射的敌人的编号
	int flag, knd, cnt; enemy_c* from;
	//基本角度、基本速度
	double base_angle[1], base_spd[1];
	bullet_c bullet[SHOT_BULLET_MAX];
	void shot_bullet_H000(); void shot_bullet_H001(); void shot_bullet_H002(); void shot_bullet_H003(); void shot_bullet_H004();
	void shot_bullet_H005(); void shot_bullet_H006(); void shot_bullet_H007(); void shot_bullet_H008(); void shot_bullet_H009();
	void shot_bullet_H010(); void shot_bullet_H011(); void shot_bullet_H012(); void shot_bullet_H013(); void shot_bullet_H014();
	void shot_bullet_H015(); void shot_bullet_H016(); void shot_bullet_H017(); void shot_bullet_H018(); void shot_bullet_H019();
	void shot_bullet_H020(); void shot_bullet_H021(); void shot_bullet_H022(); void shot_bullet_H023(); void shot_bullet_H024();
	void shot_bullet_H025(); void shot_bullet_H026(); void shot_bullet_H027(); void shot_bullet_H028(); void shot_bullet_H029();
public:
	
	/*shot_bullet_func shot_bullet[SHOT_KND_MAX];
	shot_c()
	{
		shot_bullet[0] = &shot_c::shot_bullet_H000; shot_bullet[1] = &shot_c::shot_bullet_H001; shot_bullet[2] = &shot_c::shot_bullet_H002; shot_bullet[3] = &shot_c::shot_bullet_H003; shot_bullet[4] = &shot_c::shot_bullet_H004;
		shot_bullet[5] = &shot_c::shot_bullet_H005; shot_bullet[6] = &shot_c::shot_bullet_H006; shot_bullet[7] = &shot_c::shot_bullet_H007; shot_bullet[8] = &shot_c::shot_bullet_H008; shot_bullet[9] = &shot_c::shot_bullet_H009;
		shot_bullet[10] = &shot_c::shot_bullet_H010; shot_bullet[11] = &shot_c::shot_bullet_H011; shot_bullet[12] = &shot_c::shot_bullet_H012; shot_bullet[13] = &shot_c::shot_bullet_H013; shot_bullet[14] = &shot_c::shot_bullet_H014;
		shot_bullet[15] = &shot_c::shot_bullet_H015; shot_bullet[16] = &shot_c::shot_bullet_H016; shot_bullet[17] = &shot_c::shot_bullet_H017; shot_bullet[18] = &shot_c::shot_bullet_H018; shot_bullet[19] = &shot_c::shot_bullet_H019;
		shot_bullet[20] = &shot_c::shot_bullet_H020; shot_bullet[21] = &shot_c::shot_bullet_H021; shot_bullet[22] = &shot_c::shot_bullet_H022; shot_bullet[23] = &shot_c::shot_bullet_H023; shot_bullet[24] = &shot_c::shot_bullet_H024;
		shot_bullet[25] = &shot_c::shot_bullet_H025; shot_bullet[26] = &shot_c::shot_bullet_H026; shot_bullet[27] = &shot_c::shot_bullet_H027; shot_bullet[28] = &shot_c::shot_bullet_H028; shot_bullet[29] = &shot_c::shot_bullet_H029;
	}*/
	void choose_knd();
	int shot_search();
	void shot_calc();
	void shot_main();
	void graph();
	int ret_flag();
	int ret_knd();
	enemy_c* ret_from();
	void kill_shot();
	double shotatan2();
	void cnt_inc();
};

GLOBAL shot_c shot_obj[SHOT_MAX];
GLOBAL int enemy_shot_sound;
GLOBAL int enemy_shot_sound_flag;
GLOBAL int enemy_hit_sound;
GLOBAL int enemy_hit_sound_flag;
GLOBAL int enemy_death_sound;
GLOBAL int enemy_death_sound_flag;
GLOBAL int img_bullet[10][10]; //子弹的图像