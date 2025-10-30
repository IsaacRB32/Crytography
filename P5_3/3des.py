from Crypto.Cipher import DES3
from Crypto.Util.Padding import pad, unpad
from Crypto.Random import get_random_bytes
## 16bytes (K1, K2, K3 = K1) ó 24 bytes (K1, K2, K3)
key = DES3.adjust_key_parity(get_random_bytes(24))
iv = get_random_bytes(8)

mensaje = "Hola </IsaacRB*>".encode()

cipher = DES3.new(key,DES3.MODE_CBC,iv)
cifrado = cipher.encrypt(pad(mensaje,8))

descifrador = DES3.new(key, DES3.MODE_CBC, iv)
decifrado = unpad(descifrador.decrypt(cifrado), 8)

print("Llave:", key.hex())
print("IV:", iv.hex())
print("Texto cifrado:", cifrado)
print("Texto decifrado:", decifrado.decode())