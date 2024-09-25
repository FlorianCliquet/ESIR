/**
 * @file sort.c
 * The bubble sort algorithm sorts a list of elements by comparing each element with the next one and swapping them if they are in the wrong order.
 * It tracks if the list is sorted using a boolean variable.
 * Space complexity is O(1) and time complexity is O(n^2).
 * It's easy to implement but not efficient for large lists.
 * A better sorting algorithm would be quicksort with a time complexity of O(n log n).
 */

#include "../headers/prototypes.h"

// Function prototypes
void bubble_sort(void *array, size_t n_items, size_t item_size, int (*comp)(const void *, const void *));
void quick_sort(void *array, size_t n_items, size_t item_size, int (*comp)(const void *, const void *));
void ft_memcpy(void *dest, const void *src, size_t n);
int int_cmp(const void *a, const void *b);
void quick_sort_recursive(void *array, int low, int high, size_t item_size, int (*comp)(const void *, const void *));
int partition(void *array, int low, int high, size_t item_size, int (*comp)(const void *, const void *));

/**
 * @brief Function that sorts an array of elements using the bubble sort algorithm, given a comparison function.
 * @param array: pointer to the array of elements to be sorted. It could be an array of any type.
 * @param n_items: number of items in the array.
 * @param item_size: size of each item in the array.
 * @param comp: pointer to the comparison function that will be used to compare the elements of the array. It must be in accordance with the array type.
 */
void bubble_sort(void *array, size_t n_items, size_t item_size, int (*comp)(const void *, const void *)) {
    char *arr = array;
    int sorted;
    size_t i;
    char temp[item_size];

    do {
        sorted = 1;
        for (i = 0; i < n_items - 1; i++) {
            if (comp(arr + i * item_size, arr + (i + 1) * item_size) > 0) {
                // Swap elements
                ft_memcpy(temp, arr + i * item_size, item_size);
                ft_memcpy(arr + i * item_size, arr + (i + 1) * item_size, item_size);
                ft_memcpy(arr + (i + 1) * item_size, temp, item_size);
                sorted = 0;
            }
        }
    } while (!sorted);
}

/**
 * @brief Function that sorts an array of elements using the quicksort algorithm, given a comparison function.
 * @param array: pointer to the array of elements to be sorted. It could be an array of any type.
 * @param n_items: number of items in the array.
 * @param item_size: size of each item in the array.
 * @param comp: pointer to the comparison function that will be used to compare the elements of the array. It must be in accordance with the array type.
 */
void quick_sort(void *array, size_t n_items, size_t item_size, int (*comp)(const void *, const void *)) {
    // Check if there are at least two items to sort
    if (n_items > 1) {
        // Call the recursive quicksort function
        quick_sort_recursive(array, 0, n_items - 1, item_size, comp);
    }
}

// low represents the first index of the array, high represents the last index of the array
void quick_sort_recursive(void *array, int low, int high, size_t item_size, int (*comp)(const void *, const void *)) {
    /* low > high condiiton is the base case for the recursive function
    * If the low index is greater than the high index, the array is sorted 
    */
    if (low < high) {
        // pivot_index is the index where the pivot element is present in the array
        int pivot_index = partition(array, low, high, item_size, comp);
        // Recursively sort the left and right subarrays
        quick_sort_recursive(array, low, pivot_index - 1, item_size, comp);
        quick_sort_recursive(array, pivot_index + 1, high, item_size, comp);
    }
}

// Function to partition the array and return the index of the pivot element
int partition(void *array, int low, int high, size_t item_size, int (*comp)(const void *, const void *)) {
    char *arr = array;
    char pivot[item_size];
    // Copy the pivot element to the pivot array
    ft_memcpy(pivot, arr + high * item_size, item_size);
    // i is the index of the smaller element
    int i = low - 1;
    // loop through the array and compare each element with the pivot element
    for (int j = low; j < high; j++) {
        // If the current element is smaller than the pivot element, swap the elements
        if (comp(arr + j * item_size, pivot) <= 0) {
            i++;
            char temp[item_size];
            ft_memcpy(temp, arr + i * item_size, item_size);
            ft_memcpy(arr + i * item_size, arr + j * item_size, item_size);
            ft_memcpy(arr + j * item_size, temp, item_size);
        }
    }
    // Swap the pivot element with the element at index i + 1
    char temp[item_size];
    ft_memcpy(temp, arr + (i + 1) * item_size, item_size);
    ft_memcpy(arr + (i + 1) * item_size, arr + high * item_size, item_size);
    ft_memcpy(arr + high * item_size, temp, item_size);

    return i + 1;
}

