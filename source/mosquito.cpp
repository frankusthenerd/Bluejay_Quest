#include <allegro.h>
#include "mosquito.hpp"
#include "application.hpp"
#include "level.hpp"

const int Mosquito::IDLE = 1;
const int Mosquito::ATTACKING = 2;

Mosquito::Mosquito()
{

    id = Level::MOSQUITO;
    bitmap = Application::MOSQUITO_WINGS_DOWN_BM;
    strength = 1;
    number_of_areas = 1;
    state = IDLE;

}

void Mosquito::Process(Application& app,
                       Level& level)
{

    if (Is_On_Screen(level.x, level.y, app))
    {

        timer++;
        
        if (level.signal == Level::SIGNAL_COLLAPSE_CEMENT)
        {
        
            hit = true;
        
        }
        
        if (strength > 0)
        {

            if (hit)
            {

                strength--;

            }
            else // not hit
            {

                bitmap = Application::MOSQUITO_WINGS_DOWN_BM+(timer%2);

                if (state == IDLE)
                {

                    if ((rand()%50) == 0)
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
                        play_sample(app.sound_effects[Application::MOSQUITO_SE],
                                    255, 128, 1000, 0);

                    }

                }
                
                if (state == ATTACKING)
                {

                    if ((rand()%20) == 0)
                    {

                        state = IDLE;

                    }

                    x += (x_direction*4);
                    y += (y_direction*4);
                        
                }

            }
            
        }
        else // strength == 0
        {

            y += 4;

        }

        draw_sprite(app.canvas, app.bitmaps[bitmap], (x-level.x), (y-level.y));

    }
    else if (level.signal == Level::SIGNAL_ATTACK_BLUEJAY)
    {

        if (strength > 0)
        {

            int bluejay_middle_x = level.characters[level.bluejay]->x+(app.bitmaps[level.characters[level.bluejay]->bitmap]->w/2);
            int bluejay_middle_y = level.characters[level.bluejay]->y+(app.bitmaps[level.characters[level.bluejay]->bitmap]->h/2);

            if (x < bluejay_middle_x)
            {

                x += 4;

            }

            if (x > bluejay_middle_x)
            {

                x -= 4;

            }

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
