#ifndef FLY_HEADER
#define FLY_HEADER 1

#include "character.hpp"

class Fly: public Character
{

    public:

    bool hunter;
    Fly();
    void Process(Application& app,
                 Level& level);
                 
    private:
    
    int state;
    int y_max;
    static const int RISING;
    static const int ATTACKING;

};

#endif
