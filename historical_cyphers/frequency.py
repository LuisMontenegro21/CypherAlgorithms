

def frequency_analysis(text: str) -> dict:
    relative_freq_dict: dict[str, float] = {}
    letter_freq: dict[str, int] = {} # count how many times a letter is found throughout the string
    seen: set = set()
    for t in text:
        if t not in seen:
            seen.add(t)
            letter_freq[t] = 1
        else:
            letter_freq[t] = letter_freq.get(t, 0) + 1
    
    for letter in seen:
        relative_freq_dict[letter] = letter_freq.get(letter, 1) / len(text)
        
    return relative_freq_dict


if __name__ == '__main__':
    try: 
        text: str = input("Ingrese texto: ")
        print(f"Frequencias del texto:")
        frequencies: dict = frequency_analysis(text)
        for k, v in frequencies.items():
            print(f"{k} : {v:.2f}")        
    except KeyboardInterrupt:
        print("Programa finalizado por usuario")
    else:
        print("Programa finalizado")
