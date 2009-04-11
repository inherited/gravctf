/* nade launcher projectile */

#ifndef NADE_H
#define NADE_H

#include <game/server/entity.hpp>
#include <game/generated/gs_data.hpp>
#include <game/generated/g_protocol.hpp>

#include <game/gamecore.hpp>
#include "physentity.hpp"

class projectileNade : public PHYS_ENTITY
{
	protected:
		virtual bool    _is_colliding_with_nade( );
	public:
		projectileNade( int owner_client, vec2 start_pos, vec2 direction );
		virtual void    destroy( );
		virtual void    fill_info( NETOBJ_PROJECTILE *snap_item );
		virtual void    do_explode( );
		virtual void	die( );
		virtual void    tick( );
		virtual void    snap( int snapping_client );
};

#endif
