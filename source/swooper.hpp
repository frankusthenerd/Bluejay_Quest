#ifndef SWOOPER_HEADER
#define SWOOPER_HEADER 1

#include "character.hpp"

class Swooper: public Character
{

    public:
    
    Swooper();
    void Process(Application& app,
                 Level& level);
    int Get_Points();

};

#endif
