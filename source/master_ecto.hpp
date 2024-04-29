#ifndef MASTER_ECTO_HEADER
#define MASTER_ECTO_HEADER 1

#include "character.hpp"

class Master_Ecto: public Character
{

    public:
    
    Master_Ecto();
    void Process(Application& app,
                 Level& level);

    private:

    bool relocated;

};

#endif
