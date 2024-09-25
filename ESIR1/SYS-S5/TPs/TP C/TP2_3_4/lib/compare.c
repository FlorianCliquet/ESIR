/**
 * File: compare.c
 * Compare function are used to compare the values of the countries based on the sorting criteria.
 * They are kinda all the same, they just compare different values.
 * Except for the population, which is a long int so we need to handle it differently.
 */
#include "../headers/prototypes.h"

// Trivial comparison functions
int compare_co2(const void *a, const void *b) {
    return ((Country *)a)->co2 - ((Country *)b)->co2;
}

int compare_consumption_co2(const void *a, const void *b) {
    return ((Country *)a)->consumption_co2 - ((Country *)b)->consumption_co2;
}

int compare_cumulative_co2(const void *a, const void *b) {
    return ((Country *)a)->cumulative_co2 - ((Country *)b)->cumulative_co2;
}

int compare_co2_per_person(const void *a, const void *b) {
    return ((Country *)a)->co2_per_person - ((Country *)b)->co2_per_person;
}

// Comparison function for the population
int compare_population(const void *a, const void *b) {
    // We need to cast the values to long int to compare them
    // We can't just subtract them because the result could be greater than INT_MAX
    // And we would have an overflow and an incorrect comparison
    long int pop_a = ((Country *)a)->population;
    long int pop_b = ((Country *)b)->population;

    // We use a if else if else structure to return 1, -1 or 0
    // It might seems not very efficient, but it's actually the most efficient way to do it
    // Because the compiler can optimize it and it's very readable
    // homemade branchless comparison would be less readable and less efficient
    // Because we are not better than the compiler at optimizing
    if (pop_a > pop_b) {
        return 1;
    } else if (pop_a < pop_b) {
        return -1;
    } else {
        return 0;
    }
}
