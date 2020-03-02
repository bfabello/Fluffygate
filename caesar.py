import sys

rotations=[7,8,9,6]

#A python program to illustrate Caesar Cipher Technique
def encrypt(text,s):
    result = "" 
    # traverse text
    for i in range(len(text)):
        char = text[i]
        ordChar = ord(char)
#	if(ordChar<65 or ordChar>122 or (ordChar<97 and ordChar>90)):
#	    result += char
	# Encrypt uppercase characters                
        if (char.isupper()):
            result += chr((ord(char) + s-65) % 26 + 65)
        # Encrypt lowercase characters
        elif (char.islower()):
            result += chr((ord(char) + s - 97) % 26 + 97)
	else:
	    result += char
    return result

def decrypt(text,s):
    result = ""
    # traverse text
    for i in range(len(text)):
        char = text[i]

        # Encrypt uppercase characters
        if (char.isupper()):
            result += chr((ord(char) - s-65) % 26 + 65)
        # Encrypt lowercase characters
        elif(char.islower()):
            result += chr((ord(char) - s-97) % 26 + 97)
        else:
            result += char
    return result

def rotateDecrypt(text):
    result=""
    rotIndex=3
    # traverse text
    for i in range(len(text)):
        char = text[i]
        # Decrypt uppercase characters
        if (char.isupper()):
            result += chr((ord(char) - rotations[rotIndex]-65) % 26 + 65)
        # Decrypt lowercase characters
        elif(char.islower()):
            result += chr((ord(char) - rotations[rotIndex]-97) % 26 + 97)
        else:
            result += char
        rotIndex += 1
        if(rotIndex>=len(rotations)):
            rotIndex=0
    return result

if(len(sys.argv)<3):
    print "Invalid arguments"
    print "Usage: python caesar.py [-e|-d] [text] [rotation]" 
    exit()

#check the above function
opt = sys.argv[1]
text = sys.argv[2]

if(len(sys.argv)==4 and opt == "-e"):
    s = int(sys.argv[3])
    print ""+encrypt(text,s)
elif(len(sys.argv)==4 and opt == "-d"):
    s = int(sys.argv[3])
    print ""+decrypt(text,s)
elif(len(sys.argv)==3 and opt == "-rd"):
    print ""+rotateDecrypt(text)

