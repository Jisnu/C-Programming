#include <stdio.h>
#include <math.h>

/*
    Program: Sine and Cosine Table
    --------------------------------
    This program prints a table of sine and cosine values
    for x in the interval 0 < x < 1 (radians).

    The values are computed using the standard library
    functions sin() and cos() from math.h.
*/

/*
    Returns the sine of x.

    Input:
        x - angle in radians

    Output:
        sin(x), a value in the range [-1, 1]
*/
double calculateSine(double x) {
    return sin(x);
}

/*
    Returns the cosine of x.

    Input:
        x - angle in radians

    Output:
        cos(x), a value in the range [-1, 1]
*/
double calculateCosine(double x) {
    return cos(x);
}

/*
    Prints a formatted table of sine and cosine values
    for x in the interval (0, 1), using step size 0.1.
*/
void displayTable(void) {
    double x;

    printf("x\t\tsin(x)\t\tcos(x)\n");
    printf("-----------------------------------------\n");

    /* Loop strictly within 0 < x < 1 */
    for (x = 0.1; x < 1.0; x += 0.1) {
        printf("%.1lf\t\t%.5lf\t\t%.5lf\n",
               x,
               calculateSine(x),
               calculateCosine(x));
    }
}

int main(void) {
    displayTable();
    return 0;
}