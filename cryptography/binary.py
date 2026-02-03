
def ascii_to_bin(ascii_char: int): 
    arr: list = []
    x: int = ascii_char
    while (x != 0):
        y: int = x % 2
        arr.append(str(y))
        x //= 2
    while len(arr) < 8:
        arr.append("0") # final bits
    arr = arr[::-1]
    return ''.join(arr)

def bin_to_ascii(bin_str: str) -> int:
    ascii_num: int = 0
    for i, b in enumerate(reversed(bin_str)):
        ascii_num += (2**i) * int(b) 
    return ascii_num




if __name__ == '__main__':
    try: 
        mode: str = input("Ingrese modo: ")
        text_input: str = input("Ingrese texto: ")
        print(ascii_to_bin(int(text_input)))
    except KeyboardInterrupt:
        print("Programa finalizado por usuario")
    else:
        print("Programa finalizado")
    
