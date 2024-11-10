#include <stdio.h>
#include <math.h>
#include "circle.h"


double calculate_circle_area(double radius) 
{
    return M_PI * radius * radius;
}

double calculate_circle_perimeter(double radius)
{
    return 2 * M_PI * radius;
}

