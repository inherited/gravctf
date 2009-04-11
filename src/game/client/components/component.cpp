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

#include <base/system.h>

#include "component.hpp"

void 
gameComponent::on_statechange( int new_state, int old_state )
{
	dbg_msg( "client/component", 
		"STUB on_statechange should be overwriten!" );
}

void 
gameComponent::on_console_init( )
{
	dbg_msg( "client/component", 
		"STUB on_console_init should be overwriten!" );
}

void 
gameComponent::on_init( )
{
	dbg_msg( "client/component", 
		"STUB on_init should be overwriten!" );
}

void 
gameComponent::on_save( )
{
	dbg_msg( "client/component", 
		"STUB on_save should be overwriten!" );
}

void 
gameComponent::on_reset( )
{
	dbg_msg( "client/component", 
		"STUB on_reset should be overwriten!" );
}

void 
gameComponent::on_render( )
{
	dbg_msg( "client/component", 
		"STUB on_render should be overwriten!" );
}

void 
gameComponent::on_mapload( )
{
	dbg_msg( "client/component", 
		"STUB on_mapload should be overwriten!" );
}

bool 
gameComponent::on_message( int msg, void *rawmsg )
{
	dbg_msg( "client/component", 
		"STUB on_message should be overwriten!" );
	
	return false;
}

bool 
gameComponent::on_mousemove( float x_pos, float y_pos )
{
	dbg_msg( "client/component", 
		"STUB on_mousemove should be overwriten!" );
	
	return false;
}

bool 
gameComponent::on_input( INPUT_EVENT new_input )
{
	dbg_msg( "client/component", 
		"STUB on_input should be overwriten!" );
	
	return false;
}
