#include <allegro.h>
#include "mud_drop.hpp"
#include "application.hpp"
#include "level.hpp"

const int Mud_Drop::MAX_JUMP_HEIGHT = 212;

Mud_Drop::Mud_Drop()
{

    id = Level::MUD_DROP;
    bitmap = Application::MUD_DROP_BM;
    number_of_areas = 1;
    strength = 1;
    y_direction = -1;
    y_max = Application::CANVAS_HEIGHT;

}

void Mud_Drop::Process(Application& app,
                       Level& level)
{

    if (y_max == Application::CANVAS_HEIGHT)
    {
    
        y_max = initial_y-MAX_JUMP_HEIGHT;
    
    }

    if (Is_On_Screen(level.x, level.y, app))
    {
    
        timer++;
        
        if (hit)
        {
        
            strength--;
        
        }
        
        if (strength > 0)
        {
    
            if (y == y_max)
            {
            
                y_direction = 1;
            
            }
            
            if (y == initial_y)
            {
            
                y_direction = -1;
            
            }
            
            if ((timer%4) == 0)
            {
            
                x_direction *= -1;
            
            }
            
            x += (x_direction*4);
            y += (y_direction*4);
            
        }
        else // strength == 0
        {
        
            y += 4;
        
        }
        
        draw_sprite(app.canvas, app.bitmaps[bitmap], (x-level.x), (y-level.y));
    
    }

}
