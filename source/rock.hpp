#ifndef ROCK_HEADER
#define ROCK_HEADER 1

#include "character.hpp"

class Rock: public Character
{

    public:
    
    bool local;
    Rock();
    void Process(Application& app,
                 Level& level);
                 
    private:
    
    int angle;

};

#endif
