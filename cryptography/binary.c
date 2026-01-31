#include <stdio.h>
#include <stdlib.h>


void printarr(char* arr, size_t size){
    for (int i = 0; i < size; ++i) {
        if (arr[i] != '\0') {
            printf("%d", arr[i]);
        }
    }
}


char* char_to_bin(char *input, size_t size){
    char* bin_message = (char*)malloc((size * 8) + 1); // size * 8 bits + null terminator
    
    for (int i = 0; i != size; ++i) {
        if (input[i] != '\0'){
            bin_message[i] = input[i];
        }
    }


    return bin_message;
} 


int main(){

    return 0;
}