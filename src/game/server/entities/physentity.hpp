/* nade launcher projectile */

#ifndef PHYSENTITY_H
#define PHYSENTITY_H

#include <game/server/entity.hpp>
#include <game/generated/gs_data.hpp>
#include <game/generated/g_protocol.hpp>

#include <game/gamecore.hpp>

class PHYS_ENTITY : public ENTITY
{
	protected:
		int     m_owner_client;
		int     m_start_tick;
		vec2    m_velocity;
		
		//virtual bool    _is_colliding_with_characters( );
	
	public:
		vec2    m_position;
		bool	attracted;
		bool	collide;
	
		PHYS_ENTITY( int owner_client, vec2 start_pos, vec2 direction );
		
		virtual PHYS_ENTITY *colliding_with_entity( );
		virtual CHARACTER *colliding_with_character( );
		
		virtual void	die( );
		virtual void    fill_info( NETOBJ_PROJECTILE *snap_item );
		
		
		virtual void    tick( );
		virtual void    destroy( );
		virtual void    snap( int snapping_client );
};

#endif
