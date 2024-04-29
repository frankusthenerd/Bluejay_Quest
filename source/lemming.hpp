#ifndef LEMMING_HEADER
#define LEMMING_HEADER 1

#include "character.hpp"

class Lemming: public Character
{

    public:
    
    Lemming();
    void Process(Application& app,
                 Level& level);

    private:
    
    int state;
    int y_max;
    bool carrying_object;
    int rock;
    static const int WALKING;
    static const int JUMPING;
    static const int FALLING;
    static const int MAX_JUMP_HEIGHT;

};

#endif
