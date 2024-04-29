#include <allegro.h>
#include "character.hpp"
#include "application.hpp"
#include "level.hpp"

const int Character::MAX_BUMP_MAPS = 15;
const int Character::NO_PLATFORM_HIT = -1;
const int Character::NO_CHARACTER_HIT = -1;
const int Character::SIGNAL_ATTACK_BLUEJAY = 1;
const int Character::HIT_LEFT = 1;
const int Character::HIT_RIGHT = 2;
const int Character::HIT_TOP = 4;
const int Character::HIT_BOTTOM = 8;
const int Character::HIT_TOP_LEFT = 16;
const int Character::HIT_BOTTOM_LEFT = 32;
const int Character::HIT_TOP_RIGHT = 64;
const int Character::HIT_BOTTOM_RIGHT = 128;
const int Character::IS_INSIDE = 256;

Character::Character()
{

    int bump_map = 0;

    timer = 0;
    bump_maps = new Rectangle* [MAX_BUMP_MAPS];
    number_of_bump_maps = 0;
    x_direction = 1;
    y_direction = 1;
    hit = false;
    signal = 0;
    can_hurt = true;
    
    while (bump_map < MAX_BUMP_MAPS)
    {

        bump_maps[bump_map] = new Rectangle();
        bump_map++;

    }

}

Character::~Character()
{

    int bump_map = 0;
    
    while (bump_map < MAX_BUMP_MAPS)
    {

        delete bump_maps[bump_map];
        bump_map++;

    }
    
    delete[] bump_maps;

}

void Character::Load_Bump_Maps(const char* bump_map_db)
{

    ifstream file;
    
    file.open(bump_map_db);
    
    if (file)
    {

        while (!file.eof())
        {

            file >> bump_maps[number_of_bump_maps]->left;
            
            if (!file.eof())
            {

                file >> bump_maps[number_of_bump_maps]->top;
                file >> bump_maps[number_of_bump_maps]->right;
                file >> bump_maps[number_of_bump_maps]->bottom;
                number_of_bump_maps++;

            }

        }

    }

}

bool Character::Is_On_Screen(int level_x,
                             int level_y,
                             Application& app)
{

    int screen_x = x-level_x;
    int screen_y = y-level_y;
    
    return (((screen_x+app.bitmaps[bitmap]->w-1) >= 0) && (screen_x < Application::CANVAS_WIDTH) &&
            ((screen_y+app.bitmaps[bitmap]->h-1) >= 0) && (screen_y < Application::CANVAS_HEIGHT));

}

void Character::Which_Platforms_Were_Hit(int& left_platform,
                                         int& right_platform,
                                         int& top_platform,
                                         int& bottom_platform,
                                         int& top_left_platform,
                                         int& bottom_left_platform,
                                         int& top_right_platform,
                                         int& bottom_right_platform,
                                         Level& level,
                                         int area,
                                         Application& app)
{

    int platform = 0;
    
    left_platform = NO_PLATFORM_HIT;
    right_platform = NO_PLATFORM_HIT;
    top_platform = NO_PLATFORM_HIT;
    bottom_platform = NO_PLATFORM_HIT;
    top_left_platform = NO_PLATFORM_HIT;
    bottom_left_platform = NO_PLATFORM_HIT;
    top_right_platform = NO_PLATFORM_HIT;
    bottom_right_platform = NO_PLATFORM_HIT;
    
    while (platform < level.number_of_platforms)
    {

        if (level.platforms[platform]->type != Platform::BACKGROUND)
        {

            Rectangle character_bump_map;
            Rectangle platform_bump_map;

            Get_Bump_Map(character_bump_map, area, app);
            level.platforms[platform]->Get_Bump_Map(platform_bump_map, app);

            if (character_bump_map.Is_Touching_Left(platform_bump_map))
            {

                left_platform = platform;

            }
            
            if (character_bump_map.Is_Touching_Right(platform_bump_map))
            {

                right_platform = platform;

            }
            
            if (character_bump_map.Is_Touching_Top(platform_bump_map))
            {

                top_platform = platform;

            }
            
            if (character_bump_map.Is_Touching_Bottom(platform_bump_map))
            {

                bottom_platform = platform;

            }
            
            if (character_bump_map.Is_Touching_Top_Left_Corner(platform_bump_map))
            {

                top_left_platform = platform;

            }
            
            if (character_bump_map.Is_Touching_Bottom_Left_Corner(platform_bump_map))
            {

                bottom_left_platform = platform;

            }
            
            if (character_bump_map.Is_Touching_Top_Right_Corner(platform_bump_map))
            {

                top_right_platform = platform;

            }
            
            if (character_bump_map.Is_Touching_Bottom_Right_Corner(platform_bump_map))
            {

                bottom_right_platform = platform;

            }

        }
        
        platform++;

    }

}

