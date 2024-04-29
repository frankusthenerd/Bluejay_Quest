#include <allegro.h>
#include "stop_attack_object.hpp"
#include "application.hpp"
#include "level.hpp"

Stop_Attack_Object::Stop_Attack_Object()
{

    id = Level::STOP_ATTACK_OBJECT;
    bitmap = Application::STOP_ATTACK_BM;
    number_of_areas = 0;

}

void Stop_Attack_Object::Process(Application& app,
                                 Level& level)
{

    if (Is_On_Screen(level.x, level.y, app))
    {
    
        if (level.signal == Level::SIGNAL_ATTACK_BLUEJAY)
        {
    
            level.signal = 0;
            
        }
    
    }

}
