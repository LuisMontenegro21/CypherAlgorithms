
def dynamic_key_gen() -> None:
    pass

def new_cypher_static(key: str) -> None:
    pass

def new_cypher_dynamic(key: str) -> None:
    pass


if __name__ == '__main__':
    try: 
        mode: str = input("Ingrese modo: ")
        text_input: str = input("Ingrese texto: ")

    except KeyboardInterrupt:
        print("Programa finalizado por usuario")
    else:
        print("Programa finalizado")