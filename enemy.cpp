#include "include.h"

void enemy_main()
{
	for (int i = 0; i < ENEMY_MAX; i++)
		if (enemy[i].ret_flag() == true)
			enemy[i].round();
}

void enter_main()
{
	for (int i = entered_enemy; i < ENEMY_ORDER_MAX; i++)
	{
		if (enemy_order[i].ret_cnt() > enemy_order[entered_enemy].ret_cnt())
			break;
		if (enemy_order[i].ret_cnt() == open_time_count)
		{
			enemy_order[i].enter();
			entered_enemy++;
		}
	}
}

void bullet_main()
{
	for (int i = 0; i<SHOT_MAX; i++) {//弹幕数据计算
								  //如果flag为有效且设定的种类没有错误的情况（防止溢出）

		if (shot_obj[i].ret_flag() != 0 && 0 <= shot_obj[i].ret_knd() && shot_obj[i].ret_knd() < SHOT_KND_MAX) {
			shot_obj[i].shot_main();
		}
	}
}

void shot_c::shot_main()
{
	choose_knd();//调用.knd的弹幕计算函数
	shot_calc();//计算第i号弹幕
	cnt_inc();
	graph();
}

void shot_c::shot_calc() {
	int i, max = 0;
	if (from->flag != 1)//如果敌人被打倒的话
		flag = 2;//将之前登录的射击的flag设置为无效
	for (i = 0; i<SHOT_BULLET_MAX; i++) {//计算第n号弹幕数据的子弹
		if (bullet[i].flag>0) {//如果那子弹并没有被登录
			bullet[i].x += cos(bullet[i].angle)*bullet[i].spd;
			bullet[i].y += sin(bullet[i].angle)*bullet[i].spd;
			bullet[i].cnt++;
			if (bullet[i].x<-50 || bullet[i].x>FIELD_MAX_X + 50 ||
				bullet[i].y<-50 || bullet[i].y>FIELD_MAX_Y + 50) {//如果跑到画面外面的话
				if (bullet[i].till<bullet[i].cnt)//且比最低程度不会销毁的时间还要很长
					bullet[i].flag = 0;//销毁之
			}
		}
	}
	//查询当前显示中的子弹的熟练是否至少还有一个
	for (i = 0; i<SHOT_BULLET_MAX; i++)
		if (bullet[i].flag>0)
			return;
	if (from->flag != 1) {
		flag = 0;//終了
		from->flag = 0;
	}
}

//搜索空着的子弹
int shot_c::shot_search() {
	int i;
	for (i = 0; i<SHOT_BULLET_MAX; i++) {
		if (bullet[i].flag == 0) {
			return i;
		}
	}
	return -1;
}

void shot_c::graph() {
	int i, j;
	SetDrawMode(DX_DRAWMODE_BILINEAR);//线性插值绘制
	if (flag>0) {//如果敌人的弹幕数据为有效
		for (j = 0; j<SHOT_BULLET_MAX; j++) {//弹幕所拥有的子弹的最大数量次循环
			if (bullet[j].flag != 0) {//如果子弹的数据为有效
				if (bullet[j].eff == 1)
					SetDrawBlendMode(DX_BLENDMODE_ADD, 255);

				DrawRotaGraphF(
					bullet[j].x + FIELD_X, bullet[j].y + FIELD_Y,
					1.0, bullet[j].angle + PI / 2,
					img_bullet[bullet[j].knd][bullet[j].col], TRUE);

				if (bullet[j].eff == 1)
					SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
			}
		}
	}
	SetDrawMode(DX_DRAWMODE_NEAREST);//还原绘制状态
}

//返回登录了的第n号射击的敌人和自机的之间的夹角
double shot_c::shotatan2() {
	return atan2(ch.y - from->y, ch.x - from->x);
}

double bullet_c::bulletatan2() {
	return atan2(ch.y - y, ch.x - x);
}

