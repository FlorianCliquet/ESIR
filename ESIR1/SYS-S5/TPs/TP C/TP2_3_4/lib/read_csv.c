/**
 * read_csv - Reads a CSV file and stores the data in an array of Country structs
 * @filename: the name of the file to read
 * @countries: an array of Country structs to store the data
 * @num_countries: a pointer to an integer to store the number of countries read
 */

#include "../headers/prototypes.h"

void read_csv(char *filename, Country countries[], int *num_countries) {
    char buffer[BUFFER_SIZE];
    // fp is the file pointer, which will be used to read the file
    // "r" means that the file will be opened in read mode
    // FILE is a special type defined in stdio.h that represents a file stream
    FILE *fp = fopen(filename, "r");

    // fp will be NULL if the file could not be opened
    if (fp == NULL) {
        // perror uses the global variable errno to print an error message
        // it prints into stderr, which is the standard error stream
        perror("Error opening file");
        return;
    }

    // Skip the first line (header)
    // Each fgets reads a line from the file and stores it in the buffer
    // Since we don't need the first line, we just read it and discard it
    fgets(buffer, BUFFER_SIZE, fp);


    // Temporary variables to store the values read from the file
    char consumption_co2_str[30];
    int country_count = 0;

    // Read the rest of the file line by line
    // fgets returns NULL when it reaches the end of the file
    // or when an error occurs
    while (fgets(buffer, BUFFER_SIZE, fp) != NULL && country_count < MAX_COUNTRIES) {
        // Pointer to current country struct in the array
        Country *current_country = &countries[country_count];

        //sscanf reads formatted input from a string, it differs from scanf because it reads from a string instead of stdin
        // The format string specifies the format of the input
        // %[^,] reads a string until a comma is found
        // %d reads an integer
        // %f reads a float
        // %ld reads a long int, we use it for the population because the world population is a large number and 
        // greater than 2^31 - 1, which is the maximum value for an int
        sscanf(buffer, "%[^,],%[^,],%d,%f,%[^,],%f,%ld",
                        current_country->iso_code, current_country->country, &current_country->year,
                        &current_country->co2, consumption_co2_str, &current_country->cumulative_co2,
                        &current_country->population);

        // Handle the special case for co2_consumption
        // Instead of using strcmp, we can directly compare the first character of the string
        // If the first character is '?', it means that the value is missing
        if (consumption_co2_str[0] == '?') {
            // Set the value to -1.0 to indicate that it is missing
            current_country->consumption_co2 = -1.0;
            current_country->co2_per_person = -1.0;
        } else {
            // If the value is not missing, convert it to a float
            sscanf(consumption_co2_str, "%f", &current_country->consumption_co2);
            // As we have the consumption_co2, we can calculate the co2 per person
            // We multiply the co2 by 1,000,000 to convert it to tons and not Million of tons
            // Either the value will be too small to be compared 
            current_country->co2_per_person = (1000000 * current_country->co2) / current_country->population;
        }

        // Increment the number of countries read
        country_count++;
    }

    // Set the total number of countries read into the num_countries pointer
    *num_countries = country_count;

    // Close the file
    fclose(fp);
}