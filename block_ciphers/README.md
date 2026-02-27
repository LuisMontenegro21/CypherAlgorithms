### Block Ciphers

### Requerimientos
Tener WSL instalado o alguna distribución que soporte OpenSSL y tenga GNU GCC. 

### Compilar
```
gcc main.c keys.c padding.c enc_3des.c -o -lcrypto -lssl main
```