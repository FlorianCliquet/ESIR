#include "../headers/util.h"

/**
 * Function to check if a given character is an alphabetic letter (A-Z or a-z).
 * If the character is a lowercase letter (a-z), it is converted to uppercase (A-Z).
 * 
 * @param c Pointer to a character that will be checked and potentially modified.
 * @return Returns 1 if the character is an alphabetic letter, 0 otherwise.
 */
char isAlpha(char *c) {
    /**
     * Check if the character is an uppercase alphabetic letter (A-Z).
     * - The condition '*c >= 'A' && *c <= 'Z'' checks if the character is within the range of uppercase ASCII values.
     * - If true, return 1 to indicate the character is alphabetic.
     */
    if (*c >= 'A' && *c <= 'Z') {
        return 1;
    }
    /**
     * Check if the character is a lowercase alphabetic letter (a-z).
     * - The condition '*c >= 'a' && *c <= 'z'' checks if the character is within the range of lowercase ASCII values.
     * - If true, convert it to the corresponding uppercase letter by subtracting 32 from its ASCII value.
     * - The conversion is done in place, modifying the original character pointed to by 'c'.
     * - Return 1 to indicate the character is alphabetic.
     */
    else if (*c >= 'a' && *c <= 'z') {
        *c = *c - 32;  // Convert to uppercase by subtracting 32 from ASCII value
        return 1;
    }
    /**
     * If the character is neither an uppercase nor a lowercase letter, it is not alphabetic.
     * - Return 0 to indicate the character is not an alphabetic letter.
     */
    else {
        return 0;
    }
}


/**
 * Function to calculate the length of a null-terminated string.
 * 
 * @param str Pointer to the null-terminated string whose length is to be determined.
 * @return Returns the length of the string (number of characters before the null terminator).
 */
int ft_strlen(char *str) {
    /**
     * Initialize an integer variable 'i' to -1.
     * - The variable 'i' will be used as an index to traverse the string.
     * - Starting at -1 allows the first increment to set 'i' to 0, which is the starting index for the string.
     */
    int i = -1;

    /**
     * Iterate through the string until the null terminator ('\0') is encountered.
     * - The 'while' loop continues as long as 'str[++i]' is not equal to the null terminator ('\0').
     * - The expression 'str[++i]' increments 'i' before using it to access the character in 'str'.
     * - The loop condition implicitly checks if the character at the current index is not '\0'.
     */
    while (str[++i]);

    /**
     * Return the length of the string.
     * - After the loop exits, 'i' will hold the number of characters in the string, as it was incremented each time the loop iterated.
     * - The length does not include the null terminator.
     */
    return i;
}

// Function to get key length from user
int get_key_length() {
    int key_length;
    printf("Enter size of the key (or press Enter to exit): ");
    if (scanf("%d", &key_length) != 1 || key_length <= 0) {
        // Clear input buffer
        int c;
        while ((c = getchar()) != '\n' && c != EOF) {}
        return -1;  // Return an invalid key length to indicate exit
    }

    // Clear input buffer after reading key_length
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {}

    return key_length;
}

// Function to get input from the user with enhanced error handling and newline removal
void get_input(char *prompt, char *buffer, int size) {
    /**
     * Display the prompt to the user.
     * The 'printf' function prints the prompt string to the console.
     * The format specifier "%s" is used to output a string, where 'prompt' is passed as an argument.
     */
    printf("%s", prompt);

    /**
     * Read a line of text from standard input using 'fgets'.
     * - 'buffer': Pointer to the location where the input string will be stored.
     * - 'size': Maximum number of characters to read, including the terminating null byte ('\0').
     * - 'stdin': The standard input stream (keyboard).
     * 
     * 'fgets' returns NULL if an error occurs or if the end of the input stream is reached without reading any characters.
     * In such a case, we set the first character of 'buffer' to '\0' to make it an empty string and return from the function.
     */
    if (fgets(buffer, size, stdin) == NULL) {
        buffer[0] = '\0';  // Set buffer to an empty string to indicate input failure
        return;
    }

    /**
     * Calculate the length of the input string using 'strlen'.
     * - 'len' will store the number of characters in 'buffer', excluding the null terminator.
     * Note: Here, we use 'strlen' (not 'ft_strlen') assuming a standard C library function.
     */
    size_t len = ft_strlen(buffer);  // Use 'strlen' to get the length of the input string

    /**
     * Check if the last character in the buffer is a newline character ('\n').
     * - If it is, replace it with a null terminator ('\0') to remove the newline.
     * This step is crucial as 'fgets' includes the newline character when the user presses Enter.
     * Removing the newline ensures that subsequent processing of the input string does not include an unwanted newline.
     */
    if (len > 0 && buffer[len - 1] == '\n') {
        buffer[len - 1] = '\0';  // Replace newline character with null terminator
    }
}
