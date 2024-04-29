#ifndef PLATFORM_HEADER
#define PLATFORM_HEADER 1

#include "rectangle.hpp"

class Application;

class Platform
{

    public:

    int id;
    int x;
    int y;
    int bitmap;
    int type;
    bool remove;
    static const int PLATFORM;
    static const int ITEM;
    static const int BACKGROUND;
    Platform();
    void Initialize();
    void Get_Bump_Map(Rectangle& map,
                      Application& app);
    void Process(Application& app,
                 int level_x,
                 int level_y);
    void Load_Bump_Map(const char* bump_map);

    private:

    bool bypass_default_bump_map;
    Rectangle loaded_bump_map;
    unsigned int timer;
    int initial_x;
    int initial_y;

};

#endif
