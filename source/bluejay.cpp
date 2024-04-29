#include <allegro.h>
#include "bluejay.hpp"
#include "application.hpp"
#include "level.hpp"
#include <cstdlib>
#include "tomatoo_plant.hpp"
#include "spiked_pole.hpp"

using namespace std;

const int Bluejay::IDLE = 1;
const int Bluejay::JUMPING = 2;
const int Bluejay::FLYING = 3;
const int Bluejay::GLIDING = 4;
const int Bluejay::GOING_DOWN_PIPE = 5;
const int Bluejay::HEAD = 0;
const int Bluejay::BODY = 1;
const int Bluejay::TAIL = 2;
const int Bluejay::MAX_JUMP_HEIGHT = 48;
const int Bluejay::MAX_STRENGTH = 5;

Bluejay::Bluejay()
{

    id = Level::BLUEJAY;
    bitmap = Application::BLUEJAY_STANDING_BM;
    state = GLIDING;
    strength = 3;
    number_of_areas = 3;
    can_jump = true;
    warped = false;
    died = false;
    flight_counter = 0;
    local_pipe = false;
    lives = 3;
    eggs = 0;
    score = 0;

}

void Bluejay::Process(Application& app,
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
            int top_left_platform_head;
            int bottom_left_platform_head;
            int top_right_platform_head;
            int bottom_right_platform_head;
            int top_left_platform_body;
            int bottom_left_platform_body;
            int top_right_platform_body;
            int bottom_right_platform_body;
            int character;
            int character_area;
            int hit_results;
            bool no_left_movement;
            bool no_right_movement;
            bool no_upper_movement;
            bool on_ground = false;
            bool tail_attack = false;

            no_upper_movement = false;
            Which_Platforms_Were_Hit(left_platform, right_platform, top_platform,
                                     bottom_platform, top_left_platform_body,
                                     bottom_left_platform_body, top_right_platform_body,
                                     bottom_right_platform_body, level, BODY, app);

            if (bottom_platform != NO_PLATFORM_HIT)
            {

                if (level.platforms[bottom_platform]->type == Platform::PLATFORM)
                {

                    on_ground = true;
                    max_y = y-MAX_JUMP_HEIGHT;
                    
                }

            }

            if (top_platform != NO_PLATFORM_HIT)
            {

                if (level.platforms[top_platform]->type == Platform::PLATFORM)
                {

                    no_upper_movement = true;
                    
                    if (state == JUMPING)
                    {
                    
                        y_direction = 1;
                        state = GLIDING;
                    
                    }

                }
                else if ((level.height == 1) && (y == 0))
                {

                    no_upper_movement = true;

                    if (state == JUMPING)
                    {

                        y_direction = 1;
                        state = GLIDING;

                    }

                }
                else if (y == -((level.height-Level::HEIGHT_ERROR)*Application::CANVAS_HEIGHT))
                {

                    no_upper_movement = true;

                    if (state != FLYING)
                    {

                        y_direction = 1;
                        state = GLIDING;

                    }

                }
                else if ((state == JUMPING) && (y == max_y))
                {

                    no_upper_movement = true;
                    
                    if (state != FLYING)
                    {

                        y_direction = 1;
                        state = GLIDING;

                    }

                }

            }
            else if ((level.height == 1) && (y == 0))
            {

                no_upper_movement = true;

                if (state == JUMPING)
                {

                    y_direction = 1;
                    state = GLIDING;

                }

            }
            else if (y == -((level.height-Level::HEIGHT_ERROR)*Application::CANVAS_HEIGHT))
            {

                no_upper_movement = true;

                if (state != FLYING)
                {

                    y_direction = 1;
                    state = GLIDING;

                }

            }
            else if ((state == JUMPING) && (y == max_y))
            {

                no_upper_movement = true;
                
                if (state != FLYING)
                {

                    y_direction = 1;
                    state = GLIDING;

                }

            }

            no_left_movement = false;
            no_right_movement = false;
            
            if (right_platform != NO_PLATFORM_HIT)
            {

                if (level.platforms[right_platform]->type == Platform::PLATFORM)
                {

                    no_right_movement = true;

                }
                else if (x == ((level.number_of_screens*Application::CANVAS_WIDTH)-app.bitmaps[bitmap]->w))
                {

                    no_right_movement = true;

                }

            }
            else if (x == ((level.number_of_screens*Application::CANVAS_WIDTH)-app.bitmaps[bitmap]->w))
            {

                no_right_movement = true;

            }

            if (left_platform != NO_PLATFORM_HIT)
            {

                if (level.platforms[left_platform]->type == Platform::PLATFORM)
                {

                    no_left_movement = true;

                }
                else if (x == 0)
                {

                    no_left_movement = true;

                }
                
            }
            else if (x == 0)
            {

                no_left_movement = true;

            }

            if (state != GOING_DOWN_PIPE)
            {
            
                if (app.signals & Application::SIGNAL_LEFT)
                {

                    tail_attack = (x_direction != -1);
                    x_direction = -1;

                }
                else if (app.signals & Application::SIGNAL_RIGHT)
                {

                    tail_attack = (x_direction != 1);
                    x_direction = 1;

                }
                
                if (app.signals & Application::SIGNAL_UP)
                {

                    if (on_ground && can_jump)
                    {

                        state = JUMPING;
                        can_jump = false;
                        y_direction = -1;

                    }

                }
                else
                {

                    can_jump = true;

                    if (state == JUMPING)
                    {

                        state = GLIDING;
                        y_direction = 1;

                    }

                }

                if ((app.signals & Application::SIGNAL_FLY) && !hit)
                {

                    if (!no_upper_movement && (strength > 1))
                    {

                        state = FLYING;
                        y_direction = -1;

                    }

                }
                else
                {

                    if (state == FLYING)
                    {

                        state = GLIDING;
                        y_direction = 1;

                    }

                }

                if (app.signals & Application::SIGNAL_DOWN)
                {

                    if (on_ground && ((level.platforms[bottom_platform]->id == Level::PIPE) ||
                                      (level.platforms[bottom_platform]->id == Level::LOCAL_PIPE)))
                    {

                        state = GOING_DOWN_PIPE;
                        pipe_x = level.platforms[bottom_platform]->x;
                        pipe_y = level.platforms[bottom_platform]->y;
                        y_direction = 1;
                        x_direction = 1;
                        x = pipe_x+4; // center the bird
                        local_pipe = (level.platforms[bottom_platform]->id == Level::LOCAL_PIPE);
                        play_sample(app.sound_effects[Application::WARP_SE], 255,
                                    128, 1000, 0);

                    }

                }
                
                if (app.signals & Application::SIGNAL_DELETE)
                {
                
                    hit = true;
                    strength = 0;
                
                }
                
            }
            
            if (state == IDLE)
            {

                bitmap = Application::BLUEJAY_STANDING_BM;

            }
            
            if (state == JUMPING)
            {

                bitmap = Application::BLUEJAY_STANDING_BM;
                
            }
            
            if (state == FLYING)
            {

                bitmap = Application::BLUEJAY_WINGS_IN_BM+(timer%2);
                flight_counter++;
                
                if (((flight_counter%(30*30)) == 0) && (strength > 1))
                {

                    strength--; // decrease energy on flight

                }
                
                if (hit || (strength == 1))
                {

                    state = GLIDING;
                    y_direction = 1;

                }

            }
            
            if (state == GLIDING)
            {

                bitmap = Application::BLUEJAY_WINGS_OUT_BM;
                
                if (on_ground)
                {

                    state = IDLE;

                }

            }
            
            if (state == GOING_DOWN_PIPE)
            {

                bitmap = Application::BLUEJAY_STANDING_BM;
                
                if (y == pipe_y)
                {

                    warped = true;
                    screen_pointer = pipe_x/Application::CANVAS_WIDTH;

                }
                else
                {

                    on_ground = false;

                }

            }

            Which_Platforms_Were_Hit(left_platform, right_platform, top_platform,
                                     bottom_platform, top_left_platform_head,
                                     bottom_left_platform_head, top_right_platform_head,
                                     bottom_right_platform_head, level, HEAD, app);
            
            if ((right_platform != NO_PLATFORM_HIT) && (x_direction == 1))
            {

                if ((level.platforms[right_platform]->id == Level::CHERRY) &&
                    !hit && !level.platforms[right_platform]->remove &&
                    ((strength < MAX_STRENGTH) || app.demo_playing))
                {
                
                    bitmap = Application::BLUEJAY_EATING_BM;
                    level.platforms[right_platform]->remove = true;
                    strength++;
                    
                }
                
                if ((level.platforms[right_platform]->id == Level::YELLOW_CHERRY) &&
                    !level.platforms[right_platform]->remove)
                {
                
                    bitmap = Application::BLUEJAY_EATING_BM;
                    level.platforms[right_platform]->remove = true;
                    lives++;
                
                }

            }

            if ((left_platform != NO_PLATFORM_HIT) && (x_direction == -1))
            {

                if ((level.platforms[left_platform]->id == Level::CHERRY) &&
                    !hit && !level.platforms[left_platform]->remove &&
                    ((strength < MAX_STRENGTH) || app.demo_playing))
                {
                
                    bitmap = Application::BLUEJAY_EATING_BM;
                    level.platforms[left_platform]->remove = true;
                    strength++;
                    
                }
                
                if ((level.platforms[left_platform]->id == Level::YELLOW_CHERRY) &&
                    !level.platforms[left_platform]->remove)
                {
                
                    bitmap = Application::BLUEJAY_EATING_BM;
                    level.platforms[left_platform]->remove = true;
                    lives++;
                
                }

            }
            
            character = Which_Character_Was_Hit(level, BODY, app, character_area,
                                                hit_results);
                                                
            if (character != NO_CHARACTER_HIT)
            {

                if ((level.characters[character]->id != Level::EGG) &&
                    !level.characters[character]->hit && !hit &&
                    (level.characters[character]->strength > 0) &&
                    (level.characters[character]->id != Level::GHOST) &&
                    (level.characters[character]->id != Level::MASTER_ECTO))
                {

                    if (hit_results & HIT_BOTTOM)
                    {

                        if ((level.characters[character]->id != Level::ROCK) &&
                            (level.characters[character]->id != Level::THROWABLE_ROCK) &&
                            (level.characters[character]->id != Level::TOMATOO_PLANT) &&
                            (level.characters[character]->id != Level::SPIKED_POLE) &&
                            (level.characters[character]->id != Level::BOILING_MUD) &&
                            level.characters[character]->Is_On_Screen(level.x, level.y, app))
                        {

                            if (level.characters[character]->strength == 1)
                            {
    
                                play_sample(app.sound_effects[Application::DAMAGING_STOMP_SE],
                                            255, 128, 1000, 0);
                                score += level.characters[character]->Get_Points();
    
                            }
                            else // level.characters[character]->strength > 1
                            {
    
                                play_sample(app.sound_effects[Application::USELESS_STOMP_SE],
                                            255, 128, 1000, 0);
    
                            }
    
                            level.characters[character]->hit = true;
                            state = JUMPING;
                            max_y = y-MAX_JUMP_HEIGHT;
                            y_direction = -1;
                            
                        }
                        else // rock, throwable rock, tomatoo plant, or spiked pole
                        {
                        
                            if ((state != GOING_DOWN_PIPE) &&
                                (level.characters[character]->id != Level::PIPE_SWITCH) &&
                                (level.characters[character]->id != Level::REVERSE_PIPE_SWITCH) &&
                                (level.characters[character]->id != Level::BOILING_MUD) &&
                                level.characters[character]->Is_On_Screen(level.x, level.y, app) &&
                                level.characters[character]->can_hurt)
                            {
                            
                                hit = true;
                                timer = 0;
                                strength--;
                                
                                if (level.characters[character]->id != Level::SUPER_MOSQUITO)
                                {
                                
                                    level.characters[character]->x_direction = -x_direction;
                                
                                }
                                
                                play_sample(app.sound_effects[Application::HIT_SE], 255,
                                            128, 1000, 0);
                            
                            }
                        
                        }
                        
                    }
                    else if (!(hit_results & HIT_BOTTOM) && (state != GOING_DOWN_PIPE) &&
                             (level.characters[character]->id != Level::PIPE_SWITCH) &&
                             (level.characters[character]->id != Level::REVERSE_PIPE_SWITCH) &&
                             level.characters[character]->can_hurt)
                    {

                        if ((hit_results & IS_INSIDE) &&
                            (level.characters[character]->id == Level::TOMATOO_PLANT) &&
                            level.characters[character]->Is_On_X_Screen(level.x, level.y, app))
                        {
                        
                            Tomatoo_Plant* tomatoo_plant = static_cast<Tomatoo_Plant*>(level.characters[character]);
                        
                            if (tomatoo_plant->hypergrowth_kill)
                            {
                        
                                strength = 0;
                                hit = true;
                                
                            }
                            else
                            {
                            
                                hit = true;
                                timer = 0;
                                strength--;
                            
                            }
                            
                            play_sample(app.sound_effects[Application::HIT_SE], 255,
                                        128, 1000, 0);
                        
                        }
                        else if ((hit_results & IS_INSIDE) &&
                                 (level.characters[character]->id == Level::SPIKED_POLE) &&
                                 level.characters[character]->Is_On_X_Screen(level.x, level.y, app))
                        {
                        
                            Spiked_Pole* spiked_pole = static_cast<Spiked_Pole*>(level.characters[character]);
                        
                            if (spiked_pole->extended)
                            {
                        
                                strength = 0;
                                hit = true;
                                
                            }
                            else
                            {
                            
                                hit = true;
                                timer = 0;
                                strength--;
                            
                            }
                            
                            play_sample(app.sound_effects[Application::HIT_SE], 255,
                                        128, 1000, 0);
                        
                        }
                        else if ((hit_results != 0) &&
                                 (level.characters[character]->id == Level::BOILING_MUD) &&
                                 level.characters[character]->Is_On_X_Screen(level.x, level.y, app))
                        {
                        
                            strength = 0;
                            hit = true;
                            play_sample(app.sound_effects[Application::HIT_SE], 255,
                                        128, 1000, 0);
                        
                        }
                        else if (level.characters[character]->Is_On_Screen(level.x, level.y, app))
                        {

                            hit = true;
                            timer = 0;
                            strength--;
                            
                            if (level.characters[character]->id != Level::SUPER_MOSQUITO)
                            {
                            
                                level.characters[character]->x_direction *= -1; // turn away
                            
                            }
                            
                            play_sample(app.sound_effects[Application::HIT_SE], 255,
                                        128, 1000, 0);
                            
                        }

                    }

                }
                else if (((level.characters[character]->id == Level::GHOST) ||
                          (level.characters[character]->id == Level::MASTER_ECTO)) &&
                         !hit && (state != GOING_DOWN_PIPE) && !died &&
                         level.characters[character]->Is_On_Screen(level.x, level.y, app) &&
                         (level.signal != Level::SIGNAL_DESTROY_ECTO))
                {
                
                    int action = rand()%3;
                
                    if (action == 0)
                    {

                        if (x > initial_x)
                        {

                            x = initial_x+((rand()%((x-initial_x)/4))*4);

                        }
                        else // x <= initial_x
                        {

                            x = initial_x;

                        }

                        level.reposition = true;
                        
                    }
                    else if (action == 1)
                    {
                    
                        hit = true;
                        timer = 0;
                    
                    }
                    else // action == 2
                    {
                    
                        x_direction *= -1;
                    
                    }
                
                }

            }
            
            character = Which_Character_Was_Hit(level, HEAD, app, character_area,
                                                hit_results);
                                                
            if (character != NO_CHARACTER_HIT)
            {

                if ((level.characters[character]->id == Level::EGG) &&
                    !level.characters[character]->hit && !hit)
                {

                    if (x_direction == 1)
                    {

                        if (hit_results & HIT_RIGHT)
                        {

                            play_sample(app.sound_effects[Application::GRAB_EGG_SE], 255, 128,
                                        1000, 0);
                            level.characters[character]->hit = true;
                            eggs++;
                            strength += 3;
                            bitmap = Application::BLUEJAY_EATING_BM;
                            
                            if (strength > MAX_STRENGTH)
                            {
                            
                                strength = MAX_STRENGTH;
                            
                            }
                            
                        }
                    
                    }
                    else // x_direction == -1
                    {

                        if (hit_results & HIT_LEFT)
                        {

                            play_sample(app.sound_effects[Application::GRAB_EGG_SE], 255, 128,
                                        1000, 0);
                            level.characters[character]->hit = true;
                            eggs++;
                            strength += 3;
                            bitmap = Application::BLUEJAY_EATING_BM;
                            
                            if (strength > MAX_STRENGTH)
                            {
                            
                                strength = MAX_STRENGTH;
                            
                            }
                        
                        }

                    }

                }

            }
            
            character = Which_Character_Was_Hit(level, TAIL, app, character_area,
                                                hit_results);
                                                
            if (character != NO_CHARACTER_HIT)
            {
            
                if (hit_results != 0)
                {
                
                    if ((level.characters[character]->id != Level::EGG) &&
                        !level.characters[character]->hit && !hit &&
                        (level.characters[character]->strength > 0) &&
                        (level.characters[character]->id != Level::GHOST) &&
                        (level.characters[character]->id != Level::MASTER_ECTO) &&
                        (level.characters[character]->id != Level::ROCK) &&
                        (level.characters[character]->id != Level::THROWABLE_ROCK) &&
                        (level.characters[character]->id != Level::TOMATOO_PLANT) &&
                        (level.characters[character]->id != Level::SPIKED_POLE) &&
                        (level.characters[character]->id != Level::BOILING_MUD) &&
                        tail_attack && level.characters[character]->Is_On_Screen(level.x, level.y, app))
                    {

                        if (level.characters[character]->strength == 1)
                        {

                            play_sample(app.sound_effects[Application::DAMAGING_STOMP_SE],
                                        255, 128, 1000, 0);
                            score += level.characters[character]->Get_Points();

                        }
                        else // level.characters[character]->strength > 1
                        {

                            play_sample(app.sound_effects[Application::USELESS_STOMP_SE],
                                        255, 128, 1000, 0);

                        }

                        level.characters[character]->hit = true;
                        
                    }
                
                }
            
            }
            
            if (hit)
            {
            
                if (timer == (30*3))
                {

                    hit = false;

                }
                
            }
            
            if (top_left_platform_body != NO_PLATFORM_HIT)
            {

                if (level.platforms[top_left_platform_body]->type == Platform::PLATFORM)
                {

                    if ((x_direction == -1) && (y_direction == -1) &&
                        !no_left_movement && !no_upper_movement &&
                        ((state == JUMPING) || (state == FLYING)))
                    {

                        no_left_movement = true;
                        no_upper_movement = true;
                        state = GLIDING;
                        y_direction = 1;

                    }

                }

            }
            
            if (top_right_platform_body != NO_PLATFORM_HIT)
            {

                if (level.platforms[top_right_platform_body]->type == Platform::PLATFORM)
                {

                    if ((x_direction == 1) && (y_direction == -1) &&
                        !no_right_movement && !no_upper_movement &&
                        ((state == JUMPING) || (state == FLYING)))
                    {

                        no_right_movement = true;
                        no_upper_movement = true;
                        state = GLIDING;
                        y_direction = 1;

                    }

                }

            }
            
            if (bottom_left_platform_body != NO_PLATFORM_HIT)
            {

                if (level.platforms[bottom_left_platform_body]->type == Platform::PLATFORM)
                {

                    if ((x_direction == -1) && (y_direction == 1) &&
                        !no_left_movement && !on_ground)
                    {

                        no_left_movement = true;

                    }

                }

            }

            if (bottom_right_platform_body != NO_PLATFORM_HIT)
            {

                if (level.platforms[bottom_right_platform_body]->type == Platform::PLATFORM)
                {

                    if ((x_direction == 1) && (y_direction == 1) &&
                        !no_right_movement && !on_ground)
                    {

                        no_right_movement = true;

                    }

                }

            }

            if ((state != IDLE) && (state != GOING_DOWN_PIPE))
            {

                if (x_direction == 1)
                {

                    if (!no_right_movement)
                    {

                        x += 4;
                        level.scroll_x = true;
                        level.x_direction = 1;

                    }

                }
                else // x_direction == -1
                {

                    if (!no_left_movement)
                    {
                        
                        x -= 4;
                        level.scroll_x = true;
                        level.x_direction = -1;
                        
                    }

                }
                    
            }
            
            if (y_direction == 1)
            {
            
                if (!on_ground)
                {

                    y += 4;
                    level.scroll_y = true;
                    level.y_direction = 1;

                }
                
            }
            else // y_direction == -1
            {

                if (!no_upper_movement)
                {

                    y -= 4;
                    level.scroll_y = true;
                    level.y_direction = -1;
                
                }

            }

        }
        else // strength == 0
        {

            bitmap = Application::BLUEJAY_HURT_BM;
            y += 4;
            
            if (!died)
            {
            
                died = true;
                lives--;
                stop_midi();
                play_sample(app.sound_effects[Application::BLUEJAY_DIES_SE], 255, 128,
                            1000, 0);
                            
            }

        }
        
        if (hit)
        {

            if ((timer%2) == 0)
            {

                if (x_direction == -1)
                {

                    draw_sprite_h_flip(app.canvas, app.bitmaps[bitmap], (x-level.x),
                                       (y-level.y));

                }
                else // x_direction == 1
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

                draw_sprite_h_flip(app.canvas, app.bitmaps[bitmap], (x-level.x),
                                   (y-level.y));

            }
            else // x_direction == 1
            {

                draw_sprite(app.canvas, app.bitmaps[bitmap], (x-level.x),
                            (y-level.y));

            }

        }
        
        if (state == GOING_DOWN_PIPE)
        {

            draw_sprite(app.canvas, app.bitmaps[Application::PIPE_BM],
                        (pipe_x-level.x), (pipe_y-level.y));

        }
        
    }
    
    // this code takes care of off screen falls

    if (!Is_On_Screen(level.x, level.y, app))
    {
    
        if (y == Application::CANVAS_HEIGHT)
        {

            if (!died)
            {
        
                died = true;
                lives--;
        
            }

        }
    
    }

}

