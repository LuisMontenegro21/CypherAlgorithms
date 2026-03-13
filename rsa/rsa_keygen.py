from Crypto.PublicKey import RSA
import os

def rsa_keygen(bits: int = 3072) -> tuple:
    '''
    Create a RSA key: private and public
    '''
    if bits < 2048:
        print("Not a secure key size")
        return None, None
    key = RSA.generate(bits)
    private_key = key.export_key()
    public_key = key.publickey().export_key()

    return private_key, public_key

def save_rsa(priv, pub) -> None:
    path: str = os.getcwd()
    full_path = f"{path}/keys"
    with open(f"{full_path}/private.pem", "wb") as f:
        f.write(priv)
    with open(f"{full_path}/public.pem", "wb") as f:
        f.write(pub)




if __name__ == '__main__':
    priv, pub = rsa_keygen(bits=3072)
    print(f"Private key: {priv} Public key: {pub}")