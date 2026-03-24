from Crypto.Hash import SHA256
# import requests

common_passwrds: list = ["abc123", "hello123", "admin", "123"]

def calc_hash(passwords: list) -> list:
    return list(map(lambda x: SHA256.new(bytes(x, "utf-8")), passwords))

def call_apis(hashes: list[bytes]) -> None:
    pass

if __name__ == '__main__':
    hashes = calc_hash(common_passwrds)
    print([hashs.hexdigest() for hashs in hashes])