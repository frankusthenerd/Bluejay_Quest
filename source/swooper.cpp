#include <allegro.h>
#include "swooper.hpp"
#include "application.hpp"
#include "level.hpp"

Swooper::Swooper()
{

    id = Level::SWOOPER;
    bitmap = Application::SWOOPER_WINGS_IN_BM;
    number_of_areas = 1;
    strength = 1;
    x_direction = -1;

}

void Swooper::Process(Application& app,
                      Level& level)
{

    if (Is_On_Screen(level.x, level.y, app))
    {
    
        timer++;
        
        if (strength > 0)
        {
        
            if (hit)
            {
            
                strength--;
                bitmap = Application::SWOOPER_WINGS_IN_BM;
            
            }
            else // not hit
            {
        
                if (x_direction == 1)
                {
                
                    if (level.characters[level.bluejay]->x_direction == -1)
                    {
                    
                        if ((x >= (level.characters[level.bluejay]->x-80)) &&
                            (x <= level.characters[level.bluejay]->x))
                        {
                        
                            int bluejay_middle_y = level.characters[level.bluejay]->y+(app.bitmaps[level.characters[level.bluejay]->bitmap]->h/2);
                        
                            if ((y+8) < bluejay_middle_y)
                            {
                        
                                y += 4;
                            
                            }
                            
                            if ((y+8) > bluejay_middle_y)
                            {
                            
                                y -= 4;
                            
                            }
                        
                        }
                    
                    }
                
                }
                else // x_direction == -1
                {
                
                    if (level.characters[level.bluejay]->x_direction == 1)
                    {
                    
                        if ((x <= (level.characters[level.bluejay]->x+80)) &&
                            (x >= level.characters[level.bluejay]->x))
                        {
                        
                            int bluejay_middle_y = level.characters[level.bluejay]->y+(app.bitmaps[level.characters[level.bluejay]->bitmap]->h/2);
                        
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
                
                }
                
                if ((timer%15) == 0)
                {
                
                    play_sample(app.sound_effects[Application::BIRD_CHIRP_SE], 255, 128, 1000, 0);
                
                }
                
                x += (x_direction*4);
                bitmap = Application::SWOOPER_WINGS_IN_BM+(timer%2);
                
            }
        
        }
        else // strength == 0
        {
        
            bitmap = Application::SWOOPER_WINGS_IN_BM;
            y += 4;
        
        }
        
        if (x_direction == 1)
        {
        
            draw_sprite(app.canvas, app.bitmaps[bitmap], (x-level.x), (y-level.y));
            
        }
        else // x_direction == -1
        {
        
            draw_sprite_h_flip(app.canvas, app.bitmaps[bitmap], (x-level.x), (y-level.y));
        
        }
    
    }

}

int Swooper::Get_Points()
{

    return 100;

}
