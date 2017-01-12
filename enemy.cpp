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
	for (int i = 0; i<SHOT_MAX; i++) {//��Ļ���ݼ���
								  //���flagΪ��Ч���趨������û�д�����������ֹ�����

		if (shot_obj[i].ret_flag() != 0 && 0 <= shot_obj[i].ret_knd() && shot_obj[i].ret_knd() < SHOT_KND_MAX) {
			shot_obj[i].shot_main();
		}
	}
}

void shot_c::shot_main()
{
	choose_knd();//����.knd�ĵ�Ļ���㺯��
	shot_calc();//�����i�ŵ�Ļ
	cnt_inc();
	graph();
}

void shot_c::shot_calc() {
	int i, max = 0;
	if (from->flag != 1)//������˱��򵹵Ļ�
		flag = 2;//��֮ǰ��¼�������flag����Ϊ��Ч
	for (i = 0; i<SHOT_BULLET_MAX; i++) {//�����n�ŵ�Ļ���ݵ��ӵ�
		if (bullet[i].flag>0) {//������ӵ���û�б���¼
			bullet[i].x += cos(bullet[i].angle)*bullet[i].spd;
			bullet[i].y += sin(bullet[i].angle)*bullet[i].spd;
			bullet[i].cnt++;
			if (bullet[i].x<-50 || bullet[i].x>FIELD_MAX_X + 50 ||
				bullet[i].y<-50 || bullet[i].y>FIELD_MAX_Y + 50) {//����ܵ���������Ļ�
				if (bullet[i].till<bullet[i].cnt)//�ұ���ͳ̶Ȳ������ٵ�ʱ�仹Ҫ�ܳ�
					bullet[i].flag = 0;//����֮
			}
		}
	}
	//��ѯ��ǰ��ʾ�е��ӵ��������Ƿ����ٻ���һ��
	for (i = 0; i<SHOT_BULLET_MAX; i++)
		if (bullet[i].flag>0)
			return;
	if (from->flag != 1) {
		flag = 0;//�K��
		from->flag = 0;
	}
}

