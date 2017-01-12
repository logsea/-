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

	if (keyboard[0]>0)//������µ����
		ch.img += 4 * 2;//ͼ������
	else if (keyboard[1]>0)//�Ҽ����µ����
		ch.img += 4 * 1;//ͼ������

	if (keyboard[0]>0|| keyboard[1]>0)//������ҷ�����������
		lr_flag = 1;//���������ƶ��ı�־
	if (keyboard[2]>0 || keyboard[3]>0)//������ҷ�����������
		ud_flag = 1;//���������ƶ��ı�־
	if (lr_flag == 1 && ud_flag == 1)//������ҡ����·���������˵��б���ƶ�
		speedtimes = sqrt(2.0);//���ƶ��ٶȱ�Ϊ1/��2

	for (int i = 0; i<4; i++) {//4�������ѭ��
		if (keyboard[i]>0) {//i����ļ���������
			x = ch.x, y = ch.y;//��ʱ���뵱ǰ������
			mx = move_x[i];   my = move_y[i];//���ƶ���������mx��my                  
			if (stateKey[KEY_INPUT_LSHIFT]>0) {//��������˶�
				mx = move_x[i] / 3; my = move_y[i] / 3;//���ƶ��ٶȱ�Ϊ1/3
			}
			x += mx / speedtimes, y += my / speedtimes;//Ϊ��ǰ��������ƶ�����
			if (!(x<10 || x>FIELD_MAX_X - 10 || y<5 || y>FIELD_MAX_Y - 5)) {//����������ڿ��ƶ���Χ��
				ch.x = x, ch.y = y;//����ʵ�ʵ��ƶ�
			}
		}
	}
}

//shot_start
void ch_c::shot_main()
{
	calc_shot();//�������ļ���
	enter_shot();//�����¼
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
				cshot[i].y<-drany || cshot[i].y>FIELD_MAX_Y + drany)//����ܵ��������˵Ļ�
				cshot[i].flag = 0;
		}
	}
}

void ch_c::enter_shot()
{
	//�����������ť��ʱ��
	if (stateKey[KEY_INPUT_Z]>0) {
		ch.shot_cnt++;
		if (ch.shot_cnt % 3 == 0) {//ÿ3�μ������һ��
			if (stateKey[KEY_INPUT_LSHIFT]>0)//������ڵ����ƶ��еĻ�
				ch1_shot_pattern();
			else
				ch0_shot_pattern();
		}
	}
	else
		ch.shot_cnt = 0;
}

//һ������ĵ�¼
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
	se_flag = 1;//���ŷ�����
}

//������һ������ĵ�¼
void ch_c::ch1_shot_pattern() {
	int k;
	for (int i = 0; i<shot0num[ch.power<200 ? 0 : 1]; i++) {
		if ((k = search_shot()) != -1) {
			cshot[k].flag = 1;
			cshot[k].cnt = 0;
			cshot[k].angle = -PI / 2;
			cshot[k].spd = 20;
			cshot[k].x = ch.x + shot0pos_x[i] / 3;//������ڵ���״̬�Ļ�����λ��������ƫ��
			cshot[k].y = ch.y + shot0pos_y[i] / 2;
			cshot[k].power = 1;
			cshot[k].knd = 0;
		}
	}
	se_flag = 1;
}

//�����Ի������¼���ܵı�š�
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

//���˵���ײ�ж���Χ
int enemy_range[ENEMY_RANGE_MAX] = { 4,6,4,7 };
//�Ի���������ӵ���ײ�ж���Χ
int cshot_range[CSHOT_RANGE_MAX] = { 6, };

void ch_c::cshot_hit_main()
{
	int i, s;
	for (i = 0; i<CSHOT_MAX; i++) {//�Ի��������
		if (cshot[i].flag>0) {
			for (s = 0; s<ENEMY_MAX; s++) {//��������
				if (enemy[s].flag>0) {
					if (cshot[i].out_judge_cshot(s)) {//����Ի��ӵ����е���
						cshot[i].flag = 0;//���Ǹ��Ի��ӵ�����
						enemy[s].hp -= cshot[i].power;//��HP�����ӵ���power������ô��
						cshot[i].enemy_death_judge(s);//���������Ƿ�����
					}
				}
			}
		}
	}
}

//�ж��Ƿ����
int cshot_c::out_judge_cshot(int s) {
	int j;
	if (cnt>0) { //�������Ĺ�����ټ����һ��
		double dx = fabs(x - enemy[s].x);//���˺��Ի�������ӵ��ľ���
		double dy = fabs(y - enemy[s].y);
		//��ֹ���
		if (knd >= CSHOT_RANGE_MAX || enemy[s].knd >= ENEMY_RANGE_MAX)
			printfDx("out_judge_cshot�����");
		//���˵���ײ�ж����Ի�������ӵ�����ײ�ж��ĺϼƷ�Χ
		double r = cshot_range[knd] + enemy_range[enemy[s].knd];
		//����б�Ҫ�����м�
		if (spd>r) {
			//����1֮֡ǰ��λ��
			double pre_x = fabs(x + cos(angle + PI)*spd);
			double pre_y = fabs(y + sin(angle + PI)*spd);
			double px, py;
			for (j = 0; j<spd / r; j++) {//ǰ���ķ�������ײ�ж�������ѭ��
				px = fabs(pre_x - enemy[s].x);
				py = fabs(pre_y - enemy[s].y);
				if (px<r&&py<r)
					return 1;
				pre_x += cos(angle)*r;
				pre_y += sin(angle)*r;
			}
		}
		if (dx<r&&dy<r)//�������ײ�ж���Χ��
			return 1;//��ײ
	}
	return 0;
}

//���������Ƿ�����
void cshot_c::enemy_death_judge(int s) {
	int i;
	enemy_hit_sound_flag = 1;//���е��˵�����
	if (enemy[s].hp<0) {//������˵�HPС��0 
		enemy[s].flag = 0;//�������
		enemy_death_sound_flag = 1;//���˻��ٵ�����
		//enter_del_effect(s);
		for (i = 0; i<SHOT_MAX; i++) {//����������ѭ��
			if (shot_obj[i].ret_flag() != 0) {//�����û�е�¼�ĵ�Ļ
				if (&enemy[s] == shot_obj[i].ret_from()) {//�ҵ������Ѿ���¼�˵ĵ�Ļ
					shot_obj[i].kill_shot();//�ı�flag�Ա�ʾ��Ļ���ټ���
					break;
				}
			}
		}
	}
}