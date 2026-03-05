# Block Ciphers

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
./main 3des.txt
```

Compilar DES: <br>
```
gcc -DDES -DTEXT main.c keys.c encdes.c -o main -lcrypto -lssl
```
Uso: <br>
```
./main des.txt
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
![Original](src/tux.png)
![AES_256_ECB](src/tux_aes_ecb.png)
![AES_256_CBC](src/tux_aes_cbc.png)

### 2.3
*Pregunta* ¿Por qué no debemos usar ECB en datos sensibles?<br>
Porque al estar cifrado bloque por bloque sin alteración, dos bloques exactamente iguales van a dar el mismo cifrado. Por lo que
si el cifrado es suficientemente largo se puede comenzar a ver patrones y esto puede ser utilizado con análisis de frecuencia para vulnerar el cifrado.<br>

Bloque cifrado con ECB<br>
```
```
BLoque cifrado con CBC<br>
```
```

### 2.4
*Pregunta* ¿Qué es el vector de inicialización y por qué es necesario en CBC pero no en ECB?<br>
El IV es un vector que se utiliza cuando vamos a cifrar el bloque consecutivo al bloque actual. Esto le da cierta aleatoriedad o cambio para que los bloques no queden idénticos unos con los otros. <br>

Mismo IV<br>
```

```
Diferente IV<br>
```
```

### 2.5
*Pregunta* ¿Qué es el padding y por qué es necesario? <br>
El padding es básicamente incluir valores predeterminados para llenar un bloque con la finalidad de que quede de la misma
longitud esperada. Es decir, llenar con un valor determinado las casillas faltantes para que el bloque alcance la longitud deseada.<br>

Mensaje de 5 bytes:<br>
```
```
Mensaje de 8 bytes: <br>
```
```
Mensaje de 10 bytes: <br>
```
```
Unpad 5 bytes:<br>
```
```
Unpad 8 bytes:<br>
```
```
Unpad 10 bytes:<br>
```
```

### 2.6
*Pregunta* ¿En qué situaciones se recomienda cada modo de operación? ¿Cómo elegir un modo seguro en cada lenguaje de programación?<br>

| ECB | CBC | CTR | GCM |
|:---|:---|:---|:---|
| No se recomienda su uso | Es seguro si se usa bien pero es bastante lento | Es seguro si se usa bien y es más rápido | Es muy seguro y rápido y es el estándar de uso en cualquier circunstancia |
| Inseguro | Seguro si se implementa bien pero lento | Seguro y rápido | Bastante seguro y rápido |