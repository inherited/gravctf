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

#include <list>

#include "game_modes/menu.hpp"

class gameClient
{
	private:
		gameMenuComponent *blar;
	
	public:
		
		/* Events der Engine */
		void    on_console_init( );
		void    on_save( );
		void    on_init( ); 
		void    on_connected( );
		void    on_predict( );
		void    on_snapshot( );
		int     on_snapinput( int *data );
		void    on_statechange( int state, int old );
		void    on_render( );
		void    on_message( int msgtype );
		void    modc_rcon_line( const char *line );
};

extern gameClient game_client;