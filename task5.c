/*******************************************************************************
 * File Name:    elephant_seal.c
 * Description:  This program reads a dataset of elephant seal weights from an
 * external file, uses modular helper functions to handle parsing,
 * encapsulates math calculations, and outputs the average weight.
 * Author:       Adaptive AI Assistant
 * Date:         May 25, 2026
 *******************************************************************************/

#include <stdio.h>
#include <stdlib.h>

// Global constants for configuration
#define MAX_SEALS 1000
#define FILE_NAME "elephant_seal_data.txt"

/* --- FUNCTION DECLARATIONS (PROTOTYPES) --- */
int read_weights_from_file(const char *filename, int array[], int max_size);
double calculate_average(const int array[], int size);
void print_report(int total_count, double average_weight);

/* ========================================================================== */
/* MAIN FUNCTION                                */
/* ========================================================================== */
int main() {
    int weights[MAX_SEALS];
    int count = 0;
    double average = 0.0;

    // Concern 1: Read and parse data via encapsulated function
    count = read_weights_from_file(FILE_NAME, weights, MAX_SEALS);
    
    // If count returns -1, it indicates a file error occurred
    if (count == -1) {
        return 1; 
    }
    
    if (count == 0) {
        printf("Error: No weight data could be processed from the file.\n");
        return 1;
    }

    // Concern 2: Compute math logic separately
    average = calculate_average(weights, count);

    // Concern 3: Present results cleanly
    print_report(count, average);

    return 0;
}

/* ========================================================================== */
/* FUNCTION DEFINITIONS                              */
/* ========================================================================== */

/**
 * Encapsulates File I/O and String Parsing.
 * Opens the specified file, bypasses metadata tags like , 
 * extracts raw integers, and safely loads them into an array.
 *
 * @param filename  Path to the input file.
 * @param array     The target integer array to populate.
 * @param max_size  The maximum capacity of the array.
 * @return          The total number of integers successfully read, or -1 on file error.
 */
int read_weights_from_file(const char *filename, int array[], int max_size) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error: Could not open file '%s'.\n", filename);
        return -1; 
    }

    int current_count = 0;

    while (current_count < max_size) {
        // Attempt to parse a weight directly
        if (fscanf(file, "%d", &array[current_count]) == 1) {
            current_count++;
        } else {
            char ch;
            // Catch non-numeric layout artifacts (like metadata brackets)
            if (fscanf(file, "%c", &ch) != 1) {
                break; // Ultimate End of File reached
            }
            
            // If it's a source tag start bracket, consume until closing bracket
            if (ch == '[') {
                while (fscanf(file, "%c", &ch) == 1 && ch != ']') {
                    // Loop execution skipped intentionally to move file cursor past tags
                }
            }
        }
    }

    fclose(file);
    return current_count; // Return total numbers read back to the caller
}

/**
 * Encapsulates Mathematical Analysis.
 * Iterates through a given integer array to figure out its average.
 *
 * @param array  The populated array of data points.
 * @param size   The logical size (active elements) of the array.
 * @return       The calculated average as a double-precision decimal.
 */
double calculate_average(const int array[], int size) {
    if (size <= 0) return 0.0;

    long long sum = 0; // Prevents data overflow scenarios
    for (int i = 0; i < size; i++) {
        sum += array[i];
    }

    // Cast to double to prevent data-chopping from standard integer division
    return (double)sum / size;
}

/**
 * Encapsulates Output and UI Reporting.
 * Generates a clean command-line data interface.
 *
 * @param total_count     Total items processed.
 * @param average_weight  The calculated float average.
 */
void print_report(int total_count, double average_weight) {
    printf("\n==================================================\n");
    printf("         ELEPHANT SEAL WEIGHT DATA REPORT         \n");
    printf("==================================================\n");
    printf(" Total Records Processed : %d seals\n", total_count);
    printf(" Calculated Average      : %.2f\n", average_weight);
    printf("==================================================\n\n");
}