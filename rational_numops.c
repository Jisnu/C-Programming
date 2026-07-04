/*
Program: Rational Number Operations
Author: Jisnu Praharaj
Date: July 2026

Description:
This program creates a sample file named "rationals.txt" containing
a list of rational numbers. The first integer in the file specifies
how many rational numbers follow. Each rational number is represented
by a numerator and a denominator and is stored in an array of
Rational structures.

The program implements functions to add, subtract, multiply, and
divide rational numbers. It reads the data from the file, computes
the sum and the average of all rational numbers, simplifies the
results to their lowest terms, and displays them on the screen.
*/

#include <stdio.h>
#include <stdlib.h>

// Structure to represent a rational number
typedef struct {
    int numerator;
    int denominator;
} Rational;

// Function prototypes
int gcd(int a, int b);
void simplify(Rational *r);
Rational add(Rational r1, Rational r2);
Rational subtract(Rational r1, Rational r2);
Rational multiply(Rational r1, Rational r2);
Rational divide(Rational r1, Rational r2);

int main() {
    FILE *fp;
    int n, i;

    // Create a sample file
    fp = fopen("rationals.txt", "w");

    fprintf(fp, "6\n");
    fprintf(fp, "9 11\n");
    fprintf(fp, "4 5\n");
    fprintf(fp, "1 2\n");
    fprintf(fp, "3 4\n");
    fprintf(fp, "7 8\n");
    fprintf(fp, "5 6\n");

    fclose(fp);

    // Open the input file for reading
    fp = fopen("rationals.txt", "r");

    if (fp == NULL) {
        printf("Error: Could not open rationals.txt\n");
        return 1;
    }

    // Read the number of rational numbers
    fscanf(fp, "%d", &n);

   // Dynamically allocate memory for the array of rationals
    Rational *data = (Rational *)malloc(n * sizeof(Rational));

    if (data == NULL) {
        printf("Memory allocation failed.\n");
        fclose(fp);
        return 1;
    }

    // Read each numerator and denominator into the array
    for (i = 0; i < n; i++) {
        fscanf(fp, "%d %d",
               &data[i].numerator,
               &data[i].denominator);

        // Simplify the fraction after reading it
        simplify(&data[i]);
    }

    fclose(fp);

    // Display all rational numbers read from the file
    printf("Rational Numbers:\n");
    for (i = 0; i < n; i++) {
        printf("%d/%d\n",
               data[i].numerator,
               data[i].denominator);
    }

    // Initialize the sum as 0/1
    Rational sum = {0, 1};

    // Add all rational numbers together
    for (i = 0; i < n; i++) {
        sum = add(sum, data[i]);
    }

    printf("\nSum = %d/%d\n", sum.numerator, sum.denominator);

    // Compute the average by dividing the sum by the number of rationals
    Rational count = {n, 1};
    Rational average = divide(sum, count);

    printf("Average = %d/%d\n", average.numerator, average.denominator);

    // Free dynamically allocated memory
    free(data);

    return 0;
}

// Returns the greatest common divisor using Euclid's algorithm
int gcd(int a, int b) {
    if (a < 0)
        a = -a;

    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }

    return a;
}

// Reduces a rational number to its simplest form
void simplify(Rational *r) {
    int g = gcd(r->numerator, r->denominator);

    r->numerator /= g;
    r->denominator /= g;

    // Ensure the denominator is always positive
    if (r->denominator < 0) {
        r->numerator = -r->numerator;
        r->denominator = -r->denominator;
    }
}

// Adds two rational numbers and returns the result
Rational add(Rational r1, Rational r2) {
    Rational result;

    result.numerator =
        r1.numerator * r2.denominator +
        r2.numerator * r1.denominator;

    result.denominator =
        r1.denominator * r2.denominator;

    simplify(&result);

    return result;
}

// Subtracts the second rational number from the first
Rational subtract(Rational r1, Rational r2) {
    Rational result;

    result.numerator =
        r1.numerator * r2.denominator -
        r2.numerator * r1.denominator;

    result.denominator =
        r1.denominator * r2.denominator;

    simplify(&result);

    return result;
}

// Multiplies two rational numbers
Rational multiply(Rational r1, Rational r2) {
    Rational result;

    result.numerator =
        r1.numerator * r2.numerator;

    result.denominator =
        r1.denominator * r2.denominator;

    simplify(&result);

    return result;
}

// Divides the first rational number by the second
Rational divide(Rational r1, Rational r2) {
    Rational result;

    result.numerator =
        r1.numerator * r2.denominator;

    result.denominator =
        r1.denominator * r2.numerator;

    simplify(&result);

    return result;
}