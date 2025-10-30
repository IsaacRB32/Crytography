from Crypto.Cipher import DES3
from Crypto.Random import get_random_bytes
from Crypto.Util.Padding import unpad
import base64

with open("Key.txt","rb") as f:
    Key = base64.b64decode(f.read())

with open("cifrado.txt", "rb") as f:
    C_file = base64.b64decode(f.read())

iv = C_file[:8]
C = C_file[8:]

cifrador = DES3.new(Key, DES3.MODE_CBC,iv)
M = unpad(cifrador.decrypt(C),8)

with open ("decifrado.txt", "wb") as f:
    f.write(M)
