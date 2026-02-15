#include <assert.h>
#include <stdio.h>
#include <string.h>
#include "keystream.h"

void returns_original_message(char* plain_text, char* decrypted);

void different_keys_different_output(char* encrypted1, char* encrypted2);

void same_key_same_output(char* encrypted1, char* encrypted2);

int main(void){
	char message1[] = "Hello world";
	char message2[] = "Hola mundo";
	char message3[] = "Hello world";

	char original1[12];
	char original2[11];
	char original3[12];
	
	char keystream1[12];
	char keystream2[11];
	char keystream3[12];

	#ifdef SAME_OUTPUT
	printf("Case: text and decipher are the same\n");
	keystream(32, keystream1, 12);
	memcpy(original1, message1, 12); // copy into original the original message to compare
	printf("Original: %s\n", original1);
	print_special_chars(original1, 12);
	encrypt_text(message1, keystream1, 12);
	printf("Encrypted: %s\n", message1);
	print_special_chars(message1, 12);
	decrypt_text(message1, keystream1, 12);
	printf("Decripted: %s\n", message1);
	print_special_chars(message1, 12);
	returns_original_message(original1, message1);
	#endif
	#ifdef DIFFERENT_OUTPUT
	printf("Case: different keystream yields different output\n");
	keystream(31, keystream1, 12);
	keystream(32, keystream3, 12);
	encrypt_text(message1, keystream1, 12);
	print_special_chars(message1, 12);
	encrypt_text(message3, keystream3, 12);
	print_special_chars(message3, 12);
	different_keys_different_output(message1, message3);
	#endif
	#ifdef SAME_KEY
	printf("Case: same keystream yields same output\n");
	keystream(32, keystream1, 12);
	keystream(32, keystream3, 12);
	encrypt_text(message1, keystream1, 12);
	print_special_chars(message1, 12);
	encrypt_text(message3, keystream3, 12);
	print_special_chars(message3, 12);
	same_key_same_output(message1, message3);
	#endif

	return 0;
}



void returns_original_message(char* plain_text, char* decrypted){
	assert(strcmp(plain_text, decrypted) == 0);
	printf("Test passed successfully: %s == %s\n", plain_text, decrypted);
}

void different_keys_different_output(char* encrypted1, char* encrypted2){
	assert(strcmp(encrypted1, encrypted2) != 0);
	printf("Test passed successfully, encrypted1 != encrypted2\n");
}

void same_key_same_output(char* encrypted1, char* encrypted2){
	assert(memcmp(encrypted1, encrypted2, 12) == 0);
	printf("Test passed successfully, encrypted1 == encrypted2\n");
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
