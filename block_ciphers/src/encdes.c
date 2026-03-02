#include "encdes.h"
#include "padding.h"
#include "openssl/des.h"
#include <string.h>

int encrypt_des_ecb(uint8_t* plaintext, uint8_t* key, uint8_t* ciphertext, int* size){

    
    DES_key_schedule schedule;
    DES_set_key_checked((const_DES_cblock*)key, &schedule);

    int pad_needed = 8 - (*size % 8);
    if (pad_needed == 0) pad_needed + 8;

    for (int i = 0; i<pad_needed; ++i){
        plaintext[*size+i] = pad_needed;
    }
    *size += pad_needed;
    
    for (int i = 0; i < *size; i+=8){
        DES_ecb_encrypt((const_DES_cblock*)(plaintext + i), (DES_cblock*)(ciphertext + i), &schedule, DES_ENCRYPT);
    }
    
    return pad_needed;
}

int decrypt_des_ecb(uint8_t* ciphertext, uint8_t* key, uint8_t* plaintext, int* size){

    DES_key_schedule schedule;
    DES_set_key_checked((const_DES_cblock*)key, &schedule);
    int padding = plaintext[*size-1];
    *size -= padding;

    for (int i = 0; i < *size; i+=8){
        DES_ecb_encrypt((const_DES_cblock*)(ciphertext + i), (DES_cblock*)(plaintext + i), &schedule, DES_DECRYPT);
    }
    
    return *size;
}
