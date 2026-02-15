#ifndef KEYSTREAM_H
#define KEYSTREAM_H

#include <stdlib.h>
#define BUFFER_SIZE 128 // fixed for commodity

void encrypt_text(char* text, char* key, size_t text_size);

void decrypt_text(char* text, char* key, size_t text_size);

void keystream(unsigned int seed, char* key, size_t length);

void print_special_chars(char* text, size_t length);

unsigned int convert_seed(char* seed);

#endif