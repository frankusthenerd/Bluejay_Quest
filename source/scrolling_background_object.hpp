#ifndef SCROLLING_BACKGROUND_OBJECT_HEADER
#define SCROLLING_BACKGROUND_OBJECT_HEADER 1

#include "character.hpp"

class Scrolling_Background_Object: public Character
{

    public:
    
    Scrolling_Background_Object();
    void Process(Application& app,
                 Level& level);

};

#endif
