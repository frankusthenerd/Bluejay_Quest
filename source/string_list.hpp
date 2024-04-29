#ifndef STRING_LIST_HEADER
#define STRING_LIST_HEADER 1

#include <string>
#include <allegro.h>

using namespace std;

class Application;

class String_List
{

    public:
    
    String_List();
    ~String_List();
    void Load_From_File(const char* list_name);
    void Print(Application& app);
    
    private:
    
    static const int MAX_STRINGS;
    string* strings;
    int number_of_strings;

};

#endif
