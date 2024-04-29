#ifndef CLAM_HEADER
#define CLAM_HEADER 1

#include "character.hpp"

class Clam: public Character
{

    public:

    Clam();
    void Process(Application& app,
                 Level& level);

};

#endif
