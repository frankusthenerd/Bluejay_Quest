#include <allegro.h>
#include "platform.hpp"
#include "level.hpp"
#include "application.hpp"

const int Platform::PLATFORM = 1;
const int Platform::ITEM = 2;
const int Platform::BACKGROUND = 3;

Platform::Platform()
{

    bypass_default_bump_map = false;
    remove = false;
    timer = 0;

}

void Platform::Initialize()
{
   
    initial_x = x;
    initial_y = y;
   
    if (id == Level::BROWN_BLOCK)
    {

        bitmap = Application::BROWN_BLOCK_BM;
        type = PLATFORM;

    }

    if (id == Level::CEMENT_BLOCK)
    {

        bitmap = Application::CEMENT_BLOCK_BM;
        type = PLATFORM;

    }

    if (id == Level::BIG_BUSH)
    {

        bitmap = Application::BIG_BUSH_BM;
        type = BACKGROUND;

    }

    if (id == Level::SMALL_BUSH)
    {

        bitmap = Application::SMALL_BUSH_BM;
        type = BACKGROUND;

    }

    if (id == Level::CHERRY)
    {

        bitmap = Application::CHERRY_BM;
        type = ITEM;

    }

    if (id == Level::GROUND)
    {

        bitmap = Application::GROUND_BM;
        type = PLATFORM;

    }

    if (id == Level::PIPE)
    {

        bitmap = Application::PIPE_BM;
        type = PLATFORM;

    }
    
    if (id == Level::LIMESTONE)
    {
    
        bitmap = Application::LIMESTONE_BM;
        type = PLATFORM;
    
    }
    
    if (id == Level::LEDGE)
    {
    
        bitmap = Application::LEDGE_BM;
        type = PLATFORM;
    
    }
    
    if (id == Level::WALK_THROUGH_DIRT)
    {
    
        bitmap = Application::WALK_THROUGH_DIRT_BM;
        type = BACKGROUND;
    
    }
    
    if (id == Level::WIRE)
    {
    
        bitmap = Application::WIRE_BM;
        type = PLATFORM;
    
    }
    
    if (id == Level::STOPPER)
    {
    
        bitmap = Application::STOPPER_BM;
        type = PLATFORM;
    
    }
    
    if (id == Level::LOCAL_PIPE)
    {
    
        bitmap = Application::PIPE_BM;
        type = PLATFORM;
    
    }
    
    if (id == Level::STONE_WALL)
    {
    
        bitmap = Application::STONE_WALL_BM;
        type = BACKGROUND;
    
    }
    
    if (id == Level::FAKE_CEMENT_BLOCK)
    {
    
        bitmap = Application::CEMENT_BLOCK_BM;
        type = BACKGROUND;
    
    }
    
    if (id == Level::YELLOW_CHERRY)
    {
    
        bitmap = Application::YELLOW_CHERRY_BM;
        type = ITEM;
    
    }
    
    if (id == Level::SHORT_VINE)
    {
    
        bitmap = Application::SHORT_VINE_BM;
        type = BACKGROUND;
    
    }
    
    if (id == Level::TALL_VINE)
    {
    
        bitmap = Application::TALL_VINE_BM;
        type = BACKGROUND;
    
    }

}

void Platform::Get_Bump_Map(Rectangle& map,
                            Application& app)
{

    if (bypass_default_bump_map)
    {

        map.left = (x/4)+loaded_bump_map.left;
        map.top = (y/4)+loaded_bump_map.top;
        map.right = (x/4)+loaded_bump_map.right;
        map.bottom = (y/4)+loaded_bump_map.bottom;

    }
    else
    {

        map.left = x/4;
        map.top = y/4;
        map.right = (x/4)+(app.bitmaps[bitmap]->w/4)-1;
        map.bottom = (y/4)+(app.bitmaps[bitmap]->h/4)-1;
        
    }

}

void Platform::Process(Application& app,
                       int level_x,
                       int level_y)
{

    if (!remove)
    {
    
        timer++;
    
        if ((id == Level::PIPE) || (id == Level::LOCAL_PIPE))
        {
        
            if ((timer%2) == 0)
            {
        
                if (app.levels[app.current_level]->signal == Level::SIGNAL_LOWER_PIPES)
                {
        
                    if (y < Application::CANVAS_HEIGHT)
                    {
        
                        y += 4;
                        
                    }
                    
                }
                
                if (app.levels[app.current_level]->signal == Level::SIGNAL_RAISE_PIPES)
                {
                
                    if (y > initial_y)
                    {
                
                        y -= 4;
                        
                    }
                
                }
                
            }
        
        }
        
        if (id == Level::CEMENT_BLOCK)
        {
        
            if (app.levels[app.current_level]->signal == Level::SIGNAL_COLLAPSE_CEMENT)
            {
                
                if ((timer%4) == 0)
                {
                
                    y += 4;
                    
                }
            
            }
        
        }

        if (id != Level::STOPPER)
        {

            draw_sprite(app.canvas, app.bitmaps[bitmap], (x-level_x), (y-level_y));
            
        }

    }

}

void Platform::Load_Bump_Map(const char* bump_map)
{

    ifstream file;
    
    file.open(bump_map);
    
    if (file)
    {

        file >> loaded_bump_map.left;
        file >> loaded_bump_map.top;
        file >> loaded_bump_map.right;
        file >> loaded_bump_map.bottom;
        bypass_default_bump_map = true;

    }

}
