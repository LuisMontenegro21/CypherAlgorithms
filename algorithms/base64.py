from binary import ascii_to_bin, bin_to_ascii


base64_chars: str = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/"
base64_dict: dict[int, str] = {i: ch for i, ch in enumerate(base64_chars)}
base64_dict_swapped: dict[str, int] = {ch: i for i, ch in enumerate(base64_chars)}


def binary_to_base64(input_bin: str) -> str:
    arr: list = []
    for ch in input_bin:
        if ch == " ":
            continue
        else:
            arr.append(ch)

    if len(arr) % 8 != 0:
        return "Error: bin number is not divisible by 8"

    text: str = ''.join(arr)
    arr = []
    chunk: list = []

    for l in text:
        chunk.append(l)
        if len(chunk) == 6:
            arr.append(''.join(chunk))
            chunk = []

    # fill last chunk
    print("chunk before", chunk)
    if chunk:
        padding: str = "00111101" # bin for '='
        while len(chunk) < 6:
            chunk.append('0')

        arr.append(''.join(chunk))
    print("chunk after", chunk)




    final_arr: list = []

    for i, a in enumerate(arr):
        final_arr.append(base64_dict.get(bin_to_ascii(a), "?"))


    # TODO missing padding
    return ''.join(final_arr)


def base64_to_binary(input_base64: str) -> list:
    arr: list = []
    for char in input_base64:
        arr.append(ascii_to_bin(base64_dict_swapped.get(char, 0)))
    return arr


def base64_to_ascii(input_base64: str) -> list:
    arr: list = base64_to_binary(input_base64=input_base64)

        

if __name__ == '__main__':
    try: 
        mode: str = input("Ingrese modo: ")
        text_input: str = input("Ingrese texto: ")
        if mode == "encrypt":
            print(binary_to_base64(input_bin=text_input))
        elif mode == "decrypt":
            print(base64_to_binary(input_base64=text_input))
    except KeyboardInterrupt:
        print("Programa finalizado por usuario")
    else:
        print("Programa finalizado")