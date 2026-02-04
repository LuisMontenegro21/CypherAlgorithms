import time


MIN_ASCII = 32
MAX_ASCII = 126
CHARACTERS = 256

def dynamic_key_gen(length: int, seed: int = 42) -> str:
    '''
    Generated with the help of ChatGPT 4o
    Prompt:
    May you help me with a function that generates dynamic keys within a range 
    of ascii values. Use a pseudo-random number function to randomize since 
    external modules are not allowed
    '''
    seed = seed * int(time.time() * 1000) # make it random with time

    key: list = []
    value = seed
    for _ in range(length):
        value = (value * 1103515245 + 12345) % (2**31) #  pseudo random number function
        char = chr(MIN_ASCII + (value % (MAX_ASCII - MIN_ASCII + 1)))
        key.append(char)
    return ''.join(key)


def new_cypher_static(text: str, key: str) -> str:
    cypher = []
    key_len: int = len(key)
    for i, c in enumerate(text):
        k: str = key[i % key_len]
        shifted: int = (ord(c) + ord(k)) % CHARACTERS # 256 ASCII characters
        cypher.append(chr(shifted))
    return ''.join(cypher)    

def new_cypher_dynamic(text: str, seed: int = 42) -> str:
    dynamic_key: str = dynamic_key_gen(len(text), seed)
    cypher: list = []
    for t, k in zip(text, dynamic_key):
        shifted: int = (ord(t) + ord(k)) % CHARACTERS
        cypher.append(chr(shifted))
    return ''.join(cypher)

if __name__ == '__main__':
    try: 
        text_input: str = input("Ingrese texto: ")
        mode: str = input("Ingrese modo: static | dynamic:  ")
        if mode == "static":
            key: str = input("Ingrese llave: ")
            print(new_cypher_static(text_input, key))
        elif mode == "dynamic":
            seed: int = int(input("Ingrese semilla: "))
            print(new_cypher_dynamic(text_input, seed))

    except KeyboardInterrupt:
        print("Programa finalizado por usuario")
    else:
        print("Programa finalizado")