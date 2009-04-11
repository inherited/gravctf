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

#include <math.h>

#include <base/system.h>
#include <base/math.hpp>

#include "menu.hpp"

inline float hue_to_rgb( float v1, float v2, float h )
{
	if(h < 0) 
		h += 1;
	
	if(h > 1) 
		h -= 1;
	
	if ( ( 6 * h ) < 1 ) 
		return v1 + ( v2 - v1 ) * 6 * h;
	if ( ( 2 * h ) < 1 ) 
		return v2;
	if ( ( 3 * h ) < 2 ) 
		return v1 + ( v2 - v1 ) * ((2.0f/3.0f) - h) * 6;
	
	return v1;
}

inline vec3 hsl_to_rgb( vec3 in )
{
	float v1, v2;
	vec3 out;

	if ( in.s == 0 ) {
		out.r = in.l;
		out.g = in.l;
		out.b = in.l;
	
	} else {
		v2 = ( in.l < 0.5f ) ? ( in.l * ( 1 + in.s ) ) : 
			( ( in.l + in.s ) - ( in.s * in.l ) );

		v1 = 2 * in.l - v2;

		out.r = hue_to_rgb( v1, v2, in.h + ( 1.0f / 3.0f ) );
		out.g = hue_to_rgb( v1, v2, in.h );
		out.b = hue_to_rgb( v1, v2, in.h - ( 1.0f / 3.0f ) );
	} 

	return out;
}

gameMenuComponent::gameMenuComponent( )
{
	m_blob_texture = gfx_load_texture( "blob.png", IMG_AUTO, 0 );
	
	vec3 rgb = hsl_to_rgb( vec3( 
		config.ui_color_hue / 255.0f, 
		config.ui_color_sat / 255.0f, 
		config.ui_color_lht / 255.0f ) );
	
	dbg_msg( "menu/background", "r=%f g=%f b=%f", rgb.r, rgb.g, rgb.b );
	
	m_gui_color = vec4( rgb.r, rgb.g, rgb.b, config.ui_color_alpha / 255.0f );
}

void
gameMenuComponent::render_background( )
{
	float screen_x_map = 300 * gfx_screenaspect( );
	float screen_y_map = 300;
	
	gfx_mapscreen( 0, 0, screen_x_map, screen_y_map );

	// render background color
	gfx_texture_set( -1 );
	gfx_quads_begin( );
	
	vec4 bottom( m_gui_color.r, m_gui_color.g, m_gui_color.b, 1.0f );
	vec4 top( m_gui_color.r, m_gui_color.g, m_gui_color.b, 1.0f );
	
	gfx_setcolorvertex( 0, top.r, top.g, top.b, top.a );
	gfx_setcolorvertex( 1, top.r, top.g, top.b, top.a );
	gfx_setcolorvertex( 2, bottom.r, bottom.g, bottom.b, bottom.a );
	gfx_setcolorvertex( 3, bottom.r, bottom.g, bottom.b, bottom.a );
	gfx_quads_drawTL( 0, 0, screen_x_map, screen_y_map );
		
	gfx_quads_end( );
	
	// render the tiles
	gfx_blend_normal( );
	gfx_texture_set( -1 );
	gfx_quads_begin( );
	
	float size = 15.0f;
	float offset_time = fmod( client_localtime( ) * 0.15f, 2.0f );
	
	for ( int y_index = -2; y_index < (int)( screen_x_map / size ); y_index++ ) {
		
		for ( int x_index = -2; x_index < (int)( screen_y_map / size ); x_index++) {
			gfx_setcolor( 0, 0, 0, 0.045f );
			
			gfx_quads_drawTL( ( x_index - offset_time ) * size * 2 + 
				( y_index & 1 ) * size, ( y_index + offset_time ) * size, size, size);
		}
	}
	
	gfx_quads_end( );

	//~ // render border fade
	//~ 
	gfx_texture_set( m_blob_texture );
	gfx_quads_begin( );
	
	gfx_setcolor( 0, 0, 0, 0.5f );
	gfx_quads_drawTL( -100, -100, screen_x_map + 200, screen_y_map + 200 );
	
	gfx_quads_end( );

	// gfx_mapscreen(0,0,gfx_screenwidth(),gfx_screenheight());
	// restore screen
	// RECT screen_rect = *ui_screen( );
	// gfx_mapscreen( screen_rect.x, screen_rect.y, screen_rect.w, screen_rect.h );
}