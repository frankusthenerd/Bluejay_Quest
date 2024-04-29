#include "application.hpp"
#include <cstdio>
#include "macros.hpp"
#include <fstream>
#include "bluejay.hpp"
#include <cstring>
#define OBJECT_GFX_OFFSET 7
#define NON_LEVEL_MT_OFFSET 10

/*

    Movie Recording:
    
    To begin uncomment out the movie recorder code and set the current level to the level
    that you used for the demo. The code that sets the current level to the level you want
    is labeled. Comment out the block of code that plays the title screen. Now recompile
    and start the game. Press 4 to record, 5 to play back the recording, and 6 to stop
    the movie or recording.

*/

using namespace std;

const int Application::NUMBER_OF_SCREENS = 50;
const int Application::GRASS_BACKGROUND_BM = 0;
const int Application::CLOUDY_BACKGROUND_BM = 1;
const int Application::FOREST_BACKGROUND_BM = 2;
const int Application::DARK_BACKGROUND_BM = 3;
const int Application::UNDERWORLD_BACKGROUND_BM = 4;
const int Application::HILLY_BACKGROUND_BM = 5;
const int Application::BLACK_BACKGROUND_BM = 6;
const int Application::BLACK_BIRD_STANDING_BM = OBJECT_GFX_OFFSET;
const int Application::BLACK_BIRD_HURT_BM = OBJECT_GFX_OFFSET+1;
const int Application::BROWN_BLOCK_BM = OBJECT_GFX_OFFSET+2;
const int Application::CEMENT_BLOCK_BM = OBJECT_GFX_OFFSET+3;
const int Application::BLUEJAY_STANDING_BM = OBJECT_GFX_OFFSET+4;
const int Application::BLUEJAY_EATING_BM = OBJECT_GFX_OFFSET+5;
const int Application::BLUEJAY_HURT_BM = OBJECT_GFX_OFFSET+6;
const int Application::BLUEJAY_WINGS_IN_BM = OBJECT_GFX_OFFSET+7;
const int Application::BLUEJAY_WINGS_OUT_BM = OBJECT_GFX_OFFSET+8;
const int Application::BIG_BUSH_BM = OBJECT_GFX_OFFSET+9;
const int Application::SMALL_BUSH_BM = OBJECT_GFX_OFFSET+10;
const int Application::CHERRY_BM = OBJECT_GFX_OFFSET+11;
const int Application::CLAM_MOUTH_CLOSED_BM = OBJECT_GFX_OFFSET+12;
const int Application::CLAM_MOUTH_OPEN_BM = OBJECT_GFX_OFFSET+13;
const int Application::EGG_BM = OBJECT_GFX_OFFSET+14;
const int Application::FLY_WINGS_IN_BM = OBJECT_GFX_OFFSET+15;
const int Application::FLY_WINGS_OUT_BM = OBJECT_GFX_OFFSET+16;
const int Application::GROUND_BM = OBJECT_GFX_OFFSET+17;
const int Application::MOSQUITO_WINGS_DOWN_BM = OBJECT_GFX_OFFSET+18;
const int Application::MOSQUITO_WINGS_UP_BM = OBJECT_GFX_OFFSET+19;
const int Application::PIPE_BM = OBJECT_GFX_OFFSET+20;
const int Application::TITLE_BM = OBJECT_GFX_OFFSET+21;
const int Application::LIMESTONE_BM = OBJECT_GFX_OFFSET+22;
const int Application::GHOST_BM = OBJECT_GFX_OFFSET+23;
const int Application::MASTER_ECTO_BM = OBJECT_GFX_OFFSET+24;
const int Application::ROCK_BM = OBJECT_GFX_OFFSET+25;
const int Application::SHOUTING_BLACK_BIRD_BM = OBJECT_GFX_OFFSET+26;
const int Application::LEAPING_BLACK_BIRD_BM = OBJECT_GFX_OFFSET+27;
const int Application::LEDGE_BM = OBJECT_GFX_OFFSET+28;
const int Application::WALK_THROUGH_DIRT_BM = OBJECT_GFX_OFFSET+29;
const int Application::GOLDENJAY_PERCHED_BM = OBJECT_GFX_OFFSET+30;
const int Application::GOLDENJAY_MOUTH_OPEN_BM = OBJECT_GFX_OFFSET+31;
const int Application::GOLDENJAY_WINGS_IN_BM = OBJECT_GFX_OFFSET+32;
const int Application::GOLDENJAY_WINGS_OUT_BM = OBJECT_GFX_OFFSET+33;
const int Application::SWOOPER_WINGS_IN_BM = OBJECT_GFX_OFFSET+34;
const int Application::SWOOPER_WINGS_OUT_BM = OBJECT_GFX_OFFSET+35;
const int Application::FAKE_BUSH_BM = OBJECT_GFX_OFFSET+36;
const int Application::WIRE_BM = OBJECT_GFX_OFFSET+37;
const int Application::LOCAL_ROCK_BM = OBJECT_GFX_OFFSET+38;
const int Application::SWITCH_NORMAL_BM = OBJECT_GFX_OFFSET+39;
const int Application::SWITCH_PRESSED_BM = OBJECT_GFX_OFFSET+40;
const int Application::PIPE_SWITCH_BM = OBJECT_GFX_OFFSET+41;
const int Application::REVERSE_PIPE_SWITCH_BM = OBJECT_GFX_OFFSET+42;
const int Application::SUPER_MOSQUITO_WINGS_DOWN_BM = OBJECT_GFX_OFFSET+43;
const int Application::SUPER_MOSQUITO_WINGS_UP_BM = OBJECT_GFX_OFFSET+44;
const int Application::LEMMING_STILL_BM = OBJECT_GFX_OFFSET+45;
const int Application::LEMMING_WALK_BM = OBJECT_GFX_OFFSET+46;
const int Application::LEMMING_STILL_ARMS_UP_BM = OBJECT_GFX_OFFSET+47;
const int Application::LEMMING_WALK_ARMS_UP_BM = OBJECT_GFX_OFFSET+48;
const int Application::THROWABLE_ROCK_BM = OBJECT_GFX_OFFSET+49;
const int Application::STOP_ATTACK_BM = OBJECT_GFX_OFFSET+50;
const int Application::HUNTING_FLY_BM = OBJECT_GFX_OFFSET+51;
const int Application::TOMATOO_PLANT_HEAD_BM = OBJECT_GFX_OFFSET+52;
const int Application::TOMATOO_PLANT_STEM_BM = OBJECT_GFX_OFFSET+53;
const int Application::STOPPER_BM = OBJECT_GFX_OFFSET+54;
const int Application::SCROLLING_BACKGROUND_BM = OBJECT_GFX_OFFSET+55;
const int Application::LOCAL_PIPE_BM = OBJECT_GFX_OFFSET+56;
const int Application::MESSAGE_BOX_BM = OBJECT_GFX_OFFSET+57;
const int Application::STONE_WALL_BM = OBJECT_GFX_OFFSET+58;
const int Application::FAKE_CEMENT_BLOCK_BM = OBJECT_GFX_OFFSET+59;
const int Application::SPIKED_POLE_POINT_BM = OBJECT_GFX_OFFSET+60;
const int Application::SPIKED_POLE_POLE_BM = OBJECT_GFX_OFFSET+61;
const int Application::BOILING_MUD_BM = OBJECT_GFX_OFFSET+62;
const int Application::MUD_DROP_BM = OBJECT_GFX_OFFSET+63;
const int Application::STRENGTH_MARK_BM = OBJECT_GFX_OFFSET+64;
const int Application::YELLOW_CHERRY_BM = OBJECT_GFX_OFFSET+65;
const int Application::BLUEJAY_ICON_BM = OBJECT_GFX_OFFSET+66;
const int Application::SHORT_VINE_BM = OBJECT_GFX_OFFSET+67;
const int Application::TALL_VINE_BM = OBJECT_GFX_OFFSET+68;
const int Application::EMPTY_MARK_BM = OBJECT_GFX_OFFSET+69;
const int Application::NO_ECTO_SWITCH_BM = OBJECT_GFX_OFFSET+70;
const int Application::ATHLETIC_THEME_MT = 0;
const int Application::HERE_WE_GO_MT = 1;
const int Application::HURRY_HURRY_MT = 2;
const int Application::MARIO_3_MT = 3;
const int Application::UNDERWORLD_MT = 4;
const int Application::GHOST_MT = 5;
const int Application::NEW_SUPER_MARIO_BROTHERS_MT = 6;
const int Application::BATTLE_MT = 7;
const int Application::OLD_SUPER_MARIO_BROTHERS_MT = 8;
const int Application::SEWERS_MT = 9;
const int Application::GAME_OVER_MT = NON_LEVEL_MT_OFFSET;
const int Application::TITLE_SCREEN_MT = NON_LEVEL_MT_OFFSET+1;
const int Application::VICTORY_MT = NON_LEVEL_MT_OFFSET+2;
const int Application::NUMBER_OF_BITMAPS = OBJECT_GFX_OFFSET+70+1;
const int Application::NUMBER_OF_MUSIC_TRACKS = NON_LEVEL_MT_OFFSET+2+1;
const int Application::CANVAS_WIDTH = 256;
const int Application::CANVAS_HEIGHT = 224;
const int Application::NUMBER_OF_LEVELS = 120;
const int Application::NUMBER_OF_SOUND_EFFECTS = 12;
const int Application::BLUEJAY_DIES_SE = 0;
const int Application::DAMAGING_STOMP_SE = 1;
const int Application::GRAB_EGG_SE = 2;
const int Application::HIT_SE = 3;
const int Application::MOSQUITO_SE = 4;
const int Application::USELESS_STOMP_SE = 5;
const int Application::WARP_SE = 6;
const int Application::BIRD_CHIRP_SE = 7;
const int Application::PAUSE_SE = 8;
const int Application::GROWING_SE = 9;
const int Application::SHRINKING_SE = 10;
const int Application::THUD_SE = 11;
const int Application::SCREEN_MODE = 1;
const int Application::CHARACTER_MODE = 2;
const int Application::PLATFORM_MODE = 3;
const int Application::NO_OBJECT_SELECTED = -1;
const long Application::SIGNAL_FLY = 1; // bit 0
const long Application::SIGNAL_LEFT = 2; // bit 1
const long Application::SIGNAL_RIGHT = 4; // bit 2
const long Application::SIGNAL_UP = 8; // bit 3
const long Application::SIGNAL_DOWN = 16; // bit 4
const long Application::SIGNAL_PAUSE = 32; // bit 5
const long Application::SIGNAL_QUIT = 64; // bit 6
const long Application::SIGNAL_START = 128; // bit 7
const long Application::SIGNAL_CURSOR_LEFT = 256; // bit 8
const long Application::SIGNAL_CURSOR_RIGHT = 512; // bit 9
const long Application::SIGNAL_CURSOR_UP = 1024; // bit 10
const long Application::SIGNAL_CURSOR_DOWN = 2048; // bit 11
const long Application::SIGNAL_SELECT = 4096; // bit 12
const long Application::SIGNAL_DELETE = 8192; // bit 13
const long Application::SIGNAL_SAVE = 16384; // bit 14
const long Application::SIGNAL_LEVEL_UP = 32768; // bit 15
const long Application::SIGNAL_LEVEL_DOWN = 65536; // bit 16
const long Application::SIGNAL_SCROLL_UP_1 = 131072; // bit 17
const long Application::SIGNAL_SCROLL_DOWN_1 = 262144; // bit 18
const long Application::SIGNAL_SCROLL_UP_2 = 524288; // bit 19
const long Application::SIGNAL_SCROLL_DOWN_2 = 1048576; // bit 20
const long Application::SIGNAL_SCROLL_UP_3 = 2097152; // bit 21
const long Application::SIGNAL_SCROLL_DOWN_3 = 4194304; // bit 22
const long Application::SIGNAL_SCREEN_MODE = 8388608; // bit 23
const long Application::SIGNAL_CHARACTER_MODE = 16777216; // bit 24
const long Application::SIGNAL_PLATFORM_MODE = 33554432; // bit 25
const long Application::SIGNAL_MOVIE_RECORD = 67108864; // bit 26
const long Application::SIGNAL_MOVIE_PLAY = 134217728; // bit 27
const long Application::SIGNAL_MOVIE_STOP = 268435456; // bit 28
const int Application::MOVIE_RECORDING_MODE = 1;
const int Application::MOVIE_PLAYBACK_MODE = 2;
const int Application::MOVIE_STOP_MODE = 3;
const int Application::MAX_SIGNAL_BUFFER_LENGTH = 30*60*10; // 10 minutes
const int Application::ENDING_MESSAGE = 23;
extern volatile bool timing_signal;

