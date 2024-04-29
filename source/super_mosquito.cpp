#include <allegro.h>
#include "super_mosquito.hpp"
#include "application.hpp"
#include "level.hpp"
#include <cstdlib>

using namespace std;

const int Super_Mosquito::HOVERING = 1;
const int Super_Mosquito::ATTACKING = 2;
const int Super_Mosquito::CALLING_MOSQUITOS = 3;

Super_Mosquito::Super_Mosquito()
{

    id = Level::SUPER_MOSQUITO;
    bitmap = Application::SUPER_MOSQUITO_WINGS_DOWN_BM;
    number_of_areas = 1;
    strength = 3;
    state = HOVERING;
    reset_timer = false;
    flipped_directions = false;

}

void Super_Mosquito::Process(Application& app,
                             Level& level)
{

    timer++;

    if (strength > 0)
    {
    
        if (hit)
        {
        
            if (!reset_timer)
            {
            
                timer = 0;
                reset_timer = true;
                strength--;
            
            }
            
            if (timer > 30)
            {
            
                hit = false;
                reset_timer = false;
            
            }
        
        }
        else
        {
    
            bitmap = Application::SUPER_MOSQUITO_WINGS_DOWN_BM+(timer%2);
        
            if (state == HOVERING)
            {
            
                if (x < 0)
                {
                
                    x_direction = 1;
                
                }
                
                if ((x+app.bitmaps[bitmap]->w-1) >= Application::CANVAS_WIDTH)
                {
                
                    x_direction = -1;
                
                }
                
                if ((rand()%25) == 0)
                {
                
                    int bluejay_middle_x = level.characters[level.bluejay]->x+(app.bitmaps[level.characters[level.bluejay]->bitmap]->w/2);
                    int bluejay_middle_y = level.characters[level.bluejay]->y+(app.bitmaps[level.characters[level.bluejay]->bitmap]->h/2);
    
                    if (x < bluejay_middle_x)
                    {
    
                        x_direction = 1;
    
                    }
                    
                    if (x > bluejay_middle_x)
                    {
    
                        x_direction = -1;
    
                    }
                    
                    if (y < bluejay_middle_y)
                    {
    
                        y_direction = 1;
    
                    }
                    
                    if (y > bluejay_middle_y)
                    {
    
                        y_direction = -1;
    
                    }
                    
                    state = ATTACKING;
                    previous_x = x;
                    previous_y = y;
                
                }
                else if ((strength == 1) && (level.signal != Level::SIGNAL_ATTACK_BLUEJAY))
                {
                
                    state = CALLING_MOSQUITOS;
                    previous_x = x;
                    previous_y = y;
                
                }
            
            }
            else if (state == ATTACKING)
            {
            
                if (!Is_On_Screen(level.x, level.y, app))
                {
                
                    if (!flipped_directions)
                    {
                    
                        x_direction *= -1; // reverse directions
                        y_direction *= -1;
                        flipped_directions = true;
                        
                    }
                
                }
                
                if ((x == previous_x) && (y == previous_y))
                {
                
                    flipped_directions = false;
                    state = HOVERING;
                
                }
            
            }
            else if (state == CALLING_MOSQUITOS)
            {
            
                if (!Is_On_Screen(level.x, level.y, app))
                {
                
                    if (!flipped_directions)
                    {
                
                        level.signal = Level::SIGNAL_ATTACK_BLUEJAY;
                        flipped_directions = true;
                        x_direction *= -1;
                        y_direction *= -1;
                    
                    }
                
                }
                
                if (flipped_directions)
                {
                
                    if ((x == previous_x) && (y == previous_y))
                    {
                    
                        state = HOVERING;
                        flipped_directions = false;
                    
                    }
                
                }
            
            }
            
            x += (x_direction*4);
            
            if (state != HOVERING)
            {
            
                y += (y_direction*4);
                
            }
            
        }
    
    }
    else
    {
    
        bitmap = Application::SUPER_MOSQUITO_WINGS_DOWN_BM;
        y += 4;
        level.signal = Level::SIGNAL_COLLAPSE_CEMENT;
    
    }
    
    if (hit)
    {
    
        if ((timer%2) == 0)
        {
        
            draw_sprite(app.canvas, app.bitmaps[bitmap], (x-level.x), (y-level.y));
        
        }
    
    }
    else
    {
    
        draw_sprite(app.canvas, app.bitmaps[bitmap], (x-level.x), (y-level.y));
    
    }
    
}

int Super_Mosquito::Get_Points()
{

    return 1000;

}

void Super_Mosquito::Reset(bool demo_playing)
{

    x = initial_x;
    y = initial_y;
    strength = 3;
    state = HOVERING;
    reset_timer = false;
    flipped_directions = false;

}
