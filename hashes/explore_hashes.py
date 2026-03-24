from Crypto.Hash import SHA256, MD5, SHA1, SHA3_256

data: bytes = b"MediSoft-v2.1.0"
data_low: bytes = b"medisoft-v2.1.0"

def print_table(data: bytes) -> None:
    '''
    Prompt:
    def print_table(data: bytes) -> None: 
        d5 = MD5.new(data) 
        ha1 = SA1.new(data) 
        sha256 = SHA256.new(data) 
        sha3_256 = SHA3_256.new(data) 
        hashes: list = [md5, sha1, sha256, sha3_256] 
	    for hash in hashes: 
		    print(f"Name: {type(hash)} Hash: {hash.hexdigest()} Hex length: {len(hash.hexdigest())} Binary length: {hash.digest_size}") 
    
    Make this print prettier
    '''
    md5 =  MD5.new(data)
    sha1 = SHA1.new(data)
    sha256 = SHA256.new(data)
    sha3_256 = SHA3_256.new(data)
    hashes = [
        ("MD5", md5),
        ("SHA1", sha1),
        ("SHA256", sha256),
        ("SHA3-256", sha3_256),
    ]
    headr_len: int = 80
    print("=" * headr_len)
    print(f"{'Algorithm':<12} {'Hex Digest':<66} {'Hex Len':<8} {'Bytes':<6}")
    print("=" * headr_len)

    for name, h in hashes:
        hex_digest = h.hexdigest()
        print(f"{name:<12} {hex_digest:<66} {len(hex_digest):<8} {h.digest_size:<6}")

    print("=" * headr_len)

def compare_sha(first, second) -> int:
    return 0



if __name__ == '__main__':
    print("MediSoft-v2.1.0")
    print_table(data)
    print("medisoft-v2.1.0")
    print_table(data_low)