Application::Application()
{

    int level = 0;

    current_level = 0;
    game_over = false;
    timer = 7;
    canvas = create_bitmap(CANVAS_WIDTH, CANVAS_HEIGHT);
    bitmaps = new BITMAP* [NUMBER_OF_BITMAPS];
    music_tracks = new MIDI* [NUMBER_OF_MUSIC_TRACKS];
    sound_effects = new SAMPLE* [NUMBER_OF_SOUND_EFFECTS];
    levels = new Level* [NUMBER_OF_LEVELS];
    signals = 0;
    cursor_x = 0;
    cursor_y = 0;
    mode = SCREEN_MODE;
    current_object = NO_OBJECT_SELECTED;
    movie_mode = MOVIE_STOP_MODE;
    signal_buffer = new long[MAX_SIGNAL_BUFFER_LENGTH];
    number_of_recorded_signals = 0;
    movie_pos = 0;
    movie_level = 0;
    demo_playing = false;
    messages = new String_List* [NUMBER_OF_LEVELS];
    game_won = false;

    while (level < NUMBER_OF_LEVELS)
    {

        levels[level] = new Level();
        messages[level] = new String_List();
        level++;

    }

}

Application::~Application()
{

    int bitmap = 0;
    int music_track = 0;
    int sound_effect = 0;
    int level = 0;

    while (bitmap < NUMBER_OF_BITMAPS)
    {

        destroy_bitmap(bitmaps[bitmap]);
        bitmap++;

    }
   
    while (music_track < NUMBER_OF_MUSIC_TRACKS)
    {

        destroy_midi(music_tracks[music_track]);
        music_track++;

    }
    
    while (sound_effect < NUMBER_OF_SOUND_EFFECTS)
    {

        destroy_sample(sound_effects[sound_effect]);
        sound_effect++;

    }

    while (level < NUMBER_OF_LEVELS)
    {

        delete levels[level];
        delete messages[level];
        level++;

    }
    
    delete[] bitmaps;
    delete[] music_tracks;
    delete[] sound_effects;
    delete[] levels;
    destroy_bitmap(canvas);
    destroy_bitmap(ghost_temp_bitmap);
    destroy_bitmap(master_ecto_temp_bitmap);
    delete[] signal_buffer;
    delete[] messages;

}

