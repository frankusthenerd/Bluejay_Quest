#ifndef GHOST_HEADER
#define GHOST_HEADER 1

#include "character.hpp"

class Ghost: public Character
{

    public:
    
    Ghost();
    void Process(Application& app,
                 Level& level);

};

#endif
