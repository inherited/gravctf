#include <game/client/component.hpp>

class HUD : public COMPONENT
{	
	float width;
	
	void render_cursor();
	
	void render_fps();
	void render_connectionwarning();
	void render_healthandammo();
	
public:
	HUD();
	
	virtual void on_reset();
	virtual void on_render();
};

