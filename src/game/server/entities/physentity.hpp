/* nade launcher projectile */

class PHYS_ENTITY : public ENTITY
{
	private:
		int     m_owner_client;
		int     m_start_tick;
		vec2    m_velocity;
		

		virtual PHYS_ENTITY _colliding_with_entity( );
		virtual CHARACTER _colliding_with_character( );
		//virtual bool    _is_colliding_with_characters( );
	
	public:
		vec2    m_position;
		bool	attracted;
		bool	collide;
	
		PHYS_ENTITY( int owner_client, vec2 start_pos, vec2 direction );
		
		virtual void	die( );
		virtual void    fill_info( NETOBJ_PROJECTILE *snap_item );
		
		
		virtual void    tick( );
		virtual void    destroy( );
		virtual void    snap( int snapping_client );
};
