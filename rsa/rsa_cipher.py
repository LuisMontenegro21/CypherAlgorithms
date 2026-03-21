from Crypto.PublicKey import RSA
from Crypto.Cipher import PKCS1_OAEP
from rsa_keygen import rsa_keygen
import binascii

def rsa_cipher(message: bytes, public_key_pem: bytes) -> bytes:
    cipher = PKCS1_OAEP.new(public_key_pem)
    ciphertext = cipher.encrypt(message)
    return ciphertext

def rsa_decipher(ciphertext: bytes, private_key_pem: bytes) -> bytes:
    cipher = PKCS1_OAEP.new(private_key_pem)
    plaintext = cipher.decrypt(ciphertext)
    return plaintext


if __name__ == '__main__':
    keyPair = RSA.generate(3072)
    pub_key = keyPair.publickey()
    message: bytes = b"Hello world"
    ciphertext = rsa_cipher(message, pub_key)
    print(f"Ciphertext 1: {binascii.hexlify(ciphertext)}")
    ciphertext = rsa_cipher(message, pub_key)
    print(f"Ciphertext 2: {binascii.hexlify(ciphertext)}")
    plaintext = rsa_decipher(ciphertext, keyPair)
    
    assert message == plaintext
    print("Worked correctly")