## Stream Cipher

## Descripción
Este proyecto consiste en la generación de streamkeys.

## Instrucciones de uso
Para compilación utilizando gcc:<br>
`gcc keystream.c -o keystream` <br>
Para ejecutar: <br>
`.\keystream`

## Parte 1: Implementación de stream cipher

### 1.1 Generación del keystream
Para ver el [códigofuente](./stream_cyphers/keystream.c)

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

Segundo ejemplo: <br>

Tercer ejemplo: <br>

### 3.2 Pruebas unitarias

## Parte 4: Reflexión técnica

### 4.1 Limitaciones de PRNG simples
1. Una limitación bastante obvia es que utilizando la misma semilla va a resultar en la generación del mismo valor. 
2. Se puede repetir el mismo valor. 

### 4.2 Comparación con stream ciphers modernos
1. Mejoras del ChaCha frente a la generación de mi keystream.
2. Evitar vulnerabilidades de PRNG básicos.
3. Manejo de inicialización y estado interno.
4. Fuentes

### Fuentes 
