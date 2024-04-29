#include <allegro.h>
#include "level.hpp"
#include "application.hpp"
#include "black_bird.hpp"
#include "bluejay.hpp"
#include "clam.hpp"
#include "egg.hpp"
#include "fly.hpp"
#include "mosquito.hpp"
#include "ghost.hpp"
#include "master_ecto.hpp"
#include "rock.hpp"
#include <fstream>
#include "macros.hpp"
#include <cstring>
#include "goldenjay.hpp"
#include "swooper.hpp"
#include "switch.hpp"
#include "super_mosquito.hpp"
#include "throwable_rock.hpp"
#include "lemming.hpp"
#include "stop_attack_object.hpp"
#include "tomatoo_plant.hpp"
#include "scrolling_background_object.hpp"
#include "message_object.hpp"
#include "spiked_pole.hpp"
#include "boiling_mud.hpp"
#include "mud_drop.hpp"

using namespace std;

const int Level::BLACK_BIRD = 1; // characters
const int Level::BLUEJAY = 2;
const int Level::CLAM = 3;
const int Level::EGG = 4;
const int Level::FLY = 5;
const int Level::MOSQUITO = 6;
const int Level::SHOUTING_BLACK_BIRD = 7;
const int Level::LEAPING_BLACK_BIRD = 8;
const int Level::GHOST = 9;
const int Level::MASTER_ECTO = 10;
const int Level::ROCK = 11;
const int Level::GOLDENJAY = 12;
const int Level::SWOOPER = 13;
const int Level::LOCAL_ROCK = 14;
const int Level::PIPE_SWITCH = 15;
const int Level::REVERSE_PIPE_SWITCH = 16;
const int Level::SUPER_MOSQUITO = 17;
const int Level::LEMMING = 18;
const int Level::THROWABLE_ROCK = 19;
const int Level::STOP_ATTACK_OBJECT = 20;
const int Level::HUNTING_FLY = 21;
const int Level::TOMATOO_PLANT = 22;
const int Level::SCROLLING_BACKGROUND = 23;
const int Level::MESSAGE_OBJECT = 24;
const int Level::SPIKED_POLE = 25;
const int Level::BOILING_MUD = 26;
const int Level::MUD_DROP = 27;
const int Level::NO_ECTO_SWITCH = 28;
const int Level::BROWN_BLOCK = 1000; // "platforms"
const int Level::CEMENT_BLOCK = 1001;
const int Level::BIG_BUSH = 1002;
const int Level::SMALL_BUSH = 1003;
const int Level::CHERRY = 1004;
const int Level::GROUND = 1005;
const int Level::PIPE = 1006;
const int Level::LIMESTONE = 1007;
const int Level::LEDGE = 1008;
const int Level::WALK_THROUGH_DIRT = 1009;
const int Level::WIRE = 1010;
const int Level::STOPPER = 1011;
const int Level::LOCAL_PIPE = 1012;
const int Level::STONE_WALL = 1013;
const int Level::FAKE_CEMENT_BLOCK = 1014;
const int Level::YELLOW_CHERRY = 1015;
const int Level::SHORT_VINE = 1016;
const int Level::TALL_VINE = 1017;
const int Level::MAX_CHARACTERS = 2000;
const int Level::MAX_PLATFORMS = 5000;
const int Level::NUMBER_OF_POINTERS = 50;
const int Level::MAX_HEIGHT = 50;
const int Level::SIGNAL_ATTACK_BLUEJAY = 1;
const int Level::SIGNAL_LOWER_PIPES = 2;
const int Level::SIGNAL_RAISE_PIPES = 3;
const int Level::SIGNAL_COLLAPSE_CEMENT = 4;
const int Level::SIGNAL_DESTROY_ECTO = 5;
const int Level::HEIGHT_ERROR = 1;

