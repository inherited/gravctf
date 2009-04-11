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

#include "modes.hpp"

#include <base/system.h>

void 
gameMode::on_statechange( int new_state, int old_state )
{
	std::list<gameComponent *>::iterator iter;
	
	for ( iter = mode_components.begin( ); iter != mode_components.end( ); ++iter )
		(*iter)->on_statechange( new_state, old_state );
}

void 
gameMode::on_console_init( )
{
	std::list<gameComponent *>::iterator iter;
	
	for ( iter = mode_components.begin( ); iter != mode_components.end( ); ++iter )
		(*iter)->on_console_init( );
}

void 
gameMode::on_init( )
{
	std::list<gameComponent *>::iterator iter;
	
	for ( iter = mode_components.begin( ); iter != mode_components.end( ); ++iter )
		(*iter)->on_init( );
}

void 
gameMode::on_save( )
{
	std::list<gameComponent *>::iterator iter;
	
	for ( iter = mode_components.begin( ); iter != mode_components.end( ); ++iter )
		(*iter)->on_save( );
}

void 
gameMode::on_reset( )
{
	std::list<gameComponent *>::iterator iter;
	
	for ( iter = mode_components.begin( ); iter != mode_components.end( ); ++iter )
		(*iter)->on_reset( );
}

void 
gameMode::on_render( )
{
	std::list<gameComponent *>::iterator iter;
	
	for ( iter = mode_components.begin( ); iter != mode_components.end( ); ++iter )
		(*iter)->on_render( );
}

void 
gameMode::on_mapload( )
{
	std::list<gameComponent *>::iterator iter;
	
	for ( iter = mode_components.begin( ); iter != mode_components.end( ); ++iter )
		(*iter)->on_mapload( );
}

void 
gameMode::on_message( int msg, void *rawmsg )
{
	std::list<gameComponent *>::iterator iter;
	
	for ( iter = mode_components.begin( ); iter != mode_components.end( ); ++iter ) {
		if ( (*iter)->on_message( msg, rawmsg ) )
			break;
	}
}

void 
gameMode::on_mousemove( float x_pos, float y_pos )
{
	std::list<gameComponent *>::iterator iter;
	
	for ( iter = mode_components.begin( ); iter != mode_components.end( ); ++iter ) {
		if ( (*iter)->on_mousemove( x_pos, y_pos ) )
			break;
	}
}

void 
gameMode::on_input( INPUT_EVENT new_input )
{
	std::list<gameComponent *>::iterator iter;
	
	for ( iter = mode_components.begin( ); iter != mode_components.end( ); ++iter ) {
		if ( (*iter)->on_input( new_input ) )
			break;
	}
}
