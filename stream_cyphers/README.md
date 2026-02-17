## Stream Cipher

## Descripción
Este proyecto consiste en la generación de streamkeys.

## Instrucciones de uso
Para compilación del programa princial utilizando gcc:<br>
`gcc keystream.c -o keystream` <br>
Para ejecutar: <br>
`.\keystream`<br>

Para ejecución de las pruebas:<br>
`gcc testing.c -o testing`<br>
Para ejecutar: <br>
`.\testing`


## Parte 1: Implementación de stream cipher

### 1.1 Generación del keystream
Para ver el [códigofuente](./keystream.c)

Función generadora del keystream:
```
 keystream(unsigned int seed, char* key, size_t length){
	// srand(time(NULL)); needs time.h to work
	srand(seed);
	for(size_t i = 0; i < length; ++i)
		key[i] = rand() % 256;
}
```

### 1.2 Función de cifrado
```
void encrypt_text(char* text, char* key,  size_t text_size){
	for(size_t i = 0; i < text_size; ++i)
		text[i] = (text[i] ^ key[i]); 
}
```

### 1.3 Función de descifrado 
```
void decrypt_text(char* text, char* key, size_t text_size){
	for(size_t i = 0; i < text_size; ++i)
		text[i] = (text[i] ^ key[i]);
}
```

## Parte 2: Análisis de seguridad

### 2.1 Variación de clave
* ¿Qué sucede cuando cambia la clave utilizada para generar el keystream? Demuestre con un ejemplo concreto.<br>
En dado caso uno cambie la clave utilizada para generar un keystream se genera un cifrado totalmente diferente al cifrado inicial. 

### 2.2 Reutilización del keystream
* ¿Qué riesgos de seguridad existen si reutiliza el mismo keystream para cifrar dos mensajes diferentes? Implemente un ejemplo que demuestre esta vulnerabilidad.<br>
Si se utiliza el mismo keystream para cifrar dos mensajes distintos tenemos la vulnerabilidad de que ambos mensajes pueden ser decifrados si se llega a saber la llave. 

* Sugerencia: Cifre dos mensajes con la misma clave y analice qué información puede extraer un
atacante que intercepte ambos textos cifrados.


### 2.3 Longitud del keystream
* ¿Cómo afecta la longitud del keystream a la seguridad del cifrado? Considere tanto keystreams más cortos como más largos que el mensaje.<br>
La longitud del mensaje del keystream en este caso debe ser equivalente al mensaje que debe cifrarse. Entre más largo es un keystream más seguro será el encriptado y menos probable adivinarlo. Sin embargo, entre más largo sea el mensaje mayor será la complejidad del keystream. Es decir más fácil decifrar un keystream corto pero más complejo igual es cifrar y decifrar un keystream largo. Por lo que la longitud es tanto su fuerte como su debilidad.

### 2.4 Consideraciones prácticas
* ¿Qué consideraciones debe tener al generar un keystream en un entorno de producción real? Mencione al menos 3 aspectos críticos.
- Un keystream debe ser único, no debe repetirse a la hora de cifrar distintos mensajes.
- La longitud del keystream debe ser equivalente a la del mensaje a cifrar.
- Entre mayor sea el mensaje a cifrar mayor será el keystream, por lo que se ve limitado en la praxis si el mensaje es elongado.

## Parte 3: Validación y pruebas 

### 3.1 Ejemplos de entrada 
Ejemplos de ejecución:<br>

Primer ejemplo: <br>
```
Input plain text (max 128 chars): hola mundo
Input key (max 128 chars): conveniente
Text: hola mundo
Keystream: fff0 fffa 37 ff9f 7e 50 7d 3d ff97 67
Encrypted: ff98 ff95 5b fffe 5e 3d 08 53 fff3 08
Decrypted: hola mundo
```