Level::Level()
{

    int platform = 0;
    int character = 0;

    number_of_platforms = 0;
    platforms = new Platform* [MAX_PLATFORMS];
    pointers = new int[NUMBER_OF_POINTERS];
    number_of_characters = 0;
    characters = new Character* [MAX_CHARACTERS];
    x = 0;
    y = 0;
    entered_level = true;
    signal = 0;
    platform_objects = new Object* [MAX_PLATFORMS];
    character_objects = new Object* [MAX_CHARACTERS];
    platform = 0;
    character = 0;
    background = Application::GRASS_BACKGROUND_BM;
    music_track = Application::ATHLETIC_THEME_MT;
    memset(pointers, 0, (NUMBER_OF_POINTERS*sizeof(int)));
    background_x = 0;
    autoscroll_background = false;
    display_message = false;
    displayed_message = false;
    timer = 0;
    
    while (platform < MAX_PLATFORMS)
    {

        platforms[platform] = new Platform();
        platform++;

    }

    while (character < MAX_CHARACTERS)
    {

        characters[character] = NULL;
        character++;

    }
    
    platform = 0;
    character = 0;
    
    while (platform < MAX_PLATFORMS)
    {

        platform_objects[platform] = new Object();
        platform++;

    }

    while (character < MAX_CHARACTERS)
    {

        character_objects[character] = new Object();
        character++;

    }

}

Level::~Level()
{

    int platform = 0;
    int character = 0;
    
    while (platform < MAX_PLATFORMS)
    {

        delete platforms[platform];
        platform++;

    }
    
    while (character < MAX_CHARACTERS)
    {

        delete characters[character];
        character++;

    }
    
    platform = 0;
    character = 0;
    
    while (platform < MAX_PLATFORMS)
    {
    
        delete platform_objects[platform];
        platform++;
    
    }
    
    while (character < MAX_CHARACTERS)
    {
    
        delete character_objects[character];
        character++;
    
    }
    
    delete[] platforms;
    delete[] pointers;
    delete[] characters;
    delete[] platform_objects;
    delete[] character_objects;

}

/*
 * Levels are formatted as shown below.
 *
 * background
 * music track
 * character 1 id
 * character 1 x
 * character 1 y
 * .
 * .
 * .
 * character n id
 * character n x
 * character n y
 * -1
 * platform 1 id
 * platform 1 x
 * platform 1 y
 * .
 * .
 * .
 * platform n id
 * platform n x
 * platform n y
 * -1
 * pointer 1
 * .
 * .
 * .
 * pointer n
 */

