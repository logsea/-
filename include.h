#pragma once
#include "define.h"
#include "load.h"
#include "graph.h"
#include "key.h"
#include "character.h"
#include "init.h"
#include "menu.h"
#include "music.h"
#include "replay.h"
#include "manual.h"
#include "enemy.h"
#include "board.h"
#include "background.h"

GLOBAL int choose;
GLOBAL int choose_t;
GLOBAL int func_state;//��Ϸ����
GLOBAL int open_time_count;//��Ϸʱ�������
GLOBAL int stage_count;//
GLOBAL int img_menu[2][7];
GLOBAL int rank_menu[5];
GLOBAL int manual_menu[6][7];
GLOBAL int manual_text[9];
GLOBAL int image_board[Image_Board_Max];//���
GLOBAL unsigned int stateKey[256];//�洢����
GLOBAL int sound_se[MUSIC_MAX];
GLOBAL int replay_choose_page;
GLOBAL int ascii[100];