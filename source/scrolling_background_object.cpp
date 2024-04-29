#include <allegro.h>
#include "scrolling_background_object.hpp"
#include "application.hpp"
#include "level.hpp"

Scrolling_Background_Object::Scrolling_Background_Object()
{

    id = Level::SCROLLING_BACKGROUND;
    bitmap = Application::SCROLLING_BACKGROUND_BM;
    number_of_areas = 0;

}

void Scrolling_Background_Object::Process(Application& app,
                                          Level& level)
{

    if (Is_On_Screen(level.x, level.y, app))
    {
    
        level.autoscroll_background = true;
    
    }

}
