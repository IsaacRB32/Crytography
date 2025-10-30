from Crypto.Cipher import DES3
from Crypto.Random import get_random_bytes
import base64

Key = DES3.adjust_key_parity(get_random_bytes(24))

Key_64 = base64.b64encode(Key)

with open("Key.txt", "wb") as f:
    f.write(Key_64)

print("Llave guardada en Key.txt")