from Crypto.Cipher import DES3
from Crypto.Util.Padding import pad
from Crypto.Random import get_random_bytes
import base64

with open("Key.txt", "rb") as f:
    Key = base64.b64decode(f.read())

with open("mensaje.txt", "rb") as f:
    M = f.read()

iv = get_random_bytes(8)

cifrador = DES3.new(Key,DES3.MODE_CBC,iv)
C = cifrador.encrypt(pad(M,8))

with open("cifrado.txt", "wb") as f:
    f.write(base64.b64encode(iv+C))