
def ascii_to_bin(ascii_char: int): 
    arr: list = []
    x: int = ascii_char
    while (x != 0):
        y: int = x % 2
        arr.append(str(y))
        x //= 2
    if len(arr) < 8:
        arr.append("0") # final bit
    arr = reversed(arr)
    return ''.join(arr)

def bin_to_ascii(bin_str: str):
    pass


# TODO assumes each byte is always LEN % 8 = 0
def bytes_to_char(binary: str) -> str:
    arr: list = []
    chunk: str = ""
    for b in binary:
        if b != " ":
            chunk += b
        elif b == " ":
            arr.append(chunk)
            arr.append(" ")
            chunk = ""
        else:
            arr.append(chunk)

    return ''.join(arr)




def char_to_bytes(text: str) -> str:
    arr: list = []
    for t in text: 
        if t.isalnum():
            arr.append(f"{ascii_to_bin(ord(t))}")
        else: 
            arr.append(f"{ascii_to_bin(ord(" "))}")
            
    return ' '.join(arr)



if __name__ == '__main__':
    try: 
        mode: str = input("Ingrese modo: ")
        text_input: str = input("Ingrese texto: ")
        if mode == "encrypt":
            print(char_to_bytes(text=text_input))
        elif mode == "decrypt":
            print(bytes_to_char(binary=text_input))
    except KeyboardInterrupt:
        print("Programa finalizado por usuario")
    else:
        print("Programa finalizado")
    
