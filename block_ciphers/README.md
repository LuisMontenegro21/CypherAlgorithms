# Block Ciphers
Créditos a Sean Barrett (github nothings) por la libería std para manejar imágenes.

### Requerimientos
Tener WSL instalado si se utiliza Windows 10/11 o alguna distribución que soporte OpenSSL y tenga GNU GCC en caso sea Unix. 

### Compilar

Compilar AES 256 CBC:<br>
```
gcc -std=c17 -Wall -pedantic -DAES -DCBC main.c keys.c aes.c -o main -lcrypto -lssl -lm
```
Uso: <br>
```
./main <path/original.png> <path/encrypt.png>
```

Compilar AES 256 ECB:<br>
```
gcc -std=c17 -Wall -pedantic -DAES -DECB main.c keys.c aes.c -o main -lcrypto -lssl -lm
```
Uso: <br>
```
./main <path/original.png> <path/encrypt.png>
```

Compilar 3DES: <br>
```
gcc -DDES3 -DTEXT main.c keys.c enc3des.c -o main -lcrypto -lssl
```
Uso: <br>
```
./main ../tests/3des.txt
```

Compilar DES: <br>
```
gcc -DDES -DTEXT -DPADDING main.c keys.c encdes.c paddinc.c -o main -lcrypto -lssl
```
Uso: <br>
```
./main ../tests/des.txt
```

Compilar para padding:<br>
```
gcc -DPADDING main.c padding.c -o main
./main
```

Compilar para ver llaves: <br>
```
gcc -DKEYS main.c keys.c -o main
./main
```
## Respuestas

### 2.1
*Pregunta* ¿Qué tamaño de clave está utilizando para DES, 3DES y AES? <br>
Para DES se utiliza un tamaño de llave de 8 bytes, 3DES usa 24 bytes y AES utiliza una llave de 32 bytes. <br>

DES hoy en día se considera inseguro ya que es posible revertir la encriptación de una manera más fácil ya que la longitud de
la llave es muy corta para los estándares. <br>

Un ataque de fuerza bruta para DES tomaría un total de 2^56 posibles combinaciones (el número de bits utilizados)
lo cual para los estándares actuales es basante vulnerable por la capacidad computacional que tienen los dispositivos.

*Output de las llaves*
```
AES KEY: bf 7d c9 b9 3d bc 4f 2c fc 8b ba b4 e5 13 91 c3 66 b0 af 59 a5 ae 08 cd 17 d9 56 1f d7 a5 55 c3 
DES KEY: 4f 13 9d 25 5b 40 34 1f
3DES KEY: f4 31 83 2c 2a 46 38 38 7f 40 89 45 92 b6 e0 07 d9 0e f2 76 ad da 7c 3d
```
### 2.2
*Pregunta* Compare ECB vs CBC mostrando:<br>
¿Qué modo de operación implementó en cada algoritmo? <br>
Para el AES utilicé 256 y modo ECB y CBC. <br>
¿Cuáles son las diferencias fundamentales entre ECB y CBC? <br>
El CBC utiliza el bloque anteriormente cifrado como input del siguiente, lo cual
lo hace más aleatorio. Mientras que el ECB utiliza solametne cifrado por bloque consecutivamente
pero no depende uno del otro, lo cual puede llevar a revelar patrones en mensajes largos.<br>
¿Se puede notar la diferencia directamente en una imagen? <br>
Sí se puede ver la diferencia ya que con el CBC se nota lo más similar a ruido mientras que con el ECB
se ve más como un relieve o patrones a lo largo de la imagen lo cual deja ver aún su diseño. <br>

*Imágenes*
![Original](images/bill.png)
![AES_256_ECB](images/bill_aes_ecb.png)
![AES_256_CBC](images/bill_aes_cbc.png)

