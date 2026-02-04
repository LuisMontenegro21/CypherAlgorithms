
def xor_binary(binary_str: str, key: str) -> str:
	if len(binary_str) != len(key):
		raise ValueError(f"String and key must be the same size")
	arr: list = []
	for i, j in zip(binary_str, key):
		arr.append(str(int(i) ^ int(j)))
	return ''.join(arr)


if __name__ == '__main__':

	text_input: str = input("Ingrese texto: ")
	key: str = input("Ingrese llave: ")
	print(xor_binary(text_input, key))