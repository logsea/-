#include "include.h"

void ch_c::round()
{
	calc_ch();
	move();
	shot_main();
	graph_main();
	music_play();
	cshot_hit_main();
}

void ch_c::move()
{
	int i, lr_flag, ud_flag;
	double x, y, mx, my, speedtimes = 1;
	double move_x[] = { -4.0,4.0,0,0 }, move_y[] = { 0,0,-4.0,4.0 };
	int keyboard[4];
	keyboard[0] = stateKey[KEY_INPUT_LEFT]; keyboard[1] = stateKey[KEY_INPUT_RIGHT];
	keyboard[2] = stateKey[KEY_INPUT_UP]; keyboard[3] = stateKey[KEY_INPUT_DOWN];

	if (keyboard[0]>0)//左键按下的情况
		ch.img += 4 * 2;//图像左移
	else if (keyboard[1]>0)//右键按下的情况
		ch.img += 4 * 1;//图像右移

	if (keyboard[0]>0|| keyboard[1]>0)//如果左右方向上有输入
		lr_flag = 1;//设置左右移动的标志
	if (keyboard[2]>0 || keyboard[3]>0)//如果左右方向上有输入
		ud_flag = 1;//设置左右移动的标志
	if (lr_flag == 1 && ud_flag == 1)//如果左右、上下方向都有输入说明斜向移动
		speedtimes = sqrt(2.0);//将移动速度变为1/√2

	for (int i = 0; i<4; i++) {//4方向分量循环
		if (keyboard[i]>0) {//i方向的键盘有输入
			x = ch.x, y = ch.y;//暂时存入当前的坐标
			mx = move_x[i];   my = move_y[i];//将移动分量带入mx和my                  
			if (stateKey[KEY_INPUT_LSHIFT]>0) {//如果低速运动
				mx = move_x[i] / 3; my = move_y[i] / 3;//将移动速度变为1/3
			}
			x += mx / speedtimes, y += my / speedtimes;//为当前坐标加上移动分量
			if (!(x<10 || x>FIELD_MAX_X - 10 || y<5 || y>FIELD_MAX_Y - 5)) {//如果计算结果在可移动范围内
				ch.x = x, ch.y = y;//进行实际的移动
			}
		}
	}
}

//shot_start
void ch_c::shot_main()
{
	calc_shot();//射击轨道的计算
	enter_shot();//射击登录
}

void ch_c::calc_shot()
{
	for (int i = 0; i<CSHOT_MAX; i++) {
		if (cshot[i].flag == 1) {
			int dranx = cshot[i].spd + 11 / 2, drany = cshot[i].spd + 55 / 2;
			cshot[i].x += cos(cshot[i].angle)*cshot[i].spd;
			cshot[i].y += sin(cshot[i].angle)*cshot[i].spd;
			cshot[i].cnt++;
			if (cshot[i].x<-dranx || cshot[i].x>FIELD_MAX_X + dranx ||
				cshot[i].y<-drany || cshot[i].y>FIELD_MAX_Y + drany)//如果跑到画面外了的话
				cshot[i].flag = 0;
		}
	}
}

void ch_c::enter_shot()
{
	//当按下射击按钮的时候
	if (stateKey[KEY_INPUT_Z]>0) {
		ch.shot_cnt++;
		if (ch.shot_cnt % 3 == 0) {//每3次计数射击一次
			if (stateKey[KEY_INPUT_LSHIFT]>0)//如果处于低速移动中的话
				ch1_shot_pattern();
			else
				ch0_shot_pattern();
		}
	}
	else
		ch.shot_cnt = 0;
}

//一般射击的登录
void ch_c::ch0_shot_pattern() {
	int k;
	for (int i = 0; i<shot0num[ch.power<200 ? 0 : 1]; i++) {
		if ((k = search_shot()) != -1) {
			cshot[k].flag = 1;
			cshot[k].cnt = 0;
			cshot[k].angle = -PI / 2;
			cshot[k].spd = 20;
			cshot[k].x = ch.x + shot0pos_x[i];
			cshot[k].y = ch.y + shot0pos_y[i];
			cshot[k].power = 23;
			cshot[k].knd = 0;
		}
	}
	se_flag = 1;//播放发射音
}

//低速下一般射击的登录
void ch_c::ch1_shot_pattern() {
	int k;
	for (int i = 0; i<shot0num[ch.power<200 ? 0 : 1]; i++) {
		if ((k = search_shot()) != -1) {
			cshot[k].flag = 1;
			cshot[k].cnt = 0;
			cshot[k].angle = -PI / 2;
			cshot[k].spd = 20;
			cshot[k].x = ch.x + shot0pos_x[i] / 3;//如果处于低速状态的话，将位置向中心偏移
			cshot[k].y = ch.y + shot0pos_y[i] / 2;
			cshot[k].power = 1;
			cshot[k].knd = 0;
		}
	}
	se_flag = 1;
}

//返回自机射击登录可能的编号。
int ch_c::search_shot() {
	for (int i = 0; i<CSHOT_MAX; i++) {
		if (cshot[i].flag == 0)
			return i;
	}
	return -1;
}
//shot_end

