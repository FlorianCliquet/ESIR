// To avoid multiple definitions of the same function, we use the #ifndef directive
#ifndef PROTOTYPES_H


#define PROTOTYPES_H

// Needed to include the data structure
#include "datastructures.h"

// Any include needed for the prototypes
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string.h>
#include <stddef.h>
#include <time.h>
#include <stdint.h>

// Function prototypes for the functions in the project
// If we don't provide them , the compiler will assume that the function is defined in the same file
// and will raise a warning if it's not the case
void read_csv(char *filename, Country countries[], int *num_countries);

void quick_sort(void *array, size_t n_items, size_t item_size, int (*comp)(const void *, const void *));
void bubble_sort(void *array, size_t n_items, size_t item_size, int (*comp)(const void *, const void *));
int int_cmp(const void *a, const void *b);
Country *allocate_countries(int num_countries);


void bubble_sort_vs_quick_sort();

int compare_co2(const void *a, const void *b);
int compare_consumption_co2(const void *a, const void *b);
int compare_cumulative_co2(const void *a, const void *b);
int compare_population(const void *a, const void *b);
int compare_co2_per_person(const void *a, const void *b);

void sort_csv(Country countries[], int num_countries, uint8_t flag, uint8_t sort_flag);
void display_15_countries(Country countries[], int num_countries);
int process_csv(char *filepath, uint8_t flag, uint8_t sort_flag);
void print_help(char *program_name);
#endif