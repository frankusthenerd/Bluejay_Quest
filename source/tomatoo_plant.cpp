#include <allegro.h>
#include "tomatoo_plant.hpp"
#include "application.hpp"
#include "level.hpp"
#include <cstdlib>

using namespace std;

Tomatoo_Plant::Tomatoo_Plant()
{

    id = Level::TOMATOO_PLANT;
    bitmap = Application::TOMATOO_PLANT_HEAD_BM;
    number_of_areas = 1;
    strength = 1;
    hypergrowth = false;
    number_of_stems = 0;
    hypergrowth_kill = false;
    timer = 61;

}

void Tomatoo_Plant::Process(Application& app,
                            Level& level)
{

    hypergrowth_kill = false;

    if (Is_On_X_Screen(level.x, level.y, app))
    {
    
        int bluejay_middle_x = level.characters[level.bluejay]->x+(app.bitmaps[level.characters[level.bluejay]->bitmap]->w/2);
        
        timer++;
    
        if (((rand()%50) == 0) &&
            ((bluejay_middle_x >= (x-16)) && (bluejay_middle_x <= (x+app.bitmaps[bitmap]->w+16))) &&
            (timer > 60))
        {
        
            if (!hypergrowth)
            {
        
                number_of_stems = (level.height == 1) ? 3 : 30;
                y -= (app.bitmaps[Application::TOMATOO_PLANT_STEM_BM]->h*number_of_stems);
                play_sample(app.sound_effects[Application::GROWING_SE], 255, 128, 1000, 0);
                hypergrowth = true;
                hypergrowth_kill = true;
                timer = 0;
            
            }
        
        }
        
        if (timer > 30)
        {
        
            if (hypergrowth)
            {
            
                y = initial_y;
                hypergrowth = false; // the plant retracts
                play_sample(app.sound_effects[Application::SHRINKING_SE], 255, 128, 1000, 0);
            
            }
        
        }
        
        draw_sprite(app.canvas, app.bitmaps[bitmap], (x-level.x), (y-level.y));
        
        if (hypergrowth)
        {
        
            int stem = 0;
            
            while (stem < number_of_stems)
            {
            
                draw_sprite(app.canvas, app.bitmaps[Application::TOMATOO_PLANT_STEM_BM], (x-level.x),
                            (((y+app.bitmaps[bitmap]->h)+(stem*app.bitmaps[Application::TOMATOO_PLANT_STEM_BM]->h))-level.y));
                stem++;
            
            }
        
        }
    
    }

}

void Tomatoo_Plant::Get_Bump_Map(Rectangle& map,
                                 int area,
                                 Application& app)
{

    if (hypergrowth)
    {
    
        map.left = (x/4)+bump_maps[area]->left;
        map.right = (x/4)+bump_maps[area]->right;
        map.top = (y/4)+bump_maps[area]->top;
        map.bottom = (y/4)+bump_maps[area]->bottom+((app.bitmaps[Application::TOMATOO_PLANT_STEM_BM]->h/4)*number_of_stems);
    
    }
    else
    {
    
        map.left = (x/4)+bump_maps[area]->left;
        map.right = (x/4)+bump_maps[area]->right;
        map.top = (y/4)+bump_maps[area]->top;
        map.bottom = (y/4)+bump_maps[area]->bottom;
    
    }

}
