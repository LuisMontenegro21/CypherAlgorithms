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

#ifdef PADDING
#include "padding.h"
#endif



#ifdef AES
#include "aes.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"
#endif

void print_hexadecimal(unsigned char *msg, size_t length){
    for (size_t i = 0; i<length; ++i) {
        printf("%02hhx ", msg[i]); 
    }
    printf("\n");
}



int main(int argc, char **argv){
    #ifdef KEYS
    unsigned char aes_key[32];
    unsigned char des_key[8];
    unsigned char des3_key[24];
    int i1 = aes_keygen(aes_key, 32);
    int i2 = des_keygen(des_key);
    int i3 = des3_keygen(des3_key, 24);
    printf("AES KEY: ");
    print_hexadecimal(aes_key, 32);
    printf("DES KEY: ");
    print_hexadecimal(des_key, 8);
    printf("3DES KEY: ");
    print_hexadecimal(des3_key, 24);
    #endif


    #ifdef PADDING
    char pad1[5] = "Hola";
    char pad2[8] = "Palabra";
    char pad3[10] = "Problemas";
    size_t new1;
    size_t new2;
    size_t new3;
    unsigned char *p1 = pkcs7_padding(pad1, 5, 8, &new1);
    unsigned char *p2 = pkcs7_padding(pad2, 8, 8, &new2);
    unsigned char *p3 = pkcs7_padding(pad3, 10, 8, &new3);
    if (!p1 || !p2 || !p3){
        perror("Error allocating");
        return 1;
    }
    
    printf("Padding 5 bytes: %s length: %zu\n", p1, new1);
    print_hexadecimal(p1, new1);
    printf("Padding 8 bytes: %s length: %zu\n", p2, new2);
    print_hexadecimal(p2, new2);
    printf("Padding 10 bytes: %s length: %zu\n", p3, new3);
    print_hexadecimal(p3, new3);

    int i1 =pkcs7_unpadding(p1, &new1, 8);
    int i2 = pkcs7_unpadding(p2, &new2, 8);
    int i3 = pkcs7_unpadding(p3, &new3, 8);
    if (i1 != 0 || i2 != 0 || i3 != 0){
        perror("Error unpadding");
        return 1;
    }

    printf("Unpadding 5 bytes: %s length: %zu\n", p1, new1);
    print_hexadecimal(p1, new1);
    printf("Unpadding 8 bytes: %s length: %zu\n", p2, new2);
    print_hexadecimal(p2, new2);
    printf("Unpadding 10 bytes: %s length: %zu\n", p3, new3);
    print_hexadecimal(p3, new3);
    free_padding_pkc7s(p1);
    free_padding_pkc7s(p2);
    free_padding_pkc7s(p3);
    #endif

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
    size_t padded_len;
    unsigned char* padded_content = NULL;
    if (file_size % 8 != 0){
        padded_content = pkcs7_padding(content, file_size, 8, &padded_len);

    }
    
    int message_len = encrypt_des_ecb(padded_content, padded_len, key, cipher);
    print_hexadecimal(cipher, file_size);
    decrypt_des_ecb(cipher, padded_len, key, original);
    printf("Original: %s\n", original);
    if (padded_content)
        free_padding_pkc7s(padded_content);
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