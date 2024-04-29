#include <allegro.h>
#include "ghost.hpp"
#include "level.hpp"
#include "application.hpp"
#include <cstdlib>

using namespace std;

Ghost::Ghost()
{

    number_of_areas = 1;
    id = Level::GHOST;
    bitmap = Application::GHOST_BM;
    strength = 1;

}

void Ghost::Process(Application& app,
                    Level& level)
{

    if (Is_On_Screen(level.x, level.y, app) && (level.signal != Level::SIGNAL_DESTROY_ECTO))
    {

        timer++;
        
        if ((timer%150) == 0) // every 5 seconds
        {
        
            x = (rand()%(((level.number_of_screens*Application::CANVAS_WIDTH)-app.bitmaps[bitmap]->w)/4))*4;
        
        }
        else
        {
        
            if ((timer%4) == 0)
            {
        
                int bluejay_middle_x = level.characters[level.bluejay]->x+(app.bitmaps[level.characters[level.bluejay]->bitmap]->w/2);
                int bluejay_middle_y = level.characters[level.bluejay]->y+(app.bitmaps[level.characters[level.bluejay]->bitmap]->h/2);
            
                if (x < bluejay_middle_x)
                {
            
                    x += 4;
            
                }
                
                if (x > bluejay_middle_x)
                {
                
                    x -= 4;
                
                }
                
                if (y < bluejay_middle_y)
                {
                
                    y += 4;
                
                }
                
                if (y > bluejay_middle_y)
                {
                
                    y -= 4;
                
                }
            
            }
        
        }
        
        clear_to_color(app.ghost_temp_bitmap, makecol(255, 0, 255)); // pink
        
        if ((timer%2) == 0)
        {
        
            draw_sprite_h_flip(app.ghost_temp_bitmap, app.bitmaps[Application::GHOST_BM], 0, 0);
        
        }
        else
        {
        
            draw_sprite(app.ghost_temp_bitmap, app.bitmaps[Application::GHOST_BM], 0, 0);
        
        }
        
        set_trans_blender(100, 100, 100, 100);
        draw_trans_sprite(app.canvas, app.ghost_temp_bitmap, (x-level.x), (y-level.y));
    
    }

}
