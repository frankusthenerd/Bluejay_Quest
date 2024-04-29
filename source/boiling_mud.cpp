#include <allegro.h>
#include "boiling_mud.hpp"
#include "application.hpp"
#include "level.hpp"

Boiling_Mud::Boiling_Mud()
{

    id = Level::BOILING_MUD;
    bitmap = Application::BOILING_MUD_BM;
    number_of_areas = 1;
    strength = 1;
    flip = false;

}

void Boiling_Mud::Process(Application& app,
                          Level& level)
{

    if (Is_On_Screen(level.x, level.y, app))
    {
    
        timer++;
        
        if ((timer%4) == 0)
        {
        
            flip = !flip;
        
        }
        
        if (flip)
        {
        
            draw_sprite_h_flip(app.canvas, app.bitmaps[bitmap], (x-level.x), (y-level.y));
        
        }
        else
        {
        
            draw_sprite(app.canvas, app.bitmaps[bitmap], (x-level.x), (y-level.y));
        
        }
    
    }

}
