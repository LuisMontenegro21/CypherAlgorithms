#include <stdio.h>
#include <string.h>
#include <stdint.h>
// #include "enc3des.h"
// #include "encdes.h"
#include "keys.h"
#include "aes.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"


void print_hexadecimal(unsigned char* msg, size_t length){
    for (size_t i = 0; i<length; ++i) printf("%02hhx ", msg[i]);
    printf("\n");
}


int main(){

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
    unsigned char iv[16];
    aes_keygen(key, 32);
    size_t encrypt_size = (img_size / 16) * 16;
    // int siz = encrypt_aes_cbc(image_data, encrypt_size, key, iv, encrypted);
    int siz = encrypt_aes_ecb(image_data, encrypt_size, key, encrypted); 
    printf("Image loaded with size: %d\n", siz);
    stbi_write_png("tux_aes_cbc.png", width, height, channels, encrypted, width*channels);



    stbi_image_free(image_data);
    free(encrypted);
    return 0;
}