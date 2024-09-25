/**
 * @file display.c
 * This file contains functions to display the top 15 countries based on the sorting criteria.
 * The display_15_countries function prints the top 15 countries based on the sorting criteria.
 * The print_help function displays the help message with the program usage.
 */
#include "../headers/prototypes.h"

/**
 * @brief Function to display the top 15 countries based on the sorting criteria.
 * @param countries: an array of Country structs to display
 * @param num_countries: the number of countries in the array
 */
void display_15_countries(Country countries[], int num_countries) {
    // Display the top 15 countries or all of them if there are less than 15
    int display_count = (num_countries < 15) ? num_countries : 15;

    // Print the header with column titles
    // %-xs means a string with a width of x characters, left-aligned
    // If the string is shorter than x, it will be padded with spaces
    // so that the total length is x and we keep a nice table format
    printf("-------------------------------------------------------------------------------------------------------------------------------------------------------\n");
    printf("| %-10s | %-20s | %-6s | %-12s | %-21s | %-17s | %-17s | %-20s |\n", 
           "ISO Code", "Country", "Year", "CO2 (MT)", "CO2 Consumption (MT)", "Cumulative CO2 (MT)", "CO2 per Person (T)", "Population");
    printf("-------------------------------------------------------------------------------------------------------------------------------------------------------\n");

    // Loop through the last 15 (or fewer) countries, starting from the end of the list
    for (int i = num_countries - 1; i >= num_countries - display_count; i--) {
        // Handle missing values for consumption_co2 and co2_per_person
        char consumption_co2_str[10], co2_per_person_str[10];
        if (countries[i].consumption_co2 == -1.0) {
            // snprintf formats a string and stores it in a buffer
            // it's similar to printf but instead of printing to stdout, it stores the result in a buffer
            // %f formats a float number
            snprintf(consumption_co2_str, sizeof(consumption_co2_str), "N/A");
        } else {
            snprintf(consumption_co2_str, sizeof(consumption_co2_str), "%.2f", countries[i].consumption_co2);
        }

        if (countries[i].co2_per_person == -1.0) {
            snprintf(co2_per_person_str, sizeof(co2_per_person_str), "N/A");
        } else {
            snprintf(co2_per_person_str, sizeof(co2_per_person_str), "%.2f", countries[i].co2_per_person);
        }

        // Print country information
        // %-xd is the same as above, but for integers
        // %-x.yf formats a float number with y decimal places
        // %ld formats a long integer
        printf("| %-10s | %-20s | %-6d | %-12.2f | %-21s | %-19.2f | %-18s | %-20ld |\n",
               countries[i].iso_code, 
               countries[i].country, 
               countries[i].year, 
               countries[i].co2, 
               consumption_co2_str, 
               countries[i].cumulative_co2, 
               co2_per_person_str,
               countries[i].population);
        printf("-------------------------------------------------------------------------------------------------------------------------------------------------------\n");
    }
}


void print_help(char *program_name) {
    // Basic print of the help message
    // Nothing weird done here
    printf("Second Usage: %s <filename> <flag> <sort_flag>\n", program_name);
    printf("\nOptions:\n");
    printf("  --help          Display this help message.\n");
    printf("  --sort          Show bubble sort versus quick sort.\n");
    printf("\nArguments:\n");
    printf("  <filename>      The path to the CSV file to process.\n");
    printf("  <flag>          Sorting criteria:\n");
    printf("                    1 - Sort by CO2 emissions\n");
    printf("                    2 - Sort by consumption-based CO2 emissions\n");
    printf("                    3 - Sort by cumulative CO2 emissions\n");
    printf("                    4 - Sort by CO2 emissions per person\n");
    printf("                    5 - Sort by population\n");
    printf("  <sort_flag>     Sorting algorithm:\n");
    printf("                    1 - Quick Sort\n");
    printf("                    2 - Bubble Sort\n");
}
