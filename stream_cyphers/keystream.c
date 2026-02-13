#include <stdio.h>
#include <stdlib.h>

#define BUFFER_SIZE 32

char* encrypt_text(char* text, char* key, size_t text_size);

char* decrypt_text(char* text, char* key, size_t text_size);

char* keystream(unsigned int seed, size_t length);

unsigned int convert_seed(char* seed);


int main(){ 
	char arr[BUFFER_SIZE]; 
	char seed[BUFFER_SIZE];
	printf("Input plain text (max 31 chars): ");
	if (fgets(arr, sizeof(arr), stdin) == NULL){
		printf("ERROR READING TEXT");
		return 1;
	}
	printf("Input key (max 31 chars): ");
	if (fgets(seed, sizeof(seed), stdin) == NULL){
		printf("ERROR READING SEED");
		return 1;
	}

	size_t length = sizeof(arr) / sizeof(arr[0]);
	char* key = keystream(convert_seed(seed), length); // hard typed for now
	char* encrypted = encrypt_text(arr, key, length);
	char* decrypted = decrypt_text(encrypted, key, length);
	printf("Text: %s\n", arr);
	printf("Keystream: %s\n", key);
	printf("Encrypted: %s\n", encrypted);
	printf("Decrypted: %s\n", decrypted);

	free(key);
	free(encrypted);
	free(decrypted);
	return 0;
}


/*
Deterministic keystream generation
@param seed Seed input
@param length Text length
*/
char* keystream(unsigned int seed, size_t length){
	// srand(time(NULL)); needs time.h to work
	srand(seed);
	char* stream = (char*)malloc(length + 1); // null terminator
	for(size_t i = 0; i <= length; ++i){
		stream[i] = rand() % 256; 
	}
	stream[length + 1] = '\0';
	return stream;
}

/*
Encrypts a text using a keystream
@param text Text to be encrypted
@param key Keystream to encrypt text
@param text_size The length of the text (not in bytes, but indices)
*/
char* encrypt_text(char* text, char* key,  size_t text_size){
	char* encrypted_text = (char*)malloc(text_size+1);
	for(size_t i = 0; i <= text_size; ++i) {
		encrypted_text[i] = (text[i] ^ key[i]); 
	}
	return encrypted_text;
}

/*
Decrypts a text using the same keystream as it was encrypted
@param text Text to be decrypted
@param key Keystream to decrypt the text with
@param text_size The length of the cipher (not in bytes, but indices)
*/
char* decrypt_text(char* text, char* key, size_t text_size){
	char* decrypt_text = (char*)malloc(text_size+1);
	for(size_t i = 0; i <= text_size; ++i){
		decrypt_text[i] = (text[i] ^ key[i]);
	}
	return decrypt_text;
}

/*
Converts a string seed into a unsigned int
@param seed The seed to be turn into unsigned int
*/
unsigned int convert_seed(char* seed){
	unsigned int result = 0;
	size_t length = sizeof(seed)/sizeof(seed[0]);
	for(size_t i = 0; i <= length; ++i){
		result += seed[i];
	}
	return result;
}