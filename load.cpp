#include "include.h"

void load()
{
	int debug = 9;
	image_board[0] = LoadGraph("dat/img/menu/00.png");
	image_board[1] = LoadGraph("dat/img/menu/01.png");
	image_board[2] = LoadGraph("dat/img/menu/02.png");
	image_board[3] = LoadGraph("dat/img/menu/05.png");
	image_board[4] = LoadGraph("dat/img/menu/08.png");
	image_board[5] = LoadGraph("dat/img/menu/07.png");
	LoadDivGraph("dat/img/menu/03.png", 7, 1, 7, 160, 32, img_menu[0]);
	LoadDivGraph("dat/img/menu/04.png", 7, 1, 7, 160, 32, img_menu[1]);
	LoadDivGraph("dat/img/menu/06.png", 5, 1, 5, 160, 75, rank_menu);
	LoadDivGraph("dat/img/menu/09.png", 7, 1, 7, 280, 40, manual_menu[0]);
	LoadDivGraph("dat/img/menu/09-1.png", 7, 1, 7, 280, 40, manual_menu[1]);
	LoadDivGraph("dat/img/menu/09-2.png", 7, 1, 7, 280, 40, manual_menu[2]);
	LoadDivGraph("dat/img/menu/09-3.png", 7, 1, 7, 280, 40, manual_menu[3]);
	LoadDivGraph("dat/img/menu/09-1.png", 7, 1, 7, 280, 40, manual_menu[5]);
	LoadDivGraph("dat/img/menu/09-2.png", 7, 1, 7, 280, 40, manual_menu[4]);
	//manual_text
	manual_text[2] = LoadGraph("dat/img/menu/manual/00.png");
	manual_text[3] = LoadGraph("dat/img/menu/manual/01.png");
	manual_text[4] = LoadGraph("dat/img/menu/manual/02.png");
	manual_text[5] = LoadGraph("dat/img/menu/manual/03.png");
	manual_text[6] = LoadGraph("dat/img/menu/manual/04.png");
	manual_text[7] = LoadGraph("dat/img/menu/manual/05.png");
	manual_text[8] = LoadGraph("dat/img/menu/manual/06.png");
	//number
	LoadDivGraph("dat/img/num/ascii.png", 100, 18, 6, 14, 14, ascii);
	LoadDivGraph("dat/img/enemy/0.png", 9, 3, 3, 32, 32, enemy_img[0]);
	
	//LoadDivGraph("dat/img/char/0.png", 12, 4, 3, 73, 73, img_ch[0]);//0:success -1:error

	//读入子弹的图像文件
	LoadDivGraph("dat/img/bullet/b0.png", 5, 5, 1, 76, 76, img_bullet[0]);
	LoadDivGraph("dat/img/bullet/b1.png", 6, 6, 1, 22, 22, img_bullet[1]);
	LoadDivGraph("dat/img/bullet/b2.png", 10, 10, 1, 5, 120, img_bullet[2]);
	LoadDivGraph("dat/img/bullet/b3.png", 5, 5, 1, 19, 34, img_bullet[3]);
	LoadDivGraph("dat/img/bullet/b4.png", 10, 10, 1, 38, 38, img_bullet[4]);
	LoadDivGraph("dat/img/bullet/b5.png", 3, 3, 1, 14, 16, img_bullet[5]);
	LoadDivGraph("dat/img/bullet/b6.png", 3, 3, 1, 14, 18, img_bullet[6]);
	LoadDivGraph("dat/img/bullet/b7.png", 9, 9, 1, 16, 16, img_bullet[7]);
	LoadDivGraph("dat/img/bullet/b8.png", 10, 10, 1, 12, 18, img_bullet[8]);
	LoadDivGraph("dat/img/bullet/b9.png", 3, 3, 1, 13, 19, img_bullet[9]);

	//读入敌人的射击音效
	enemy_shot_sound = LoadSoundMem("dat/se/enemy_shot.wav");
	
	enemy_death_sound = LoadSoundMem("dat/se/enemy_death.wav");
	enemy_hit_sound = LoadSoundMem("dat/se/hit.wav");
	/*ChangeVolumeSoundMem(50, sound_se[0]);//设定各素材的重播音量
	ChangeVolumeSoundMem(128, sound_se[1]);
	ChangeVolumeSoundMem(128, sound_se[2]);
	ChangeVolumeSoundMem(80, sound_se[8]);

	LoadDivGraph("dat/img/enemy/hit_effect.png", 5, 5, 1, 140, 140, img_del_effect);*/

	img_back[0] = LoadGraph("dat/img/back/0/back0.png");
}