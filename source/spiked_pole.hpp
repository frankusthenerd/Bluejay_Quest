#ifndef SPIKED_POLE_HEADER
#define SPIKED_POLE_HEADER 1

#include "character.hpp"

class Spiked_Pole: public Character
{

    public:
    
    bool extended;
    Spiked_Pole();
    void Process(Application& app,
                 Level& level);
    void Get_Bump_Map(Rectangle& map,
                      int area,
                      Application& app);
                 
    private:

    static const int MAX_HEIGHT;

};

#endif