void Level::Load(const char* level)
{

    ifstream file;
    
    file.open(level);
    
    if (file)
    {

        int id = 0;
        int x;
        int y;
        int pointer = 0;
        int platform = 0;
        int biggest_x = 0;
        int smallest_y = 400;

        file >> background;
        file >> music_track;
        
        while (id != -1)
        {

            file >> id;
            
            if (id != -1)
            {
            
                file >> x;
                file >> y;

                if (id == BLACK_BIRD)
                {

                    characters[number_of_characters] = new Black_Bird();
                    Load_Bump_Map_For_Character("data\\bump_maps\\black_bird.map", characters, number_of_characters);

                }
                
                if (id == BLUEJAY)
                {

                    characters[number_of_characters] = new Bluejay();
                    Load_Bump_Map_For_Character("data\\bump_maps\\bluejay.map", characters, number_of_characters);
                    bluejay = number_of_characters;

                }
                
                if (id == CLAM)
                {

                    characters[number_of_characters] = new Clam();
                    Load_Bump_Map_For_Character("data\\bump_maps\\clam.map", characters, number_of_characters);

                }
                
                if (id == EGG)
                {

                    characters[number_of_characters] = new Egg();
                    Load_Bump_Map_For_Character("data\\bump_maps\\egg.map", characters, number_of_characters);

                }
                
                if (id == FLY)
                {

                    characters[number_of_characters] = new Fly();
                    Load_Bump_Map_For_Character("data\\bump_maps\\fly.map", characters, number_of_characters);

                }
                
                if (id == MOSQUITO)
                {

                    characters[number_of_characters] = new Mosquito();
                    Load_Bump_Map_For_Character("data\\bump_maps\\mosquito.map", characters, number_of_characters);

                }
                
                if (id == SHOUTING_BLACK_BIRD)
                {

                    Black_Bird* shouting_black_bird;

                    characters[number_of_characters] = new Black_Bird();
                    Load_Bump_Map_For_Character("data\\bump_maps\\black_bird.map", characters, number_of_characters);
                    shouting_black_bird = static_cast<Black_Bird*>(characters[number_of_characters]);
                    shouting_black_bird->mode = Black_Bird::SHOUT;

                }
                
                if (id == LEAPING_BLACK_BIRD)
                {

                    Black_Bird* leaping_black_bird;

                    characters[number_of_characters] = new Black_Bird();
                    Load_Bump_Map_For_Character("data\\bump_maps\\black_bird.map", characters, number_of_characters);
                    leaping_black_bird = static_cast<Black_Bird*>(characters[number_of_characters]);
                    leaping_black_bird->mode = Black_Bird::LEAP;

                }
                
                if (id == GHOST)
                {
                
                    characters[number_of_characters] = new Ghost();
                    Load_Bump_Map_For_Character("data\\bump_maps\\ghost.map", characters, number_of_characters);
                
                }
                
                if (id == MASTER_ECTO)
                {
                
                    characters[number_of_characters] = new Master_Ecto();
                    Load_Bump_Map_For_Character("data\\bump_maps\\master_ecto.map", characters, number_of_characters);
                
                }
                
                if (id == ROCK)
                {
                
                    characters[number_of_characters] = new Rock();
                    Load_Bump_Map_For_Character("data\\bump_maps\\rock.map", characters, number_of_characters);
                
                }
                
                if (id == GOLDENJAY)
                {
                
                    characters[number_of_characters] = new Goldenjay();
                    Load_Bump_Map_For_Character("data\\bump_maps\\goldenjay.map", characters, number_of_characters);
                
                }
                
                if (id == SWOOPER)
                {
                
                    characters[number_of_characters] = new Swooper();
                    Load_Bump_Map_For_Character("data\\bump_maps\\swooper.map", characters, number_of_characters);
                
                }
                
                if (id == LOCAL_ROCK)
                {
                
                    Rock* rock;
                
                    characters[number_of_characters] = new Rock();
                    Load_Bump_Map_For_Character("data\\bump_maps\\rock.map", characters, number_of_characters);
                    rock = static_cast<Rock*>(characters[number_of_characters]);
                    rock->local = true;
                
                }
                
                if (id == PIPE_SWITCH)
                {
                
                    characters[number_of_characters] = new Switch();
                    Load_Bump_Map_For_Character("data\\bump_maps\\switch.map", characters, number_of_characters);
                
                }
                
                if (id == REVERSE_PIPE_SWITCH)
                {
                
                    Switch* s;
                
                    characters[number_of_characters] = new Switch();
                    Load_Bump_Map_For_Character("data\\bump_maps\\switch.map", characters, number_of_characters);
                    s = static_cast<Switch*>(characters[number_of_characters]);
                    s->mode = Switch::REVERSE_PIPE;
                
                }
                
                if (id == SUPER_MOSQUITO)
                {
                
                    characters[number_of_characters] = new Super_Mosquito();
                    Load_Bump_Map_For_Character("data\\bump_maps\\super_mosquito.map", characters, number_of_characters);
                
                }
                
                if (id == LEMMING)
                {
                
                    characters[number_of_characters] = new Lemming();
                    Load_Bump_Map_For_Character("data\\bump_maps\\lemming.map", characters, number_of_characters);
                
                }
                
                if (id == THROWABLE_ROCK)
                {
                
                    characters[number_of_characters] = new Throwable_Rock();
                    Load_Bump_Map_For_Character("data\\bump_maps\\throwable_rock.map", characters, number_of_characters);
                
                }
                
                if (id == STOP_ATTACK_OBJECT)
                {
                
                    characters[number_of_characters] = new Stop_Attack_Object();
                
                }
                
                if (id == HUNTING_FLY)
                {
                
                    Fly* fly;
                
                    characters[number_of_characters] = new Fly();
                    Load_Bump_Map_For_Character("data\\bump_maps\\fly.map", characters, number_of_characters);
                    fly = static_cast<Fly*>(characters[number_of_characters]);
                    fly->hunter = true;
                
                }
                
                if (id == TOMATOO_PLANT)
                {
                
                    characters[number_of_characters] = new Tomatoo_Plant();
                    Load_Bump_Map_For_Character("data\\bump_maps\\tomatoo_plant.map", characters, number_of_characters);
                
                }
                
                if (id == SCROLLING_BACKGROUND)
                {
                
                    characters[number_of_characters] = new Scrolling_Background_Object();
                
                }
                
                if (id == MESSAGE_OBJECT)
                {
                
                    characters[number_of_characters] = new Message_Object();
                
                }
                
                if (id == SPIKED_POLE)
                {
                
                    characters[number_of_characters] = new Spiked_Pole();
                    Load_Bump_Map_For_Character("data\\bump_maps\\spiked_pole.map", characters, number_of_characters);
                
                }
                
                if (id == BOILING_MUD)
                {
                
                    characters[number_of_characters] = new Boiling_Mud();
                    Load_Bump_Map_For_Character("data\\bump_maps\\boiling_mud.map", characters, number_of_characters);
                
                }
                
                if (id == MUD_DROP)
                {
                
                    characters[number_of_characters] = new Mud_Drop();
                    Load_Bump_Map_For_Character("data\\bump_maps\\mud_drop.map", characters, number_of_characters);
                
                }

                if (id == NO_ECTO_SWITCH)
                {
                
                    Switch* s;
                
                    characters[number_of_characters] = new Switch();
                    Load_Bump_Map_For_Character("data\\bump_maps\\switch.map", characters, number_of_characters);
                    s = static_cast<Switch*>(characters[number_of_characters]);
                    s->mode = Switch::NO_ECTO;
                
                }
                
                characters[number_of_characters]->x = x;
                characters[number_of_characters]->y = y;
                characters[number_of_characters]->initial_x = x;
                characters[number_of_characters]->initial_y = y;
                number_of_characters++;
            
            }

        }
        
        id = 0;
        
        while (id != -1)
        {

            file >> id;
            
            if (id != -1)
            {

                platforms[number_of_platforms]->id = id;
                file >> platforms[number_of_platforms]->x;
                file >> platforms[number_of_platforms]->y;
                platforms[number_of_platforms]->Initialize();

                if (platforms[number_of_platforms]->id == CHERRY)
                {

                    Load_Bump_Map_For_Platform("data\\bump_maps\\cherry.map", platforms, number_of_platforms);

                }
                
                if (platforms[number_of_platforms]->id == WIRE)
                {
                
                    Load_Bump_Map_For_Platform("data\\bump_maps\\wire.map", platforms, number_of_platforms);
                
                }
                
                if (platforms[number_of_platforms]->id == YELLOW_CHERRY)
                {
                
                    Load_Bump_Map_For_Platform("data\\bump_maps\\cherry.map", platforms, number_of_platforms);
                
                }

                number_of_platforms++;

            }

        }
        
        while (pointer < NUMBER_OF_POINTERS)
        {

            int pointer_value;

            file >> pointer_value;
            pointers[pointer] = pointer_value;
            pointer++;

        }
        
        while (platform < number_of_platforms)
        {

            if (platforms[platform]->x > biggest_x)
            {

                biggest_x = platforms[platform]->x;

            }
            
            if (platforms[platform]->y < smallest_y)
            {
            
                smallest_y = platforms[platform]->y;
            
            }

            platform++;

        }
        
        number_of_screens = (biggest_x/Application::CANVAS_WIDTH)+1;
        height = (smallest_y >= 0) ? 1 : (((-(smallest_y+1))/Application::CANVAS_HEIGHT)+2);

    }

}

