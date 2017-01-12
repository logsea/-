#include "include.h"

double brang(double ang) {
	return (-ang + ang * 2 * GetRand(10000) / 10000.0);
}

void shot_c::choose_knd()
{
	switch (from->knd)
	{
	case 0:shot_bullet_H000(); break;
	case 1:shot_bullet_H001(); break;
	case 2:shot_bullet_H002(); break;
	case 3:shot_bullet_H003(); break;
	default:break;
	}
}

//只发射一发，向着自机直线发射
void shot_c::shot_bullet_H000() {
	int k;
	if (cnt == 0) {
		if (flag != 2 && (k = shot_search()) != -1) {
			bullet[k].knd = from->blknd2;
			bullet[k].angle = shotatan2();
			bullet[k].flag = 1;
			bullet[k].x = from->x;
			bullet[k].y = from->y;
			bullet[k].col = from->col;
			bullet[k].cnt = 0;
			bullet[k].spd = 3;
			enemy_shot_sound_flag = 1;
		}
	}
}

//每秒发射30发子弹，自机依存，90度张角，每5发有一发冲着自机去
void shot_c::shot_bullet_H001() {
	int k;
	int t = cnt;
	if (t >= 0 && t <= 120 && t % 2 == 0) {
		if (flag != 2 && (k = shot_search()) != -1) {
			bullet[k].knd = from->blknd2;
			if (t % 10 == 0)
				bullet[k].angle = shotatan2();
			else
				bullet[k].angle = shotatan2() + brang(PI/4);
			bullet[k].flag = 1;
			bullet[k].x = from->x;
			bullet[k].y = from->y;
			bullet[k].col = from->col;
			bullet[k].cnt = 0;
			bullet[k].spd = 3;
			enemy_shot_sound_flag = 1;
		}
	}
}

void shot_c::shot_bullet_H002() {
	int k;
	int t = cnt;
	if (t >= 0 && t <= 120 && t % 2 == 0) {
		if (flag != 2 && (k = shot_search()) != -1) {
			bullet[k].knd = from->blknd2;
			bullet[k].angle = PI*(1.0-t/120.0);
			bullet[k].flag = 1;
			bullet[k].x = from->x;
			bullet[k].y = from->y;
			bullet[k].col = from->col;
			bullet[k].cnt = 0;
			bullet[k].spd = 3;
			bullet[k].state = t;
			enemy_shot_sound_flag = 1;
		}
	}
	for (int i = 0; i < SHOT_BULLET_MAX; i++)
	{
		int t = bullet[i].cnt;
		int y = bullet[i].y;
		int state = bullet[i].state;
		if (bullet[i].flag > 0)
		{
			if (t < 180 - state && y>=150.0)
				bullet[i].spd = 0;
			if (t == 180 - state)
			{
				bullet[i].angle = bullet[i].bulletatan2();
				bullet[i].spd = 5;
			}
		}
	}
}

void shot_c::shot_bullet_H003() {
	int k;
	int t = cnt;
	if (t >= 0 && t <= 120) {
		if (flag != 2 && (k = shot_search()) != -1) {
			bullet[k].knd = from->blknd2;
			bullet[k].angle = 0;
			bullet[k].flag = 1;
			bullet[k].x = from->x + 30 * sin(2*PI / 30 * t);
			bullet[k].y = from->y + 30 * cos(2*PI / 30 * t);
			bullet[k].col = from->col;
			bullet[k].cnt = 0;
			bullet[k].spd = 0;
			bullet[k].state = t;
			enemy_shot_sound_flag = 1;
		}
	}
	double ang = brang(PI);
	for (int i = 0; i < SHOT_BULLET_MAX; i++)
	{
		int t = bullet[i].cnt;
		int y = bullet[i].y, x = bullet[i].x;
		int state = bullet[i].state;
		if (bullet[i].flag > 0)
		{
			if (t == 30 - state%30)
			{
				bullet[i].angle = ang;
				bullet[i].spd = 3;
			}
			if (x < 5.0 && state < 10000)
			{
				bullet[i].angle = PI- bullet[i].angle;
				bullet[i].x = 5.0001;
				//state += 10001;
			}
			if (x>416.0 && state < 10000)
			{
				bullet[i].angle = PI - bullet[i].angle;
				bullet[i].x = 415.9999;
				//state += 10001;
			}
			if (y < 5.0 && state < 10000)
			{
				bullet[i].angle = -bullet[i].angle;
				bullet[i].y = 5.0001;
				//state += 10001;
			}
		}
	}
}

void shot_c::shot_bullet_H004() {}
void shot_c::shot_bullet_H005() {}
void shot_c::shot_bullet_H006() {}
void shot_c::shot_bullet_H007() {}
void shot_c::shot_bullet_H008() {}
void shot_c::shot_bullet_H009() {}
void shot_c::shot_bullet_H010() {}
void shot_c::shot_bullet_H011() {}
void shot_c::shot_bullet_H012() {}
void shot_c::shot_bullet_H013() {}
void shot_c::shot_bullet_H014() {}
void shot_c::shot_bullet_H015() {}
void shot_c::shot_bullet_H016() {}
void shot_c::shot_bullet_H017() {}
void shot_c::shot_bullet_H018() {}
void shot_c::shot_bullet_H019() {}
void shot_c::shot_bullet_H020() {}
void shot_c::shot_bullet_H021() {}
void shot_c::shot_bullet_H022() {}
void shot_c::shot_bullet_H023() {}
void shot_c::shot_bullet_H024() {}
void shot_c::shot_bullet_H025() {}
void shot_c::shot_bullet_H026() {}
void shot_c::shot_bullet_H027() {}
void shot_c::shot_bullet_H028() {}
void shot_c::shot_bullet_H029() {}