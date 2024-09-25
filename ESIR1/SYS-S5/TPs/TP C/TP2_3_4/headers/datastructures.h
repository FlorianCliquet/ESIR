// Same as datastructures.h but with a different name to avoid conflicts with other libraries
#ifndef DATA_H

#define DATA_H

// Constants
#define BUFFER_SIZE 4096 // Buffer size for reading lines from the file, 4096 bytes because it's a common size for a page
#define MAX_COUNTRIES 215 // Maximum number of countries in the CSV file, explicitly defined in the subject

// Data structure for a country
typedef struct {
    char iso_code[10]; // ISO code of the country (longest code is 9 characters, so 10 is enough)
    char country[50]; // Name of the country (longest name is 44 characters, so 50 is enough, and it's really small)
    int year;
    float co2;
    float co2_per_person;
    float consumption_co2;
    float cumulative_co2; 
    long int population; // Long int because the world population is greater than 2^31 - 1
} Country;

#endif