void Level::Reset(bool demo_playing)
{

    int character = 0;
    int platform = 0;
    
    signal = 0;
    entered_level = true;
    background_x = 0;
    autoscroll_background = false;
    display_message = false;
    
    while (character < number_of_characters)
    {

        if ((characters[character]->strength > 0) &&
            (characters[character]->id != THROWABLE_ROCK))
        {

            characters[character]->Reset(demo_playing);

        }
        
        character++;

    }
    
    if (demo_playing)
    {
    
        while (platform < number_of_platforms)
        {
    
            platforms[platform]->remove = false;
            platform++;
    
        }
        
    }

}

void Level::Process(Application& app)
{

    int platform = 0;
    int character = 0;
    Bluejay* main_character;
    int background_frame_2_x;
    
    reposition = false;
    scroll_x = false;
    scroll_y = false;

    if (entered_level)
    {

        app.Stop_Sound_Effects();
        Position_For_Main_Character();
        entered_level = false;
        
        if (!app.demo_playing)
        {
        
            play_midi(app.music_tracks[music_track], 1);
        
        }

    }
    
    if (background_x < 0)
    {
    
        background_frame_2_x = background_x+Application::CANVAS_WIDTH;
    
    }
    else // background_x >= 0
    {
    
        background_frame_2_x = background_x-Application::CANVAS_WIDTH;
    
    }
    
    blit(app.bitmaps[background], app.canvas, 0, 0, background_x, 0,
         Application::CANVAS_WIDTH, Application::CANVAS_HEIGHT);
    blit(app.bitmaps[background], app.canvas, 0, 0, background_frame_2_x, 0,
         Application::CANVAS_WIDTH, Application::CANVAS_HEIGHT);
    
    while (platform < number_of_platforms)
    {

        platforms[platform]->Process(app, x, y);
        platform++;

    }
    
    while (character < number_of_characters)
    {

        characters[character]->Process(app, (*this));
        character++;

    }
    
    if (reposition)
    {
    
        Position_For_Main_Character();
    
    }
    
    if (scroll_x)
    {
    
        Scroll_X(x_direction);
        
        if (!autoscroll_background)
        {
        
            Scroll_Background(x_direction);
            
        }
    
    }
    
    if (scroll_y)
    {
    
        Scroll_Y(y_direction);
    
    }
    
    if (autoscroll_background)
    {
    
        background_x += 8;
    
        if (background_x >= Application::CANVAS_WIDTH)
        {
    
            background_x = -Application::CANVAS_WIDTH;
    
        }
    
        if (background_x < -Application::CANVAS_WIDTH)
        {
    
            background_x = Application::CANVAS_WIDTH;
    
        }
    
    }
    
    if (display_message)
    {
    
        set_trans_blender(64, 64, 64, 64);
        drawing_mode(DRAW_MODE_TRANS, NULL, 0, 0);
        rectfill(app.canvas, 0, 0, (Application::CANVAS_WIDTH-1),
                 (Application::CANVAS_HEIGHT-1), makecol(0, 0, 0));
        app.messages[app.current_level]->Print(app);
        solid_mode();
        displayed_message = true;
    
    }
    
    main_character = static_cast<Bluejay*>(characters[bluejay]);
    
    if (main_character->warped)
    {

        if (main_character->local_pipe)
        {
        
            main_character->x = (pointers[main_character->screen_pointer]*Application::CANVAS_WIDTH)+16;
            main_character->y = 128;
            main_character->Reset(app.demo_playing);
            Position_For_Main_Character();
        
        }
        else
        {

            app.current_level = pointers[main_character->screen_pointer];
            app.levels[app.current_level]->Reset(app.demo_playing);
            app.levels[app.current_level]->x = 0;
            app.levels[app.current_level]->y = 0;
            main_character->Copy_Status((*static_cast<Bluejay*>(app.levels[app.current_level]->characters[app.levels[app.current_level]->bluejay])));
        
        }

    }
    
    if (main_character->died && !main_character->Is_On_Screen(x, y, app))
    {
    
        if (main_character->lives == 0)
        {
    
            app.game_over = true;
            app.Stop_Sound_Effects();
            play_midi(app.music_tracks[Application::GAME_OVER_MT], 0);
            
        }
        else // lives > 0
        {
        
            main_character->Reset(app.demo_playing); // level will not reset Bluejay
            Reset(app.demo_playing);
            Position_For_Main_Character();
        
        }
        
    }

    if (signal == SIGNAL_DESTROY_ECTO)
    {

        timer++;

        if (timer == 15)
        {

            app.game_won = true;
            main_character->score += (main_character->eggs*1000);
            app.messages[Application::ENDING_MESSAGE]->Print(app);
            

        }

    }
    
    if (!app.demo_playing && !display_message)
    {

        if (!app.game_won)
        {
    
            int n = 0;
            int x = text_length(font, "Energy: ");
            int empty_units = Bluejay::MAX_STRENGTH-main_character->strength;
    
            textout_ex(app.canvas, font, "Energy: ", 1, 1, makecol(255, 0, 0), -1);
        
            while (n < main_character->strength)
            {
        
                draw_sprite(app.canvas, app.bitmaps[Application::STRENGTH_MARK_BM], x, 1);
                x += app.bitmaps[Application::STRENGTH_MARK_BM]->w;
                n++;
        
            }
        
            n = 0;
        
            while (n < empty_units)
            {
        
                draw_sprite(app.canvas, app.bitmaps[Application::EMPTY_MARK_BM], x, 1);
                x += app.bitmaps[Application::STRENGTH_MARK_BM]->w;
                n++;
        
            }
        
            draw_sprite(app.canvas, app.bitmaps[Application::EGG_BM], 1, 25);
            textprintf_ex(app.canvas, font, (app.bitmaps[Application::EGG_BM]->w+5), 25,
                          makecol(255, 0, 0), -1, "x %i", main_character->eggs);
            draw_sprite(app.canvas, app.bitmaps[Application::BLUEJAY_ICON_BM], 195, 25);
            textprintf_ex(app.canvas, font, (app.bitmaps[Application::BLUEJAY_ICON_BM]->w+200), 25,
                          makecol(255, 0, 0), -1, "x %i", main_character->lives);

        }

        textprintf_ex(app.canvas, font, (Application::CANVAS_WIDTH-text_length(font, "0000000")),
                      1, makecol(255, 0, 0), -1, "%i", main_character->score);

    }

}

