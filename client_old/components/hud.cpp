#include <memory.h> // memcmp

#include <engine/e_client_interface.h>
#include <game/generated/g_protocol.hpp>
#include <game/generated/gc_data.hpp>

#include <game/layers.hpp>

#include <game/client/gameclient.hpp>
#include <game/client/animstate.hpp>
#include <game/client/render.hpp>

#include "controls.hpp"
#include "camera.hpp"
#include "hud.hpp"
#include "binds.hpp"

HUD::HUD()
{
	
}
	
void HUD::on_reset()
{
}

static void mapscreen_to_group(float center_x, float center_y, MAPITEM_GROUP *group)
{
	float points[4];
	mapscreen_to_world(center_x, center_y, group->parallax_x/100.0f, group->parallax_y/100.0f,
		group->offset_x, group->offset_y, gfx_screenaspect(), 1.0f, points);
	gfx_mapscreen(points[0], points[1], points[2], points[3]);
}

void HUD::render_fps()
{
	if(config.cl_showfps)
	{
		char buf[512];
		str_format(buf, sizeof(buf), "%d", (int)(1.0f/client_frametime()));
		gfx_text(0, width-10-gfx_text_width(0,12,buf,-1), 5, 12, buf, -1);
	}
}

void HUD::render_connectionwarning()
{
	if(client_connection_problems())
	{
		const char *text = "Connection Problems...";
		float w = gfx_text_width(0, 24, text, -1);
		gfx_text(0, 150*gfx_screenaspect()-w/2, 50, 24, text, -1);
	}
}

void HUD::render_cursor()
{
	if(!gameclient.snap.local_character)
		return;
		
	mapscreen_to_group(gameclient.camera->center.x, gameclient.camera->center.y, layers_game_group());
	gfx_texture_set(data->images[IMAGE_GAME].id);
	gfx_quads_begin();

	// render cursor
	select_sprite(data->weapons.id[gameclient.snap.local_character->weapon%NUM_WEAPONS].sprite_cursor);
	float cursorsize = 64;
	draw_sprite(gameclient.controls->target_pos.x, gameclient.controls->target_pos.y, cursorsize);
	gfx_quads_end();
}

void HUD::render_healthandammo()
{
	//mapscreen_to_group(gacenter_x, center_y, layers_game_group());

	float x = 5;
	float y = 5;

	// render ammo count
	// render gui stuff

	gfx_texture_set(data->images[IMAGE_GAME].id);
	gfx_mapscreen(0,0,width,300);
	
	gfx_quads_begin();
	
	// if weaponstage is active, put a "glow" around the stage ammo
	select_sprite(data->weapons.id[gameclient.snap.local_character->weapon%NUM_WEAPONS].sprite_proj);
	for (int i = 0; i < min(gameclient.snap.local_character->ammocount, 10); i++)
		gfx_quads_drawTL(x+i*12,y+24,10,10);

	gfx_quads_end();

	gfx_quads_begin();
	int h = 0;

	// render health
	select_sprite(SPRITE_HEALTH_FULL);
	for(; h < gameclient.snap.local_character->health; h++)
		gfx_quads_drawTL(x+h*12,y,10,10);

	select_sprite(SPRITE_HEALTH_EMPTY);
	for(; h < 10; h++)
		gfx_quads_drawTL(x+h*12,y,10,10);

	// render armor meter
	h = 0;
	select_sprite(SPRITE_ARMOR_FULL);
	for(; h < gameclient.snap.local_character->armor; h++)
		gfx_quads_drawTL(x+h*12,y+12,10,10);

	select_sprite(SPRITE_ARMOR_EMPTY);
	for(; h < 10; h++)
		gfx_quads_drawTL(x+h*12,y+12,10,10);
	gfx_quads_end();
}

void HUD::on_render()
{
	width = 300 * gfx_screenaspect( );
	
	if ( gameclient.snap.local_character )
		render_healthandammo( );

	render_fps( );
	if ( client_state( ) != CLIENTSTATE_DEMOPLAYBACK )
		render_connectionwarning( );
	render_cursor( );
}
