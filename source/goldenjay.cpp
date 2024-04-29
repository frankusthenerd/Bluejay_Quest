#include <allegro.h>
#include "goldenjay.hpp"
#include "application.hpp"
#include "level.hpp"

const int Goldenjay::IDLE = 1;
const int Goldenjay::ATTACKING = 2;

Goldenjay::Goldenjay()
{

    id = Level::GOLDENJAY;
    bitmap = Application::GOLDENJAY_PERCHED_BM;
    strength = 6;
    number_of_areas = 1;
    state = IDLE;
    reset_timer = false;

}

void Goldenjay::Process(Application& app,
                        Level& level)
{

    int bush_x = initial_x-24;
    int bush_y = initial_y-16;

    if (Is_On_Screen(level.x, level.y, app))
    {
    
        timer++;
        
        if (strength > 0)
        {
        
            if (hit)
            {
            
                bitmap = Application::GOLDENJAY_MOUTH_OPEN_BM;
                y += 4;
                
                if (!reset_timer)
                {
                
                    timer = 0;
                    reset_timer = true;
                    strength--;
                    state = ATTACKING;
                
                }
                
                if (timer > 30)
                {
                
                    hit = false;
                    reset_timer = false;
                
                }
            
            }
            else // not hit
            {
            
                if (state == IDLE)
                {
                
                    int bluejay_middle_x = level.characters[level.bluejay]->x+(app.bitmaps[level.characters[level.bluejay]->bitmap]->w/2);
                
                    bitmap = Application::GOLDENJAY_PERCHED_BM;
                    
                    if ((x > (bluejay_middle_x-32)) && (x < (bluejay_middle_x+32)))
                    {
                    
                        state = ATTACKING;
                    
                    }
                
                }
                
                if (state == ATTACKING)
                {
                
                    bitmap = Application::GOLDENJAY_WINGS_IN_BM+(timer%2);
                    y_direction = -1;
                    
                    if ((timer%(30*4)) == 0)
                    {
                    
                        x_direction *= -1;
                    
                    }
                    
                    if ((timer%2) == 0)
                    {
                    
                        x += (x_direction*4);
                        y += (y_direction*4);
                        
                    }
                
                }
            
            }
            
        }
        else // strength == 0
        {
        
            y += 4;
            bitmap = Application::GOLDENJAY_MOUTH_OPEN_BM;
            hit = false; // prevent flashing
        
        }
        
        if (hit)
        {
        
            if ((timer%2) == 1)
            {
            
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
        else
        {
        
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
    
    draw_sprite(app.canvas, app.bitmaps[Application::FAKE_BUSH_BM], (bush_x-level.x),
                (bush_y-level.y));

}

int Goldenjay::Get_Points()
{

    return 200;

}
