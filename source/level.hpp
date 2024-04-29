#ifndef LEVEL_HEADER
#define LEVEL_HEADER 1

#include "platform.hpp"
#include "character.hpp"
#include "object.hpp"

class Application;

class Level
{

    public:

    static const int BLACK_BIRD; // characters
    static const int BLUEJAY;
    static const int CLAM;
    static const int EGG;
    static const int FLY;
    static const int MOSQUITO;
    static const int SHOUTING_BLACK_BIRD;
    static const int LEAPING_BLACK_BIRD;
    static const int GHOST;
    static const int MASTER_ECTO;
    static const int ROCK;
    static const int GOLDENJAY;
    static const int SWOOPER;
    static const int LOCAL_ROCK;
    static const int PIPE_SWITCH;
    static const int REVERSE_PIPE_SWITCH;
    static const int SUPER_MOSQUITO;
    static const int LEMMING;
    static const int THROWABLE_ROCK;
    static const int STOP_ATTACK_OBJECT;
    static const int HUNTING_FLY;
    static const int TOMATOO_PLANT;
    static const int SCROLLING_BACKGROUND;
    static const int MESSAGE_OBJECT;
    static const int SPIKED_POLE;
    static const int BOILING_MUD;
    static const int MUD_DROP;
    static const int NO_ECTO_SWITCH;
    static const int BROWN_BLOCK; // "platforms"
    static const int CEMENT_BLOCK;
    static const int BIG_BUSH;
    static const int SMALL_BUSH;
    static const int CHERRY;
    static const int GROUND;
    static const int PIPE;
    static const int LIMESTONE;
    static const int LEDGE;
    static const int WALK_THROUGH_DIRT;
    static const int WIRE;
    static const int STOPPER;
    static const int LOCAL_PIPE;
    static const int STONE_WALL;
    static const int FAKE_CEMENT_BLOCK;
    static const int YELLOW_CHERRY;
    static const int SHORT_VINE;
    static const int TALL_VINE;
    static const int MAX_HEIGHT;
    static const int SIGNAL_ATTACK_BLUEJAY;
    static const int SIGNAL_LOWER_PIPES;
    static const int SIGNAL_RAISE_PIPES;
    static const int SIGNAL_COLLAPSE_CEMENT;
    static const int SIGNAL_DESTROY_ECTO;
    static const int MAX_CHARACTERS;
    static const int MAX_PLATFORMS;
    static const int HEIGHT_ERROR;
    int x;
    int y;
    int number_of_platforms;
    int number_of_characters;
    int bluejay; // location of Bluejay
    int number_of_screens;
    int music_track;
    int signal;
    int background;
    Platform** platforms;
    int* pointers;
    Character** characters;
    bool entered_level;
    Object** platform_objects;
    Object** character_objects;
    bool reposition;
    bool scroll_x;
    bool scroll_y;
    int x_direction;
    int y_direction;
    bool autoscroll_background;
    bool display_message;
    bool displayed_message;
    int height;
    Level();
    ~Level();
    void Load(const char* level);
    void Load_For_Editing(const char* level);
    void Save(const char* level);
    void Process(Application& app);
    void Reset(bool demo_playing);

    private:

    static const int NUMBER_OF_POINTERS;
    int background_x;
    unsigned int timer;
    void Scroll_Background(int direction);
    void Scroll_X(int direction);
    void Scroll_Y(int direction);
    void Position_For_Main_Character();

};

#endif
