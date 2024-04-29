#ifndef BOILING_MUD_HEADER
#define BOILING_MUD_HEADER 1

#include "character.hpp"

class Boiling_Mud: public Character
{

    public:
    
    Boiling_Mud();
    void Process(Application& app,
                 Level& level);
                 
    private:
    
    bool flip;

};

#endif
