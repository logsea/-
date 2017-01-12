#include "include.h"

void music_main()
{
	if (enemy_shot_sound_flag == 1)
	{
		PlaySoundMem(enemy_shot_sound, DX_PLAYTYPE_BACK);
		enemy_shot_sound_flag = 0;
	}
	if (enemy_hit_sound_flag == 1)
	{
		PlaySoundMem(enemy_hit_sound, DX_PLAYTYPE_BACK);
		enemy_hit_sound_flag = 0;
	}
	if (enemy_death_sound_flag == 1)
	{
		PlaySoundMem(enemy_death_sound, DX_PLAYTYPE_BACK);
		enemy_death_sound_flag = 0;
	}
}