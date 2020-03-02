from pycipher import PolybiusSquare

file = open('bfabello.ciphertext3.cipher','r').read();

p = PolybiusSquare('abcdefghijklmnopqrstuvwxy', 5,'12345').decipher(file)
print(p)


