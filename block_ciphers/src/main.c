#include <stdio.h>
#include <string.h>
#include "keys.h"

//#ifdef DES3
#include "enc3des.h"
//#endif

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


// unsigned char* msg size_t length
void print_hexadecimal(unsigned char *msg, size_t length){
    for (size_t i = 0; i<length; ++i) {
        printf("%02hhx ", msg[i]); 
    }
    printf("\n");
}


int main(int argc, char **argv){
    if (argc < 2){
        printf("Usage: %s <filename.txt>", argv[0]);
        return 1;
    }

    FILE *fptr = fopen(argv[1], "r");
    if (fptr == NULL){
        perror("Error openning file");
        return 1;
    }
    char content[100];
    char cipher[100];
    char original[100];
    //#ifdef DES3
    char key[24];
    char iv[8];
    des3_keygen(key, 24);
    if (fgets(content, sizeof(content), fptr)) encrypt_3des_cbc(content, 100, key, iv, cipher);
    decrypt_3des_cbc(cipher, 100, key, iv, original);
    printf("Original: %s\n", original);
    //#endif

    #ifdef DES
    char key[8];
    des_keygen(key);
    if (fgets(content, sizeof(content), fptr)) encrypt_des_ecb(content, 100, key, cipher);
    print_hexadecimal(cipher, 100);
    decrypt_des_ecb(cipher, 100, key, original);
    printf("Original: %s\n", original);
    #endif
    
    

    

    #ifdef AES
    int width, height, channels;
    unsigned char* image_data = stbi_load("tux.png", &width, &height, &channels, 0);
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
    #endif

    #ifdef CBC
    unsigned char iv[16];
    int siz = encrypt_aes_cbc(image_data, encrypt_size, key, iv, encrypted);
    stbi_write_png("tux_aes_cbc.png", width, height, channels, encrypted, width*channels);
    printf("Image loaded with size: %d\n", siz);

    #endif

    #ifdef ECB
    int siz = encrypt_aes_ecb(image_data, encrypt_size, key, encrypted); 
    stbi_write_png("tux_aes_ecb.png", width, height, channels, encrypted, width*channels);
    printf("Image loaded with size: %d\n", siz);
    #endif
    
    #ifdef AES
    stbi_image_free(image_data);
    free(encrypted);
    #endif

    return 0;
}