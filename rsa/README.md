# Descripción
Implementación de RSA y otros algoritmos asimétricos.



## Problemas
1. El sistema usa RSA como mecanismo de intercambio de clave, protegiendo una clave AES que
cifra el documento real.
¿Explique por qué no cifrar el documento directamente con RSA? <br>
Porque es demasiado complejo y tardado encriptar con RSA el documento entero. RSA sirve más
para cuestiones de autenticación, no de encriptación de datos per se.

2. Generación de Claves
¿Qué información contiene un archivo .pem? Abre public_key.pem con un editor de texto y
describe su estructura. <br>
Un .pem contiene lo que sería una private key y una public key consiguiente.

3. Cifrado y descifrado con RSA-OAEP
¿Porqué cifrar el mismo mensaje dos veces produce resultados distintos? Demuéstrenlo y
expliquen que propiedad de OAEP lo cause <br>
Esto sucede debido a que el cifrado utilzia el padding PKCS1 utiliza un elemento aleatorio a la hora de realizarlo. Es por esto que cuando ciframos dos veces el mismo elemento obtenemos un resultado distinto.

4. Cifrado híbrido RSA-OEAP + AES-GCM
a. Generar clave AES aleatoria de 256 bits
b. Cifrar el documento con AES-GCM
n   i. El resultado les dará nonce + tag + ciphertext
c. Cifrar la clave AES con la clave pública RSA usando PKCS1_OAEP
