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

#include "gameclient.hpp"

gameClient game_client;

void 
gameClient::on_console_init( )
{
}

void 
gameClient::on_save( )
{
}

void 
gameClient::on_init( )
{
}

void 
gameClient::on_connected( )
{
}

void 
gameClient::on_predict( )
{
}

void 
gameClient::on_snapshot( )
{
}

int 
gameClient::on_snapinput( int *data )
{
}

void 
gameClient::on_statechange( int state, int old )
{
}

void 
gameClient::on_render( )
{
}

void 
gameClient::on_message( int msgtype )
{
}

void 
gameClient::modc_rcon_line( const char *line )
{
}
