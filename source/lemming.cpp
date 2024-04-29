#include <allegro.h>
#include "lemming.hpp"
#include "application.hpp"
#include "level.hpp"
#include "throwable_rock.hpp"

const int Lemming::WALKING = 1;
const int Lemming::JUMPING = 2;
const int Lemming::FALLING = 3;
const int Lemming::MAX_JUMP_HEIGHT = 64;

Lemming::Lemming()
{

    id = Level::LEMMING;
    bitmap = Application::LEMMING_WALK_BM;
    number_of_areas = 1;
    strength = 1;
    state = FALLING;
    x_direction = -1;

}

void Lemming::Process(Application& app,
                      Level& level)
{

    if (Is_On_Screen(level.x, level.y, app))
    {
    
        timer++;
    
        if (hit)
        {
        
            strength--;
        
        }
    
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
            int character_hit;
            int character_area;
            int hit_results;
            int still_bm;
            int walk_bm;
            int bluejay_middle_x = level.characters[level.bluejay]->x+(app.bitmaps[level.characters[level.bluejay]->bitmap]->w/2);
            int bluejay_bottom = level.characters[level.bluejay]->y+app.bitmaps[level.characters[level.bluejay]->bitmap]->h;
            int my_bottom = y+app.bitmaps[bitmap]->h;
            bool no_left_movement;
            bool no_right_movement;
            bool on_ground = false;

            Which_Platforms_Were_Hit(left_platform, right_platform, top_platform, bottom_platform,
                                     top_left_platform, bottom_left_platform, top_right_platform,
                                     bottom_right_platform, level, 0, app);
                                     
            if (y_direction == 1)
            {
            
                if (bottom_platform != NO_PLATFORM_HIT)
                {
                
                    if (level.platforms[bottom_platform]->type == Platform::PLATFORM)
                    {
                    
                        on_ground = true;
                        y_max = y-MAX_JUMP_HEIGHT;
                    
                    }
                
                }
                
            }
            else // y_direction == -1
            {
            
                if (top_platform != NO_PLATFORM_HIT)
                {
                
                    if (level.platforms[top_platform]->type == Platform::PLATFORM)
                    {
                
                        y_direction = 1;
                        state = FALLING;
                        
                    }
                    else if ((level.height == 1) && (y == 0))
                    {
                    
                        y_direction = 1;
                        state = FALLING;
                    
                    }
                    else if (y == -((level.height-Level::HEIGHT_ERROR)*Application::CANVAS_HEIGHT))
                    {
                    
                        y_direction = 1;
                        state = FALLING;
                    
                    }
                    else if (y == y_max)
                    {
                    
                        y_direction = 1;
                        state = FALLING;
                    
                    }
                
                }
                else if ((level.height == 1) && (y == 0))
                {
                
                    y_direction = 1;
                    state = FALLING;
                
                }
                else if (y == -((level.height-Level::HEIGHT_ERROR)*Application::CANVAS_HEIGHT))
                {
                
                    y_direction = 1;
                    state = FALLING;
                
                }
                else if (y == y_max)
                {
                
                    y_direction = 1;
                    state = FALLING;
                
                }
            
            }
            
            no_left_movement = false;
            no_right_movement = false;
            
            if (right_platform != NO_PLATFORM_HIT)
            {
            
                if (level.platforms[right_platform]->type == Platform::PLATFORM)
                {
            
                    if (on_ground)
                    {
                    
                        state = JUMPING; // jump over the ledge
                        y_direction = -1;
                    
                    }
                    
                    no_right_movement = true;
                
                }
                else if (x == ((level.number_of_screens*Application::CANVAS_WIDTH)-app.bitmaps[bitmap]->w))
                {
                
                    x_direction = -1;
                    no_right_movement = true;
                
                }
            
            }
            else if (x == ((level.number_of_screens*Application::CANVAS_WIDTH)-app.bitmaps[bitmap]->w))
            {
            
                x_direction = -1;
                no_right_movement = true;
            
            }
            
            if (left_platform != NO_PLATFORM_HIT)
            {
        
                if (level.platforms[left_platform]->type == Platform::PLATFORM)
                {
            
                    if (on_ground)
                    {
                    
                        state = JUMPING; // jump over the ledge
                        y_direction = -1;
                    
                    }
                    
                    no_left_movement = true;
                
                }
                else if (x == 0)
                {
                
                    x_direction = 1;
                    no_left_movement = true;
                
                }
                
            }
            else if (x == 0)
            {
            
                x_direction = 1;
                no_left_movement = true;
            
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
            
            character_hit = Which_Character_Was_Hit(level, 0, app, character_area, hit_results);
            
            if (character_hit != NO_CHARACTER_HIT)
            {
            
                if (level.characters[character_hit]->id == Level::THROWABLE_ROCK)
                {
                
                    if (x_direction == 1)
                    {
                    
                        if ((hit_results & HIT_RIGHT) && !carrying_object &&
                            !level.characters[character_hit]->can_hurt)
                        {
                        
                            carrying_object = true;
                            rock = character_hit;
                            level.characters[character_hit]->x = x;
                            level.characters[character_hit]->y = y-12;
                            level.characters[character_hit]->can_hurt = true;
                        
                        }
                    
                    }
                    else // x_direction == -1
                    {
                    
                        if ((hit_results & HIT_LEFT) && !carrying_object &&
                            !level.characters[character_hit]->can_hurt)
                        {
                        
                            carrying_object = true;
                            rock = character_hit;
                            level.characters[character_hit]->x = x;
                            level.characters[character_hit]->y = y-12;
                            level.characters[character_hit]->can_hurt = true;
                        
                        }
                    
                    }
                
                }
            
            }
            
            still_bm = carrying_object ? Application::LEMMING_STILL_ARMS_UP_BM : Application::LEMMING_STILL_BM;
            walk_bm = carrying_object ? Application::LEMMING_WALK_ARMS_UP_BM : Application::LEMMING_WALK_BM;
            
            if (state == WALKING)
            {
            
                bitmap = ((timer%2) == 0) ? still_bm : walk_bm;
                
                if (carrying_object)
                {
                
                    Throwable_Rock* throwable_rock = static_cast<Throwable_Rock*>(level.characters[rock]);
                
                    throwable_rock->released = true;
                    carrying_object = false;
                    
                    if (bluejay_middle_x < x)
                    {
                    
                        x_direction = -1;
                    
                    }
                    
                    if (bluejay_middle_x > (x+16))
                    {
                    
                        x_direction = 1;
                    
                    }
                    
                    throwable_rock->x_direction = x_direction;
                    
                    if (bluejay_bottom == my_bottom)
                    {
                    
                        throwable_rock->y_direction = 0;
                    
                    }
                    
                    if (bluejay_bottom > my_bottom)
                    {
                    
                        throwable_rock->y_direction = 1;
                    
                    }
                    
                    if (bluejay_bottom < my_bottom)
                    {
                    
                        throwable_rock->y_direction = -1;
                    
                    }
                    
                }
                
                if (!on_ground)
                {
                
                    state = FALLING;
                
                }
            
            }
            
            if (state == JUMPING)
            {
            
                bitmap = walk_bm;
            
            }
            
            if (state == FALLING)
            {
            
                bitmap = walk_bm;
                
                if (on_ground)
                {
                
                    state = WALKING;
                
                }
            
            }
            
            if ((timer%2) == 0)
            {
            
                if ((x_direction == 1) && !no_right_movement)
                {
                
                    x += 4;
                    
                    if (carrying_object)
                    {
                    
                        level.characters[rock]->x += 4;
                    
                    }
                
                }
                
                if ((x_direction == -1) && !no_left_movement)
                {
                
                    x -= 4;
                    
                    if (carrying_object)
                    {
                    
                        level.characters[rock]->x -= 4;
                    
                    }
                
                }
                
            }
                
            if (!on_ground)
            {
            
                y += (y_direction*4);
                
                if (carrying_object)
                {
                
                    level.characters[rock]->y += (y_direction*4);
                
                }
            
            }
                
            
        }
        else // strength == 0
        {
        
            y += 4;
            
            if (carrying_object)
            {
            
                level.characters[rock]->y += 4;
            
            }
        
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
