from Crypto.PublicKey import RSA
from Crypto.Cipher import PKCS1_OAEP
from rsa_keygen import rsa_keygen, save_rsa
import binascii


def encrypt_document(document: bytes, recipient_public_key_bytes: bytes) -> bytes:

    return 

def decrypt_document(pkg: bytes, recipient_private_key_pem: bytes) -> bytes

    return


if __name__ == '__main__':
    priv, pub = rsa_keygen(bits=3072)
    save_rsa(priv, pub)
    