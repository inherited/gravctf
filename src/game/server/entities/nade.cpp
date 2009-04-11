/* nade launcher projectile */

#include <list>

#include <base/vmath.hpp>

#include <engine/e_config.h>
#include <engine/e_server_interface.h>

#include <game/layers.hpp>
#include <game/server/gamemodes/ctf.hpp>
#include <game/server/gamecontext.hpp>
#include <game/generated/g_protocol.hpp>
#include "physentity.hpp"

#include "nade.hpp"

//list<char> charList;
std::list<projectileNade *> nade_list;

projectileNade::projectileNade( int owner_client, vec2 start_pos, vec2 direction )
	: PHYS_ENTITY( owner_client, start_pos, direction )
{
	//PHYS_ENTITY::PHYS_ENTITY(owner_client, start_pos, direction);
	
	nade_list.push_front( this );
}


void projectileNade::destroy( )
{
	nade_list.remove( this );
	PHYS_ENTITY::destroy( );
}

bool projectileNade::_is_colliding_with_nade( )
{
	std::list<projectileNade *>::iterator iter;
	bool is_collided = false;
	
	for ( iter = nade_list.begin( ); iter != nade_list.end( ); ++iter ) {
		if ( *iter == this ) 
			continue;
		
		if ( distance( m_position, (*iter)->m_position ) <= proximity_radius ) { //TODO: raus hier, nade klasse
			if ( config.sv_smod_nade_collide_with_other )
				(*iter)->die( );
			
			is_collided = true;
		}
	}
	
	return is_collided;
}

void projectileNade::die( ) {
	do_explode();
	PHYS_ENTITY::die( );
}

void projectileNade::do_explode( ) 
{
	game.create_explosion( m_position, 
		m_owner_client, WEAPON_GRENADE, false );
	game.create_sound( m_position, SOUND_GRENADE_EXPLODE );
}

void projectileNade::tick( )
{
	PHYS_ENTITY::tick( );
	
	if ( config.sv_smod_nade_collide_with_other ) {
		if( _is_colliding_with_nade() ) 
			die( );
	}
	
	if ( config.sv_smod_nade_collide_with_player && colliding_with_character( ) )
		die( );
}

void projectileNade::fill_info( NETOBJ_PROJECTILE *snap_item )
{
	PHYS_ENTITY::fill_info(snap_item);
	
	snap_item->vx = 0;
	snap_item->vy = 0;
	snap_item->type = WEAPON_GRENADE;
}


