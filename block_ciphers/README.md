### Block Ciphers

### Requerimientos
Tener WSL instalado si se utiliza Windows 10/11 o alguna distribución que soporte OpenSSL y tenga GNU GCC en caso sea Unix. 

### Compilar

Compilar AES 256 CBC:<br>
```
gcc -std=c17 -Wall -pedantic -DAES -DCBC main.c keys.c aes.c -o main -lcrypto -lssl -lm
```

Compilar AES 256 ECB:<br>
```
gcc -std=c17 -Wall -pedantic -DAES -DECB main.c keys.c aes.c -o main -lcrypto -lssl -lm
```

Compilar 3DES: <br>

Compilar DES: <br>