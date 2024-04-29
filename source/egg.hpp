#ifndef EGG_HEADER
#define EGG_HEADER 1

#include "character.hpp"

class Egg: public Character
{

    public:

    Egg();
    void Process(Application& app,
                 Level& level);
    void Reset(bool demo_playing);

};

#endif
