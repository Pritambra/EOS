#include <stdio.h>
#include "rectangle.h"

double calculate_rectangle_area(double length, double width) 
{
    return length * width;
}

double calculate_rectangle_perimeter(double length, double width)
{
    return 2 * (length + width);
}

