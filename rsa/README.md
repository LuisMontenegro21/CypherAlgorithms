# Descripción
Implementación de RSA y algoritmos asimétricos.


## Cómo usar
Crear un ambiente virtual usando Python 3.12, activarlo y descargar los requerimientos con `pip install -r requirements.txt`

## Problemas
1. ¿Explique por qué no cifrar el documento directamente con RSA? <br>
Porque es demasiado complejo y tardado encriptar con el RSA el documento entero. RSA sirve más para cuestiones de autenticación, no de encriptación de datos per se.
2. ¿Qué información contiene un archivo .pem? Abre public_key.pem con un editor de texto y
describe su estructura. <br>
Un .pem contiene lo que sería una private key y por consiguiente una public key.

3. ¿Porqué cifrar el mismo mensaje dos veces produce resultados distintos? Demuéstrenlo y
expliquen que propiedad de OAEP lo cause <br>
Eso sucede debido a que el cifrado utiliza en padding PKCS1 el cual utiliza un elemento aleatorio a la hora de realizarlo. Por eso es que cuando ciframos dos veces consecutivas el mmismo mensaje obtenemos distinto resultado.
