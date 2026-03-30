from Crypto.PublicKey import RSA
from Crypto.Hash import SHA256
from Crypto.Signature import pkcs1_15
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

def save_rsa(priv, pub, name: str = "medisoft") -> None:
    path: str = os.getcwd()
    full_path = f"{path}/keys"
    os.makedirs(name=full_path, exist_ok=True)
    with open(f"{full_path}/{name}_private.pem", "wb") as f:
        f.write(priv)
    with open(f"{full_path}/{name}_public.pem", "wb") as f:
        f.write(pub)


def sign_file(file: str, private_key_path: str, output_path_file: str) -> None:
    with open(file, "rb") as f:
        data = f.read()
    
    hash = SHA256.new(data)
    with open(private_key_path, "rb") as f:
        private_key = RSA.import_key(f.read())
    
    signature = pkcs1_15.new(private_key).sign(hash)
    
    with open(output_path_file, "wb") as f:
        f.write(signature)
    print("Signed and saved")

def verify_file_signature(file: str, public_key_path: str, signature_path_file: str) -> None:
    with open(file, "rb") as f:
        data = f.read()
    
    hash = SHA256.new(data)

    with open(public_key_path, "rb") as f:
        public_key = RSA.import_key(f.read())

    with open(signature_path_file, "rb") as f:
        signature = f.read()
    
    try:
        pkcs1_15.new(public_key).verify(hash, signature)
        print("Valid signature")
    except (ValueError, TypeError):
        print("Not valid signature")

if __name__ == '__main__':
    #priv, pub = rsa_keygen()
    #save_rsa(priv, pub)
    directory: str = os.getcwd()
    text_file: str = os.path.join(directory, "hashed_documents", "SHA256SUMS.txt")
    public_key: str = os.path.join(directory, "keys", "medisoft_public.pem")
    private_key: str = os.path.join(directory, "keys", "medisoft_private.pem")
    output_path: str = os.path.join(directory, "output")
    os.makedirs(output_path, exist_ok=True) 
    output: str = os.path.join(output_path, "SHA256SUMS.sig")
    sign_file(text_file, private_key, output)
    verify_file_signature(text_file, public_key, output)