Segundo ejemplo: <br>
```
Input plain text (max 128 chars): este es un test de prueba
Input key (max 128 chars): 32
Text: este es un test de prueba
Keystream: ff91 ff98 ffc1 38 ffed ffb0 37 ffde 25 ffd0 ffbc ffde ffbe 7b ff9b ffe1 0e ffbd 7e 7e ffa1 03 ffed ffae ffdc
Encrypted: fff4 ffeb ffb5 5d ffcd ffd5 44 fffe 50 ffbe ff9c ffaa ffdb 08 ffef ffc1 6a ffd8 5e 0e ffd3 76 ff88 ffcc ffbd
Decrypted: este es un test de prueba
```

Tercer ejemplo: <br>
```
Input plain text (max 128 chars): probando con caraceres diferentes _?
Input key (max 128 chars): __
Text: probando con caraceres diferentes _?
Keystream: ffb3 58 58 fffb ffda ffd7 47 2e ff80 66 50 2e 75 ffea ffda ff93 7f 62 fff4 fffe 4d 0e ffed 5a ffac ffd7 1e 61 fffe ffeb 0b 62 ffe7 ffa8 ffab 42
Encrypted: ffc3 2a 37 ff99 ffbb ffb9 23 41 ffa0 05 3f 40 55 ff89 ffbb ffe1 1e 01 ff91 ff8c 28 7d ffcd 3e ffc5 ffb1 7b 13 ff9b ff85 7f 07 ff94 ff88 fff4 7d
Decrypted: probando con caraceres diferentes _?
```

### 3.2 Pruebas unitarias
Para correr las pruebas unitarias se debe compilar el archivo `testing.c`. <br>
* El descifrado recupera exactamente el mensaje original
`gcc -DSAME_OUTPUT testing.c -o testing`<br>
` .\testing`
* Diferentes claves producen diferentes textos cifrados
`gcc -DDIFFERENT_OUTPUT testing.c -o testing`<br>
` .\testing`
* La misma clave produce el mismo texto cifrado
`gcc -DSAME_KEY testing.c -o testing`<br>
` .\testing`
* El cifrado maneja correctamente mensajes de diferentes longitudes

## Parte 4: Reflexión técnica

### 4.1 Limitaciones de PRNG simples
1. Una limitación bastante obvia es que utilizando la misma semilla va a resultar en la generación del mismo valor. 
2. Se puede repetir el mismo valor. 

### 4.2 Comparación con stream ciphers modernos
1. Mejoras del ChaCha frente a la generación de mi keystream.
El ChaCha20, por ejemplo, toma varios pasos extras que un stream cipher como el mío no toma. El ChaCha20, tiene por nombre 20, ya que realiza 20 rondas de operaciones de suma y de xor para generar aleatoriedad y revolver bien los valores. Esto lo hace tomando el texto como una matriz y aplicando las operaciones en vertical y diagonal. Este proceso se repite en bloques de 64 bytes utilizando un contador y un nonce para cada bloque, de esta forma asegurando que cada bloque sea completamente diferente del otro. [1][2]
2. Evitar vulnerabilidades de PRNG básicos.
El ChaCha20 intenta mejorar la capacidad de aleatoriedad y determinismo que tiene un PRNG básico. Es decir, busca que sea casi imposible hacerle la inversa a las transformaciones que se hizo si no es mediante el uso de la misma stream cipher key. 
3. Manejo de inicialización y estado interno.
El ChaCha20, como se dijo antes, utiliza un estado de rotación para generar aleatoriedad en grupos de 512 bits, mezclando 4 de 32 bits (un cuarto de bloque).
Sin embargo, solamente revolver y hacer esta transformación a cada parte aún es reversible. Por lo que lo que se hace es adherir el bloque revuelto con el
bloque original. De esta forma se intenta garantizar que sea más difícil revertirlo considerando que el atacante dezconoce la mitad del bloque.
También se llena el bloque con una constante. Esta constante sirve para reducir la cantidad de control que tiene un atacante sobre un input. [2]

4. Fuentes

### Fuentes 
[1] _ParejAbertzale, Algoritmo de Cifrado ChaCha20, Medium (2023) [https://medium.com/@parejaemi/algoritmo-de-cifrado-chacha20-119a6d7c19a7]_ <br>
[2] _Thomas Ptacek, The Design of ChaCha20 (2017) [https://loup-vaillant.fr/tutorials/chacha20-design]_
