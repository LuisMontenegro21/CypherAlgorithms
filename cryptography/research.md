# Historia del cifrado Vigénere

### Invención
El cifrado Vigenère obtiene su nombre por Blaise de Vigenère. Apareciendo en el libro Traicté des Chiffres de 1585.
Sin embargo, otros personajes como Alberti, Trithemius y Porta contribuyeron significativamente al desarrollo del cifrado, pero fue Vigenère quien lo desarrolló a completitud.

### Funcionamiento
El algoritmo funciona a partir de dar un texto y una clave cuya longitud debe ser menor a la del texto plano. Teniendo ya la clave y el texto, se extiende la clave repetidas veces hasta lograr la longitud del texto inicial.
Por ejemplo: <br>
```
texto: hola mundo
clave: netnetnetn
```
Donde la clave `net` se va repitiendo hasta lograr la misma longitud que la del texto.<br>

Luego para encriptar el texto necesitamos la matriz del alfabeto donde se va comparando cada índice, digamos, el índice 0 en este caso es h y n (respectivamente al texto y la clave) y para esto se busca el intercepto de h y n y esa será la letra del cifrado para el primer índice. Y así se hace repetidamente hasta abarcar todo el texto. 

### Aplicación
Pese a ser capaz un algoritmo bastante antiguo, ya que surgío por allá del siglo XVI, puede servir para encriptar mensajes simples a papel. Capaz
no da la capacidad para proteger un sitio web con autenticación o encriptar datos a la hora de enviar SMS, pero para encriptar pequeños mensajes puede ser útil.

### Por qué lo elegí
Porque me pareció bastante interesante. El método de crear no solamente 1 desplazamiento si no N desplazamientos (donde N es el número de letras del alfabeto que usaremos) me parece más robusto que un simple desplazamiento como el del César. Es un método bastante creativo y por eso me llamó la atención. 