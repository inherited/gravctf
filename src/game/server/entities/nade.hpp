/* nade launcher projectile */

class projectileNade : public ENTITY
{
	private:
		int     m_owner_client;
		int     m_start_tick;
		vec2    m_velocity;
		
		bool    _is_colliding_with_other_nades( );
		bool    _is_colliding_with_characters( );
	
	public:
		vec2    m_position;
	
		projectileNade( int owner_client, vec2 start_pos, vec2 direction );
		
		void    fill_info( NETOBJ_PROJECTILE *snap_item );
		void    do_explode( );
		
		void    tick( );
		void    destroy( );
		void    snap( int snapping_client );
};