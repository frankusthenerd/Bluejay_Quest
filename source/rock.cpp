#include <allegro.h>
#include "rock.hpp"
#include "application.hpp"
#include "level.hpp"

Rock::Rock()
{

    id = Level::ROCK;
    bitmap = Application::ROCK_BM;
    number_of_areas = 1;
    strength = 1;
    angle = 0;
    local = false;

}

void Rock::Process(Application& app,
                   Level& level)
{

    bool can_process;
    
    if (local)
    {
    
        can_process = Is_On_Screen(level.x, level.y, app);
    
    }
    else
    {
    
        can_process = Is_On_X_Screen(level.x, level.y, app);
    
    }

    if (can_process)
    {

        timer++;
    
        if ((timer%2) == 0)
        {
    
            y += 4;
            
        }
        
        angle += 16;
        angle &= 0xFF;
        rotate_sprite(app.canvas, app.bitmaps[bitmap], (x-level.x),
                      (y-level.y), itofix(angle));
    
    }
    
}
