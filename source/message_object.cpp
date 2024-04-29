#include <allegro.h>
#include "message_object.hpp"
#include "application.hpp"
#include "level.hpp"

Message_Object::Message_Object()
{

    id = Level::MESSAGE_OBJECT;
    bitmap = Application::MESSAGE_BOX_BM;
    number_of_areas = 0;

}

void Message_Object::Process(Application& app,
                             Level& level)
{

    if (Is_On_Screen(level.x, level.y, app))
    {
    
        if (!level.displayed_message)
        {
        
            level.display_message = true;
        
        }
    
    }

}