//graph_start
void ch_c::graph_main()
{
	graph_ch();
	graph_shot();
}
void ch_c::graph_shot()
{
	for (int i = 0; i<CSHOT_MAX; i++) {
		if (cshot[i].flag>0) {
			DrawRotaGraphF(cshot[i].x + FIELD_X, cshot[i].y + FIELD_Y, 1, 0,
				img_cshot[cshot[i].knd], TRUE);
		}
	}
}
void ch_c::graph_ch()
{
	DrawRotaGraphF(ch.x + FIELD_X, ch.y + FIELD_Y, 1.0f, 0.0f, img_ch[0][img], TRUE);
}
//graph_end

//music_start
void ch_c::music_play() {
	int i;
	if (se_flag == 1) {
		if (CheckSoundMem(shot_sound) != 0) {
			StopSoundMem(shot_sound);
		}
		PlaySoundMem(shot_sound, DX_PLAYTYPE_BACK);
	}
	se_flag = 0;
}
//music_end

void ch_c::init()
{
	x = FIELD_MAX_X / 2;
	y = FIELD_MAX_Y * 3 / 4;
	power = 0;
	shot0num[0] = 2; shot0num[1] = 4;
	shot0pos_x[0] = -10; shot0pos_x[1] = 10; shot0pos_x[2] = -30; shot0pos_x[3] = 30;
	shot0pos_y[0] = -30; shot0pos_y[1] = -30; shot0pos_y[2] = -10; shot0pos_y[3] = -10;
	img_cshot[0] = LoadGraph("dat/img/char/bl_00.png");
	img_cshot[1] = LoadGraph("dat/img/char/bl_01.png");
	LoadDivGraph("dat/img/char/0.png", 12, 4, 3, 73, 73, img_ch[0]);
	shot_sound = LoadSoundMem("dat/se/cshot.wav");
}

void ch_c::calc_ch() {
	cnt++;
	img = (cnt % 24) / 6;
}

int ch_c::ret_power() {
	return power;
}

//敌人的碰撞判定范围
int enemy_range[ENEMY_RANGE_MAX] = { 4,6,4,7 };
//自机的射击的子弹碰撞判定范围
int cshot_range[CSHOT_RANGE_MAX] = { 6, };

void ch_c::cshot_hit_main()
{
	int i, s;
	for (i = 0; i<CSHOT_MAX; i++) {//自机射击总数
		if (cshot[i].flag>0) {
			for (s = 0; s<ENEMY_MAX; s++) {//敌人总数
				if (enemy[s].flag>0) {
					if (cshot[i].out_judge_cshot(s)) {//如果自机子弹射中敌人
						cshot[i].flag = 0;//将那个自机子弹销毁
						enemy[s].hp -= cshot[i].power;//将HP减少子弹的power的量那么多
						cshot[i].enemy_death_judge(s);//决定敌人是否死掉
					}
				}
			}
		}
	}
}

//判定是否击中
int cshot_c::out_judge_cshot(int s) {
	int j;
	if (cnt>0) { //如果射击的轨道至少计算过一次
		double dx = fabs(x - enemy[s].x);//敌人和自机射击的子弹的距离
		double dy = fabs(y - enemy[s].y);
		//防止溢出
		if (knd >= CSHOT_RANGE_MAX || enemy[s].knd >= ENEMY_RANGE_MAX)
			printfDx("out_judge_cshot中溢出");
		//敌人的碰撞判定和自机射击的子弹的碰撞判定的合计范围
		double r = cshot_range[knd] + enemy_range[enemy[s].knd];
		//如果有必要计算中间
		if (spd>r) {
			//保存1帧之前的位置
			double pre_x = fabs(x + cos(angle + PI)*spd);
			double pre_y = fabs(y + sin(angle + PI)*spd);
			double px, py;
			for (j = 0; j<spd / r; j++) {//前进的分量÷碰撞判定分量次循环
				px = fabs(pre_x - enemy[s].x);
				py = fabs(pre_y - enemy[s].y);
				if (px<r&&py<r)
					return 1;
				pre_x += cos(angle)*r;
				pre_y += sin(angle)*r;
			}
		}
		if (dx<r&&dy<r)//如果在碰撞判定范围内
			return 1;//碰撞
	}
	return 0;
}

//决定敌人是否死掉
void cshot_c::enemy_death_judge(int s) {
	int i;
	enemy_hit_sound_flag = 1;//击中敌人的声音
	if (enemy[s].hp<0) {//如果敌人的HP小于0 
		enemy[s].flag = 0;//消灭敌人
		enemy_death_sound_flag = 1;//敌人击毁的声音
		//enter_del_effect(s);
		for (i = 0; i<SHOT_MAX; i++) {//敌人总数次循环
			if (shot_obj[i].ret_flag() != 0) {//如果有没有登录的弹幕
				if (&enemy[s] == shot_obj[i].ret_from()) {//且敌人有已经登录了的弹幕
					shot_obj[i].kill_shot();//改变flag以表示弹幕不再继续
					break;
				}
			}
		}
	}
}