### 2.3
*Pregunta* ¿Por qué no debemos usar ECB en datos sensibles?<br>
Porque al estar cifrado bloque por bloque sin alteración, dos bloques exactamente iguales van a dar el mismo cifrado. Por lo que
si el cifrado es suficientemente largo se puede comenzar a ver patrones y esto puede ser utilizado con análisis de frecuencia para vulnerar el cifrado.<br>

Bloque cifrado con ECB<br>
```
06 49 aa dd e0 68 61 bf e8 9f ea b1 93 3e f2 a5 76 85 4c 1d 68 2f 66 92 0d 85 59 7a fe 84 a4 3c 50 5f 1b 91 ad d0 2b a8 37 77 38 53 33 e3 06 56 cf df e7 22 55 84 32 55 44 92 a3 70 e1 55 5f aa 36 80 90 e9 7a a1 b1 0e 58 dd 3e 26 c5 ea d9 29 3b dd 0d b6 27 cd 0d ac 3c ee 97 c2 8a 05 36 eb f5 60 ef 77 81 56 c8 6f 0f 8f 2f 13 d8 6e 1e 7b e7 4c 69 84 70 7c 3a f5 6f 06 dd a0 1e 59 8c c6 15 83 fe f5 e4 c6 7f 39 32 bb 27 6a da 74 51 d4 e8 78 93 bf 26 e4 91 99 ab f4 e3 98 c9 14 51 39 
0c 44 00 df 80 30 f3 92 69 fe b3 7b e6 ef 81 a9 90 ea 6e bb e1 fc 98 19 e2 74 a6 3b 83 18 da 4e 6b f4 c4 7e c8 0f 8f e3 94 e8 6f bf 01 f6 68 47 3f ed 94 0c b3 46 ce cb a3 ca 21 26 c5 4b f6 a6 10 83 47 9c c4 61 82 e5 3a c7 a5 5f f6 c3 00 65 04 39 1d 3e cb df 9e 10 dd de 9f fa 91 83 f5 d8 56 c1 d1 e5 63 55 34 8d 47 e3 ff b5 9d 93 cd 50 77 4e ba a5 c9 f5 aa e9 3e d1 43 9c 2d 18 fc 69 aa a7 00 85 6b a3 56 1d 8e df ff da a3 c8 ee 8f 63 fd 74 71 4a 93 c1 1b f3 57 68 ff bd e2 54 87 
cd 5c f5 66 5a c0 85 04 77 77 d0 cb 44 6a aa 1e 0a 8a 42 c8 f9 c1 d3 5a 44 85 13 52 89 f5 9b 9f 93 fd 74 e7 43 f7 58 88 3b 0f e2 c9 63 4b b3 c3 e6 17 36 ca 52 48 58 39 ca 32 ca 39 19 23 cf 4a 34 cb ed 33 b4 ef 4c 66 db 48 d7 61 f5 f0 29 18 01 e4 6e 7c 34 9c 8b 36 a8 1d 60 af 9b aa b0 d4 90 bd 4a a0 78 e8 7d 87 a3 87
```
BLoque cifrado con CBC<br>
```
d4 80 e6 e7 08 c0 97 be e0 5f 05 98 e9 db 9d c3 3e fc 81 d6 a7 0f 84 db 4e db 70 af 93 9d 1a 30 f5 95 3a 4f 16 56 44 1e 0f 6f 63 4b 0d 45 5d cf 1d cb e9 94 7e 8f a0 b7 26 42 ab cf 28 7a e7 ae 1e 36 78 ab 61 9a a4 c3 8e 81 4b 82 14 a9 7e 7e fa 60 1f 3e 87 2e 2c 2f 0b b9 36 19 44 dc 8d c3 41 98 14 b4 60 de 6a eb 37 fa 09 47 aa 29 30 57 48 86 49 a4 90 84 12 0c 92 f0 e6 1c b6 bf d6 1d 9f 83 1d 8b 04 7d 97 f9 5f de e5 09 cd a4 fc 40 be 4f b2 c7 9f 8b 94 86 4d c7 81 df 45 e1 6a 0a 
2e a0 74 40 1f a2 5a bd a9 4b a0 cd b7 41 5f 03 35 f6 bd 02 e7 2f 91 8c eb f5 78 6b 9e 77 72 e2 cf 6a 17 8a 3f 7c 91 be dc 93 3b 38 f3 34 d1 b6 0f ee d4 01 76 1f 6c 3e d6 11 86 c4 f4 4c e0 31 3e 55 5a 04 bd 59 4c b6 9c a7 b6 1f a6 8e a6 e4 9d 1c 75 ad d1 9a d9 2d dc fa 11 e0 4c 7a 87 79 d3 60 e0 60 1b 8a 9f e8 85 8c 48 8f 4e a8 c8 e0 0a 2f 9b 91 06 f4 39 c5 95 84 85 38 0d 9f 03 a0 b1 ad 24 b5 98 08 74 b2 61 5f ab 43 b6 ed 9c 28 5b a7 9f 09 eb ff 3a 53 c5 cb 12 c1 06 3b a3 3d 
62 0f 6c b7 cf d7 d9 9c f1 5f 8f 97 5c 43 48 f8 d9 6f c7 76 a0 ae 39 c5 7b 4a 4c 60 5e 98 d4 4b ed 43 47 eb 48 8e a8 80 54 4a f0 83 67 1e f5 0f 63 76 b8 61 4b b8 83 4c f6 e1 0f 7d 0a 4c b2 ec 90 96 e4 24 df 77 cd de 0a 21 31 26 71 df ad 12 3b 0e 7c 5c 50 7b 9a d8 2c 32 f6 d3 65 f9 59 6f c2 5e 60 64 aa c4 5f 44 5a c3
```

