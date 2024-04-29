#ifndef CHARACTER_HEADER
#define CHARACTER_HEADER 1

#include "rectangle.hpp"
#include <fstream>

using namespace std;

class Application;
class Level;

class Character
{

    public:

    int id;
    int x;
    int y;
    int initial_x;
    int initial_y;
    int bitmap;
    int x_direction;
    int y_direction;
    int strength;
    int number_of_areas;
    int signal;
    unsigned int timer;
    bool hit;
    bool can_hurt;
    static const int SIGNAL_ATTACK_BLUEJAY;
    Character();
    ~Character();
    void Load_Bump_Maps(const char* bump_map_db);
    virtual void Get_Bump_Map(Rectangle& map,
                              int area,
                              Application& app);
    virtual void Process(Application& app,
                         Level& level) = 0;
    virtual void Reset(bool demo_playing);
    bool Is_On_Screen(int level_x,
                      int level_y,
                      Application& app);
    bool Is_On_X_Screen(int level_x,
                        int level_y,
                        Application& app);
    virtual int Get_Points();

    protected:
    
    Rectangle** bump_maps;
    int number_of_bump_maps;
    static const int MAX_BUMP_MAPS;
    static const int NO_PLATFORM_HIT;
    static const int NO_CHARACTER_HIT;
    static const int HIT_LEFT;
    static const int HIT_RIGHT;
    static const int HIT_TOP;
    static const int HIT_BOTTOM;
    static const int HIT_TOP_LEFT;
    static const int HIT_BOTTOM_LEFT;
    static const int HIT_TOP_RIGHT;
    static const int HIT_BOTTOM_RIGHT;
    static const int IS_INSIDE;
    void Which_Platforms_Were_Hit(int& left_platform,
                                  int& right_platform,
                                  int& top_platform,
                                  int& bottom_platform,
                                  int& top_left_platform,
                                  int& bottom_left_platform,
                                  int& top_right_platform,
                                  int& bottom_right_platform,
                                  Level& level,
                                  int area,
                                  Application& app);
    int Which_Character_Was_Hit(Level& level,
                                int area,
                                Application& app,
                                int& character_area,
                                int& hit_results);
    void Flip_Bump_Map(Rectangle& unflipped_map,
                       Rectangle& flipped_map,
                       Application& app);

};

#endif
