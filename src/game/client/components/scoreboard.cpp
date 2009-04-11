#include <string.h>
#include <engine/e_client_interface.h>
#include <game/generated/g_protocol.hpp>
#include <game/generated/gc_data.hpp>
#include <game/client/gameclient.hpp>
#include <game/client/animstate.hpp>
#include <game/client/render.hpp>
#include <game/client/components/motd.hpp>
#include "scoreboard.hpp"


SCOREBOARD::SCOREBOARD()
{
	on_reset();
}

void SCOREBOARD::con_key_scoreboard( void *result, void *user_data )
{
	((SCOREBOARD *)user_data)->m_active = console_arg_int(result, 0) != 0;
}

void SCOREBOARD::on_reset( )
{
	m_active = false;
}

void SCOREBOARD::on_console_init()
{
	MACRO_REGISTER_COMMAND( "+scoreboard", "", 
		CFGFLAG_CLIENT, con_key_scoreboard, this, "Show scoreboard" );
}

void SCOREBOARD::render_scoreboard( float x, float y, float w )
{
	//float ystart = y;
	float h = 750.0f;

	gfx_blend_normal();
	gfx_texture_set(-1);
	gfx_quads_begin();
	gfx_setcolor(0,0,0,0.5f);
	draw_round_rect(x-10.f, y-10.f, w, h, 17.0f);
	gfx_quads_end();

	// find players
	const NETOBJ_PLAYER_INFO *players[MAX_CLIENTS] = {0};
	int num_players = 0;
	for(int i = 0; i < snap_num_items(SNAP_CURRENT); i++)
	{
		SNAP_ITEM item;
		const void *data = snap_get_item(SNAP_CURRENT, i, &item);

		if(item.type == NETOBJTYPE_PLAYER_INFO) {
			players[num_players++] = (const NETOBJ_PLAYER_INFO *)data;
		}
	}

	// sort players
	for(int k = 0; k < num_players; k++) // ffs, bubblesort
	{
		for(int i = 0; i < num_players-k-1; i++)
		{
			if(players[i]->score < players[i+1]->score)
			{
				const NETOBJ_PLAYER_INFO *tmp = players[i];
				players[i] = players[i+1];
				players[i+1] = tmp;
			}
		}
	}

	// render headlines
	gfx_text(0, x+10  , y, 24.0f, "Score", -1);
	gfx_text(0, x+125 , y, 24.0f, "Name", -1);
	gfx_text(0, x+w-70, y, 24.0f, "Ping", -1);
	y += 29.0f;

	float font_size = 35.0f;
	float line_height = 50.0f;
	float tee_sizemod = 1.0f;
	float tee_offset = 0.0f;
	
	if(num_players > 13)
	{
		font_size = 30.0f;
		line_height = 40.0f;
		tee_sizemod = 0.8f;
		tee_offset = -5.0f;
	}
	
	// render player scores
	for(int i = 0; i < num_players; i++)
	{
		const NETOBJ_PLAYER_INFO *info = players[i];

		// make sure that we render the correct team

		char buf[128];
		if(info->local)
		{
			// background so it's easy to find the local player
			gfx_texture_set(-1);
			gfx_quads_begin();
			gfx_setcolor(1,1,1,0.25f);
			draw_round_rect(x, y, w-20, line_height*0.95f, 17.0f);
			gfx_quads_end();
		}

		str_format(buf, sizeof(buf), "%4d", info->score);
		gfx_text(0, x+60-gfx_text_width(0, font_size,buf,-1), y, font_size, buf, -1);
		
		gfx_text(0, x+128, y, font_size, gameclient.clients[info->cid].name, -1);

		str_format(buf, sizeof(buf), "%4d", info->latency);
		float tw = gfx_text_width(0, font_size, buf, -1);
		gfx_text(0, x+w-tw-35, y, font_size, buf, -1);

		// render avatar
		TEE_RENDER_INFO teeinfo = gameclient.clients[info->cid].render_info;
		teeinfo.size *= tee_sizemod;
		render_tee(ANIMSTATE::get_idle(), &teeinfo, EMOTE_NORMAL, vec2(1,0), vec2(x+90, y+28+tee_offset));

		
		y += line_height;
	}
}

void SCOREBOARD::on_render()
{
	if ( !m_active ) 
		return;
	else
		gameclient.motd->clear();
	
	float x_size = 400.0f * 3.0f * gfx_screenaspect( );
	float y_size = 400.0f * 3.0f;
	
	gfx_mapscreen( 0, 0, x_size, y_size );

	render_scoreboard( x_size - 520.0f, 150.0f, 500.0f );
}
