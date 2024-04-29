#ifndef MUD_DROP_HEADER
#define MUD_DROP_HEADER 1

#include "character.hpp"

class Mud_Drop: public Character
{

    public:
    
    Mud_Drop();
    void Process(Application& app,
                 Level& level);
                 
    private:
    
    int y_max;
    static const int MAX_JUMP_HEIGHT;

};

#endif
