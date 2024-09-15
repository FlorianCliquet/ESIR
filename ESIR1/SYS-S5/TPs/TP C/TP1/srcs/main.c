/*
    *****************************************************************************************
    *       TP_1                                                                            *
    *                                                                                       *
    *  name : Florian Cliquet and Pierre Bertholom                                          *
    *                                                                                       *
    *****************************************************************************************

*/

// Headers to every function prototype and defined variable
#include "../headers/util.h"

// Main function
int main() {

    // Variable declaration
    char ciphertext[MAX_INPUT_SIZE];
    char crib[MAX_INPUT_SIZE];
    int key_length;
    char *key = NULL;
    char *cleartext = NULL;

    /**
     * We use an infinite while loop here, so that until we don't have a blank input we loop the program
     */
    while (1) {
        // Get ciphertext input
        get_input("Enter the ciphertext (max 1024 characters, or press Enter to exit): ", ciphertext, MAX_INPUT_SIZE);
        if (ciphertext[0] == '\0') break;

        // Get crib input
        get_input("Enter the crib (max 1024 characters, or press Enter to exit): ", crib, MAX_INPUT_SIZE);
        if (crib[0] == '\0') break;

        // Get key length
        key_length = get_key_length();
        if (key_length <= 0) break;

        // Generate the key using the crib and ciphertext
        key = generate_key(crib, ciphertext, key_length);
        if (key == NULL) {
            printf("Error: Failed to generate key\n");
            continue;  // Skip to the next iteration without exiting the loop
        }

        printf("The key is: %s\n", key);

        // Decrypt the ciphertext using the generated key
        cleartext = decrypt_ciphertext(ciphertext, key);
        if (cleartext == NULL) {
            printf("Error: Decryption failed\n");
            free(key);
            key = NULL;
            continue;  // Skip to the next iteration
        }
        printf("The cleartext is:\n%s\n\n", cleartext);

        // Free allocated memory
        free(key);
        free(cleartext);
        // Set variable to original state
        key = NULL;
        cleartext = NULL;
    }

    // Final cleanup (in case of early exit)
    if (key) free(key);
    if (cleartext) free(cleartext);

    printf("\n\nGoodbye! I hope you enjoyed this small program.\n");
    return 0;
}