void shot_c::cnt_inc()
{
	cnt++;
}

void enemy_c::round()
{
	move();
	if (bltime == cnt)
		shot();
	graph();
}

void enemy_c::move()
{
	if (flag == 1) {//如果敌人的flag为有效
		if (0 <= pattern && pattern<ENEMY_PATTERN_MAX) {
			choose_pattern();
			x += cos(ang)*sp;
			y += sin(ang)*sp;
			x += vx;
			y += vy;
			cnt++;
			img = muki * 3 + (cnt % 18) / 6;
			//敌人跑到画面外面的话销毁
			if (x<-20 || FIELD_MAX_X + 20<x || y<-20 || FIELD_MAX_Y + 20<y)
				flag = 0;
		}
		else
			printfDx("enemy[i].pattern的%d的值错误。", pattern);
	}
}

void enemy_c::shot()
{
	int j;
	for (j = 0; j<SHOT_MAX; j++) {//搜索flag为无效的敌人
		if (shot_obj[j].flag == 0) {//如果有没有使用过的弹幕数据
			memset(&shot_obj[j], 0, sizeof(shot_c));//初始化并登录之
			shot_obj[j].flag = 1;//设置flag为有效
			shot_obj[j].knd = blknd;//子弹的种类
			shot_obj[j].from = this;//是哪个敌人发射过来的
			shot_obj[j].cnt = 0;
			return;
		}
	}
}

void enemy_c::graph()
{
	DrawRotaGraphF(x + FIELD_X, y + FIELD_Y, 1.0f, 0.0f, enemy_img[0][img], TRUE);
}

bool enemy_c::ret_flag()
{
	return flag;
}

//enemy_order
int enemy_order_c::ret_cnt()
{
	return cnt;
}

void enemy_order_c::enter()
{
	int i, j, t;
	if ((i = num_search()) != -1) {
		enemy[i].flag = true;//flag
		enemy[i].cnt = 0;//计数器
		enemy[i].pattern = pattern;//移动模式
		enemy[i].muki = 1;//方向
		enemy[i].knd = knd;//敌人的种类
		enemy[i].x = x;//坐标
		enemy[i].y = y;
		enemy[i].sp = sp;//速度
		enemy[i].bltime = bltime;//子弹的发射时间
		enemy[i].blknd = blknd;//弹幕的种类
		enemy[i].blknd2 = blknd2;//子弹的种类
		enemy[i].col = col;//颜色
		enemy[i].wait = wait;//停止时间
		enemy[i].hp = hp;//体力
		enemy[i].hp_max = enemy[i].hp;//体力最大值
		enemy[i].vx = 0;//水平分量的速度
		enemy[i].vy = 0;//竖直分量的速度
		enemy[i].ang = 0;//角度
		enemy[i].back_col = GetRand(4);
		for (j = 0; j<6; j++)
			enemy[i].item_n[j] = item_n[j];//掉落的道具
	}
}

//检查空的敌人编号
int enemy_order_c::num_search() {
	for (int i = 0; i<ENEMY_MAX; i++) {//查询flag为无效的enemy
		if (enemy[i].flag == 0) {
			return i;//返回使用可能的编号
		}
	}
	return -1;//如果全部被使用返回错误
}

//bullet
int shot_c::ret_flag()
{
	return flag;
}
int shot_c::ret_knd()
{
	return knd;
}
enemy_c* shot_c::ret_from()
{
	return from;
}
void shot_c::kill_shot()
{
	flag = 2;
}


//pattern
void enemy_c::choose_pattern()
{
	switch (pattern)
	{
	case 0:pattern0(); break;
	case 1:pattern1(); break;
	case 2:pattern2(); break;
	case 3:pattern3(); break;
	case 4:pattern4(); break;
	case 5:pattern5(); break;
	case 6:pattern6(); break;
	case 7:pattern7(); break;
	case 8:pattern8(); break;
	case 9:pattern9(); break;
	case 10:pattern10(); break;
	default:printfDx("PATTERN ERROR\n");
	}
}

