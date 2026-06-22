/* Generates 10 employees with random departments, salaries, and unique SSNs.

Each employee has:
- a department (enum)
- a base salary determined by department + random offset
- a unique 4-digit SSN

A lookup table is used to convert enum values to readable department names.
SSNs are validated to ensure no duplicates.

Output prints one employee per line.
*/

#define MAX 9999 // Maximum number possible for SSN
#define MIN 1000 // Minimum number possible for SSN
#include <stdio.h>
#include <stdlib.h>
#include <time.h> // Libraries being declared

enum business_dep // Enum for list of possible departments employees are part of
{
    HR,
    Sales,
    Research,
    Software,
    Executive
};

typedef struct employee { // Struct data type for defining each attribute associated with an employee.
    enum business_dep department;
    int annual_salary;
    int unsigned ssn; //SSN is never negative, so it's unsigned.
} employee;

const char *deptNames[] = { // List of departments written as string. Used as reference when printing out final result. Enum cannot directly convert to string.
    "HR",
    "Sales",
    "Research",
    "Software",
    "Executive"};

employee employees[10]; // Array introduction to store information of 10 employees.

int main(void)
{
    srand(time(NULL)); // Randomness factor to minimise repeated generation of same set of value with every test run.

    // Generate data for each employee
    for (int i = 0; i < 10; i++) {
        int base; // Variable to store base salary. Resets with every loop to prevent overwriting from previous value.

        employees[i].department = rand() % 5; // Randomly chooses from position of 5 departments (0 to 4) in enum list.

        switch (employees[i].department){ // Assign base salary based on department
        case HR: // Enum values map to array indices (0 = HR, 1 = Sales, etc.)
            base = 50000;
            break;
        case Sales:
            base = 65000;
            break;
        case Research:
            base = 70000;
            break;
        case Software:
            base = 90000;
            break;
        case Executive:
            base = 150000;
            break;
        default:
            base = 0;
            break;
        };

        employees[i].annual_salary = base + (rand() % 5000); // Annual salary calculated with offset value not exceeding 5000

        int ssn;
        int unique; // used for SSN validation loop

        do
        {
            unique = 1; // True value to stay in loop.
            ssn = MIN + (rand() % (MAX - MIN + 1)); // SSN generated randomly

            for (int j = 0; j < i; j++)
            {
                if (employees[j].ssn == ssn) // Loops through employees array to check previously generated SSNs for any matches.
                {
                    unique = 0; // Changes to False value if match is found.
                    break;
                }
            }

        } while (!unique); // Repeat until a unique SSN is found

        employees[i].ssn = ssn;

        // Prints final values in one line per employee.
        printf("Employee %d: dept = %s; salary = %d; ssn = %u\n", i + 1, deptNames[employees[i].department], employees[i].annual_salary, employees[i].ssn);
    }

    return 0;
}