void Application::Load_Resources()
{

    clear_bitmap(canvas);
    textout_ex(canvas, font, "Loading... please wait.", 1, 1, makecol(255, 255, 255), -1);
    Display_Scene();
    Load_Bitmap_File(GRASS_BACKGROUND_BM, "data\\graphics\\backgrounds\\grass.bmp", bitmaps);
    Load_Bitmap_File(CLOUDY_BACKGROUND_BM, "data\\graphics\\backgrounds\\cloudy.bmp", bitmaps);
    Load_Bitmap_File(FOREST_BACKGROUND_BM, "data\\graphics\\backgrounds\\forest.bmp", bitmaps);
    Load_Bitmap_File(BLACK_BIRD_STANDING_BM, "data\\graphics\\black_bird\\standing.bmp", bitmaps);
    Load_Bitmap_File(BLACK_BIRD_HURT_BM, "data\\graphics\\black_bird\\hurt.bmp", bitmaps);
    Load_Bitmap_File(BROWN_BLOCK_BM, "data\\graphics\\blocks\\brown.bmp", bitmaps);
    Load_Bitmap_File(CEMENT_BLOCK_BM, "data\\graphics\\blocks\\cement.bmp", bitmaps);
    Load_Bitmap_File(BLUEJAY_STANDING_BM, "data\\graphics\\bluejay\\standing.bmp", bitmaps);
    Load_Bitmap_File(BLUEJAY_EATING_BM, "data\\graphics\\bluejay\\eating.bmp", bitmaps);
    Load_Bitmap_File(BLUEJAY_HURT_BM, "data\\graphics\\bluejay\\hurt.bmp", bitmaps);
    Load_Bitmap_File(BLUEJAY_WINGS_IN_BM, "data\\graphics\\bluejay\\wings_in.bmp", bitmaps);
    Load_Bitmap_File(BLUEJAY_WINGS_OUT_BM, "data\\graphics\\bluejay\\wings_out.bmp", bitmaps);
    Load_Bitmap_File(BIG_BUSH_BM, "data\\graphics\\bush\\big.bmp", bitmaps);
    Load_Bitmap_File(SMALL_BUSH_BM, "data\\graphics\\bush\\small.bmp", bitmaps);
    Load_Bitmap_File(CHERRY_BM, "data\\graphics\\cherry\\cherry.bmp", bitmaps);
    Load_Bitmap_File(CLAM_MOUTH_OPEN_BM, "data\\graphics\\clam\\mouth_open.bmp", bitmaps);
    Load_Bitmap_File(CLAM_MOUTH_CLOSED_BM, "data\\graphics\\clam\\mouth_closed.bmp", bitmaps);
    Load_Bitmap_File(EGG_BM, "data\\graphics\\egg\\egg.bmp", bitmaps);
    Load_Bitmap_File(FLY_WINGS_IN_BM, "data\\graphics\\fly\\wings_in.bmp", bitmaps);
    Load_Bitmap_File(FLY_WINGS_OUT_BM, "data\\graphics\\fly\\wings_out.bmp", bitmaps);
    Load_Bitmap_File(GROUND_BM, "data\\graphics\\ground\\ground.bmp", bitmaps);
    Load_Bitmap_File(MOSQUITO_WINGS_DOWN_BM, "data\\graphics\\mosquito\\wings_down.bmp", bitmaps);
    Load_Bitmap_File(MOSQUITO_WINGS_UP_BM, "data\\graphics\\mosquito\\wings_up.bmp", bitmaps);
    Load_Bitmap_File(PIPE_BM, "data\\graphics\\pipe\\pipe.bmp", bitmaps);
    Load_Bitmap_File(TITLE_BM, "data\\graphics\\misc\\title.bmp", bitmaps);
    Load_Bitmap_File(DARK_BACKGROUND_BM, "data\\graphics\\backgrounds\\dark.bmp", bitmaps);
    Load_Bitmap_File(UNDERWORLD_BACKGROUND_BM, "data\\graphics\\backgrounds\\underworld.bmp", bitmaps);
    Load_Bitmap_File(LIMESTONE_BM, "data\\graphics\\ground\\limestone.bmp", bitmaps);
    Load_Bitmap_File(GHOST_BM, "data\\graphics\\ghost\\ghost.bmp", bitmaps);
    Load_Bitmap_File(MASTER_ECTO_BM, "data\\graphics\\master_ecto\\master_ecto.bmp", bitmaps);
    Load_Bitmap_File(ROCK_BM, "data\\graphics\\rock\\rock.bmp", bitmaps);
    Load_Bitmap_File(LEAPING_BLACK_BIRD_BM, "data\\graphics\\black_bird\\leaping.bmp", bitmaps);
    Load_Bitmap_File(SHOUTING_BLACK_BIRD_BM, "data\\graphics\\black_bird\\shouting.bmp", bitmaps);
    Load_Bitmap_File(LEDGE_BM, "data\\graphics\\ground\\ledge.bmp", bitmaps);
    Load_Bitmap_File(WALK_THROUGH_DIRT_BM, "data\\graphics\\ground\\walk_through_dirt.bmp", bitmaps);
    Load_Bitmap_File(GOLDENJAY_PERCHED_BM, "data\\graphics\\goldenjay\\perched.bmp", bitmaps);
    Load_Bitmap_File(GOLDENJAY_MOUTH_OPEN_BM, "data\\graphics\\goldenjay\\mouth_open.bmp", bitmaps);
    Load_Bitmap_File(GOLDENJAY_WINGS_IN_BM, "data\\graphics\\goldenjay\\wings_in.bmp", bitmaps);
    Load_Bitmap_File(GOLDENJAY_WINGS_OUT_BM, "data\\graphics\\goldenjay\\wings_out.bmp", bitmaps);
    Load_Bitmap_File(SWOOPER_WINGS_IN_BM, "data\\graphics\\swooper\\wings_in.bmp", bitmaps);
    Load_Bitmap_File(SWOOPER_WINGS_OUT_BM, "data\\graphics\\swooper\\wings_out.bmp", bitmaps);
    Load_Bitmap_File(FAKE_BUSH_BM, "data\\graphics\\bush\\fake.bmp", bitmaps);
    Load_Bitmap_File(WIRE_BM, "data\\graphics\\wire\\wire.bmp", bitmaps);
    Load_Bitmap_File(LOCAL_ROCK_BM, "data\\graphics\\rock\\local.bmp", bitmaps);
    Load_Bitmap_File(SWITCH_NORMAL_BM, "data\\graphics\\switch\\normal.bmp", bitmaps);
    Load_Bitmap_File(SWITCH_PRESSED_BM, "data\\graphics\\switch\\pressed.bmp", bitmaps);
    Load_Bitmap_File(PIPE_SWITCH_BM, "data\\graphics\\switch\\pipe.bmp", bitmaps);
    Load_Bitmap_File(REVERSE_PIPE_SWITCH_BM, "data\\graphics\\switch\\reverse_pipe.bmp", bitmaps);
    Load_Bitmap_File(SUPER_MOSQUITO_WINGS_DOWN_BM, "data\\graphics\\super_mosquito\\wings_down.bmp", bitmaps);
    Load_Bitmap_File(SUPER_MOSQUITO_WINGS_UP_BM, "data\\graphics\\super_mosquito\\wings_up.bmp", bitmaps);
    Load_Bitmap_File(HILLY_BACKGROUND_BM, "data\\graphics\\backgrounds\\hilly.bmp", bitmaps);
    Load_Bitmap_File(LEMMING_STILL_BM, "data\\graphics\\lemming\\still.bmp", bitmaps);
    Load_Bitmap_File(LEMMING_WALK_BM, "data\\graphics\\lemming\\walk.bmp", bitmaps);
    Load_Bitmap_File(LEMMING_STILL_ARMS_UP_BM, "data\\graphics\\lemming\\still_arms_up.bmp", bitmaps);
    Load_Bitmap_File(LEMMING_WALK_ARMS_UP_BM, "data\\graphics\\lemming\\walk_arms_up.bmp", bitmaps);
    Load_Bitmap_File(THROWABLE_ROCK_BM, "data\\graphics\\rock\\throwable.bmp", bitmaps);
    Load_Bitmap_File(STOP_ATTACK_BM, "data\\graphics\\misc\\stop_attack.bmp", bitmaps);
    Load_Bitmap_File(HUNTING_FLY_BM, "data\\graphics\\fly\\hunting.bmp", bitmaps);
    Load_Bitmap_File(TOMATOO_PLANT_HEAD_BM, "data\\graphics\\tomatoo_plant\\head.bmp", bitmaps);
    Load_Bitmap_File(TOMATOO_PLANT_STEM_BM, "data\\graphics\\tomatoo_plant\\stem.bmp", bitmaps);
    Load_Bitmap_File(STOPPER_BM, "data\\graphics\\misc\\stopper.bmp", bitmaps);
    Load_Bitmap_File(SCROLLING_BACKGROUND_BM, "data\\graphics\\misc\\scrolling_background.bmp", bitmaps);
    Load_Bitmap_File(LOCAL_PIPE_BM, "data\\graphics\\pipe\\local.bmp", bitmaps);
    Load_Bitmap_File(MESSAGE_BOX_BM, "data\\graphics\\misc\\message_box.bmp", bitmaps);
    Load_Bitmap_File(BLACK_BACKGROUND_BM, "data\\graphics\\backgrounds\\black.bmp", bitmaps);
    Load_Bitmap_File(STONE_WALL_BM, "data\\graphics\\misc\\stone_wall.bmp", bitmaps);
    Load_Bitmap_File(FAKE_CEMENT_BLOCK_BM, "data\\graphics\\blocks\\fake_cement.bmp", bitmaps);
    Load_Bitmap_File(SPIKED_POLE_POINT_BM, "data\\graphics\\spiked_pole\\point.bmp", bitmaps);
    Load_Bitmap_File(SPIKED_POLE_POLE_BM, "data\\graphics\\spiked_pole\\pole.bmp", bitmaps);
    Load_Bitmap_File(BOILING_MUD_BM, "data\\graphics\\boiling_mud\\mud.bmp", bitmaps);
    Load_Bitmap_File(MUD_DROP_BM, "data\\graphics\\mud_drop\\mud_drop.bmp", bitmaps);
    Load_Bitmap_File(STRENGTH_MARK_BM, "data\\graphics\\misc\\strength_mark.bmp", bitmaps);
    Load_Bitmap_File(YELLOW_CHERRY_BM, "data\\graphics\\cherry\\one_up.bmp", bitmaps);
    Load_Bitmap_File(BLUEJAY_ICON_BM, "data\\graphics\\bluejay\\icon.bmp", bitmaps);
    Load_Bitmap_File(SHORT_VINE_BM, "data\\graphics\\vine\\short.bmp", bitmaps);
    Load_Bitmap_File(TALL_VINE_BM, "data\\graphics\\vine\\tall.bmp", bitmaps);
    Load_Bitmap_File(EMPTY_MARK_BM, "data\\graphics\\misc\\empty_mark.bmp", bitmaps);
    Load_Bitmap_File(NO_ECTO_SWITCH_BM, "data\\graphics\\switch\\no_ecto.bmp", bitmaps);
    Load_Music_Track_File(ATHLETIC_THEME_MT, "data\\sounds\\music_tracks\\athletic_theme.mid", music_tracks);
    Load_Music_Track_File(HERE_WE_GO_MT, "data\\sounds\\music_tracks\\here_we_go.mid", music_tracks);
    Load_Music_Track_File(HURRY_HURRY_MT, "data\\sounds\\music_tracks\\hurry_hurry.mid", music_tracks);
    Load_Music_Track_File(MARIO_3_MT, "data\\sounds\\music_tracks\\mario_3.mid", music_tracks);
    Load_Music_Track_File(GAME_OVER_MT, "data\\sounds\\music_tracks\\game_over.mid", music_tracks);
    Load_Music_Track_File(UNDERWORLD_MT, "data\\sounds\\music_tracks\\underworld.mid", music_tracks);
    Load_Music_Track_File(GHOST_MT, "data\\sounds\\music_tracks\\ghost.mid", music_tracks);
    Load_Music_Track_File(NEW_SUPER_MARIO_BROTHERS_MT, "data\\sounds\\music_tracks\\new_super_mario_brothers.mid", music_tracks);
    Load_Music_Track_File(BATTLE_MT, "data\\sounds\\music_tracks\\battle.mid", music_tracks);
    Load_Music_Track_File(OLD_SUPER_MARIO_BROTHERS_MT, "data\\sounds\\music_tracks\\old_super_mario_brothers.mid", music_tracks);
    Load_Music_Track_File(TITLE_SCREEN_MT, "data\\sounds\\music_tracks\\title_screen.mid", music_tracks);
    Load_Music_Track_File(SEWERS_MT, "data\\sounds\\music_tracks\\sewers.mid", music_tracks);
    Load_Music_Track_File(VICTORY_MT, "data\\sounds\\music_tracks\\victory.mid", music_tracks);
    Load_Sound_Effect_File(BLUEJAY_DIES_SE, "data\\sounds\\sound_effects\\bluejay_dies.wav", sound_effects);
    Load_Sound_Effect_File(DAMAGING_STOMP_SE, "data\\sounds\\sound_effects\\damaging_stomp.wav", sound_effects);
    Load_Sound_Effect_File(GRAB_EGG_SE, "data\\sounds\\sound_effects\\grab_egg.wav", sound_effects);
    Load_Sound_Effect_File(HIT_SE, "data\\sounds\\sound_effects\\hit.wav", sound_effects);
    Load_Sound_Effect_File(MOSQUITO_SE, "data\\sounds\\sound_effects\\mosquito.wav", sound_effects);
    Load_Sound_Effect_File(USELESS_STOMP_SE, "data\\sounds\\sound_effects\\useless_stomp.wav", sound_effects);
    Load_Sound_Effect_File(WARP_SE, "data\\sounds\\sound_effects\\warp.wav", sound_effects);
    Load_Sound_Effect_File(BIRD_CHIRP_SE, "data\\sounds\\sound_effects\\bird_chirp.wav", sound_effects);
    Load_Sound_Effect_File(PAUSE_SE, "data\\sounds\\sound_effects\\pause.wav", sound_effects);
    Load_Sound_Effect_File(GROWING_SE, "data\\sounds\\sound_effects\\growing.wav", sound_effects);
    Load_Sound_Effect_File(SHRINKING_SE, "data\\sounds\\sound_effects\\shrinking.wav", sound_effects);
    Load_Sound_Effect_File(THUD_SE, "data\\sounds\\sound_effects\\thud.wav", sound_effects);
    ghost_temp_bitmap = create_bitmap(bitmaps[GHOST_BM]->w, bitmaps[GHOST_BM]->h);
    master_ecto_temp_bitmap = create_bitmap(bitmaps[MASTER_ECTO_BM]->w, bitmaps[MASTER_ECTO_BM]->h);

}

