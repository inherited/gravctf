/*
 *      This program is free software; you can redistribute it and/or modify
 *      it under the terms of the GNU General Public License as published by
 *      the Free Software Foundation; either version 2 of the License, or
 *      (at your option) any later version.
 *      
 *      This program is distributed in the hope that it will be useful,
 *      but WITHOUT ANY WARRANTY; without even the implied warranty of
 *      MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *      GNU General Public License for more details.
 *      
 *      You should have received a copy of the GNU General Public License
 *      along with this program; if not, write to the Free Software
 *      Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 *      MA 02110-1301, USA.
 */

#include <engine/e_client_interface.h>

#include <game/version.hpp>
#include <game/generated/g_protocol.hpp>

#include "gameclient.hpp"

/*
	Function: modc_entergame
		Called when the client has successfully connect to a server and
		loaded a map.
	
	Remarks:
		The client can check for items in the map and load them.
*/
extern "C" void modc_entergame( ) 
{
}

/*
	Function: modc_shutdown
		Called when the client closes down.
*/
extern "C" void modc_shutdown( ) 
{
}

/*
	Function: modc_console_init
		TODO
*/
extern "C" void modc_console_init( )
{ 
	game_client.on_console_init( ); 
}

/*
	Function: modc_save_config
		TODO
*/
extern "C" void modc_save_config( ) 
{ 
	game_client.on_save( );
}

/*
	Function: modc_init
		Called when the client starts.
	
	Remarks:
		The game should load resources that are used during the entire
		time of the game. No map is loaded.
*/
extern "C" void modc_init( ) 
{
	game_client.on_init( ); 
}

/*
	Function: modc_connected
		TODO
*/
extern "C" void modc_connected( ) 
{
	game_client.on_connected( ); 
}

/*
	Function: modc_predict
		TODO
*/
extern "C" void modc_predict( ) 
{ 
	game_client.on_predict( ); 
}

/*
	Function: modc_newsnapshot
		Called when the client progressed to a new snapshot.
	
	Remarks:
		The client can check for items in the snapshot and perform one time
		events like playing sounds, spawning client side effects etc.
*/
extern "C" void modc_newsnapshot( ) 
{ 
	game_client.on_snapshot( ); 
}

/*
	Function: modc_snap_input
		TODO
*/
extern "C" int modc_snap_input( int *data ) 
{
	return game_client.on_snapinput( data ); 
}

/*
	Function: modc_statechange
		Called every time client changes state.
*/
extern "C" void modc_statechange( int state, int old ) 
{ 
	game_client.on_statechange( state, old ); 
}

/*
	Function: modc_render
		Called every frame to let the game render it self.
*/
extern "C" void modc_render( ) 
{
	game_client.on_render( ); 
}

/*
	Function: modc_message
		TODO
*/
extern "C" void modc_message( int msgtype ) 
{ 
	game_client.on_message( msgtype ); 
}

/*
	Function: modc_rcon_line
		TODO
*/
extern "C" void modc_rcon_line( const char *line ) 
{ 
	// game_client.console->print_line( 1, line ); 
}

extern "C" const char *modc_net_version( ) 
{ 
	return GAME_NETVERSION; 
}

extern "C" const char *modc_getitemname( int type ) 
{ 
	return netobj_get_name( type ); 
}

