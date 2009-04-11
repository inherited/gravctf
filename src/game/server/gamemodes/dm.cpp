/* copyright (c) 2007 magnus auvinen, see licence.txt for more info */
#include "dm.hpp"


GAMECONTROLLER_DM::GAMECONTROLLER_DM()
{
	gametype = "gravDM";
	gravtiles = 0;
}

void GAMECONTROLLER_DM::tick()
{
	do_player_score_wincheck();
	GAMECONTROLLER::tick();
}

