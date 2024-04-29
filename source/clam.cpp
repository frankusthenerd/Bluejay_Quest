#include <allegro.h>
#include "clam.hpp"
#include "application.hpp"
#include "level.hpp"

Clam::Clam()
{

    id = Level::CLAM;
    bitmap = Application::CLAM_MOUTH_OPEN_BM;
    number_of_areas = 1;
    strength = 2;

}

void Clam::Process(Application& app,
                   Level& level)
{

    if (Is_On_Screen(level.x, level.y, app))
    {

        timer++;
        hit = false;
        bitmap = Application::CLAM_MOUTH_CLOSED_BM+((timer%8)/4);
        draw_sprite(app.canvas, app.bitmaps[bitmap], (x-level.x), (y-level.y));

    }

}