/*
* Function to copy n bytes from src to dest
* @param dest: pointer to the destination array
* @param src: pointer to the source array
* @param n: number of bytes to copy
*/
void ft_memcpy(void *dest, const void *src, size_t n) {
    char *d = dest;
    const char *s = src;
    for (size_t i = 0; i < n; i++) {
        d[i] = s[i];
    }
}

// Comparison function for integers
int int_cmp(const void *a, const void *b) {
    return *(int *)a - *(int *)b;
}

void bubble_sort_vs_quick_sort() {
    int home_made_array[120000];

    // Populate the array with random values for demonstration purposes
    for (int i = 0; i < 120000; i++) {
        home_made_array[i] = rand() % 10000; // Random values between 0 and 9999
    }

    int array_to_be_sorted[] = {9, 2, 1, 15, 25, 27, 20, 2, 14, 9, 2, 12, 21, 40, 23, 5, 17, 29, 22, 30};
    size_t size = sizeof(array_to_be_sorted) / sizeof(array_to_be_sorted[0]);
    size_t home_made_size = sizeof(home_made_array) / sizeof(home_made_array[0]);

    // Divider for clarity
    printf("\n==========================================================\n");
    printf("                BUBBLE SORT VS QUICK SORT                ");
    printf("\n==========================================================\n");

    // Bubble sort for small array
    printf("\n>>> Bubble Sort (20 elements):\n");
    printf("Array before bubble sort:\n");
    for (size_t i = 0; i < size; i++) {
        printf("%d ", array_to_be_sorted[i]);
    }

    clock_t begin = clock();
    bubble_sort(array_to_be_sorted, size, sizeof(int), int_cmp);
    clock_t end = clock();
    printf("\n\nArray after bubble sort (20 elements):\n");
    for (size_t i = 0; i < size; i++) {
        printf("%d ", array_to_be_sorted[i]);
    }
    printf("\n\nBubble sort completed in: \033[1;32m%f seconds\033[0m\n", (double)(end - begin) / CLOCKS_PER_SEC);

    // Copy home_made_array to home_made_copy for bubble sort
    int home_made_copy[120000];
    ft_memcpy(home_made_copy, home_made_array, sizeof(home_made_array));

    printf("\n>>> Bubble Sort (120,000 elements):\n");
    printf("\033[1;33mNote:\033[0m This may take a while (quadratic time complexity)...\n");

    begin = clock();
    bubble_sort(home_made_copy, home_made_size, sizeof(int), int_cmp);
    end = clock();
    double bubble_sort_time = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("\033[1;32mBubble sort completed for 120,000 elements in %f seconds\033[0m\n", bubble_sort_time);

    // Divider for quick sort
    printf("\n----------------------------------------------------------\n");

    // Quick sort for 120,000 elements
    printf("\n>>> Quick Sort (120,000 elements):\n");

    begin = clock();
    quick_sort(home_made_array, home_made_size, sizeof(int), int_cmp);
    end = clock();
    double quick_sort_time = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("\033[1;32mQuick sort completed for 120,000 elements in %f seconds\033[0m\n", quick_sort_time);

    printf("\n==========================================================\n");
    printf("             COMPARISON RESULTS (120,000 elements)         ");
    printf("\n==========================================================\n");

    printf("\nBubble Sort Time: \033[1;31m%f seconds\033[0m\n", bubble_sort_time);
    printf("Quick Sort Time:  \033[1;32m%f seconds\033[0m\n", quick_sort_time);
    printf("\nQuick sort is approximately \033[1;34m%f times faster\033[0m than bubble sort.\n", bubble_sort_time / quick_sort_time);
    printf("\n==========================================================\n");
}
