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
    if chunk:
        while len(chunk) < 6:
            chunk.append('0')
        arr.append(''.join(chunk))


    final_arr: list = []

    for i, a in enumerate(arr):
        final_arr.append(base64_dict.get(bin_to_ascii(a), "?"))
    # fill missing padding
    
    if len(final_arr) % 4 == 3:
        final_arr.append("=")
    elif len(final_arr) % 4 == 2:
        final_arr.extend(["=", "="])

    return ''.join(final_arr)


def base64_to_binary(input_base64: str) -> str:
    arr: list = []
    for char in input_base64:
        arr.append(ascii_to_bin(base64_dict_swapped.get(char, 0)))
    return ''.join(arr)


def base64_to_ascii(input_base64: str) -> list:
    bin_arr: str = base64_to_binary(input_base64=input_base64)
    chunk: str = ""
    output: list = []
    print(len(bin_arr))
    for i in range(len(bin_arr)):
        chunk += bin_arr[i]
        if i % 8 == 0:
            output.append(bin_to_ascii(chunk))
            chunk = ""
    return output

    

        

if __name__ == '__main__':
    try: 
        mode: str = input("Ingrese modo: ")
        text_input: str = input("Ingrese texto: ")
        if mode == "binary":
            print(binary_to_base64(input_bin=text_input))
        elif mode == "b64":
            print(base64_to_binary(input_base64=text_input))
        elif mode == "ascii":
            print(base64_to_ascii(input_base64=text_input))
        else:
            pass
    except KeyboardInterrupt:
        print("Programa finalizado por usuario")
    else:
        print("Programa finalizado")