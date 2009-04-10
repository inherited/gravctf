/* nade launcher projectile */

class projectileNade : public ENTITY
{
	private:
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
