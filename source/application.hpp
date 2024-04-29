#ifndef APPLICATION_HEADER
#define APPLICATION_HEADER 1

#include <allegro.h>
#include "level.hpp"
#include "string_list.hpp"

class Application
{

    public:

    static const int CANVAS_WIDTH;
    static const int CANVAS_HEIGHT;
    static const int GRASS_BACKGROUND_BM; // background gfx
    static const int CLOUDY_BACKGROUND_BM;
    static const int FOREST_BACKGROUND_BM;
    static const int DARK_BACKGROUND_BM;
    static const int UNDERWORLD_BACKGROUND_BM;
    static const int HILLY_BACKGROUND_BM;
    static const int BLACK_BACKGROUND_BM;
    static const int BLACK_BIRD_STANDING_BM; // object gfx
    static const int BLACK_BIRD_HURT_BM;
    static const int BROWN_BLOCK_BM;
    static const int CEMENT_BLOCK_BM;
    static const int BLUEJAY_STANDING_BM;
    static const int BLUEJAY_EATING_BM;
    static const int BLUEJAY_HURT_BM;
    static const int BLUEJAY_WINGS_IN_BM;
    static const int BLUEJAY_WINGS_OUT_BM;
    static const int BIG_BUSH_BM;
    static const int SMALL_BUSH_BM;
    static const int CHERRY_BM;
    static const int CLAM_MOUTH_CLOSED_BM;
    static const int CLAM_MOUTH_OPEN_BM;
    static const int EGG_BM;
    static const int FLY_WINGS_IN_BM;
    static const int FLY_WINGS_OUT_BM;
    static const int GROUND_BM;
    static const int MOSQUITO_WINGS_DOWN_BM;
    static const int MOSQUITO_WINGS_UP_BM;
    static const int PIPE_BM;
    static const int TITLE_BM;
    static const int LIMESTONE_BM;
    static const int GHOST_BM;
    static const int MASTER_ECTO_BM;
    static const int ROCK_BM;
    static const int SHOUTING_BLACK_BIRD_BM;
    static const int LEAPING_BLACK_BIRD_BM;
    static const int LEDGE_BM;
    static const int WALK_THROUGH_DIRT_BM;
    static const int GOLDENJAY_PERCHED_BM;
    static const int GOLDENJAY_MOUTH_OPEN_BM;
    static const int GOLDENJAY_WINGS_IN_BM;
    static const int GOLDENJAY_WINGS_OUT_BM;
    static const int SWOOPER_WINGS_IN_BM;
    static const int SWOOPER_WINGS_OUT_BM;
    static const int FAKE_BUSH_BM;
    static const int WIRE_BM;
    static const int LOCAL_ROCK_BM;
    static const int SWITCH_NORMAL_BM;
    static const int SWITCH_PRESSED_BM;
    static const int PIPE_SWITCH_BM;
    static const int REVERSE_PIPE_SWITCH_BM;
    static const int SUPER_MOSQUITO_WINGS_DOWN_BM;
    static const int SUPER_MOSQUITO_WINGS_UP_BM;
    static const int LEMMING_STILL_BM;
    static const int LEMMING_WALK_BM;
    static const int LEMMING_STILL_ARMS_UP_BM;
    static const int LEMMING_WALK_ARMS_UP_BM;
    static const int THROWABLE_ROCK_BM;
    static const int STOP_ATTACK_BM;
    static const int HUNTING_FLY_BM;
    static const int TOMATOO_PLANT_HEAD_BM;
    static const int TOMATOO_PLANT_STEM_BM;
    static const int STOPPER_BM;
    static const int SCROLLING_BACKGROUND_BM;
    static const int LOCAL_PIPE_BM;
    static const int MESSAGE_BOX_BM;
    static const int STONE_WALL_BM;
    static const int FAKE_CEMENT_BLOCK_BM;
    static const int SPIKED_POLE_POINT_BM;
    static const int SPIKED_POLE_POLE_BM;
    static const int BOILING_MUD_BM;
    static const int MUD_DROP_BM;
    static const int STRENGTH_MARK_BM;
    static const int YELLOW_CHERRY_BM;
    static const int BLUEJAY_ICON_BM;
    static const int SHORT_VINE_BM;
    static const int TALL_VINE_BM;
    static const int EMPTY_MARK_BM;
    static const int NO_ECTO_SWITCH_BM;
    static const int ATHLETIC_THEME_MT; // level music tracks
    static const int HERE_WE_GO_MT;
    static const int HURRY_HURRY_MT;
    static const int MARIO_3_MT;
    static const int UNDERWORLD_MT;
    static const int GHOST_MT;
    static const int NEW_SUPER_MARIO_BROTHERS_MT;
    static const int BATTLE_MT;
    static const int OLD_SUPER_MARIO_BROTHERS_MT;
    static const int SEWERS_MT;
    static const int GAME_OVER_MT; // non level music tracks
    static const int TITLE_SCREEN_MT;
    static const int VICTORY_MT;
    static const int BLUEJAY_DIES_SE;
    static const int DAMAGING_STOMP_SE;
    static const int GRAB_EGG_SE;
    static const int HIT_SE;
    static const int MOSQUITO_SE;
    static const int USELESS_STOMP_SE;
    static const int WARP_SE;
    static const int BIRD_CHIRP_SE;
    static const int PAUSE_SE;
    static const int GROWING_SE;
    static const int SHRINKING_SE;
    static const int THUD_SE;
    static const long SIGNAL_FLY; // generated input signals
    static const long SIGNAL_LEFT;
    static const long SIGNAL_RIGHT;
    static const long SIGNAL_UP;
    static const long SIGNAL_DOWN;
    static const long SIGNAL_PAUSE;
    static const long SIGNAL_QUIT;
    static const long SIGNAL_START;
    static const long SIGNAL_CURSOR_LEFT;
    static const long SIGNAL_CURSOR_RIGHT;
    static const long SIGNAL_CURSOR_UP;
    static const long SIGNAL_CURSOR_DOWN;
    static const long SIGNAL_SELECT;
    static const long SIGNAL_DELETE;
    static const long SIGNAL_SAVE;
    static const long SIGNAL_LEVEL_UP;
    static const long SIGNAL_LEVEL_DOWN;
    static const long SIGNAL_SCROLL_UP_1;
    static const long SIGNAL_SCROLL_DOWN_1;
    static const long SIGNAL_SCROLL_UP_2;
    static const long SIGNAL_SCROLL_DOWN_2;
    static const long SIGNAL_SCROLL_UP_3;
    static const long SIGNAL_SCROLL_DOWN_3;
    static const long SIGNAL_SCREEN_MODE;
    static const long SIGNAL_CHARACTER_MODE;
    static const long SIGNAL_PLATFORM_MODE;
    static const long SIGNAL_MOVIE_RECORD;
    static const long SIGNAL_MOVIE_PLAY;
    static const long SIGNAL_MOVIE_STOP;
    static const int ENDING_MESSAGE;
    BITMAP* canvas;
    BITMAP** bitmaps;
    BITMAP* ghost_temp_bitmap;
    BITMAP* master_ecto_temp_bitmap;
    MIDI** music_tracks;
    SAMPLE** sound_effects;
    bool game_over;
    int current_level;
    long signals;
    Level** levels;
    bool demo_playing;
    String_List** messages;
    bool game_won;
    Application();
    ~Application();
    void Load_Resources();
    void Run_Game();
    void Run_Editor();
    void Stop_Sound_Effects();
    
    private:
    
    static const int NUMBER_OF_SCREENS;
    static const int NUMBER_OF_BITMAPS;
    static const int NUMBER_OF_MUSIC_TRACKS;
    static const int NUMBER_OF_LEVELS;
    static const int NUMBER_OF_SOUND_EFFECTS;
    static const int SCREEN_MODE;
    static const int CHARACTER_MODE;
    static const int PLATFORM_MODE;
    static const int NO_OBJECT_SELECTED;
    static const int MOVIE_RECORDING_MODE;
    static const int MOVIE_PLAYBACK_MODE;
    static const int MOVIE_STOP_MODE;
    static const int MAX_SIGNAL_BUFFER_LENGTH;
    unsigned int timer;
    int mode;
    int cursor_x;
    int cursor_y;
    int current_object;
    long* signal_buffer;
    int movie_mode;
    int number_of_recorded_signals;
    int movie_pos;
    int movie_level;
    void Rebuild_Levels();
    void Select_Object();
    int Get_Object_Bitmap(int id);
    void Generate_Signals();
    void Load_Movie(const char* movie);
    void Save_Movie(const char* movie);
    void Display_Scene();

};

#endif
