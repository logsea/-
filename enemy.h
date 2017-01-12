#pragma once
#include "global.h"

//using shot_bullet_func = void(shot_c::*shot_bullet[SHOT_KND_MAX])();

void enemy_main();
void enter_main();
void bullet_main();

//�͵�����صĽṹ��
class enemy_c 
{
	friend class enemy_order_c;
	friend class ch_c;
	friend class shot_c;
	friend class cshot_c;
private:
	bool flag;//flag
	//���������ƶ�ģʽ�����򡢵��˵����ࡢHP���ֵ��������ߡ�ͼ��
	int cnt, pattern, muki, knd, hp, hp_max, item_n[6], img, back_col;
	//���ꡢ�ٶ�x�������ٶ�y�������ٶȡ��Ƕ�
	double x, y, vx, vy, sp, ang;
	//��Ļ��ʼʱ�䡢��Ļ�����ࡢ�������ࡢ��ɫ��״̬������ʱ�䡢ֹͣʱ��
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
	//���������ƶ�ģʽ�����˵�����
	int cnt, pattern, knd;
	//��ʼ��������ƶ��ٶ�
	double x, y, sp;
	//��Ļ��ʼʱ�䡢��Ļ���ࡢ��ɫ���������ӵ������ࡢֹͣʱ�䡢��Ʒ��6�����ࣩ
	int bltime, blknd, col, hp, blknd2, wait, item_n[6];
public:
	int ret_cnt();
	void enter();
	int num_search();//���յĵ��˱��
};

GLOBAL enemy_order_c enemy_order[ENEMY_ORDER_MAX];
GLOBAL int entered_enemy;

//���ӵ���صĽṹ��
class bullet_c
{
	friend class shot_c;
private:
	//flag�����ࡢ����������ɫ��״̬����֤����ʧ�����ʱ�䡢Ч��������
	int flag, knd, cnt, col, state, till, eff;
	//���ꡢ�Ƕȡ��ٶȡ������Ƕȡ�˲������ٶ�
	double x, y, angle, spd, base_angle[1], rem_spd[1];
public:
	double bulletatan2();
};

//������йصĽṹ��
class shot_c{
	using shot_bullet_func = void(shot_c::*)();
	friend class enemy_c;
private:
	//flag�����ࡢ������������ĵ��˵ı��
	int flag, knd, cnt; enemy_c* from;
	//�����Ƕȡ������ٶ�
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
GLOBAL int img_bullet[10][10]; //�ӵ���ͼ��