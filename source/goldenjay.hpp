#ifndef GOLDENJAY_HEADER
#define GOLDENJAY_HEADER 1

#include "character.hpp"

class Goldenjay: public Character
{

    public:
    
    Goldenjay();
    void Process(Application& app,
                 Level& level);
    int Get_Points();
                 
    private:
    
    static const int IDLE;
    static const int ATTACKING;
    int state;
    bool reset_timer;

};

#endif
