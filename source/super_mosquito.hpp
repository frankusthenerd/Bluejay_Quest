#ifndef SUPER_MOSQUITO_HEADER
#define SUPER_MOSQUITO_HEADER 1

#include "character.hpp"

class Super_Mosquito: public Character
{

    public:
    
    Super_Mosquito();
    void Process(Application& app,
                 Level& level);
    int Get_Points();
    void Reset(bool demo_playing);
                 
    private:
    
    int state;
    bool reset_timer;
    int previous_x;
    int previous_y;
    bool flipped_directions;
    static const int HOVERING;
    static const int ATTACKING;
    static const int CALLING_MOSQUITOS;

};

#endif
