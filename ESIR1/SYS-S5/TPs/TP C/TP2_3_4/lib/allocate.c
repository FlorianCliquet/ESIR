/**
 * allocate.c - Functions for allocating memory
 * allocate_countries - Allocate memory for the array of countries
 */
#include "../headers/prototypes.h"

Country *allocate_countries(int num_countries) {
    // Allocate memory for the array of countries
    // malloc function allocates memory in the heap
    // We multiply the number of countries by the size of a Country struct
    // to allocate enough memory for all the countries
    // We don't need to allocate memory for each field of the struct
    // because the struct is a contiguous block of memory and any data from the struct
    // is allocated in the stack because we are aware of potential size of each field
    // char iso_code[10] -> 10 bytes, the same for the other fields
    // It's safer to use the stack instead of the heap for small fixed-size arrays
    Country *countries = (Country *)malloc(num_countries * sizeof(Country));

    //Error handling
    if (countries == NULL) {
        perror("Error allocating memory for countries");
        exit(1);
    }

    return countries;
}