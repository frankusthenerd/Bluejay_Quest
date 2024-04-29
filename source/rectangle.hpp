#ifndef RECTANGLE_HEADER
#define RECTANGLE_HEADER 1

class Rectangle
{

    public:

    int left;
    int top;
    int right;
    int bottom;
    bool Is_Touching_Left(Rectangle& rect);
    bool Is_Touching_Right(Rectangle& rect);
    bool Is_Touching_Top(Rectangle& rect);
    bool Is_Touching_Bottom(Rectangle& rect);
    bool Is_Touching_Top_Left_Corner(Rectangle& rect);
    bool Is_Touching_Bottom_Left_Corner(Rectangle& rect);
    bool Is_Touching_Top_Right_Corner(Rectangle& rect);
    bool Is_Touching_Bottom_Right_Corner(Rectangle& rect);
    bool Is_Inside(Rectangle& rect);
    
    private:
    
    bool Is_Point_Inside(int x,
                         int y);

};

#endif
