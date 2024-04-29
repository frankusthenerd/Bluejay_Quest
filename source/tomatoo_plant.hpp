#ifndef TOMATOO_PLANT_HEADER
#define TOMATOO_PLANT_HEADER 1

#include "character.hpp"

class Tomatoo_Plant: public Character
{

    public:
    
    bool hypergrowth_kill;
    Tomatoo_Plant();
    void Process(Application& app,
                 Level& level);
    void Get_Bump_Map(Rectangle& map,
                      int area,
                      Application& app);
                 
    private:
    
    int number_of_stems;
    bool hypergrowth;

};

#endif
