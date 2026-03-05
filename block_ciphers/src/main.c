#include <stdio.h>
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


// unsigned char* msg size_t length
#define print_hexadecimal(msg, length)(for (size_t i = 0; i<length; ++i) \
    printf("%02hhx ", msg[i]); \
    printf("\n"); )



int main(){
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
    stbi_write_png("tux_aes_ebc.png", width, height, channels, encrypted, width*channels);
    printf("Image loaded with size: %d\n", siz);
    #endif
    
    #ifdef AES
    stbi_image_free(image_data);
    free(encrypted);
    #endif

    return 0;
}