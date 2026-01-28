
def xor_binary(binary_str: str, key: str) -> str:
	if len(binary_str) != len(key):
		raise InputError()

	arr: list = []
	for i, bn in enumerate(binary_str):
		arr.append(str(int(bn) ^ int(key[i])))
	return ''.join(arr)


if __name__ == '__main__':

	text_input: str = input("Ingrese texto: ")
	key: str = input("Ingrese llave: ")
	print(xor_binary(text_input, key))