void Application::Run_Game()
{

    bool done = false;
    bool skip_title = false;
    bool paused = false;
    int level = 0;
    char level_name[30+1];
    char movie_file[30+1];
    char message_name[30+1];
    
    while (level < NUMBER_OF_LEVELS)
    {

        sprintf(level_name, "data\\levels\\level_%i.map", level);
        fix_filename_slashes(level_name);
        levels[level]->Load(level_name);
        sprintf(message_name, "data\\messages\\message_%i.txt", level);
        fix_filename_slashes(message_name);
        messages[level]->Load_From_File(message_name);
        level++;

    }

    strcpy(movie_file, "data\\movie\\movie.dat");
    fix_filename_slashes(movie_file);
    Load_Movie(movie_file);
    
    // title screen code

    movie_mode = MOVIE_PLAYBACK_MODE;
    demo_playing = true;
    play_midi(music_tracks[TITLE_SCREEN_MT], 1);
    
    while (!skip_title)
    {

        if (timing_signal)
        {

            timing_signal = false;
            Generate_Signals();
    
            if (signals & SIGNAL_START)
            {
    
                skip_title = true;
                movie_mode = MOVIE_STOP_MODE;
                continue;
    
            }
            
            if (signals & SIGNAL_QUIT)
            {
            
                skip_title = true;
                movie_mode = MOVIE_STOP_MODE;
                done = true;
                continue;
            
            }
            
            if (movie_mode == MOVIE_PLAYBACK_MODE)
            {
            
                if (movie_pos < number_of_recorded_signals)
                {
                
                    signals = signal_buffer[movie_pos];
                    movie_pos++;
                
                }
                else
                {
                
                    levels[movie_level]->Reset(demo_playing);
                    movie_pos = 0;
                
                }
            
            }
            
            levels[movie_level]->Process((*this));
            draw_sprite(canvas, bitmaps[TITLE_BM], 0, 0);
            Display_Scene();
        
        }

    }
    
    // end of title screen code
    
    demo_playing = false;
    stop_midi();
    clear_bitmap(canvas);
    textout_ex(canvas, font, "Loading... please wait.", 1, 1, makecol(255, 255, 255), -1);
    Display_Scene();
    Rebuild_Levels();
    // current_level = 5; // set this to point to the demo level
    // current_level = 22; // this is for debugging
    
    while (!done)
    {

        if (timing_signal)
        {

            timing_signal = false;
            timer++;
            Generate_Signals();
            
            if (signals & SIGNAL_QUIT)
            {

                done = true;
                continue;

            }
            /*
            // recorder code
            
            if (signals & SIGNAL_MOVIE_RECORD)
            {
            
                movie_mode = MOVIE_RECORDING_MODE;
                movie_level = current_level;
                levels[current_level]->Reset(demo_playing);
                number_of_recorded_signals = 0;
            
            }
            
            if (signals & SIGNAL_MOVIE_PLAY)
            {
            
                movie_mode = MOVIE_PLAYBACK_MODE;
                current_level = movie_level;
                levels[current_level]->Reset(demo_playing);
                movie_pos = 0;
            
            }
            
            if (signals & SIGNAL_MOVIE_STOP)
            {
            
                movie_mode = MOVIE_STOP_MODE;
            
            }
            
            if (movie_mode == MOVIE_RECORDING_MODE)
            {
            
                if (number_of_recorded_signals < MAX_SIGNAL_BUFFER_LENGTH)
                {
                
                    signal_buffer[number_of_recorded_signals] = signals;
                    number_of_recorded_signals++;
                
                }
                else
                {
                
                    movie_mode = MOVIE_STOP_MODE;
                
                }
            
            }
            
            if (movie_mode == MOVIE_PLAYBACK_MODE)
            {
            
                if (movie_pos < number_of_recorded_signals)
                {
                
                    signals = signal_buffer[movie_pos];
                    movie_pos++;
                
                }
                else
                {
                
                    movie_mode = MOVIE_STOP_MODE;
                
                }
            
            }
            
            // end recorder code
            */
            if (!game_won)
            {

                if (levels[current_level]->signal == Level::SIGNAL_DESTROY_ECTO)
                {

                    signals &= SIGNAL_QUIT; // disable all signals but quit

                }

                if ((signals & SIGNAL_PAUSE) && (timer > 6) &&
                    !levels[current_level]->display_message &&
                    !game_over)
                {

                    timer = 0;

                    if (!paused)
                    {

                        paused = true;
                        midi_pause();
                        Stop_Sound_Effects();
                        play_sample(sound_effects[PAUSE_SE], 255, 128, 1000, 0);

                    }
                    else
                    {

                        paused = false;
                        play_sample(sound_effects[PAUSE_SE], 255, 128, 1000, 0);
                        midi_resume();

                    }

                }
            
                if (levels[current_level]->display_message)
                {
            
                    if (signals & SIGNAL_START)
                    {
                
                        levels[current_level]->display_message = false; // dismiss the message
                
                    }
            
                }
            
                if (!game_over)
                {
            
                    if (!paused && !levels[current_level]->display_message)
                    {

                        levels[current_level]->Process((*this));

                    }
               
                }
                else // game over
                {

                    textout_centre_ex(canvas, font, "Game Over", 128, 112, makecol(255, 0, 0), -1);

                    if (signals & SIGNAL_START)
                    {

                        game_over = false;
                        paused = false;
                        stop_midi();
                        clear_bitmap(canvas);
                        textout_ex(canvas, font, "Loading... please wait.", 1, 1, makecol(255, 255, 255), -1);
                        Display_Scene();
                        Rebuild_Levels();
                        current_level = 0;

                    }

                }

            }

            Display_Scene();
            
        }

    }
    
    Save_Movie(movie_file);
    stop_midi();
    clear_bitmap(canvas);
    textout_ex(canvas, font, "Exiting... please wait.", 1, 1, makecol(255, 255, 255), -1);
    Display_Scene();
    
}

