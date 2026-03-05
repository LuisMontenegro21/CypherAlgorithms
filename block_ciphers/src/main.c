#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "keys.h"

#ifdef DES3
#include "enc3des.h"
#endif

#ifdef DES
#include "encdes.h"
#endif

#ifdef AES
#include "aes.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"
#endif

#ifdef TEXT
void print_hexadecimal(unsigned char *msg, size_t length){
    for (size_t i = 0; i<length; ++i) {
        printf("%02hhx ", msg[i]); 
    }
    printf("\n");
}
#endif


int main(int argc, char **argv){


    #ifdef TEXT
    if (argc < 2){
        printf("Usage: %s <filename.txt>", argv[0]);
        return 1;
    }

    FILE *fptr = fopen(argv[1], "r");
    if (fptr == NULL){
        perror("Error openning file");
        return 1;
    }
    // get size of the file
    fseek(fptr, 0, SEEK_END);
    size_t file_size = ftell(fptr);
    rewind(fptr);

    // i know its badly optimized but it works
    unsigned char *content = malloc(file_size); 
    unsigned char *cipher = malloc(file_size+16);
    unsigned char *original = malloc(file_size+16);
    if (!content || !cipher || !original){
        printf("Memory allocation failed\n");
        return 1;
    }
    fread(content, 1, file_size, fptr);
    fclose(fptr);



    #ifdef DES3
    char key[24];
    char iv[8];
    des3_keygen(key, 24);
    int message_len = encrypt_3des_cbc(content, file_size, key, iv, cipher);
    print_hexadecimal(cipher, file_size);
    decrypt_3des_cbc(cipher, message_len, key, iv, original);
    printf("Original: %s\n", original);
    #endif

    #ifdef DES
    char key[8];
    des_keygen(key);
    int message_len = encrypt_des_ecb(content, file_size, key, cipher);
    print_hexadecimal(cipher, file_size);
    decrypt_des_ecb(cipher, message_len, key, original);
    printf("Original: %s\n", original);
    #endif
    
  
    free(content);
    free(cipher);
    free(original);
    #endif
      
    #ifdef AES
    if (argc < 3){
        printf("Usage: %s <original.png> <encrypted.png>", argv[0]);
        return 1;
    }

  
    int width, height, channels;
    unsigned char* image_data = stbi_load(argv[1], &width, &height, &channels, 0);
    if (image_data == NULL){
        printf("Error loading image\n");
        return 1;
    }
    size_t img_size = width * height * channels;
    printf("Image loaded Dimensions: %d x %d , Channels: %d\n", width, height, channels);
    unsigned char* encrypted = malloc(img_size);
    if (encrypted == NULL){
        printf("Error allocating memory\n");
        return 1;
    }
    unsigned char key[32];
    aes_keygen(key, 32);
    size_t encrypt_size = (img_size / 16) * 16;

    #ifdef CBC
    unsigned char iv[16];
    int siz = encrypt_aes_cbc(image_data, encrypt_size, key, iv, encrypted);
    stbi_write_png(argv[2], width, height, channels, encrypted, width*channels);
    printf("Image loaded with size: %d\n", siz);

    #endif

    #ifdef ECB
    int siz = encrypt_aes_ecb(image_data, encrypt_size, key, encrypted); 
    stbi_write_png(argv[2], width, height, channels, encrypted, width*channels);
    printf("Image loaded with size: %d\n", siz);
    #endif
    
    stbi_image_free(image_data);
    free(encrypted);
    #endif

    return 0;
}