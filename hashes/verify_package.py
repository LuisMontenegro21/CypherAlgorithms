from Crypto.Hash import SHA256
from generate_manifesto import read_documents, read_file


def verify_hashed_documents(original_documents: list[bytes], hashed_documents: list[bytes]) -> None:
    for i, (original, stored) in enumerate(zip(original_documents, hashed_documents)):

        new_hash = SHA256.new(original).hexdigest()
        try:
            stored_hash, name = stored.split(b"\t", 1)
            stored_hash = stored_hash.strip().decode("utf-8")
            name = name.strip().decode("utf-8")
            print(stored_hash)
            print(new_hash)
            if new_hash == stored_hash:
                print(f"[MATCH] {name}")
            else:
                print(f"[MISMATCH] {name}")
        except Exception:
            print(f"[ERROR] Could not parse stored document {i}")
            continue


if __name__ == '__main__':
    verify_hashed_documents(original_documents=read_documents(), hashed_documents=read_file())