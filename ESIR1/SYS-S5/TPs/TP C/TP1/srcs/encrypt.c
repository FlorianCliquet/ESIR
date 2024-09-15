#include "../headers/util.h"

/**
 * Function to encrypt a single character using the Beaufort cipher.
 * 
 * @param c Character to be encrypted (assumed to be an uppercase letter 'A' to 'Z').
 * @param key Key character used for encryption (assumed to be an uppercase letter 'A' to 'Z').
 * @return Returns the encrypted character after applying the Beaufort cipher.
 */
char crypt(char c, char key) {
    /**
     * Calculate the shift value based on the key character.
     * - The key character is converted to its corresponding index in the alphabet by subtracting 'A'.
     * - 'key - 'A'' gives the zero-based position of the key character in the alphabet (0 for 'A', 1 for 'B', etc.).
     */
    int shift = key - 'A'; // Key index in the alphabet

    /**
     * Calculate the position of the plaintext character in the alphabet.
     * - The character 'c' is converted to its zero-based position in the alphabet by subtracting 'A'.
     * - 'c - 'A'' gives the index of the character in the alphabet (0 for 'A', 1 for 'B', etc.).
     */
    int pos = c - 'A'; // Plaintext character index in the alphabet

    /**
     * Apply the Beaufort cipher encryption.
     * - The Beaufort cipher is a variant of the Vigenère cipher. It encrypts a character using the formula:
     *   crypted = shift - pos
     * - Since we are working with indices in the alphabet (0 to 25), we need to handle the result of the subtraction.
     * - To ensure a positive result and wrap around the alphabet, we add 26 (the number of letters in the alphabet) and then take modulo 26.
     * - This ensures that the result always falls within the range of 0 to 25, corresponding to the alphabet indices.
     */
    return alphabet[(shift - pos + 26) % 26];
}


// We just iterate throw the entire word
char *cryptWord(char *word, char *key) {
    int i = -1, keyIndex = 0;
    while (word[++i]) {
        if (isAlpha(&word[i])) {
            word[i] = crypt(word[i], key[keyIndex % 5]);
            keyIndex++;
        }
    }
    return word;
}