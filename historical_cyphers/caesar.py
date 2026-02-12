characters: str = "abcdefghijklmnopqrstuvwxyz"
pos_to_char: dict[int, str] = {i : k for i, k in enumerate(characters)}
char_to_pos: dict[str, int] = {k : i for i, k in enumerate(characters)}

def caesar_encrypt(text: str, offset: int = 3) -> str:
    cypher: list = []
    length: int = len(characters)
    for c in text:
        i: int = char_to_pos.get(c, 0)
        new_position: int = (i + offset) % length
        cypher.append(pos_to_char.get(new_position, "?"))
    return "".join(cypher)

def caesar_decrypt(text: str, offset: int = 3) -> str:
    plain_text: list = []
    length: int = len(characters)
    for c in text:
        i: int = char_to_pos.get(c, 0)
        old_position: int = (i - offset) % length
        plain_text.append(pos_to_char.get(old_position, "?"))
    return "".join(plain_text)



if __name__ == '__main__':
    try: 
        mode: str = input("Ingrese modo: ")
        text_input: str = input("Ingrese texto: ")
        if mode == "encrypt": 
            print(caesar_encrypt(text=text_input))
        elif mode == "decrypt":
            print(caesar_decrypt(text=text_input))

    except KeyboardInterrupt:
        print("Programa finalizado por usuario")
    else:
        print("Programa finalizado")
