
characters: str = " abcdefghijklmnopqrstuvwxyz"
length: int = len(characters)
matrix: list[list[str]] = [[characters[(i+j)%length] for j in range(length)] for i in range(length)]
char_to_index: dict[str, int] = {v: i for i, v in enumerate(characters)}

def vigenere_encrypt(text: str, key: str) -> str:
    cypher: list = []
    len_text: int = len(text)
    len_key: int = len(key)
    if len_text < len_key:
        raise ValueError("Key length is longer than cypher text")
    # match lengths 
    new_key: str = ""
    for i in range(len_text):
        new_key += key[i % len_key]
    
    for t, k in zip(text, new_key):
        curr_text_pos: int = char_to_index.get(t, 0)
        curr_key_pos: int = char_to_index.get(k, 0)
        cypher.append(matrix[curr_text_pos][curr_key_pos])

    return "".join(cypher)

def vigenere_decrypt(text: str, key: str) -> str:
    return ""


if __name__ == '__main__':
    try: 
        mode: str = input("Ingrese modo: ")
        text_input: str = input("Ingrese texto: ")
        if mode == "encrypt": 
            print(vigenere_encrypt(text=text_input, key="cryptii"))
        elif mode == "decrypt":
            print(vigenere_decrypt(text=text_input, key="cryptii"))

    except KeyboardInterrupt:
        print("Programa finalizado por usuario")
    else:
        print("Programa finalizado")