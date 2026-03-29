from Crypto.Hash import SHA256
import os

def save_encrypted_document(document: bytes, name: str) -> None:
    curr_path: str = os.getcwd()
    abs_path: str = os.path.join(curr_path, "hashed_documents")
    os.makedirs(abs_path, exist_ok=True)
    with open(f"{abs_path}/{name}.txt", "wb") as f: 
        f.write(document)
        f.write(b"\t")
        f.write(name.encode("utf-8"))
        f.write(b"\n")

def manifesto(documents: list[str]) -> None:
    
    for i, document in enumerate(documents):
        if not isinstance(document, bytes):
            print("Document is not bytes")
            continue
        sha256_doc = SHA256.new(document)
        save_encrypted_document(sha256_doc, f"document{i}")
        
def generate_documents(num_docs: int, size: int = 512) -> None:
    path: str = os.getcwd()
    abs_path: str = f"{path}/documents"
    os.makedirs(abs_path, exist_ok=True)
    for i in range(num_docs):
        with open(f"{abs_path}/document{i}", "wb") as f:
            f.write(os.urandom(size*size))
    f.close()  

def read_documents() -> list[str]:
    path: str = f"{os.getcwd()}/documents"
    for doc in os.listdir(path):
        with open(doc, "rb") as f:
            

if __name__ == '__main__':
    # generate_documents(5, 512)
    pass