int Character::Which_Character_Was_Hit(Level& level,
                                       int area,
                                       Application& app,
                                       int& character_area,
                                       int& hit_results)
{

    int character = 0;
    int character_hit = NO_CHARACTER_HIT;
    
    hit_results = 0;
    
    while (character < level.number_of_characters)
    {

        if (level.characters[character] != this) // not self
        {

            Rectangle my_bump_map;

            character_area = 0;
            Get_Bump_Map(my_bump_map, area, app);
            
            while (character_area < level.characters[character]->number_of_areas)
            {

                Rectangle character_bump_map;

                level.characters[character]->Get_Bump_Map(character_bump_map,
                                                          character_area, app);

                if (my_bump_map.Is_Touching_Bottom(character_bump_map))
                {

                    hit_results |= HIT_BOTTOM;

                }

                if (my_bump_map.Is_Touching_Top(character_bump_map))
                {

                    hit_results |= HIT_TOP;

                }
                
                if (my_bump_map.Is_Touching_Left(character_bump_map))
                {

                    hit_results |= HIT_LEFT;

                }
                
                if (my_bump_map.Is_Touching_Right(character_bump_map))
                {

                    hit_results |= HIT_RIGHT;

                }
                
                if (my_bump_map.Is_Touching_Top_Left_Corner(character_bump_map))
                {

                    hit_results |= HIT_TOP_LEFT;

                }
                
                if (my_bump_map.Is_Touching_Top_Right_Corner(character_bump_map))
                {

                    hit_results |= HIT_TOP_RIGHT;

                }
                
                if (my_bump_map.Is_Touching_Bottom_Left_Corner(character_bump_map))
                {

                    hit_results |= HIT_BOTTOM_LEFT;

                }
                
                if (my_bump_map.Is_Touching_Bottom_Right_Corner(character_bump_map))
                {

                    hit_results |= HIT_BOTTOM_RIGHT;

                }
                
                if (my_bump_map.Is_Inside(character_bump_map))
                {
                
                    hit_results |= IS_INSIDE;
                
                }

                if (hit_results != 0)
                {

                    character_hit = character;
                    character = level.number_of_characters;
                    break;

                }
                
                character_area++;

            }
        
        }

        character++;

    }
    
    return character_hit;

}

void Character::Reset(bool demo_playing)
{

    x = initial_x;
    y = initial_y;

}

void Character::Get_Bump_Map(Rectangle& map,
                             int area,
                             Application& app)
{

    map.left = (x/4)+bump_maps[area]->left;
    map.right = (x/4)+bump_maps[area]->right;
    map.top = (y/4)+bump_maps[area]->top;
    map.bottom = (y/4)+bump_maps[area]->bottom;

}

void Character::Flip_Bump_Map(Rectangle& unflipped_map,
                              Rectangle& flipped_map,
                              Application& app)
{

    flipped_map.right = -unflipped_map.left+((app.bitmaps[bitmap]->w-1)/4);
    flipped_map.left = -unflipped_map.right+((app.bitmaps[bitmap]->w-1)/4);
    flipped_map.top = unflipped_map.top;
    flipped_map.bottom = unflipped_map.bottom;

}

bool Character::Is_On_X_Screen(int level_x,
                               int level_y,
                               Application& app)
{

    int screen_x = x-level_x;

    return (((screen_x+app.bitmaps[bitmap]->w-1) >= 0) &&
             (screen_x < Application::CANVAS_WIDTH));

}

int Character::Get_Points()
{

    return 10;

}
