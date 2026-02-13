#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

char* encrypt_text(char* text, char* key, size_t text_size);

char* decrypt_text(char* text, char* key, size_t text_size);

char* keystream(unsigned int seed, size_t length);

unsigned int convert_seed(char* seed); // pending


int main(){ 
	char arr[32]; // initial buffer, needs resizing to fit input 

	printf("Input plain text (max 31 chars): ");
	if (fgets(arr, sizeof(arr), stdin) != NULL){
		printf("Success");
	} else {
		printf("Error reading input");
		return 1;
	}

	size_t length = sizeof(arr) / sizeof(arr[0]);
	char* key = keystream(32, length); // hard typed for now
	printf("Text: %s\n", arr);
	printf("Keystream: %s\n", key);
	char* encrypted = encrypt_text(arr, key, length);
	char* decrypted = decrypt_text(encrypted, key, length);
	printf("Encrypted: %s\n", encrypted);
	printf("Decrypted: %s\n", decrypted);


	free(key);
	free(encrypted);
	free(decrypted);
	return 0;
}

char* keystream(unsigned int seed, size_t length){
	// srand(time(NULL));
	srand(seed);
	char* stream = (char*)malloc(length + 1); // null terminator
	for(size_t i = 0; i <= length; ++i){
		stream[i] = (rand() % 256);
	}
	stream[length + 1] = '\0';
	return stream;
}


char* encrypt_text(char* text, char* key,  size_t text_size){
	char* encrypted_text = (char*)malloc(text_size+1);
	for(size_t i = 0; i <= text_size; ++i) {
		encrypted_text[i] = (text[i] ^ key[i]); 
	}
	return encrypted_text;
}

char* decrypt_text(char* text, char* key, size_t text_size){
	char* decrypt_text = (char*)malloc(text_size+1);
	for(size_t i = 0; i <= text_size; ++i){
		decrypt_text[i] = (text[i] ^ key[i]);
	}
	return decrypt_text;
}

