/**
 * main.c - The main entry point of the program
 */
#include "../headers/prototypes.h"

int main(int ac, char **av) {
    // ac is the number of arguments passed to the program
    // av is an array of strings containing the arguments

    // if ac is 2 and the argument is "--help", display the help message
    // we use strcmp to compare each ascii character of the string
    // if one character is different, strcmp returns a non-zero value
    if (ac == 2 && strcmp(av[1], "--help") == 0) {
        // If the user passed "--help", display the help message
        print_help(av[0]);
        return 0;
    }

    // same as above but for "--sort"
    if (ac == 2 && strcmp(av[1], "--sort") == 0) {
        // If the user didn't pass any arguments, show the bubble_sort vs quick_sort
        bubble_sort_vs_quick_sort();
        return 0;
    }

    // If the number of arguments is incorrect, show usage and exit
    // We need 4 arguments: the program name, the filename, the flag, and the sort_flag
    if (ac != 4) {
        // If the number of arguments is incorrect, show usage and exit
        printf("Usage: %s <filename> <flag> <sort_flag>\n", av[0]);
        printf("Use '%s --help' for more information.\n", av[0]);
        return 1;
    }

    // Process the CSV file using the provided flags
    // atoi converts a string to an integer
    // and we cast it to uint8_t because we know the values will never be negative
    // atoi is useful here and already made into the standard library
    // i could have done a atoi myself to make it uint8_t but it's not necessary
    // As this project is not about reinventing the wheel
    // But i still cast it to uint8_t to make it clear that the value will never be negative and it's a small number
    // It's a good practice to use the smallest data type possible to save memory
    process_csv(av[1], (uint8_t)atoi(av[2]), (uint8_t)atoi(av[3]));
    return 0;
}