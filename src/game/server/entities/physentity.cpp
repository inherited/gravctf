/* nade launcher projectile */

#include <list>

#include <base/vmath.hpp>

#include <engine/e_config.h>
#include <engine/e_server_interface.h>

#include <game/layers.hpp>
#include <game/server/gamecontroller.hpp>
#include <game/server/gamecontext.hpp>
#include <game/generated/g_protocol.hpp>

#include "physentity.hpp"

//list<char> charList;
std::list<PHYS_ENTITY *> entity_list;

PHYS_ENTITY::PHYS_ENTITY( int owner_client, vec2 start_pos, vec2 direction )
	: ENTITY( NETOBJ_INVALID )
{
	m_position     = start_pos;
	m_start_tick   = server_tick( );
	m_owner_client = owner_client;
	m_velocity     = direction * 10.0f;
	attracted      = true;
	
	game.world.insert_entity( this );
	entity_list.push_front( this );
}

void PHYS_ENTITY::destroy( )
{
	entity_list.remove( this );
	delete this;
}

/* bool PHYS_ENTITY::_is_colliding_with_characters( )
{
	CHARACTER *chr = (CHARACTER *)game.world.find_first( NETOBJTYPE_CHARACTER );
	
	for ( ; chr; chr = (CHARACTER *)chr->typenext( ) ) {
		float dist = distance( m_position, chr->pos );
		
		if ( distance( m_position, chr->pos ) < CHARACTER::phys_size ) {
			if ( config.sv_smod_nade_collide_with_player ) //TODO: raus hier, inj grenade klasse
				chr->take_damage( vec2( 0.0f, 0.0f ), 1, m_owner_client, WEAPON_GRENADE );
			
			return true;
		}
	}
	
	return false;
}

 */

PHYS_ENTITY *PHYS_ENTITY::colliding_with_entity( )
{
	std::list<PHYS_ENTITY *>::iterator iter;
	
	for ( iter = entity_list.begin( ); iter != entity_list.end( ); ++iter ) {
		if ( *iter == this ) 
			continue;
		if ( distance( m_position, (*iter)->m_position ) < proximity_radius ) {
			return (*iter);
		}
	}
	return 0;
}

CHARACTER *PHYS_ENTITY::colliding_with_character( )
{
	CHARACTER *chr = (CHARACTER *)game.world.find_first( NETOBJTYPE_CHARACTER );
	
	for ( ; chr; chr = (CHARACTER *)chr->typenext( ) ) {
		//float dist = distance( m_position, chr->pos );
		
		if ( distance( m_position, chr->pos ) < CHARACTER::phys_size ) {
			return chr;
		}
	}
	
	return 0;
}

void PHYS_ENTITY::die( )
{
	game.world.destroy_entity( this );
	delete this;
}

void PHYS_ENTITY::tick( )
{
	if(attracted) {
		m_velocity.x += game.controller->gravity_x( m_position );
		m_velocity.y += game.controller->gravity_y( m_position );	
	}
	
	
	if ( collide ) {
		if ( col_intersect_line( m_position, m_position + m_velocity, &m_position, NULL ) )
			die( );
		
	}
	m_position = m_position + m_velocity;
}

void PHYS_ENTITY::fill_info( NETOBJ_PROJECTILE *snap_item )
{
	snap_item->x = roundf( m_position.x );
	snap_item->y = roundf( m_position.y );
	
	snap_item->vx = m_velocity.x;
	snap_item->vy = m_velocity.y;
	
	snap_item->type = WEAPON_WORLD;
	snap_item->start_tick = m_start_tick;
}

void PHYS_ENTITY::snap( int snapping_client )
{
	NETOBJ_PROJECTILE *snap_item = (NETOBJ_PROJECTILE *)snap_new_item( 
		NETOBJTYPE_PROJECTILE, id, sizeof( NETOBJ_PROJECTILE ) );
	
	fill_info( snap_item );
}
