#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "keystream.h"


int main(){ 
	char text[BUFFER_SIZE]; 
	char seed[BUFFER_SIZE];
	char keystream_buff[BUFFER_SIZE];

	printf("Input plain text (max %d chars): ", BUFFER_SIZE);
	if (fgets(text, sizeof(text), stdin) == NULL){
		printf("ERROR READING TEXT");
		return 1;
	}
	// remove \n from text
	text[strcspn(text, "\n")] = '\0';
	
	printf("Input key (max %d chars): ", BUFFER_SIZE);
	if (fgets(seed, sizeof(seed), stdin) == NULL){
		printf("ERROR READING SEED");
		return 1;
	}
	// remove \n from seed
	seed[strcspn(text, "\n")] = '\0';

	size_t length = strlen(text);
	keystream(convert_seed(seed), keystream_buff, length);
	
	printf("Text: %s\n", text);
	printf("Keystream: ");
	print_special_chars(keystream_buff, length);
	encrypt_text(text, keystream_buff, length);
	printf("Encrypted: ");
	print_special_chars(text, length);

	decrypt_text(text, keystream_buff, length);
	printf("Decrypted: %s\n", text);

	return 0;
}


/*
Deterministic keystream generation
@param seed Seed input
@param length Text length
*/
void keystream(unsigned int seed, char* key, size_t length){
	srand(seed);
	for(size_t i = 0; i < length; ++i)
		key[i] = rand() % 256;
}

/*
Encrypts a text using a keystream
@param text Text to be encrypted
@param key Keystream to encrypt text
@param text_size The length of the text (not in bytes, but indices)
*/
void encrypt_text(char* text, char* key,  size_t text_size){
	for(size_t i = 0; i < text_size; ++i)
		text[i] = (text[i] ^ key[i]); 
}

/*
Decrypts a text using the same keystream as it was encrypted
@param text Text to be decrypted
@param key Keystream to decrypt the text with
@param text_size The length of the cipher (not in bytes, but indices)
*/
void decrypt_text(char* text, char* key, size_t text_size){
	for(size_t i = 0; i < text_size; ++i)
		text[i] = (text[i] ^ key[i]);
}

/*
Prints cipher or unprintable chars or weird chars as hexadecimal
@param text Text to print
@param size The length of the text
*/
void print_special_chars(char* text, size_t size){
	for(size_t i = 0; i<size; ++i) printf("%02hhx ", text[i]); // print as hexadecimal
	printf("\n");
}

/*
Converts a string seed into a unsigned int
@param seed The seed to be turn into unsigned int
*/
unsigned int convert_seed(char* seed){
	unsigned int result = 0;
	size_t length = strlen(seed);
	for(size_t i = 0; i <= length; ++i)
		result += (unsigned int)seed[i];
	return result;
}