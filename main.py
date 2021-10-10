from Crypto.Hash import MD2
from Crypto.Cipher import AES
import sys

from Crypto.Util.Padding import pad, unpad

right_hash = b'\xf08\x81\xa8\x8cn9\x13_\x0e\xcc`\xef\xd6\t\xb9'

password = sys.argv[1]
action = sys.argv[2]
hash_value = MD2.new(password.encode()).digest()

if action == 'encrypt':
    with open('data.json', 'rb') as json_file:
        encrypter = AES.new(hash_value, AES.MODE_CFB, hash_value)
        data = encrypter.encrypt(pad(json_file.read(), AES.block_size))
        with open('crypted', 'wb') as file:
            file.write(data)

if action == 'decrypt' and right_hash == hash_value:
    with open('crypted', 'rb') as file:
        dencrypter = AES.new(hash_value, AES.MODE_CFB, hash_value)
        data = unpad(dencrypter.decrypt(file.read()), AES.block_size)
        with open('data.json', 'wb') as json_file:
            json_file.write(data)
        with open('check.json', 'wb') as json_file:
            json_file.write(data)

elif right_hash != hash_value:
    exit(1)
