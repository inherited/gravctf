#include <game/client/component.hpp>

class SCOREBOARD : public COMPONENT
{
	private:
		bool        m_active;
		
		void        render_scoreboard( float x, float y, float w );
		static void con_key_scoreboard(void *result, void *user_data);
		
	public:
		SCOREBOARD( );
		
		virtual void on_reset();
		virtual void on_console_init();
		virtual void on_render();
};