void Application::Stop_Sound_Effects()
{

    int sound_effect = 0;
    
    while (sound_effect < NUMBER_OF_SOUND_EFFECTS)
    {

        stop_sample(sound_effects[sound_effect]);
        sound_effect++;

    }

}

void Application::Rebuild_Levels()
{

    int level = 0;
    char level_name[30+1];
    
    while (level < NUMBER_OF_LEVELS)
    {

        delete levels[level];
        level++;

    }
    
    delete[] levels;
    levels = new Level* [NUMBER_OF_LEVELS];
    level = 0;
    
    while (level < NUMBER_OF_LEVELS)
    {

        sprintf(level_name, "data\\levels\\level_%i.map", level);
        levels[level] = new Level();
        levels[level]->Load(level_name);
        level++;

    }

}

void Application::Run_Editor()
{

    bool done = false;
    char level_name[50+1];
    int current_object_type;
    int level = 0;

    while (level < NUMBER_OF_LEVELS)
    {

        sprintf(level_name, "data\\levels\\level_%i.map", level);
        fix_filename_slashes(level_name);
        levels[level]->Load_For_Editing(level_name);
        level++;

    }

    set_trans_blender(200, 200, 200, 200);
    
    while (!done)
    {

        if (timing_signal)
        {

            int platform = 0;
            int character = 0;
            int screen = 0;

            timing_signal = false;
            timer++;
            Generate_Signals();
            
            if (signals & SIGNAL_QUIT)
            {

                done = true;
                continue;

            }
            
            if (signals & SIGNAL_SAVE)
            {

                sprintf(level_name, "data\\levels\\level_%i.map", current_level);
                levels[current_level]->Save(level_name);

            }
            
            if (signals & SIGNAL_SCREEN_MODE)
            {

                mode = SCREEN_MODE;
                current_object = NO_OBJECT_SELECTED;

            }
            
            if (signals & SIGNAL_CHARACTER_MODE)
            {

                mode = CHARACTER_MODE;
                current_object_type = Level::BLACK_BIRD;
                current_object = NO_OBJECT_SELECTED;

            }
            
            if (signals & SIGNAL_PLATFORM_MODE)
            {

                mode = PLATFORM_MODE;
                current_object_type = Level::BROWN_BLOCK;
                current_object = NO_OBJECT_SELECTED;

            }
            
            if (timer > 6)
            {

                if (signals & SIGNAL_LEVEL_UP)
                {

                    sprintf(level_name, "data\\levels\\level_%i.map", current_level);
                    levels[current_level]->Save(level_name);
                    current_level++;
                    timer = 0;
                    current_object = NO_OBJECT_SELECTED;
                    stop_midi();

                }
                
                if (signals & SIGNAL_LEVEL_DOWN)
                {

                    sprintf(level_name, "data\\levels\\level_%i.map", current_level);
                    levels[current_level]->Save(level_name);
                    current_level--;
                    timer = 0;
                    current_object = NO_OBJECT_SELECTED;
                    stop_midi();

                }
                
                if (current_level < 0)
                {

                    current_level = 0;

                }
                
                if (current_level == NUMBER_OF_LEVELS)
                {

                    current_level = NUMBER_OF_LEVELS-1;

                }

            }
            
            if (timer > 4)
            {

                if (signals & SIGNAL_LEFT)
                {

                    levels[current_level]->x -= 16;
                    current_object = NO_OBJECT_SELECTED;
                    timer = 0;

                }

                if (signals & SIGNAL_RIGHT)
                {

                    levels[current_level]->x += 16;
                    current_object = NO_OBJECT_SELECTED;
                    timer = 0;

                }

                if (signals & SIGNAL_UP)
                {

                    levels[current_level]->y -= 16;
                    current_object = NO_OBJECT_SELECTED;
                    timer = 0;

                }

                if (signals & SIGNAL_DOWN)
                {

                    levels[current_level]->y += 16;
                    current_object = NO_OBJECT_SELECTED;
                    timer = 0;

                }

                if (levels[current_level]->x < 0)
                {

                    levels[current_level]->x = 0;

                }
                
                if (levels[current_level]->x > ((NUMBER_OF_SCREENS-1)*CANVAS_WIDTH))
                {

                    levels[current_level]->x = (NUMBER_OF_SCREENS-1)*CANVAS_WIDTH;

                }

                if (levels[current_level]->y > 0)
                {

                    levels[current_level]->y = 0;

                }
                
                if (levels[current_level]->y < -((Level::MAX_HEIGHT-2)*CANVAS_HEIGHT))
                {

                    levels[current_level]->y = -((Level::MAX_HEIGHT-2)*CANVAS_HEIGHT);

                }

            }
            
            if (mode == SCREEN_MODE)
            {

                if (timer > 6)
                {
                
                    if (signals & SIGNAL_SCROLL_DOWN_1)
                    {

                        levels[current_level]->pointers[levels[current_level]->x/CANVAS_WIDTH]--;
                        timer = 0;

                    }

                    if (signals & SIGNAL_SCROLL_UP_1)
                    {

                        levels[current_level]->pointers[levels[current_level]->x/CANVAS_WIDTH]++;
                        timer = 0;

                    }

                    if (levels[current_level]->pointers[levels[current_level]->x/CANVAS_WIDTH] < 0)
                    {

                        levels[current_level]->pointers[levels[current_level]->x/CANVAS_WIDTH] = 0;

                    }

                    if (levels[current_level]->pointers[levels[current_level]->x/CANVAS_WIDTH] == NUMBER_OF_LEVELS)
                    {

                        levels[current_level]->pointers[levels[current_level]->x/CANVAS_WIDTH] = NUMBER_OF_LEVELS-1;

                    }
                    
                    if (signals & SIGNAL_SCROLL_DOWN_2)
                    {

                        levels[current_level]->background--;
                        timer = 0;

                    }
                    
                    if (signals & SIGNAL_SCROLL_UP_2)
                    {

                        levels[current_level]->background++;
                        timer = 0;

                    }
                    
                    if (levels[current_level]->background < GRASS_BACKGROUND_BM)
                    {

                        levels[current_level]->background = GRASS_BACKGROUND_BM;

                    }
                    
                    if (levels[current_level]->background > BLACK_BACKGROUND_BM)
                    {

                        levels[current_level]->background = BLACK_BACKGROUND_BM;

                    }
                    
                    if (signals & SIGNAL_SCROLL_DOWN_3)
                    {

                        levels[current_level]->music_track--;
                        timer = 0;
                        
                        if (levels[current_level]->music_track < ATHLETIC_THEME_MT)
                        {

                            levels[current_level]->music_track = ATHLETIC_THEME_MT;

                        }
                        
                        play_midi(music_tracks[levels[current_level]->music_track], 0);

                    }
                    
                    if (signals & SIGNAL_SCROLL_UP_3)
                    {

                        levels[current_level]->music_track++;
                        timer = 0;
                        
                        if (levels[current_level]->music_track > SEWERS_MT)
                        {

                            levels[current_level]->music_track = SEWERS_MT;

                        }
                        
                        play_midi(music_tracks[levels[current_level]->music_track], 0);

                    }
                    
                }

            }
            
            if (mode == CHARACTER_MODE)
            {

                if (timer > 6)
                {

                    if (signals & SIGNAL_SCROLL_DOWN_1)
                    {

                        current_object_type--;
                        timer = 0;

                    }
                    
                    if (signals & SIGNAL_SCROLL_UP_1)
                    {

                        current_object_type++;
                        timer = 0;

                    }
                    
                    if (current_object_type < Level::BLACK_BIRD)
                    {

                        current_object_type = Level::BLACK_BIRD;

                    }

                    if (current_object_type > Level::NO_ECTO_SWITCH)
                    {

                        current_object_type = Level::NO_ECTO_SWITCH;

                    }
                    
                    if (current_object == NO_OBJECT_SELECTED)
                    {

                        if (signals & SIGNAL_CURSOR_UP)
                        {

                            cursor_y -= 16;
                            timer = 0;

                        }

                        if (signals & SIGNAL_CURSOR_LEFT)
                        {

                            cursor_x -= 16;
                            timer = 0;

                        }

                        if (signals & SIGNAL_CURSOR_RIGHT)
                        {

                            cursor_x += 16;
                            timer = 0;

                        }

                        if (signals & SIGNAL_CURSOR_DOWN)
                        {

                            cursor_y += 16;
                            timer = 0;

                        }

                        if (cursor_x < 0)
                        {

                            cursor_x = 0;

                        }

                        if (cursor_x > (CANVAS_WIDTH-16))
                        {

                            cursor_x = CANVAS_WIDTH-16;

                        }

                        if (cursor_y < 0)
                        {

                            cursor_y = 0;

                        }

                        if (cursor_y > (CANVAS_HEIGHT-16))
                        {

                            cursor_y = CANVAS_HEIGHT-16;

                        }
                        
                        if (signals & SIGNAL_SELECT)
                        {

                            Select_Object();
                            timer = 0;
                            
                            if (current_object == NO_OBJECT_SELECTED)
                            {

                                if (levels[current_level]->number_of_characters < Level::MAX_CHARACTERS)
                                {

                                    int number_of_characters = levels[current_level]->number_of_characters;

                                    levels[current_level]->character_objects[number_of_characters]->id = current_object_type;
                                    levels[current_level]->character_objects[number_of_characters]->x = levels[current_level]->x+cursor_x;
                                    levels[current_level]->character_objects[number_of_characters]->y = levels[current_level]->y+cursor_y;
                                    current_object = number_of_characters;
                                    levels[current_level]->number_of_characters++;

                                }

                            }

                        }

                    }
                    else // object is selected
                    {

                        if (signals & SIGNAL_SELECT)
                        {

                            current_object = NO_OBJECT_SELECTED;
                            timer = 0;

                        }
                        else if (signals & SIGNAL_DELETE)
                        {

                            if (current_object != NO_OBJECT_SELECTED)
                            {

                                int number_of_characters = levels[current_level]->number_of_characters;

                                levels[current_level]->character_objects[current_object]->id = levels[current_level]->character_objects[number_of_characters-1]->id;
                                levels[current_level]->character_objects[current_object]->x = levels[current_level]->character_objects[number_of_characters-1]->x;
                                levels[current_level]->character_objects[current_object]->y = levels[current_level]->character_objects[number_of_characters-1]->y;
                                levels[current_level]->number_of_characters--;
                                current_object = NO_OBJECT_SELECTED;
                                timer = 0;

                            }

                        }

                        if (signals & SIGNAL_CURSOR_UP)
                        {

                            if (current_object != NO_OBJECT_SELECTED)
                            {

                                levels[current_level]->character_objects[current_object]->y -= 16;
                                timer = 0;

                            }

                        }

                        if (signals & SIGNAL_CURSOR_LEFT)
                        {

                            if (current_object != NO_OBJECT_SELECTED)
                            {

                                levels[current_level]->character_objects[current_object]->x -= 16;
                                timer = 0;

                            }

                        }

                        if (signals & SIGNAL_CURSOR_RIGHT)
                        {

                            if (current_object != NO_OBJECT_SELECTED)
                            {

                                levels[current_level]->character_objects[current_object]->x += 16;
                                timer = 0;

                            }

                        }

                        if (signals & SIGNAL_CURSOR_DOWN)
                        {

                            if (current_object != NO_OBJECT_SELECTED)
                            {

                                levels[current_level]->character_objects[current_object]->y += 16;
                                timer = 0;

                            }

                        }

                        if (current_object != NO_OBJECT_SELECTED)
                        {

                            if (levels[current_level]->character_objects[current_object]->x < levels[current_level]->x)
                            {

                                levels[current_level]->character_objects[current_object]->x = levels[current_level]->x;

                            }

                            if (levels[current_level]->character_objects[current_object]->x > (levels[current_level]->x+CANVAS_WIDTH-16))
                            {

                                levels[current_level]->character_objects[current_object]->x = levels[current_level]->x+CANVAS_WIDTH-16;

                            }

                            if (levels[current_level]->character_objects[current_object]->y < levels[current_level]->y)
                            {

                                levels[current_level]->character_objects[current_object]->y = levels[current_level]->y;

                            }

                            if (levels[current_level]->character_objects[current_object]->y > (levels[current_level]->y+CANVAS_HEIGHT-16))
                            {

                                levels[current_level]->character_objects[current_object]->y = levels[current_level]->y+CANVAS_HEIGHT-16;

                            }
                            
                        }

                    }

                }

            }
            
            if (mode == PLATFORM_MODE)
            {

                if (timer > 6)
                {

                    if (signals & SIGNAL_SCROLL_DOWN_1)
                    {

                        current_object_type--;
                        timer = 0;

                    }

                    if (signals & SIGNAL_SCROLL_UP_1)
                    {

                        current_object_type++;
                        timer = 0;

                    }

                    if (current_object_type < Level::BROWN_BLOCK)
                    {

                        current_object_type = Level::BROWN_BLOCK;

                    }

                    if (current_object_type > Level::TALL_VINE)
                    {

                        current_object_type = Level::TALL_VINE;

                    }
                    
                    if (current_object == NO_OBJECT_SELECTED)
                    {

                        if (signals & SIGNAL_CURSOR_UP)
                        {

                            cursor_y -= 16;
                            timer = 0;

                        }

                        if (signals & SIGNAL_CURSOR_LEFT)
                        {

                            cursor_x -= 16;
                            timer = 0;

                        }

                        if (signals & SIGNAL_CURSOR_RIGHT)
                        {

                            cursor_x += 16;
                            timer = 0;

                        }

                        if (signals & SIGNAL_CURSOR_DOWN)
                        {

                            cursor_y += 16;
                            timer = 0;

                        }

                        if (cursor_x < 0)
                        {

                            cursor_x = 0;

                        }

                        if (cursor_x > (CANVAS_WIDTH-16))
                        {

                            cursor_x = CANVAS_WIDTH-16;

                        }

                        if (cursor_y < 0)
                        {

                            cursor_y = 0;

                        }

                        if (cursor_y > (CANVAS_HEIGHT-16))
                        {

                            cursor_y = CANVAS_HEIGHT-16;

                        }

                        if (signals & SIGNAL_SELECT)
                        {

                            Select_Object();
                            timer = 0;

                            if (current_object == NO_OBJECT_SELECTED)
                            {

                                if (levels[current_level]->number_of_platforms < Level::MAX_PLATFORMS)
                                {

                                    int number_of_platforms = levels[current_level]->number_of_platforms;

                                    levels[current_level]->platform_objects[number_of_platforms]->id = current_object_type;
                                    levels[current_level]->platform_objects[number_of_platforms]->x = levels[current_level]->x+cursor_x;
                                    levels[current_level]->platform_objects[number_of_platforms]->y = levels[current_level]->y+cursor_y;
                                    current_object = number_of_platforms;
                                    levels[current_level]->number_of_platforms++;

                                }

                            }

                        }

                    }
                    else // object is selected
                    {

                        if (signals & SIGNAL_SELECT)
                        {

                            current_object = NO_OBJECT_SELECTED;
                            timer = 0;

                        }
                        else if (signals & SIGNAL_DELETE)
                        {

                            if (current_object != NO_OBJECT_SELECTED)
                            {

                                int number_of_platforms = levels[current_level]->number_of_platforms;

                                levels[current_level]->platform_objects[current_object]->id = levels[current_level]->platform_objects[number_of_platforms-1]->id;
                                levels[current_level]->platform_objects[current_object]->x = levels[current_level]->platform_objects[number_of_platforms-1]->x;
                                levels[current_level]->platform_objects[current_object]->y = levels[current_level]->platform_objects[number_of_platforms-1]->y;
                                levels[current_level]->number_of_platforms--;
                                current_object = NO_OBJECT_SELECTED;
                                timer = 0;

                            }

                        }

                        if (signals & SIGNAL_CURSOR_UP)
                        {

                            if (current_object != NO_OBJECT_SELECTED)
                            {

                                levels[current_level]->platform_objects[current_object]->y -= 16;
                                timer = 0;

                            }

                        }

                        if (signals & SIGNAL_CURSOR_LEFT)
                        {

                            if (current_object != NO_OBJECT_SELECTED)
                            {

                                levels[current_level]->platform_objects[current_object]->x -= 16;
                                timer = 0;

                            }

                        }

                        if (signals & SIGNAL_CURSOR_RIGHT)
                        {

                            if (current_object != NO_OBJECT_SELECTED)
                            {

                                levels[current_level]->platform_objects[current_object]->x += 16;
                                timer = 0;

                            }

                        }

                        if (signals & SIGNAL_CURSOR_DOWN)
                        {

                            if (current_object != NO_OBJECT_SELECTED)
                            {

                                levels[current_level]->platform_objects[current_object]->y += 16;
                                timer = 0;

                            }

                        }

                        if (current_object != NO_OBJECT_SELECTED)
                        {

                            if (levels[current_level]->platform_objects[current_object]->x < levels[current_level]->x)
                            {

                                levels[current_level]->platform_objects[current_object]->x = levels[current_level]->x;

                            }

                            if (levels[current_level]->platform_objects[current_object]->x > (levels[current_level]->x+CANVAS_WIDTH-16))
                            {

                                levels[current_level]->platform_objects[current_object]->x = levels[current_level]->x+CANVAS_WIDTH-16;

                            }

                            if (levels[current_level]->platform_objects[current_object]->y < levels[current_level]->y)
                            {

                                levels[current_level]->platform_objects[current_object]->y = levels[current_level]->y;

                            }

                            if (levels[current_level]->platform_objects[current_object]->y > (levels[current_level]->y+CANVAS_HEIGHT-16))
                            {

                                levels[current_level]->platform_objects[current_object]->y = levels[current_level]->y+CANVAS_HEIGHT-16;

                            }
                            
                        }

                    }

                }

            }
            
            // display the results
            
            while (screen < NUMBER_OF_SCREENS)
            {

                blit(bitmaps[levels[current_level]->background], canvas, 0, 0,
                     ((screen*CANVAS_WIDTH)-levels[current_level]->x),
                     0, CANVAS_WIDTH, CANVAS_HEIGHT);
                screen++;
   
            }
            
            while (platform < levels[current_level]->number_of_platforms)
            {

                draw_sprite(canvas, bitmaps[Get_Object_Bitmap(levels[current_level]->platform_objects[platform]->id)],
                            (levels[current_level]->platform_objects[platform]->x-levels[current_level]->x),
                            (levels[current_level]->platform_objects[platform]->y-levels[current_level]->y));
                hline(canvas, (levels[current_level]->platform_objects[platform]->x-levels[current_level]->x),
                      (levels[current_level]->platform_objects[platform]->y-levels[current_level]->y),
                      ((levels[current_level]->platform_objects[platform]->x-levels[current_level]->x)+3),
                      makecol(0, 255, 0));
                vline(canvas, (levels[current_level]->platform_objects[platform]->x-levels[current_level]->x),
                      ((levels[current_level]->platform_objects[platform]->y-levels[current_level]->y)+1),
                      ((levels[current_level]->platform_objects[platform]->y-levels[current_level]->y)+3),
                      makecol(0, 255, 0));
                platform++;

            }
            
            while (character < levels[current_level]->number_of_characters)
            {

                draw_sprite(canvas, bitmaps[Get_Object_Bitmap(levels[current_level]->character_objects[character]->id)],
                            (levels[current_level]->character_objects[character]->x-levels[current_level]->x),
                            (levels[current_level]->character_objects[character]->y-levels[current_level]->y));
                hline(canvas, (levels[current_level]->character_objects[character]->x-levels[current_level]->x),
                      (levels[current_level]->character_objects[character]->y-levels[current_level]->y),
                      ((levels[current_level]->character_objects[character]->x-levels[current_level]->x)+3),
                      makecol(255, 0, 0));
                vline(canvas, (levels[current_level]->character_objects[character]->x-levels[current_level]->x),
                      ((levels[current_level]->character_objects[character]->y-levels[current_level]->y)+1),
                      ((levels[current_level]->character_objects[character]->y-levels[current_level]->y)+3),
                      makecol(255, 0, 0));
                character++;

            }
            
            if (mode == SCREEN_MODE)
            {

                screen = 0;

                while (screen < Level::MAX_HEIGHT)
                {

                    hline(canvas, 0, (-(screen*CANVAS_HEIGHT)-levels[current_level]->y),
                          (CANVAS_WIDTH-1), makecol(0, 255, 0));
                    screen++;

                }

                screen = 0;

                while (screen < NUMBER_OF_SCREENS)
                {

                    vline(canvas, ((screen*CANVAS_WIDTH)-levels[current_level]->x),
                          0, (CANVAS_HEIGHT-1), makecol(0, 255, 0));
                    stretch_sprite(canvas, bitmaps[BLUEJAY_STANDING_BM],
                                   (((screen*CANVAS_WIDTH)+16)-levels[current_level]->x),
                                   (128-levels[current_level]->y), 16, 16);
                    textprintf_ex(canvas, font, (((screen*CANVAS_WIDTH)-levels[current_level]->x)+2),
                                  (CANVAS_HEIGHT-text_height(font)-1), makecol(255, 255, 255),
                                  makecol(0, 0, 0), "Screen %i", screen);
                    textprintf_ex(canvas, font, (((screen*CANVAS_WIDTH)-levels[current_level]->x)+2),
                                  (CANVAS_HEIGHT-(text_height(font)*2)-2), makecol(255, 255, 255),
                                  makecol(0, 0, 0), "Pointer %i (%i)", screen,
                                  levels[current_level]->pointers[screen]);
                    screen++;
                              
                }
                
            }
            
            if ((mode == PLATFORM_MODE) || (mode == CHARACTER_MODE))
            {

                if (current_object == NO_OBJECT_SELECTED)
                {

                    draw_trans_sprite(canvas, bitmaps[Get_Object_Bitmap(current_object_type)],
                                      1, 1);
                    rect(canvas, cursor_x, cursor_y, (cursor_x+15), (cursor_y+15),
                         makecol(255, 0, 0));

                }

            }
            
            textprintf_ex(canvas, font, 80, 2, makecol(255, 255, 255),
                          makecol(0, 0, 0), "Level %i", current_level);

            if (mode == SCREEN_MODE)
            {

                textprintf_ex(canvas, font, 80, (3+text_height(font)),
                              makecol(255, 255, 255), makecol(0, 0, 0), "Mode: %s",
                              "screen mode");

            }
            
            if (mode == CHARACTER_MODE)
            {

                textprintf_ex(canvas, font, 80, (3+text_height(font)),
                              makecol(255, 255, 255), makecol(0, 0, 0), "Mode: %s",
                              "character mode");

            }
            
            if (mode == PLATFORM_MODE)
            {

                textprintf_ex(canvas, font, 80, (3+text_height(font)),
                              makecol(255, 255, 255), makecol(0, 0, 0), "Mode: %s",
                              "platform mode");

            }
            
            Display_Scene();

        }

    }

    sprintf(level_name, "data\\levels\\level_%i.map", current_level);
    fix_filename_slashes(level_name);
    levels[current_level]->Save(level_name);
    stop_midi();
    clear_bitmap(canvas);
    textout_ex(canvas, font, "Exiting... please wait.", 1, 1, makecol(255, 255, 255), -1);
    Display_Scene();

}