//返回-ang～ang的随机角度
double rang(double ang) {
	return (-ang + ang * 2 * GetRand(10000) / 10000.0);
}

//移动模式0
//向下移动后停止然后往上移动
void enemy_c::pattern0() {
	int t = cnt;
	if (t == 0)
		vy = 3;//向下移动
	if (t == 40)
		vy = 0;//停止
	if (t == 40 + wait)//在登录的时间区间内停止
		vy = -3;//向上移动
}

//移动模式1
//向下移动然后停止然后向左下移动
void enemy_c::pattern1() {
	int t = cnt;
	if (t == 0)
		vy = 3;//向下移动
	if (t == 40)
		vy = 0;//停止
	if (t == 40 + wait) {//在登录的时间区间内停止
		vx = -1;//向左
		vy = 2;//向下移动
		muki = 0;//设置方向为左
	}
}

//移动模式2
//向下移动然后停止然后向右下移动
void enemy_c::pattern2() {
	int t = cnt;
	if (t == 0)
		vy = 3;//向下移动
	if (t == 40)
		vy = 0;//停止
	if (t == 40 + wait) {// 在登录的时间区间内停止
		vx = 1;//向右
		vy = 2;//向下移动
		muki = 2;//设置方向为右
	}
}

//移动模式3
//迅速地下降然后向左移动
void enemy_c::pattern3() {
	int t = cnt;
	if (t == 0)
		vy = 5;//向下移动
	if (t == 30) {//途中方向向左
		muki = 0;
	}
	if (t<100) {
		vx -= 5 / 100.0;//左方向加速
		vy -= 5 / 100.0;//减速
	}
}

//移动模式4
//迅速地下降然后向右移动
void enemy_c::pattern4() {
	int t = cnt;
	if (t == 0)
		vy = 5;//向下移动
	if (t == 30) {//途中方向向右
		muki = 2;
	}
	if (t<100) {
		vx += 5 / 100.0;//右方向加速
		vy -= 5 / 100.0;//減速
	}
}

//移动模式5
//斜着向左下移动
void enemy_c::pattern5() {
	int t = cnt;
	if (t == 0) {
		vx -= 1;
		vy = 2;
		muki = 0;
	}
}

//移动模式6
//斜着向右下移动
void enemy_c::pattern6() {
	int t = cnt;
	if (t == 0) {
		vx += 1;
		vy = 2;
		muki = 2;
	}
}

//移动模式7
//停止然后就那样向左上移动
void enemy_c::pattern7() {
	int t = cnt;
	if (t == wait) {//在登录的时间区间内停止
		vx = -0.7;//向左
		vy = -0.3;//向上移动
		muki = 0;//设置方向为左
	}
}

//移动模式8
//停止然后就那样向右上移动
void enemy_c::pattern8() {
	int t = cnt;
	if (t == wait) {//在登录的时间区间内停止
		vx = +0.7;//向右
		vy = -0.3;//向上移动
		muki = 2;//设置方向为右
	}
}

//移动模式9
//停止然后就那样向上移动
void enemy_c::pattern9() {
	int t = cnt;
	if (t == wait)//在登录的时间区间内停止
		vy = -1;//向上移动
}


//移动模式10
//下降然后转着圈往上移动
void enemy_c::pattern10() {
	int t = cnt;
	if (t == 0) vy = 4;//向下移动
	if (t == 40)vy = 0;//停止
	if (t >= 40) {
		if (t % 60 == 0) {
			int r = cos(ang)< 0 ? 0 : 1;
			sp = 6 + rang(2);
			ang = rang(PI / 4) + PI*r;
			muki = 2 - 2 * r;
		}
		sp *= 0.95;
	}
	if (t >= 40 + wait) {
		vy -= 0.05;
	}
}