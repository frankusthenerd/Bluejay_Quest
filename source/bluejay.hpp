#ifndef BLUEJAY_HEADER
#define BLUEJAY_HEADER 1

#include "character.hpp"

class Bluejay: public Character
{

    public:

    static const int HEAD;
    static const int BODY;
    static const int TAIL;
    static const int MAX_STRENGTH;
    bool warped;
    int screen_pointer;
    bool local_pipe;
    int lives;
    int eggs;
    int score;
    bool died;
    Bluejay();
    void Process(Application& app,
                 Level& level);
    void Copy_Status(Bluejay& bluejay);
    void Reset(bool demo_playing);
    void Get_Bump_Map(Rectangle& map,
                      int area,
                      Application& app);

    private:

    static const int IDLE;
    static const int JUMPING;
    static const int FLYING;
    static const int GLIDING;
    static const int GOING_DOWN_PIPE;
    static const int MAX_JUMP_HEIGHT;
    int state;
    int max_y;
    int pipe_x;
    int pipe_y;
    unsigned int flight_counter;
    bool can_jump;

};

#endif
