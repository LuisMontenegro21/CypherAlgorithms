from Crypto.Hash import SHA256
import requests, time
common_passwrds: list = ["abc123", "hello123", "admin", "123"]

def calc_hash(passwords: list) -> list:
    return list(map(lambda x: SHA256.new(bytes(x, "utf-8")), passwords))

def call_apis(hashes: list[bytes]) -> None:

    for i in range(0,1):
        hash_str: str = hashes[i].hexdigest()
        first_5_chars: str = hash_str[:5] 
        response = requests.get(f"https://api.pwnedpasswords.com/range/{first_5_chars}")
        if response.status_code != 200:
            raise RuntimeError(f"Error in Request for hash: {hash_str}")
        print(response.json()['json'])
        time.sleep(3)
        
        
if __name__ == '__main__':
    hashes = calc_hash(common_passwrds)
    call_apis(hashes)