void Bluejay::Copy_Status(Bluejay& bluejay)
{

    bluejay.bitmap = bitmap;
    bluejay.strength = strength;
    bluejay.flight_counter = flight_counter;
    bluejay.hit = hit;
    bluejay.timer = timer;
    bluejay.lives = lives;
    bluejay.eggs = eggs;
    bluejay.score = score;

}

void Bluejay::Reset(bool demo_playing)
{

    if (!local_pipe)
    {
    
        x = initial_x;
        y = initial_y;
    
    }

    warped = false;
    x_direction = 1;
    y_direction = 1;
    state = GLIDING;
    local_pipe = false;
    
    if (died)
    {

        died = false;
        strength = 3;
        hit = false;
        flight_counter = 0;
    
    }

}

void Bluejay::Get_Bump_Map(Rectangle& map,
                           int area,
                           Application& app)
{


    if (area == HEAD)
    {

        if (x_direction == -1)
        {

            Flip_Bump_Map((*bump_maps[area]), map, app);
            map.left += (x/4);
            map.right += (x/4);
            map.top += (y/4);
            map.bottom += (y/4);

        }
        else // x_direction == 1
        {

            map.left = (x/4)+bump_maps[area]->left;
            map.right = (x/4)+bump_maps[area]->right;
            map.top = (y/4)+bump_maps[area]->top;
            map.bottom = (y/4)+bump_maps[area]->bottom;

        }

    }
    else if (area == BODY)
    {

        map.left = (x/4)+bump_maps[area]->left;
        map.right = (x/4)+bump_maps[area]->right;
        map.top = (y/4)+bump_maps[area]->top;
        map.bottom = (y/4)+bump_maps[area]->bottom;

    }
    else // area == TAIL
    {
    
        if (x_direction == -1)
        {

            Flip_Bump_Map((*bump_maps[area]), map, app);
            map.left += (x/4);
            map.right += (x/4);
            map.top += (y/4);
            map.bottom += (y/4);

        }
        else // x_direction == 1
        {

            map.left = (x/4)+bump_maps[area]->left;
            map.right = (x/4)+bump_maps[area]->right;
            map.top = (y/4)+bump_maps[area]->top;
            map.bottom = (y/4)+bump_maps[area]->bottom;

        }
    
    }

}
