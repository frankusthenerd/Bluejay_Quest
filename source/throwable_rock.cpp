#include <allegro.h>
#include "throwable_rock.hpp"
#include "application.hpp"
#include "level.hpp"

Throwable_Rock::Throwable_Rock()
{

    id = Level::THROWABLE_ROCK;
    bitmap = Application::THROWABLE_ROCK_BM;
    number_of_areas = 1;
    strength = 1;
    released = false;
    can_hurt = false;

}

void Throwable_Rock::Process(Application& app,
                             Level& level)
{

    if (Is_On_Screen(level.x, level.y, app))
    {
    
        if (released)
        {
        
            x += (x_direction*4);
            y += (y_direction*4);
        
        }
        
        draw_sprite(app.canvas, app.bitmaps[bitmap], (x-level.x), (y-level.y));
    
    }

}