//�������ŵ��ӵ�
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
	SetDrawMode(DX_DRAWMODE_BILINEAR);//���Բ�ֵ����
	if (flag>0) {//������˵ĵ�Ļ����Ϊ��Ч
		for (j = 0; j<SHOT_BULLET_MAX; j++) {//��Ļ��ӵ�е��ӵ������������ѭ��
			if (bullet[j].flag != 0) {//����ӵ�������Ϊ��Ч
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
	SetDrawMode(DX_DRAWMODE_NEAREST);//��ԭ����״̬
}

//���ص�¼�˵ĵ�n������ĵ��˺��Ի���֮��ļн�
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
	if (flag == 1) {//������˵�flagΪ��Ч
		if (0 <= pattern && pattern<ENEMY_PATTERN_MAX) {
			choose_pattern();
			x += cos(ang)*sp;
			y += sin(ang)*sp;
			x += vx;
			y += vy;
			cnt++;
			img = muki * 3 + (cnt % 18) / 6;
			//�����ܵ���������Ļ�����
			if (x<-20 || FIELD_MAX_X + 20<x || y<-20 || FIELD_MAX_Y + 20<y)
				flag = 0;
		}
		else
			printfDx("enemy[i].pattern��%d��ֵ����", pattern);
	}
}

void enemy_c::shot()
{
	int j;
	for (j = 0; j<SHOT_MAX; j++) {//����flagΪ��Ч�ĵ���
		if (shot_obj[j].flag == 0) {//�����û��ʹ�ù��ĵ�Ļ����
			memset(&shot_obj[j], 0, sizeof(shot_c));//��ʼ������¼֮
			shot_obj[j].flag = 1;//����flagΪ��Ч
			shot_obj[j].knd = blknd;//�ӵ�������
			shot_obj[j].from = this;//���ĸ����˷��������
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
		enemy[i].cnt = 0;//������
		enemy[i].pattern = pattern;//�ƶ�ģʽ
		enemy[i].muki = 1;//����
		enemy[i].knd = knd;//���˵�����
		enemy[i].x = x;//����
		enemy[i].y = y;
		enemy[i].sp = sp;//�ٶ�
		enemy[i].bltime = bltime;//�ӵ��ķ���ʱ��
		enemy[i].blknd = blknd;//��Ļ������
		enemy[i].blknd2 = blknd2;//�ӵ�������
		enemy[i].col = col;//��ɫ
		enemy[i].wait = wait;//ֹͣʱ��
		enemy[i].hp = hp;//����
		enemy[i].hp_max = enemy[i].hp;//�������ֵ
		enemy[i].vx = 0;//ˮƽ�������ٶ�
		enemy[i].vy = 0;//��ֱ�������ٶ�
		enemy[i].ang = 0;//�Ƕ�
		enemy[i].back_col = GetRand(4);
		for (j = 0; j<6; j++)
			enemy[i].item_n[j] = item_n[j];//����ĵ���
	}
}

//���յĵ��˱��
int enemy_order_c::num_search() {
	for (int i = 0; i<ENEMY_MAX; i++) {//��ѯflagΪ��Ч��enemy
		if (enemy[i].flag == 0) {
			return i;//����ʹ�ÿ��ܵı��
		}
	}
	return -1;//���ȫ����ʹ�÷��ش���
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

//����-ang��ang������Ƕ�
double rang(double ang) {
	return (-ang + ang * 2 * GetRand(10000) / 10000.0);
}

//�ƶ�ģʽ0
//�����ƶ���ֹͣȻ�������ƶ�
void enemy_c::pattern0() {
	int t = cnt;
	if (t == 0)
		vy = 3;//�����ƶ�
	if (t == 40)
		vy = 0;//ֹͣ
	if (t == 40 + wait)//�ڵ�¼��ʱ��������ֹͣ
		vy = -3;//�����ƶ�
}

//�ƶ�ģʽ1
//�����ƶ�Ȼ��ֹͣȻ���������ƶ�
void enemy_c::pattern1() {
	int t = cnt;
	if (t == 0)
		vy = 3;//�����ƶ�
	if (t == 40)
		vy = 0;//ֹͣ
	if (t == 40 + wait) {//�ڵ�¼��ʱ��������ֹͣ
		vx = -1;//����
		vy = 2;//�����ƶ�
		muki = 0;//���÷���Ϊ��
	}
}

//�ƶ�ģʽ2
//�����ƶ�Ȼ��ֹͣȻ���������ƶ�
void enemy_c::pattern2() {
	int t = cnt;
	if (t == 0)
		vy = 3;//�����ƶ�
	if (t == 40)
		vy = 0;//ֹͣ
	if (t == 40 + wait) {// �ڵ�¼��ʱ��������ֹͣ
		vx = 1;//����
		vy = 2;//�����ƶ�
		muki = 2;//���÷���Ϊ��
	}
}

//�ƶ�ģʽ3
//Ѹ�ٵ��½�Ȼ�������ƶ�
void enemy_c::pattern3() {
	int t = cnt;
	if (t == 0)
		vy = 5;//�����ƶ�
	if (t == 30) {//;�з�������
		muki = 0;
	}
	if (t<100) {
		vx -= 5 / 100.0;//�������
		vy -= 5 / 100.0;//����
	}
}

//�ƶ�ģʽ4
//Ѹ�ٵ��½�Ȼ�������ƶ�
void enemy_c::pattern4() {
	int t = cnt;
	if (t == 0)
		vy = 5;//�����ƶ�
	if (t == 30) {//;�з�������
		muki = 2;
	}
	if (t<100) {
		vx += 5 / 100.0;//�ҷ������
		vy -= 5 / 100.0;//�p��
	}
}

//�ƶ�ģʽ5
//б���������ƶ�
void enemy_c::pattern5() {
	int t = cnt;
	if (t == 0) {
		vx -= 1;
		vy = 2;
		muki = 0;
	}
}

//�ƶ�ģʽ6
//б���������ƶ�
void enemy_c::pattern6() {
	int t = cnt;
	if (t == 0) {
		vx += 1;
		vy = 2;
		muki = 2;
	}
}

//�ƶ�ģʽ7
//ֹͣȻ��������������ƶ�
void enemy_c::pattern7() {
	int t = cnt;
	if (t == wait) {//�ڵ�¼��ʱ��������ֹͣ
		vx = -0.7;//����
		vy = -0.3;//�����ƶ�
		muki = 0;//���÷���Ϊ��
	}
}

//�ƶ�ģʽ8
//ֹͣȻ��������������ƶ�
void enemy_c::pattern8() {
	int t = cnt;
	if (t == wait) {//�ڵ�¼��ʱ��������ֹͣ
		vx = +0.7;//����
		vy = -0.3;//�����ƶ�
		muki = 2;//���÷���Ϊ��
	}
}

//�ƶ�ģʽ9
//ֹͣȻ������������ƶ�
void enemy_c::pattern9() {
	int t = cnt;
	if (t == wait)//�ڵ�¼��ʱ��������ֹͣ
		vy = -1;//�����ƶ�
}


//�ƶ�ģʽ10
//�½�Ȼ��ת��Ȧ�����ƶ�
void enemy_c::pattern10() {
	int t = cnt;
	if (t == 0) vy = 4;//�����ƶ�
	if (t == 40)vy = 0;//ֹͣ
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