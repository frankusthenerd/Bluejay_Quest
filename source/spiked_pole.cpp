#include <allegro.h>
#include "spiked_pole.hpp"
#include "application.hpp"
#include "level.hpp"

const int Spiked_Pole::MAX_HEIGHT = 3;

Spiked_Pole::Spiked_Pole()
{

    number_of_areas = 1;
    id = Level::SPIKED_POLE;
    strength = 1;
    bitmap = Application::SPIKED_POLE_POINT_BM;
    extended = false;

}

void Spiked_Pole::Process(Application& app,
                          Level& level)
{

    if (Is_On_Screen(level.x, level.y, app))
    {

        timer++;
        
        if (!extended)
        {
        
            if ((timer%23) == 0)
            {
            
                extended = true;
                play_sample(app.sound_effects[Application::THUD_SE], 255, 128, 1000, 0);
            
            }
            
            draw_sprite(app.canvas, app.bitmaps[bitmap], (x-level.x), (y-level.y));
        
        }
        else // extended
        {
        
            int height = 0;
            int y = this->y;
            
            if ((timer%23) == 0)
            {
            
                extended = false; // retract
            
            }
            
            while (height < MAX_HEIGHT)
            {
            
                draw_sprite(app.canvas, app.bitmaps[Application::SPIKED_POLE_POLE_BM],
                            (x-level.x), (y-level.y));
                y += app.bitmaps[Application::SPIKED_POLE_POLE_BM]->h;
                height++;
            
            }
            
            draw_sprite(app.canvas, app.bitmaps[bitmap], (x-level.x), (y-level.y));
        
        }
        
    }

}

void Spiked_Pole::Get_Bump_Map(Rectangle& map,
                               int area,
                               Application& app)
{

    if (extended)
    {
    
        map.left = (x/4)+bump_maps[area]->left;
        map.right = (x/4)+bump_maps[area]->right;
        map.top = (y/4)+bump_maps[area]->top;
        map.bottom = (y/4)+bump_maps[area]->bottom+((app.bitmaps[Application::SPIKED_POLE_POLE_BM]->h/4)*MAX_HEIGHT);
    
    }
    else
    {
    
        map.left = (x/4)+bump_maps[area]->left;
        map.right = (x/4)+bump_maps[area]->right;
        map.top = (y/4)+bump_maps[area]->top;
        map.bottom = (y/4)+bump_maps[area]->bottom;
    
    }

}
