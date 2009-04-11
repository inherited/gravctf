
#include <base/math.hpp>

#include <string.h> // strcmp, strlen, strncpy
#include <stdlib.h> // atoi

#include <engine/e_client_interface.h>

#include <game/generated/g_protocol.hpp>
#include <game/generated/gc_data.hpp>

#include <game/client/ui.hpp>
#include <game/client/gameclient.hpp>
#include <game/client/animstate.hpp>

#include "menus.hpp"
#include "motd.hpp"

void MENUS::render_game(RECT main_view)
{
	RECT button;
	//RECT votearea;
	ui_hsplit_t(&main_view, 45.0f, &main_view, 0);
	ui_draw_rect(&main_view, color_tabbar_active, CORNER_ALL, 10.0f);

	ui_hsplit_t(&main_view, 10.0f, 0, &main_view);
	ui_hsplit_t(&main_view, 25.0f, &main_view, 0);
	ui_vmargin(&main_view, 10.0f, &main_view);
	
	ui_vsplit_r(&main_view, 120.0f, &main_view, &button);
	static int disconnect_button = 0;
	
	if(ui_do_button(&disconnect_button, "Disconnect", 0, &button, ui_draw_menu_button, 0))
		client_disconnect();
}

void MENUS::render_serverinfo(RECT main_view)
{
	// fetch server info
	SERVER_INFO current_server_info;
	client_serverinfo(&current_server_info);
	
	if(!gameclient.snap.local_info)
		return;
	
	// count players for server info-box
	int num_players = 0;
	for(int i = 0; i < snap_num_items(SNAP_CURRENT); i++)
	{
		SNAP_ITEM item;
		snap_get_item(SNAP_CURRENT, i, &item);

		if(item.type == NETOBJTYPE_PLAYER_INFO)
		{
			num_players++;
		}
	}

	// render background
	ui_draw_rect(&main_view, color_tabbar_active, CORNER_ALL, 10.0f);
	
	RECT view, serverinfo, gameinfo, motd;
	
	float x = 0.0f;
	float y = 0.0f;
	
	char buf[1024];
	
	// set view to use for all sub-modules
	ui_margin(&main_view, 10.0f, &view);
	
	/* serverinfo */
	ui_hsplit_t(&view, view.h/2-5.0f, &serverinfo, &motd);
	ui_vsplit_l(&serverinfo, view.w/2-5.0f, &serverinfo, &gameinfo);
	ui_draw_rect(&serverinfo, vec4(1,1,1,0.25f), CORNER_ALL, 10.0f);
	
	ui_margin(&serverinfo, 5.0f, &serverinfo);
	
	x = 5.0f;
	y = 0.0f;
	
	gfx_text(0, serverinfo.x+x, serverinfo.y+y, 32, "Server info", 250);
	y += 32.0f+5.0f;
	
	mem_zero(buf, sizeof(buf));
	str_format(
		buf,
		sizeof(buf),
		"%s\n\n"
		"Address: %s\n"
		"Ping: %d\n"
		"Version: %s\n"
		"Password: %s\n",
		current_server_info.name,
		config.ui_server_address,
		gameclient.snap.local_info->latency,
		current_server_info.version,
		current_server_info.flags&1 ? "Yes" : "No"
	);
	
	gfx_text(0, serverinfo.x+x, serverinfo.y+y, 20, buf, 250);
	
	{
		RECT button;
		int is_favorite = client_serverbrowse_isfavorite(current_server_info.netaddr);
		ui_hsplit_b(&serverinfo, 20.0f, &serverinfo, &button);
		static int add_fav_button = 0;
		if (ui_do_button(&add_fav_button, "Favorite", is_favorite, &button, ui_draw_checkbox, 0))
		{
			if(is_favorite)
				client_serverbrowse_removefavorite(current_server_info.netaddr);
			else
				client_serverbrowse_addfavorite(current_server_info.netaddr);
		}
	}
	
	/* gameinfo */
	ui_vsplit_l(&gameinfo, 10.0f, 0x0, &gameinfo);
	ui_draw_rect(&gameinfo, vec4(1,1,1,0.25f), CORNER_ALL, 10.0f);
	
	ui_margin(&gameinfo, 5.0f, &gameinfo);
	
	x = 5.0f;
	y = 0.0f;
	
	gfx_text(0, gameinfo.x+x, gameinfo.y+y, 32, "Game info", 250);
	y += 32.0f+5.0f;
	
	/* motd */
	ui_hsplit_t(&motd, 10.0f, 0, &motd);
	ui_draw_rect(&motd, vec4(1,1,1,0.25f), CORNER_ALL, 10.0f);
	ui_margin(&motd, 5.0f, &motd);
	y = 0.0f;
	x = 5.0f;
	gfx_text(0, motd.x+x, motd.y+y, 32, "MOTD", -1);
	y += 32.0f+5.0f;
	gfx_text(0, motd.x+x, motd.y+y, 16, gameclient.motd->server_motd, (int)motd.w);
}
