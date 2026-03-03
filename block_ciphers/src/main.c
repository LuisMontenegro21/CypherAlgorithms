#include <stdio.h>
#include <string.h>
#include <stdint.h>
// #include "enc3des.h"
// #include "encdes.h"
// #include "keys.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"


void print_hexadecimal(uint8_t* msg, size_t length){
    for (size_t i = 0; i<length; ++i) printf("%02hhx ", msg[i]);
    printf("\n");
}

void cipher_img(unsigned char* img, size_t img_len, unsigned char* encrypted_img, size_t encrypted_img_len){
    
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
    stbi_image_free(image_data);
    return 0;
}