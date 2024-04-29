#ifndef MOSQUITO_HEADER
#define MOSQUITO_HEADER 1

#include "character.hpp"

class Mosquito: public Character
{

    public:

    Mosquito();
    void Process(Application& app,
                 Level& level);
                 
    private:

    static const int IDLE;
    static const int ATTACKING;
    int state;

};

#endif
