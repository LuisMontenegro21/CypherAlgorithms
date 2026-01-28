from binary import ascii_to_bin, bin_to_ascii

###### made with ChatGPT 4o ######
base64_chars: str = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/"
base64_dict: dict[int, str] = {i: ch for i, ch in enumerate(base64_chars)}
###### ------------------- #######


def binary_to_base64(input: str) -> list:
    arr: list = []
    for i in input:
        arr.append(ascii_to_bin(ord(i)))
    text: str = ''.join(arr)
    arr = []
    chunk: list = []

    for l in text:
        chunk.append(l)
        if len(chunk) == 6:
            arr.append(''.join(chunk))
            chunk = []
    # fill last chunk
    if chunk:
        while len(chunk) < 6:
            chunk.append('0')
        arr.append(''.join(chunk))
    

    final_arr: list = []

    for i, a in enumerate(arr):
        final_arr.append(bin_to_ascii(a))
    # TODO missing padding
    return final_arr


def base64_to_binary(input: str) -> str:
    arr: list = []
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