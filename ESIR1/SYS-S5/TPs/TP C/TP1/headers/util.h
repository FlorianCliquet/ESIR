#ifndef UTIL_H
#define UTIL_H

// Standard library headers
#include <stdio.h>   // For standard input and output functions
#include <stdint.h>  // For fixed-width integer types
#include <stdlib.h>  // For memory allocation and other utility functions

// Define constants
#define alphabet "ABCDEFGHIJKLMNOPQRSTUVWXYZ"  // Constant string representing the alphabet
#define MAX_INPUT_SIZE 1024  // Maximum size for input buffers (e.g., ciphertext and crib)

char isAlpha(char *c);
int ft_strlen(char *str);
char *cryptWord(char *word, char *key);
char* decrypt_ciphertext(char *ciphertext, char *key);
char* generate_key(char *crib, char *ciphertext, int key_length);
char *decrypt_word_without_key(char *crypted_message, char *debut_message, int key_length);
char *decrypt_word(char *crypted_message, char *key);
char *get_key(char *debut_message, char *crypted_message, char length_key);
int get_key_length();
void get_input(char *prompt, char *buffer, int size);
#endif