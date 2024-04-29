#include "rectangle.hpp"

/*
 * These functions refer to a rectangle named that is touching this
 * rectangle. So rect is touching self on the left, right, top, or bottom.
 */

bool Rectangle::Is_Touching_Bottom(Rectangle& rect)
{

    bool touching = false;
    
    if (bottom == (rect.top-1))
    {

        int tile = left;
        
        while (tile <= right)
        {

            if ((tile >= rect.left) && (tile <= rect.right))
            {

                touching = true;
                break;

            }

            tile++;

        }

    }
    
    return touching;

}

bool Rectangle::Is_Touching_Top(Rectangle& rect)
{

    bool touching = false;

    if (top == (rect.bottom+1))
    {

        int tile = left;

        while (tile <= right)
        {

            if ((tile >= rect.left) && (tile <= rect.right))
            {

                touching = true;
                break;

            }

            tile++;

        }

    }

    return touching;

}

bool Rectangle::Is_Touching_Left(Rectangle& rect)
{

    bool touching = false;

    if (left == (rect.right+1))
    {

        int tile = top;

        while (tile <= bottom)
        {

            if ((tile >= rect.top) && (tile <= rect.bottom))
            {

                touching = true;
                break;

            }

            tile++;

        }

    }

    return touching;

}

bool Rectangle::Is_Touching_Right(Rectangle& rect)
{

    bool touching = false;

    if (right == (rect.left-1))
    {

        int tile = top;

        while (tile <= bottom)
        {

            if ((tile >= rect.top) && (tile <= rect.bottom))
            {

                touching = true;
                break;

            }

            tile++;

        }

    }

    return touching;

}

bool Rectangle::Is_Touching_Top_Left_Corner(Rectangle& rect)
{

    return ((rect.right == (left-1)) && (rect.bottom == (top-1)));

}

bool Rectangle::Is_Touching_Bottom_Left_Corner(Rectangle& rect)
{

    return ((rect.right == (left-1)) && (rect.top == (bottom+1)));

}

bool Rectangle::Is_Touching_Top_Right_Corner(Rectangle& rect)
{

    return ((rect.left == (right+1)) && (rect.bottom == (top-1)));

}

bool Rectangle::Is_Touching_Bottom_Right_Corner(Rectangle& rect)
{

    return ((rect.left == (right+1)) && (rect.top == (bottom+1)));

}

/*
 * In order for this rectangle to be considered inside rect only one side has to be inside.
 * For this to work this rectangle must be smaller than rect. Such collision like this one
 * should be considered for characters only and even more for ones that move at hyperspeed.
 */
 
bool Rectangle::Is_Inside(Rectangle& rect)
{

    return (rect.Is_Point_Inside(left, top) ||
            rect.Is_Point_Inside(right, top) ||
            rect.Is_Point_Inside(left, bottom) ||
            rect.Is_Point_Inside(right, bottom));

}

bool Rectangle::Is_Point_Inside(int x,
                                int y)
{

    return (((x >= left) && (x <= right)) && ((y >= top) && (y <= bottom)));

}