void Level::Load_For_Editing(const char* level)
{

    ifstream file;
    
    file.open(level);
    
    if (file)
    {

        int pointer = 0;
        int id = 0;

        file >> background;
        file >> music_track;
        
        while (id != -1)
        {

            file >> id;
            
            if (id != -1)
            {

                character_objects[number_of_characters]->id = id;
                file >> character_objects[number_of_characters]->x;
                file >> character_objects[number_of_characters]->y;
                number_of_characters++;

            }

        }
        
        id = 0;
        
        while (id != -1)
        {

            file >> id;
            
            if (id != -1)
            {
            
                platform_objects[number_of_platforms]->id = id;
                file >> platform_objects[number_of_platforms]->x;
                file >> platform_objects[number_of_platforms]->y;
                number_of_platforms++;
            
            }

        }
        
        while (pointer < NUMBER_OF_POINTERS)
        {

            file >> pointers[pointer];
            pointer++;

        }

    }

}

void Level::Save(const char* level)
{

    ofstream file;
    
    file.open(level);
    
    if (file)
    {

        int character = 0;
        int platform = 0;
        int pointer = 0;

        file << background << endl;
        file << music_track << endl;
        
        while (character < number_of_characters)
        {

            file << character_objects[character]->id << endl;
            file << character_objects[character]->x << endl;
            file << character_objects[character]->y << endl;
            character++;

        }
        
        file << -1 << endl;
        
        while (platform < number_of_platforms)
        {

            file << platform_objects[platform]->id << endl;
            file << platform_objects[platform]->x << endl;
            file << platform_objects[platform]->y << endl;
            platform++;

        }
        
        file << -1 << endl;
        
        while (pointer < NUMBER_OF_POINTERS)
        {

            file << pointers[pointer] << endl;
            pointer++;

        }

    }

}

