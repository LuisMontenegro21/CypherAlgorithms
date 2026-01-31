from caesar import caesar_decrypt, caesar_encrypt

def rot13_encrypt(text: str, offset: int = 13) -> str:
    return caesar_encrypt(text=text, offset=offset)

def rot13_decrypt(text: str, offset: int = 13) -> str:
    return caesar_decrypt(text=text, offset=offset)


if __name__ == '__main__':
    try: 
        mode: str = input("Ingrese modo: ")
        text_input: str = input("Ingrese texto: ")
        if mode == "encrypt":
            print(rot13_encrypt(text=text_input))
        elif mode == "decrypt":
            print(rot13_decrypt(text=text_input))
    except KeyboardInterrupt:
        print("Programa finalizado por usuario")
    else:
        print("Programa finalizado")