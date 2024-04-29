#ifndef BLACK_BIRD_HEADER
#define BLACK_BIRD_HEADER 1

#include "character.hpp"

class Black_Bird: public Character
{

    public:

    int mode;
    static const int NORMAL;
    static const int SHOUT;
    static const int LEAP;
    Black_Bird();
    void Process(Application& app,
                 Level& level);
    int Get_Points();
                 
    private:

    int y_max;
    bool reset_timer;
    bool stop_fall;
    static const int MAX_JUMP;

};

#endif
