#ifndef SWITCH_HEADER
#define SWITCH_HEADER 1

#include "character.hpp"

class Switch: public Character
{

    public:
    
    int mode;
    static const int PIPE;
    static const int REVERSE_PIPE;
    static const int NO_ECTO;
    Switch();
    void Process(Application& app,
                 Level& level);

    private:
    
    bool sent_signal;

};

#endif