void Application::Select_Object()
{

    if (mode == CHARACTER_MODE)
    {

        int object = 0;
        
        current_object = NO_OBJECT_SELECTED;
        
        while (object < levels[current_level]->number_of_characters)
        {

            if (((levels[current_level]->x+cursor_x) == levels[current_level]->character_objects[object]->x) &&
                ((levels[current_level]->y+cursor_y) == levels[current_level]->character_objects[object]->y))
            {


                current_object = object;
                break;

            }

            object++;

        }

    }
    
    if (mode == PLATFORM_MODE)
    {

        int object = 0;

        current_object = NO_OBJECT_SELECTED;

        while (object < levels[current_level]->number_of_platforms)
        {

            if (((levels[current_level]->x+cursor_x) == levels[current_level]->platform_objects[object]->x) &&
                ((levels[current_level]->y+cursor_y) == levels[current_level]->platform_objects[object]->y))
            {

                current_object = object;
                break;

            }

            object++;

        }

    }

}

int Application::Get_Object_Bitmap(int id)
{

    int bitmap;
    
    if (id == Level::BLACK_BIRD)
    {

        bitmap = BLACK_BIRD_STANDING_BM;

    }
    
    if (id == Level::BLUEJAY)
    {

        bitmap = BLUEJAY_STANDING_BM;

    }
    
    if (id == Level::CLAM)
    {

        bitmap = CLAM_MOUTH_OPEN_BM;

    }
    
    if (id == Level::EGG)
    {

        bitmap = EGG_BM;

    }
    
    if (id == Level::FLY)
    {

        bitmap = FLY_WINGS_IN_BM;

    }
    
    if (id == Level::MOSQUITO)
    {

        bitmap = MOSQUITO_WINGS_DOWN_BM;

    }
    
    if (id == Level::BROWN_BLOCK)
    {

        bitmap = BROWN_BLOCK_BM;

    }
    
    if (id == Level::CEMENT_BLOCK)
    {

        bitmap = CEMENT_BLOCK_BM;

    }
    
    if (id == Level::BIG_BUSH)
    {

        bitmap = BIG_BUSH_BM;

    }
    
    if (id == Level::SMALL_BUSH)
    {

        bitmap = SMALL_BUSH_BM;

    }
    
    if (id == Level::CHERRY)
    {

        bitmap = CHERRY_BM;

    }
    
    if (id == Level::GROUND)
    {

        bitmap = GROUND_BM;

    }
    
    if (id == Level::PIPE)
    {

        bitmap = PIPE_BM;

    }
    
    if (id == Level::SHOUTING_BLACK_BIRD)
    {

        bitmap = SHOUTING_BLACK_BIRD_BM;

    }
    
    if (id == Level::LIMESTONE)
    {
    
        bitmap = LIMESTONE_BM;
    
    }
    
    if (id == Level::LEAPING_BLACK_BIRD)
    {
    
        bitmap = LEAPING_BLACK_BIRD_BM;
    
    }
    
    if (id == Level::GHOST)
    {
    
        bitmap = GHOST_BM;
    
    }
    
    if (id == Level::MASTER_ECTO)
    {
    
        bitmap = MASTER_ECTO_BM;
    
    }
    
    if (id == Level::ROCK)
    {
    
        bitmap = ROCK_BM;
    
    }
    
    if (id == Level::LEDGE)
    {
    
        bitmap = LEDGE_BM;
    
    }
    
    if (id == Level::WALK_THROUGH_DIRT)
    {
    
        bitmap = WALK_THROUGH_DIRT_BM;
    
    }
    
    if (id == Level::GOLDENJAY)
    {
    
        bitmap = GOLDENJAY_PERCHED_BM;
    
    }
    
    if (id == Level::SWOOPER)
    {
    
        bitmap = SWOOPER_WINGS_OUT_BM;
    
    }
    
    if (id == Level::WIRE)
    {
    
        bitmap = WIRE_BM;
    
    }
    
    if (id == Level::LOCAL_ROCK)
    {
    
        bitmap = LOCAL_ROCK_BM;
    
    }
    
    if (id == Level::PIPE_SWITCH)
    {
    
        bitmap = PIPE_SWITCH_BM;
    
    }
    
    if (id == Level::REVERSE_PIPE_SWITCH)
    {
    
        bitmap = REVERSE_PIPE_SWITCH_BM;
    
    }
    
    if (id == Level::SUPER_MOSQUITO)
    {
    
        bitmap = SUPER_MOSQUITO_WINGS_UP_BM;
    
    }
    
    if (id == Level::LEMMING)
    {
    
        bitmap = LEMMING_STILL_BM;
    
    }
    
    if (id == Level::THROWABLE_ROCK)
    {
    
        bitmap = THROWABLE_ROCK_BM;
    
    }
    
    if (id == Level::STOP_ATTACK_OBJECT)
    {
    
        bitmap = STOP_ATTACK_BM;
    
    }
    
    if (id == Level::HUNTING_FLY)
    {
    
        bitmap = HUNTING_FLY_BM;
    
    }
    
    if (id == Level::TOMATOO_PLANT)
    {
    
        bitmap = TOMATOO_PLANT_HEAD_BM;
    
    }
    
    if (id == Level::STOPPER)
    {
    
        bitmap = STOPPER_BM;
    
    }
    
    if (id == Level::SCROLLING_BACKGROUND)
    {
    
        bitmap = SCROLLING_BACKGROUND_BM;
    
    }
    
    if (id == Level::LOCAL_PIPE)
    {
    
        bitmap = LOCAL_PIPE_BM;
    
    }
    
    if (id == Level::MESSAGE_OBJECT)
    {
    
        bitmap = MESSAGE_BOX_BM;
    
    }
    
    if (id == Level::STONE_WALL)
    {
    
        bitmap = STONE_WALL_BM;
    
    }
    
    if (id == Level::FAKE_CEMENT_BLOCK)
    {
    
        bitmap = FAKE_CEMENT_BLOCK_BM;
    
    }
    
    if (id == Level::SPIKED_POLE)
    {
    
        bitmap = SPIKED_POLE_POINT_BM;
    
    }
    
    if (id == Level::BOILING_MUD)
    {
    
        bitmap = BOILING_MUD_BM;
    
    }
    
    if (id == Level::MUD_DROP)
    {
    
        bitmap = MUD_DROP_BM;
    
    }
    
    if (id == Level::YELLOW_CHERRY)
    {
    
        bitmap = YELLOW_CHERRY_BM;
    
    }
    
    if (id == Level::SHORT_VINE)
    {
    
        bitmap = SHORT_VINE_BM;
    
    }
    
    if (id == Level::TALL_VINE)
    {
    
        bitmap = TALL_VINE_BM;
    
    }

    if (id == Level::NO_ECTO_SWITCH)
    {

        bitmap = NO_ECTO_SWITCH_BM;

    }
    
    return bitmap;

}

