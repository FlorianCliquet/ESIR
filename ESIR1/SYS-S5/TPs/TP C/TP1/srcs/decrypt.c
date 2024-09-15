#include "../headers/util.h"

/**
 * Function to generate a key from the given debut message and crypted message.
 * 
 * @param debut_message The initial message used to generate the key.
 * @param crypted_message The encrypted message used to generate the key.
 * @param length_key The length of the key to be generated.
 * @return Returns a dynamically allocated key of length `length_key`, or NULL if memory allocation fails.
 */
char *get_key(char *debut_message, char *crypted_message, char length_key) {
    // Allocate memory for the key, with size equal to length_key
    char *key = malloc(sizeof(char) * length_key);
    if (key == NULL) {
        printf("Error: Memory allocation failed for key\n");
        return NULL;
    }

    // Generate the key by computing each character's position in the alphabet
    for (int i = 0; i < length_key; i++) {
        key[i] = alphabet[(crypted_message[i] + debut_message[i] - 2 * 'A' + 26) % 26];
        // The formula calculates the key character based on the Beaufort cipher principle
        // Adjust for negative values and ensure results wrap around the alphabet
    }

    return key;
}

/**
 * Function to decrypt a single character using the Beaufort cipher.
 * 
 * @param c Character to be decrypted (assumed to be an uppercase letter 'A' to 'Z').
 * @param key Key character used for decryption (assumed to be an uppercase letter 'A' to 'Z').
 * @return Returns the decrypted character.
 */
char decrypt(char c, char key) {
    // Calculate the shift based on the key character
    int shift = key - 'A';
    // Calculate the position of the character in the alphabet
    int pos = c - 'A';
    // Apply the Beaufort cipher decryption formula
    return alphabet[(shift - pos + 26) % 26];
}

/**
 * Function to decrypt a message without a known key, using a debut message to infer the key.
 * 
 * @param crypted_message The encrypted message to be decrypted.
 * @param debut_message The initial message used to infer the key.
 * @param key_length The length of the key to use for decryption.
 * @return Returns the decrypted message.
 */
char *decrypt_word_without_key(char *crypted_message, char *debut_message, int key_length) {
    int i = -1, keyIndex = 0;
    // Generate the key based on the debut and crypted message
    char *key = get_key(debut_message, crypted_message, key_length);

    // Decrypt the message character by character
    while (crypted_message[++i]) {
        if (isAlpha(&crypted_message[i])) {
            crypted_message[i] = decrypt(crypted_message[i], key[keyIndex % key_length]);
            keyIndex++;
        }
    }

    // Return the decrypted message (in place modification)
    return crypted_message;
}

/**
 * Function to decrypt a message using a provided key.
 * 
 * @param crypted_message The encrypted message to be decrypted.
 * @param key The key used for decryption.
 * @return Returns the decrypted message.
 */
char *decrypt_word(char *crypted_message, char *key) {
    // Allocate memory for the decrypted message
    char *decrypted_message = malloc(sizeof(char) * ft_strlen(crypted_message));
    if (decrypted_message == NULL) {
        printf("Error: Memory allocation failed for decrypted message\n");
        return NULL;
    }

    int i = -1, keyIndex = 0;
    // Decrypt the message character by character
    while (crypted_message[++i]) {
        if (isAlpha(&crypted_message[i])) {
            decrypted_message[i] = decrypt(crypted_message[i], key[keyIndex % 5]);
            keyIndex++;
        } else {
            decrypted_message[i] = crypted_message[i];
        }
    }

    return decrypted_message;
}

/**
 * Wrapper function to decrypt the ciphertext using a provided key.
 * 
 * @param ciphertext The encrypted text to be decrypted.
 * @param key The key used for decryption.
 * @return Returns the decrypted plaintext, or NULL if decryption fails.
 */
char* decrypt_ciphertext(char *ciphertext, char *key) {
    char *cleartext = decrypt_word(ciphertext, key);
    if (cleartext == NULL) {
        printf("Error: Decryption failed\n");
    }
    return cleartext;
}

/**
 * Wrapper function to generate the key for decryption.
 * 
 * @param crib The crib message used to infer the key.
 * @param ciphertext The encrypted message used to generate the key.
 * @param key_length The length of the key to be generated.
 * @return Returns a dynamically allocated key of length `key_length`, or NULL if memory allocation fails.
 */
char* generate_key(char *crib, char *ciphertext, int key_length) {
    // Allocate memory for the key, with size equal to key_length plus 1 for null terminator
    char *key = (char *)calloc(key_length + 1, sizeof(char));
    if (key == NULL) {
        printf("Error: Memory allocation failed for key\n");
        return NULL;
    }

    // Generate the key using the crib and ciphertext
    key = get_key(crib, ciphertext, key_length);
    if (key == NULL) {
        free(key);
    }
    return key;
}
