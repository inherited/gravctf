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

class gameComponent
{
	
	public:
		virtual void    on_statechange( int new_state, int old_state );
		virtual void    on_console_init( );
		virtual void    on_init( );
		virtual void    on_save( );
		virtual void    on_reset( );
		virtual void    on_render( );
		virtual void    on_mapload( );
		virtual bool    on_message( int msg, void *rawmsg );
		virtual bool    on_mousemove( float x_pos, float y_pos );
		virtual bool    on_input( INPUT_EVENT new_input );
};
