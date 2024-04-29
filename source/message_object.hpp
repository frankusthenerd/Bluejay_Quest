#ifndef MESSAGE_OBJECT_HEADER
#define MESSAGE_OBJECT_HEADER 1

#include "character.hpp"

class Message_Object: public Character
{

    public:
    
    Message_Object();
    void Process(Application& app,
                 Level& level);

};

#endif
