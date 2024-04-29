#include <allegro.h>
#include "master_ecto.hpp"
#include "application.hpp"
#include "level.hpp"

Master_Ecto::Master_Ecto()
{

    number_of_areas = 1;
    strength = 1;
    bitmap = Application::MASTER_ECTO_BM;
    id = Level::MASTER_ECTO;
    relocated = false;

}

void Master_Ecto::Process(Application& app,
                          Level& level)
{

    if (level.signal != Level::SIGNAL_DESTROY_ECTO)
    {

        timer++;
    
        if (!Is_On_Screen(level.x, level.y, app))
        {
    
            if (!relocated)
            {

                x = level.characters[level.bluejay]->x+Application::CANVAS_WIDTH+((rand()%((Application::CANVAS_WIDTH*4)/4))*4);
                relocated = true;

            }
    
        }
        else // is on the screen
        {

            relocated = false;

        }

        if ((timer%2) == 0)
        {

            int middle_x = x+(app.bitmaps[bitmap]->w/2);
            int middle_y = y+(app.bitmaps[bitmap]->h/2);
            int bluejay_middle_x = level.characters[level.bluejay]->x+(app.bitmaps[level.characters[level.bluejay]->bitmap]->w/2);
            int bluejay_middle_y = level.characters[level.bluejay]->y+(app.bitmaps[level.characters[level.bluejay]->bitmap]->h/2);
    
            if (middle_x < bluejay_middle_x)
            {
    
                x += 4;
    
            }
        
            if (middle_x > bluejay_middle_x)
            {
        
                x -= 4;
        
            }
        
            if (middle_y < bluejay_middle_y)
            {
        
                y += 4;
        
            }
        
            if (middle_y > bluejay_middle_y)
            {
        
                y -= 4;
        
            }
    
        }

        clear_to_color(app.master_ecto_temp_bitmap, makecol(255, 0, 255));
    
        if ((timer%2) == 0)
        {
    
            draw_sprite_h_flip(app.master_ecto_temp_bitmap, app.bitmaps[bitmap], 0, 0);
    
        }
        else
        {
    
            draw_sprite(app.master_ecto_temp_bitmap, app.bitmaps[bitmap], 0, 0);
    
        }
    
        set_trans_blender(50, 50, 50, 50);
        draw_trans_sprite(app.canvas, app.master_ecto_temp_bitmap, (x-level.x), (y-level.y));

    }

}
