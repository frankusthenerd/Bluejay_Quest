#include "string_list.hpp"
#include <fstream>
#include "application.hpp"

using namespace std;

const int String_List::MAX_STRINGS = 25;

String_List::String_List()
{

    number_of_strings = 0;
    strings = new string[MAX_STRINGS];

}

String_List::~String_List()
{

    delete[] strings;

}

void String_List::Load_From_File(const char* list_name)
{

    ifstream file;
    
    file.open(list_name);
    
    if (file)
    {
    
        while (!file.eof())
        {
        
            getline(file, strings[number_of_strings]);
            
            if (!file.eof() && (number_of_strings < MAX_STRINGS))
            {
            
                number_of_strings++;
            
            }
        
        }
    
    }

}

void String_List::Print(Application& app)
{

    int s = 0;
    int y = 1;
    
    while (s < number_of_strings)
    {
    
        textout_ex(app.canvas, font, strings[s].c_str(), 1, y, makecol(255, 255, 255), -1);
        y += (text_height(font)+2);
        s++;
    
    }

}
