#include <allegro.h>
#include "egg.hpp"
#include "application.hpp"
#include "level.hpp"

Egg::Egg()
{

    id = Level::EGG;
    bitmap = Application::EGG_BM;
    number_of_areas = 1;
    strength = 1;

}

void Egg::Process(Application& app,
                   Level& level)
{

    if (Is_On_Screen(level.x, level.y, app))
    {

        if (!hit)
        {

            draw_sprite(app.canvas, app.bitmaps[bitmap], (x-level.x), (y-level.y));

        }

    }

}

void Egg::Reset(bool demo_playing)
{

    x = initial_x;
    y = initial_y;
    
    if (demo_playing)
    {
    
        hit = false;
    
    }

}
