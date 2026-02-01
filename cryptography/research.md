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