/**
 * @file sort_by.c
 * This file contains functions to sort the countries based on different flags.
 * The flags are:
 * 0 - Do not sort
 * 1 - Sort by CO2 emissions
 * 2 - Sort by consumption-based CO2 emissions
 * 3 - Sort by cumulative CO2 emissions
 * 4 - Sort by CO2 emissions per person
 * 5 - Sort by population
 * The sorting algorithms used are bubble sort and quick sort.
 */

#include "../headers/prototypes.h"

// sort_by... functions
// Just associate the correct comparison function to the sorting function
void sort_by_co2_emissions(Country countries[], int num_countries, uint8_t sort_flag) {
    if (sort_flag == 1)
        quick_sort(countries, num_countries, sizeof(Country), compare_co2);
    else
        bubble_sort(countries, num_countries, sizeof(Country), compare_co2);
}

void sort_by_consumption_co2(Country countries[], int num_countries, uint8_t sort_flag) {
    if (sort_flag == 1)
        quick_sort(countries, num_countries, sizeof(Country), compare_consumption_co2);
    else
        bubble_sort(countries, num_countries, sizeof(Country), compare_consumption_co2);
}

void sort_by_cumulative_co2(Country countries[], int num_countries, uint8_t sort_flag) {
    if (sort_flag == 1)
        quick_sort(countries, num_countries, sizeof(Country), compare_cumulative_co2);
    else
        bubble_sort(countries, num_countries, sizeof(Country), compare_cumulative_co2);
}

void sort_by_population(Country countries[], int num_countries, uint8_t sort_flag) {
    if (sort_flag == 1)
        quick_sort(countries, num_countries, sizeof(Country), compare_population);
    else
        bubble_sort(countries, num_countries, sizeof(Country), compare_population);
}

void sort_by_co2_per_person(Country countries[], int num_countries, uint8_t sort_flag) {
    if (sort_flag == 1)
        quick_sort(countries, num_countries, sizeof(Country), compare_co2_per_person);
    else
        bubble_sort(countries, num_countries, sizeof(Country), compare_co2_per_person);
}

// Redirect to the correct sorting function based on the flag
void sort_csv(Country countries[], int num_countries, uint8_t flag, uint8_t sort_flag){
    // Switch case to determine which sorting function to call
    // We use a switch case because it's more readable than a series of if-else statements and more efficient
    switch (flag) {
        case 0:
            break; // Do not sort
        case 1:
            sort_by_co2_emissions(countries, num_countries, sort_flag);
            break;
        case 2:
            sort_by_consumption_co2(countries, num_countries, sort_flag);
            break;
        case 3:
            sort_by_cumulative_co2(countries, num_countries, sort_flag);
            break;
        case 4:
            sort_by_co2_per_person(countries, num_countries, sort_flag);
            break;
        case 5:
            sort_by_population(countries, num_countries, sort_flag);
            break;
        default:
            printf("Invalid flag\n");
    }
}