with open('decrypted_passwords.txt', 'r') as fileinput:
    for line in fileinput:
        line=line[14:]
        with open('decrypted_passwords_.txt', 'a') as fileinput:
   			fileinput.write(line)