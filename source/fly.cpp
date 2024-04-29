#include <allegro.h>
#include "fly.hpp"
#include "application.hpp"
#include "level.hpp"

const int Fly::RISING = 1;
const int Fly::ATTACKING = 2;

Fly::Fly()
{

    id = Level::FLY;
    bitmap = Application::FLY_WINGS_IN_BM;
    strength = 1;
    number_of_areas = 1;
    x_direction = -1;
    hunter = false;
    state = ATTACKING;

}

void Fly::Process(Application& app,
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

            }
            else // not hit
            {

                bitmap = Application::FLY_WINGS_IN_BM+(timer%2);
                
                if (hunter)
                {
                
                    int left_platform;
                    int right_platform;
                    int top_platform;
                    int bottom_platform;
                    int top_left_platform;
                    int top_right_platform;
                    int bottom_left_platform;
                    int bottom_right_platform;
                    bool no_x_movement = false;
                    bool on_ground = false;
                    
                    Which_Platforms_Were_Hit(left_platform, right_platform, top_platform,
                                             bottom_platform, top_left_platform, bottom_left_platform,
                                             top_right_platform, bottom_right_platform, level, 0, app);
                                             
                    if (bottom_platform != NO_PLATFORM_HIT)
                    {
                    
                        if (level.platforms[bottom_platform]->type == Platform::PLATFORM)
                        {
                        
                            y_max = level.characters[level.bluejay]->y-80;
                            state = RISING;
                            y_direction = -1;
                            on_ground = true;
                        
                        }
                        
                        // A hunting fly can eat cherries!
                        
                        if (level.platforms[bottom_platform]->id == Level::CHERRY)
                        {
                        
                            level.platforms[bottom_platform]->remove = true;
                        
                        }
                    
                    }
                    
                    if (top_platform != NO_PLATFORM_HIT)
                    {
                    
                        if (level.platforms[top_platform]->type == Platform::PLATFORM)
                        {
                        
                            y_direction = 1;
                            state = ATTACKING;
                        
                        }
                        else if ((level.height == 1) && (y == 0))
                        {
                        
                            y_direction = 1;
                            state = ATTACKING;
                        
                        }
                        else if (y == -((level.height-Level::HEIGHT_ERROR)*Application::CANVAS_HEIGHT))
                        {
                        
                            y_direction = 1;
                            state = ATTACKING;
                        
                        }
                        else if (y == y_max)
                        {
                        
                            y_direction = 1;
                            state = ATTACKING;
                        
                        }
                    
                    }
                    else if ((level.height == 1) && (y == 0))
                    {
                    
                        y_direction = 1;
                        state = ATTACKING;
                    
                    }
                    else if (y == -((level.height-Level::HEIGHT_ERROR)*Application::CANVAS_HEIGHT))
                    {
                    
                        y_direction = 1;
                        state = ATTACKING;
                    
                    }
                    else if (y == y_max)
                    {
                    
                        y_direction = 1;
                        state = ATTACKING;
                    
                    }
                    
                    if (left_platform != NO_PLATFORM_HIT)
                    {
                    
                        if (level.platforms[left_platform]->type == Platform::PLATFORM)
                        {
                        
                            x_direction = 1;
                        
                        }
                        else if (x == 0)
                        {
                        
                            x_direction = 1;
                        
                        }
                    
                    }
                    else if (x == 0)
                    {
                    
                        x_direction = 1;
                    
                    }
                    
                    if (right_platform != NO_PLATFORM_HIT)
                    {
                    
                        if (level.platforms[right_platform]->type != Platform::PLATFORM)
                        {
                        
                            x_direction = -1;
                        
                        }
                        else if (x == ((level.number_of_screens*Application::CANVAS_WIDTH)-app.bitmaps[bitmap]->w))
                        {
                        
                            x_direction = -1;
                        
                        }
                    
                    }
                    else if (x == ((level.number_of_screens*Application::CANVAS_WIDTH)-app.bitmaps[bitmap]->w))
                    {
                    
                        x_direction = -1;
                    
                    }
                    
                    if (y_direction == -1)
                    {
                    
                        if (top_left_platform != NO_PLATFORM_HIT)
                        {
            
                            if ((level.platforms[top_left_platform]->type == Platform::PLATFORM) &&
                                (x_direction == -1) && (y_direction == -1))
                            {
            
                                x_direction = 1;
            
                            }
            
                        }
            
                        if (top_right_platform != NO_PLATFORM_HIT)
                        {
            
                            if ((level.platforms[top_right_platform]->type == Platform::PLATFORM) &&
                                (x_direction == 1) && (y_direction == -1))
                            {
            
                                x_direction = -1;
            
                            }
            
                        }
                        
                    }
                    
                    if (!on_ground && (y_direction == 1))
                    {
                    
                        if (bottom_left_platform != NO_PLATFORM_HIT)
                        {
                        
                            if ((level.platforms[bottom_left_platform]->type == Platform::PLATFORM) &&
                                (x_direction == -1) && (y_direction == 1))
                            {
                            
                                x_direction = 1;
                            
                            }
                        
                        }
                        
                        if (bottom_right_platform != NO_PLATFORM_HIT)
                        {
                        
                            if ((level.platforms[bottom_right_platform]->type == Platform::PLATFORM) &&
                                (x_direction == 1) && (y_direction == 1))
                            {
                            
                                x_direction = -1;
                            
                            }
                        
                        }
                        
                    }
                    
                    if (state == RISING)
                    {
                    
                        no_x_movement = true;
                    
                    }
                    
                    if (state == ATTACKING)
                    {
                    
                        int bluejay_middle_x = level.characters[level.bluejay]->x+(app.bitmaps[level.characters[level.bluejay]->bitmap]->w/2);
                    
                        if (x < bluejay_middle_x)
                        {
                        
                            x_direction = 1;
                        
                        }
                        
                        if (x > bluejay_middle_x)
                        {
                        
                            x_direction = -1;
                        
                        }
                    
                    }
                    
                    if (!no_x_movement)
                    {
                    
                        x += (x_direction*4);
                    
                    }
                    
                    y += (y_direction*4);
                
                }
                else // wanderer
                {
                
                    x += (x_direction*4);
                    
                }
                
            }

        }
        else // strength == 0
        {

            y += 4;

        }
        
        if (x_direction == -1)
        {

            draw_sprite_h_flip(app.canvas, app.bitmaps[bitmap], (x-level.x),
                               (y-level.y));

        }
        else // x_direction == 1
        {

            draw_sprite(app.canvas, app.bitmaps[bitmap], (x-level.x), (y-level.y));

        }

    }

}
