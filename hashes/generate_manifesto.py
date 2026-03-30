from Crypto.Hash import SHA256
import os

def save_encrypted_document(document: bytes, name: str, folder_name: str="hashed_documents") -> None:
    curr_path: str = os.getcwd()
    abs_path: str = os.path.join(curr_path, folder_name)
    os.makedirs(abs_path, exist_ok=True)
    with open(f"{abs_path}/SHA256SUMS.txt", "a", encoding="utf-8") as f: 
        f.write(document.hexdigest())
        f.write("\t")
        f.write(name)
        f.write("\n")

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

import os

def read_documents(documents: str = "documents") -> list[bytes]:
    path = os.path.join(os.getcwd(), documents)
    documents = []

    for doc in os.listdir(path):
        file_path = os.path.join(path, doc)

        if os.path.isfile(file_path):
            with open(file_path, "rb") as f:
                documents.append(f.read())

    return documents

def read_file(file_name: str = "SHA256SUMS.txt", folder: str = "hashed_documents") -> list[bytes]:
    path = os.path.join(os.getcwd(), folder, file_name)
    lines = []

    with open(path, "rb") as f:
        for line in f:
            lines.append(line)
    return lines
            

if __name__ == '__main__':
    # generate_documents(5, 512)
    manifesto(read_documents())
