
def bytes_to_char(binary: str) -> str:
    arr: list = []
    for i, b in enumerate(binary):
        if i % 8 != 0:
            arr.append(b)
        else:
            arr.append(" ")
    return ''.join(arr)




def char_to_bytes(text: str) -> str:
    arr: list = []
    for t in text: 
        if t.isalnum():
            arr.append(f"{ord(t):08b}")
        else: 
            continue

    return ' '.join(arr)



if __name__ == '__main__':
    2
    text_input: str = input("Ingrese texto: ")
    print(char_to_bytes(text=text_input))
