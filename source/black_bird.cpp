#include <allegro.h>
#include "black_bird.hpp"
#include "application.hpp"
#include "level.hpp"
#include <cstdlib>

using namespace std;

const int Black_Bird::NORMAL = 1;
const int Black_Bird::SHOUT = 2;
const int Black_Bird::LEAP = 3;

Black_Bird::Black_Bird()
{

    id = Level::BLACK_BIRD;
    bitmap = Application::BLACK_BIRD_STANDING_BM;
    strength = 2;
    number_of_areas = 1;
    reset_timer = false;
    stop_fall = false;
    x_direction = -1;
    mode = NORMAL;

}

void Black_Bird::Process(Application& app,
                         Level& level)
{

    if (Is_On_Screen(level.x, level.y, app))
    {

        timer++;

        if (strength > 0)
        {

            int left_platform;
            int right_platform;
            int top_platform;
            int bottom_platform;
            int top_left_platform;
            int bottom_left_platform;
            int top_right_platform;
            int bottom_right_platform;

            Which_Platforms_Were_Hit(left_platform, right_platform,
                                     top_platform, bottom_platform,
                                     top_left_platform, bottom_left_platform,
                                     top_right_platform, bottom_right_platform,
                                     level, 0, app);

            if (hit)
            {

                if (y_direction == -1)
                {

                    y_direction = 1;

                }

                if (bottom_platform != NO_PLATFORM_HIT)
                {

                    if (level.platforms[bottom_platform]->type == Platform::PLATFORM)
                    {

                        stop_fall = true;

                    }

                }

                bitmap = Application::BLACK_BIRD_HURT_BM;
                
                if (!reset_timer)
                {

                    timer = 0;
                    reset_timer = true;
                    strength--;

                }
                
                if (timer == (30*3))
                {

                    reset_timer = false;
                    hit = false;
                    stop_fall = false;
                    y_direction = -1;

                }
                
                if (!stop_fall && hit)
                {

                    y += (y_direction*4);

                }

            }
            else // not hit
            {

                if (mode == SHOUT)
                {

                    stop_fall = true;
                    bitmap = Application::BLACK_BIRD_HURT_BM;
                    level.signal = Level::SIGNAL_ATTACK_BLUEJAY;
                    
                    if ((timer%12) == 0)
                    {
                    
                        x_direction *= -1;
                        play_sample(app.sound_effects[Application::BIRD_CHIRP_SE],
                                    255, 128, 1000, 0);
                        
                    }
                
                }
                else
                {

                    bitmap = Application::BLACK_BIRD_STANDING_BM;

                }

                if (right_platform != NO_PLATFORM_HIT)
                {

                    if (level.platforms[right_platform]->type == Platform::PLATFORM)
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

                if (bottom_platform != NO_PLATFORM_HIT)
                {

                    if (level.platforms[bottom_platform]->type == Platform::PLATFORM)
                    {

                        y_max = y;
                        
                        if (mode == NORMAL)
                        {
                        
                            y_max -= 8;
                        
                        }
                        
                        if (mode == LEAP)
                        {
                        
                            y_max -= (16+((rand()%25)*8));
                        
                        }
                        
                        y_direction = -1;

                    }

                }

                if (top_platform != NO_PLATFORM_HIT)
                {

                    if (level.platforms[top_platform]->type == Platform::PLATFORM)
                    {

                        y_direction = 1;

                    }
                    else if (y == y_max)
                    {

                        y_direction = 1;

                    }
                    else if ((level.height == 1) && (y == 0))
                    {
                    
                        y_direction = 1;
                    
                    }
                    else if (y == -((level.height-Level::HEIGHT_ERROR)*Application::CANVAS_HEIGHT))
                    {
                    
                        y_direction = 1;
                    
                    }

                }
                else if (y == y_max)
                {

                    y_direction = 1;

                }
                else if ((level.height == 1) && (y == 0))
                {
                
                    y_direction = 1;
                
                }
                else if (y == -((level.height-Level::HEIGHT_ERROR)*Application::CANVAS_HEIGHT))
                {
                
                    y_direction = 1;
                
                }
                
                if (top_left_platform != NO_PLATFORM_HIT)
                {

                    if (level.platforms[top_left_platform]->type == Platform::PLATFORM)
                    {

                        x_direction = 1;

                    }

                }

                if (top_right_platform != NO_PLATFORM_HIT)
                {

                    if (level.platforms[top_right_platform]->type == Platform::PLATFORM)
                    {

                        x_direction = -1;

                    }

                }
                
                if (mode != SHOUT)
                {

                    y += (y_direction*4);

                }
                
                if (((timer%4) == 0) && (mode != SHOUT))
                {

                    x += (x_direction*4);

                }

            }
            
        }
        else // strength == 0
        {

            bitmap = Application::BLACK_BIRD_HURT_BM;
            y += 4;
            hit = false; // prevent the character from flashing
            
        }
        
        if (hit)
        {

            if ((timer%2) == 0)
            {

                if (x_direction == -1)
                {

                    draw_sprite_h_flip(app.canvas, app.bitmaps[bitmap],
                                       (x-level.x), (y-level.y));

                }
                else
                {

                    draw_sprite(app.canvas, app.bitmaps[bitmap], (x-level.x),
                                (y-level.y));

                }

            }

        }
        else // not hit
        {

            if (x_direction == -1)
            {

                draw_sprite_h_flip(app.canvas, app.bitmaps[bitmap],
                                   (x-level.x), (y-level.y));

            }
            else
            {

                draw_sprite(app.canvas, app.bitmaps[bitmap], (x-level.x),
                            (y-level.y));

            }

        }
        
    }

}

int Black_Bird::Get_Points()
{

    return 50;

}
