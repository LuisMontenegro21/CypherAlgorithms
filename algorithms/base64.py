from binary import ascii_to_bin, bin_to_ascii


def char_to_base64(input: str) -> str:
    arr: list = []
    for i in input:
        arr.append(ascii_to_bin(ord(i)))
    text: str = ''.join(arr)
    print(text)
    arr = []
    for i in range(1, len(text)):
        if i == 1:
            arr.append(text[i-1])
        if i % 6 == 0:
            arr.append(text[i])
            arr.append(" ")
        else:
            arr.append(text[i])
    chunk: list = []
    final: list = []
    
    for i in range(len(arr)):
        for j in range(len(arr)):
            if arr[j] != " ":
                chunk.append(arr[i])
            else: 
                final.append(chunk)
                chunk = []
    print(''.join(arr))
    return arr   

def base64_to_char(input: str) -> str:
    raise NotImplementedError()

if __name__ == '__main__':
    try: 
        mode: str = input("Ingrese modo: ")
        text_input: str = input("Ingrese texto: ")
        if mode == "encrypt":
            print(char_to_base64(input=text_input))
        elif mode == "decrypt":
            print(base64_to_char(input=text_input))
    except KeyboardInterrupt:
        print("Programa finalizado por usuario")
    else:
        print("Programa finalizado")