void Level::Scroll_Background(int direction)
{

    if ((characters[bluejay]->x > (Application::CANVAS_WIDTH/2)) &&
        (characters[bluejay]->x < ((number_of_screens*Application::CANVAS_WIDTH)-(Application::CANVAS_WIDTH/2))))
    {

        background_x += -direction;
    
        if (background_x >= Application::CANVAS_WIDTH)
        {
    
            background_x = -Application::CANVAS_WIDTH;
    
        }
    
        if (background_x < -Application::CANVAS_WIDTH)
        {
    
            background_x = Application::CANVAS_WIDTH;
    
        }
    
    }
    
}

void Level::Scroll_X(int direction)
{

    if ((characters[bluejay]->x > (Application::CANVAS_WIDTH/2)) &&
        (characters[bluejay]->x < ((number_of_screens*Application::CANVAS_WIDTH)-(Application::CANVAS_WIDTH/2))))
    {

        x += (direction*4);

    }

    if (characters[bluejay]->x < (Application::CANVAS_WIDTH/2))
    {

        x = 0;

    }

    if (characters[bluejay]->x >= ((number_of_screens*Application::CANVAS_WIDTH)-(Application::CANVAS_WIDTH/2)))
    {

        x = (number_of_screens*Application::CANVAS_WIDTH)-Application::CANVAS_WIDTH;

    }
    
}

