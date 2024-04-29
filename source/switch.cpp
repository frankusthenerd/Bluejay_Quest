#include <allegro.h>
#include "switch.hpp"
#include "application.hpp"
#include "level.hpp"

const int Switch::PIPE = 1;
const int Switch::REVERSE_PIPE = 2;
const int Switch::NO_ECTO = 3;

Switch::Switch()
{

    id = Level::PIPE_SWITCH;
    bitmap = Application::SWITCH_NORMAL_BM;
    number_of_areas = 1;
    strength = 1;
    mode = PIPE;
    sent_signal = false;

}

void Switch::Process(Application& app,
                     Level& level)
{

    if (Is_On_Screen(level.x, level.y, app))
    {
    
        if (hit)
        {
        
            if (!sent_signal)
            {
            
                if (mode == PIPE)
                {
            
                    level.signal = Level::SIGNAL_LOWER_PIPES;
                
                }
                
                if (mode == REVERSE_PIPE)
                {
                
                    level.signal = Level::SIGNAL_RAISE_PIPES;
                
                }

                if (mode == NO_ECTO)
                {

                    level.signal = Level::SIGNAL_DESTROY_ECTO;
                    level.autoscroll_background = false;
                    play_midi(app.music_tracks[Application::VICTORY_MT], 1);

                }
                
                sent_signal = true;
            
            }
            
            bitmap = Application::SWITCH_PRESSED_BM;
        
        }
        
        draw_sprite(app.canvas, app.bitmaps[bitmap], (x-level.x), (y-level.y));
    
    }

}
