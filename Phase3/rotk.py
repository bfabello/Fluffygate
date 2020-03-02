import string

file = open('bfabello.ciphertext2.cipher','r').read();
out = open('bfabello.ciphertext2.plain ', 'a')

lower = "abcdefghijklmnopqrstuvwxyz"
upper = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"

rotations=[7,8,9,6]

for letter in file:
	count = (count % 10) + count
	if letter.islower():
		result += chr((ord(char) - s-97) % 26 + 97)
	elif letter.isupper():
 		result += chr((ord(char) - s-65) % 26 + 65)
	else:
        result += char

out.write(result)

 