from Crypto.PublicKey import RSA
from Crypto.Cipher import PKCS1_OAEP, AES
from Crypto.Random import get_random_bytes
from rsa_keygen import rsa_keygen, save_rsa
import os


def encrypt_document(document: bytes, recipient_public_key_bytes: bytes) -> tuple[bytes, bytes, bytes, bytes]:
    aeskey = get_random_bytes(32)
    cipher = AES.new(aeskey, AES.MODE_EAX)
    ciphertext, tag = cipher.encrypt_and_digest(document)
    public_key = RSA.import_key(recipient_public_key_bytes)
    cipher_rsa = PKCS1_OAEP.new(public_key)
    enc_aes_key = cipher_rsa.encrypt(aeskey)

    return ciphertext, enc_aes_key, cipher.nonce, tag

def decrypt_document(document: bytes, recipient_private_key_pem: bytes, key: bytes, nonce: bytes, tag: bytes) -> bytes:
    private_key = RSA.import_key(recipient_private_key_pem)
    cipher_rsa = PKCS1_OAEP.new(private_key)
    decrypted_key = cipher_rsa.decrypt(key)
    cipher_aes = AES.new(decrypted_key, AES.MODE_EAX, nonce=nonce)
    plaintext = cipher_aes.decrypt_and_verify(document, tag)
    return plaintext


if __name__ == '__main__':
    priv, pub = rsa_keygen(bits=3072)
    save_rsa(priv, pub)

    document = os.urandom(1024*1024)
    cipher, key, nonce, tag = encrypt_document(document, pub)
    assert decrypt_document(cipher, priv, key, nonce, tag)
    print("Success")

    