void Application::Generate_Signals()
{

    if (keyboard_needs_poll())
    {
    
        poll_keyboard();
    
    }
    
    signals = 0;
    
    if (key[KEY_LEFT])
    {
    
        signals |= SIGNAL_LEFT;
    
    }
    
    if (key[KEY_RIGHT])
    {
    
        signals |= SIGNAL_RIGHT;
    
    }
    
    if (key[KEY_UP])
    {
    
        signals |= SIGNAL_UP;
    
    }
    
    if (key[KEY_DOWN])
    {
    
        signals |= SIGNAL_DOWN;
    
    }
    
    if (key[KEY_SPACE])
    {
    
        signals |= SIGNAL_FLY;
    
    }
    
    if (key[KEY_ENTER])
    {
    
        signals |= SIGNAL_START;
    
    }
    
    if (key[KEY_Q])
    {
    
        signals |= SIGNAL_QUIT;
    
    }
    
    if (key[KEY_P])
    {
    
        signals |= SIGNAL_PAUSE;
    
    }
    
    if (key[KEY_S])
    {
    
        signals |= SIGNAL_SAVE;
    
    }
    
    if (key[KEY_D])
    {
    
        signals |= SIGNAL_DELETE;
    
    }
    
    if (key[KEY_K])
    {
    
        signals |= SIGNAL_SELECT;
    
    }
    
    if (key[KEY_I])
    {
    
        signals |= SIGNAL_CURSOR_UP;
    
    }
    
    if (key[KEY_J])
    {
    
        signals |= SIGNAL_CURSOR_LEFT;
    
    }
    
    if (key[KEY_L])
    {
    
        signals |= SIGNAL_CURSOR_RIGHT;
    
    }
    
    if (key[KEY_M])
    {
    
        signals |= SIGNAL_CURSOR_DOWN;
    
    }
    
    if (key[KEY_PGUP])
    {
    
        signals |= SIGNAL_LEVEL_UP;
    
    }
    
    if (key[KEY_PGDN])
    {
    
        signals |= SIGNAL_LEVEL_DOWN;
    
    }
    
    if (key[KEY_Z])
    {
    
        signals |= SIGNAL_SCROLL_DOWN_1;
    
    }
    
    if (key[KEY_X])
    {
    
        signals |= SIGNAL_SCROLL_UP_1;
    
    }
    
    if (key[KEY_C])
    {
    
        signals |= SIGNAL_SCROLL_DOWN_2;
    
    }
    
    if (key[KEY_V])
    {
    
        signals |= SIGNAL_SCROLL_UP_2;
    
    }

    if (key[KEY_B])
    {
    
        signals |= SIGNAL_SCROLL_DOWN_3;
    
    }
    
    if (key[KEY_N])
    {
    
        signals |= SIGNAL_SCROLL_UP_3;
    
    }

    if (key[KEY_1])
    {
    
        signals |= SIGNAL_SCREEN_MODE;
    
    }
    
    if (key[KEY_2])
    {
    
        signals |= SIGNAL_CHARACTER_MODE;
    
    }
    
    if (key[KEY_3])
    {
    
        signals |= SIGNAL_PLATFORM_MODE;
    
    }
    
    if (key[KEY_4])
    {
    
        signals |= SIGNAL_MOVIE_RECORD;
    
    }
    
    if (key[KEY_5])
    {
    
        signals |= SIGNAL_MOVIE_PLAY;
    
    }
    
    if (key[KEY_6])
    {
    
        signals |= SIGNAL_MOVIE_STOP;
    
    }
    
}

void Application::Load_Movie(const char* movie)
{

    ifstream file;
    
    file.open(movie);
    
    if (file)
    {
    
        file >> movie_level;
    
        while (!file.eof())
        {
        
            long signal_reg;
            
            file >> signal_reg;
            
            if (!file.eof() && (number_of_recorded_signals < MAX_SIGNAL_BUFFER_LENGTH))
            {
            
                signal_buffer[number_of_recorded_signals] = signal_reg;
                number_of_recorded_signals++;
            
            }
        
        }
    
    }

}

void Application::Save_Movie(const char* movie)
{

    ofstream file;
    
    file.open(movie);
    
    if (file)
    {
    
        int signal = 0;
        
        file << movie_level << endl;
    
        while (signal < number_of_recorded_signals)
        {
        
            file << signal_buffer[signal] << endl;
            signal++;
        
        }
    
    }

}

void Application::Display_Scene()
{

    acquire_screen();
    vsync();
    stretch_blit(canvas, screen, 0, 0, CANVAS_WIDTH, CANVAS_HEIGHT, 0, 0, SCREEN_W, SCREEN_H);
    release_screen();

}
