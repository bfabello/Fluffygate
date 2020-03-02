import string

file = open('bfabello.ciphertext1.cipher','r').read();
rot13 = string.maketrans( 
    "ABCDEFGHIJKLMabcdefghijklmNOPQRSTUVWXYZnopqrstuvwxyz", 
    "NOPQRSTUVWXYZnopqrstuvwxyzABCDEFGHIJKLMabcdefghijklm")

out = string.translate(file, rot13)	
with open('bfabello.ciphertext1.plain ', 'a') as fileinput:
	fileinput.write(out)
