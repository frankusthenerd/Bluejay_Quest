#ifndef THROWABLE_ROCK_HEADER
#define THROWABLE_ROCK_HEADER 1

#include "character.hpp"

class Throwable_Rock: public Character
{

    public:

    bool released;
    Throwable_Rock();
    void Process(Application& app,
                 Level& level);

};

#endif
