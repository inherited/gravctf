/* nade launcher projectile */

#include <list>

#include <base/vmath.hpp>

#include <engine/e_config.h>
#include <engine/e_server_interface.h>

#include <game/layers.hpp>
#include <game/server/gamemodes/ctf.hpp>
#include <game/server/gamecontext.hpp>
#include <game/generated/g_protocol.hpp>

#include "nade.hpp"

//list<char> charList;
std::list<projectileNade *> nade_list;

projectileNade::projectileNade( int owner_client, vec2 start_pos, vec2 direction )
	: ENTITY( NETOBJ_INVALID )
{
	m_position     = start_pos;
	m_start_tick   = server_tick( );
	m_owner_client = owner_client;
	m_velocity     = direction * 10.0f;
	
	game.world.insert_entity( this );
	nade_list.push_front( this );
}

void projectileNade::destroy( )
{
	nade_list.remove( this );
	delete this;
}

void projectileNade::do_explode( ) 
{
	game.create_explosion( m_position, 
		m_owner_client, WEAPON_GRENADE, false );
	game.create_sound( m_position, SOUND_GRENADE_EXPLODE );
	
	game.world.destroy_entity( this );
}

bool projectileNade::_is_colliding_with_characters( )
{
	CHARACTER *chr = (CHARACTER *)game.world.find_first( NETOBJTYPE_CHARACTER );
	
	for ( ; chr; chr = (CHARACTER *)chr->typenext( ) ) {
		float dist = distance( m_position, chr->pos );
		
		if ( distance( m_position, chr->pos ) < CHARACTER::phys_size ) {
			if ( config.sv_smod_nade_collide_with_player )
				chr->take_damage( vec2( 0.0f, 0.0f ), 1, m_owner_client, WEAPON_GRENADE );
			
			return true;
		}
	}
	
	return false;
}

bool projectileNade::_is_colliding_with_other_nades( )
{
	std::list<projectileNade *>::iterator iter;
	bool is_collided = false;
	
	for ( iter = nade_list.begin( ); iter != nade_list.end( ); ++iter ) {
		if ( *iter == this ) 
			continue;
		
		if ( distance( m_position, (*iter)->m_position ) < 30.0f ) {
			if ( config.sv_smod_nade_collide_with_other )
				(*iter)->do_explode( );
			
			is_collided = true;
		}
	}
	
	return is_collided;
}

void projectileNade::tick( )
{
	if((config.sv_spacemode > 0) && (config.sv_spacemode < 3)) {
		if(pos.x < layers_game_layer()->width*28 / 2) {
			m_velocity.x += config.sv_gravx / 100.0;
			
		} else {
			m_velocity.x -= config.sv_gravx / 100.0;
		}
		
		if(config.sv_spacemode == 2) {
			if(pos.y < layers_game_layer()->height*28 / 2) {
				m_velocity.y += config.sv_gravy / 100.0;
				
			} else {
				m_velocity.y -= config.sv_gravy / 100.0;
			}
			
		} else {
			m_velocity.y += config.sv_gravy / 100.0;
		}
		
	} else if(config.sv_spacemode == 3) {

	} else {
		m_velocity.x += ((GAMECONTROLLER_CTF*)game.controller)->gravity_x( m_position );
		m_velocity.y += ((GAMECONTROLLER_CTF*)game.controller)->gravity_y( m_position );	
	}
	
	if ( config.sv_smod_nade_collide_with_solid ) {
		if ( col_intersect_line( m_position, m_position + m_velocity, &m_position, NULL ) )
			return do_explode( );
		
	} else 
		m_position = m_position + m_velocity;
	
	if ( config.sv_smod_nade_collide_with_other && _is_colliding_with_other_nades( ) )
		return do_explode( );
	
	if ( config.sv_smod_nade_collide_with_player && _is_colliding_with_characters( ) )
		return do_explode( );
}

void projectileNade::fill_info( NETOBJ_PROJECTILE *snap_item )
{
	snap_item->x = roundf( m_position.x );
	snap_item->y = roundf( m_position.y );
	
	snap_item->vx = 0;
	snap_item->vy = 0;
	
	snap_item->type = WEAPON_GRENADE;
	snap_item->start_tick = m_start_tick;
}

void projectileNade::snap( int snapping_client )
{
	NETOBJ_PROJECTILE *snap_item = (NETOBJ_PROJECTILE *)snap_new_item( 
		NETOBJTYPE_PROJECTILE, id, sizeof( NETOBJ_PROJECTILE ) );
	
	fill_info( snap_item );
}
