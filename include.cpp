#include"include.h"

int choose;
int choose_t;
int func_state;//��Ϸ����
int open_time_count;//��Ϸʱ�������
int stage_count;//�ؿ�������
int img_menu[2][7];
int rank_menu[5];
int manual_menu[6][7];
int manual_text[9];
int image_board[Image_Board_Max];//���
unsigned int stateKey[256];//�洢����
int sound_se[MUSIC_MAX];
int ascii[100];
int replay_choose_page;
ch_c ch;
cshot_c cshot[CSHOT_MAX];
bd board;
enemy_c enemy[ENEMY_MAX];
enemy_order_c enemy_order[ENEMY_ORDER_MAX];
shot_c shot_obj[SHOT_MAX];
int entered_enemy;
int enemy_img[3][9];
int enemy_shot_sound;
int enemy_shot_sound_flag;
int enemy_hit_sound;
int enemy_hit_sound_flag;
int enemy_death_sound;
int enemy_death_sound_flag;
int img_bullet[10][10];
int img_back[10];
int back_count;