### 2.4
*Pregunta* ¿Qué es el vector de inicialización y por qué es necesario en CBC pero no en ECB?<br>
El IV es un vector que se utiliza cuando vamos a cifrar el bloque consecutivo al bloque actual. Esto le da cierta aleatoriedad o cambio para que los bloques no queden idénticos unos con los otros. <br>


### 2.5
*Pregunta* ¿Qué es el padding y por qué es necesario? <br>
El padding es básicamente incluir valores predeterminados para llenar un bloque con la finalidad de que quede de la misma
longitud esperada. Es decir, llenar con un valor determinado las casillas faltantes para que el bloque alcance la longitud deseada.<br>

Mensaje de 5 bytes:<br>
```
Padding 5 bytes: Hola length: 8
48 6f 6c 61 00 03 03 03
```
Mensaje de 8 bytes: <br>
```
Padding 8 bytes: Palabra length: 16
50 61 6c 61 62 72 61 00 08 08 08 08 08 08 08 08
```
Mensaje de 10 bytes: <br>
```
Padding 10 bytes: Problemas length: 16
50 72 6f 62 6c 65 6d 61 73 00 06 06 06 06 06 06
```
Unpad 5 bytes:<br>
```
Unpadding 5 bytes: Hola length: 5
48 6f 6c 61 00
```
Unpad 8 bytes:<br>
```
Unpadding 8 bytes: Palabra length: 8
50 61 6c 61 62 72 61 00
```
Unpad 10 bytes:<br>
```
Unpadding 10 bytes: Problemas length: 10
50 72 6f 62 6c 65 6d 61 73 00
```

### 2.6
*Pregunta* ¿En qué situaciones se recomienda cada modo de operación? ¿Cómo elegir un modo seguro en cada lenguaje de programación?<br>

| ECB | CBC | CTR | GCM |
|:---|:---|:---|:---|
| No se recomienda su uso | Es seguro si se usa bien pero es bastante lento | Es seguro si se usa bien y es más rápido | Es muy seguro y rápido y es el estándar de uso en cualquier circunstancia |
| Inseguro | Seguro si se implementa bien pero lento | Seguro y rápido | Bastante seguro y rápido |