#ifndef STOP_ATTACK_OBJECT_HEADER
#define STOP_ATTACK_OBJECT_HEADER 1

#include "character.hpp"

class Stop_Attack_Object: public Character
{

    public:
    
    Stop_Attack_Object();
    void Process(Application& app,
                 Level& level);

};

#endif
