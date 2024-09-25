/**
 * process_csv - Process the csv file and display the top 15 countries
 * @filepath: the path to the csv file
 * @flag: the sorting criteria
 * @sort_flag: the sorting algorithm
 */
#include "../headers/prototypes.h"

// We use uint8_t to represent a number that will never be negative
// This is more efficient than using int, as it uses less memory, and each flag won't exceed 5
int process_csv(char *filepath, uint8_t flag, uint8_t sort_flag) {
    // Initialize the number of countries read to 0
    int country_read = 0;
    // Allocate memory for the array of countries
    Country *countries = allocate_countries(MAX_COUNTRIES);
    // Read the CSV file and store the data in the countries array
    // &country_read is a pointer to the variable country_read
    // We basically dereference the actual variable, so we can modify it in the read_csv function
    read_csv(filepath, countries, &country_read);
    // Sort the countries based on the flag and sort_flag
    // We don't need any return value because the countries array is modified in place
    // As arrays are passed by reference in C, it means that the changes are made into the memory address itself
    sort_csv(countries, country_read, flag, sort_flag);
    // Display the top 15 countries based on the sorting criteria
    display_15_countries(countries, country_read);

    // Free the memory allocated for the countries array, to avoid memory leaks
    // It's not mandatory, but it's a good practice to free the memory when it's not needed anymore
    // In our case it's not a big deal because the program will exit after this function and so the memory will be freed by the OS
    free(countries);
    return 0;
}