void Level::Scroll_Y(int direction)
{
    
    if ((characters[bluejay]->strength > 0) && (height > 1))
    {

        if ((characters[bluejay]->y < (Application::CANVAS_HEIGHT/2)) &&
            (characters[bluejay]->y > (-((height-HEIGHT_ERROR)*Application::CANVAS_HEIGHT)+(Application::CANVAS_HEIGHT/2))))
        {

            y += (direction*4);

        }

        if (characters[bluejay]->y >= (Application::CANVAS_HEIGHT/2))
        {

            y = 0;

        }

        if (characters[bluejay]->y <= (-((height-HEIGHT_ERROR)*Application::CANVAS_HEIGHT)+(Application::CANVAS_HEIGHT/2)))
        {

            y = -((height-HEIGHT_ERROR)*Application::CANVAS_HEIGHT);

        }
        
    }

}

void Level::Position_For_Main_Character()
{

    if ((characters[bluejay]->x > (Application::CANVAS_WIDTH/2)) &&
        (characters[bluejay]->x < ((number_of_screens*Application::CANVAS_WIDTH)-(Application::CANVAS_WIDTH/2))))
    {

        x = characters[bluejay]->x-(Application::CANVAS_WIDTH/2);

    }

    if (characters[bluejay]->x < (Application::CANVAS_WIDTH/2))
    {

        x = 0;

    }
    
    if (characters[bluejay]->x >= ((number_of_screens*Application::CANVAS_WIDTH)-(Application::CANVAS_WIDTH/2)))
    {

        x = (number_of_screens*Application::CANVAS_WIDTH)-Application::CANVAS_WIDTH;

    }
    
    if ((characters[bluejay]->strength > 0) && (height > 1))
    {
    
        if ((characters[bluejay]->y < (Application::CANVAS_HEIGHT/2)) &&
            (characters[bluejay]->y > (-((height-HEIGHT_ERROR)*Application::CANVAS_HEIGHT)+(Application::CANVAS_HEIGHT/2))))
        {
    
            y = characters[bluejay]->y-(Application::CANVAS_HEIGHT/2);
    
        }
    
        if (characters[bluejay]->y >= (Application::CANVAS_HEIGHT/2))
        {
    
            y = 0;
    
        }
    
        if (characters[bluejay]->y <= (-((height-HEIGHT_ERROR)*Application::CANVAS_HEIGHT)+(Application::CANVAS_HEIGHT/2)))
        {
    
            y = -((height-HEIGHT_ERROR)*Application::CANVAS_HEIGHT);
    
        }
    
    }

}
