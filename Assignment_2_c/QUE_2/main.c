#include <stdio.h>
#include "circle.h"
#include "square.h"
#include "rectangle.h"

int main() {
    double radius = 5.0;
    double side = 4.0;
    double length = 6.0;
    double width = 3.0;

   
    printf("Circle with radius %.2f:\n", radius);
    printf("Area: %.2f\n", calculate_circle_area(radius));
    printf("Perimeter: %.2f\n\n", calculate_circle_perimeter(radius));

    printf("Square with side %.2f:\n", side);
    printf("Area: %.2f\n", calculate_square_area(side));
    printf("Perimeter: %.2f\n\n", calculate_square_perimeter(side));

    printf("Rectangle with length %.2f and width %.2f:\n", length, width);
    printf("Area: %.2f\n", calculate_rectangle_area(length, width));
    printf("Perimeter: %.2f\n", calculate_rectangle_perimeter(length, width));

    return 0;
}

