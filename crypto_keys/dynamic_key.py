
def dynamic_key_gen(text: str, base_key: str) -> None:
    cipher: list = []
    for p, k in zip(plaintext, base_key):
        shifted: int = (ord(p) + ord(k)) % 256
        cipher.append(chr(shifted))
    return ''.join(chiper)

def new_cypher_static(key: str) -> None:
    pass

def new_cypher_dynamic(key: str) -> None:
    pass


if __name__ == '__main__':
    try: 
        text_input: str = input("Ingrese texto: ")
        key: str = input("Ingrese llave: ")
        print(dynamic_key_gen())

    except KeyboardInterrupt:
        print("Programa finalizado por usuario")
    else:
        print("Programa finalizado")