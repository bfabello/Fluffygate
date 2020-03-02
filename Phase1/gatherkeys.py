data = open('key', 'r').read()
for i in range(0, len(data)-31):
	with open('keys.txt', 'a') as fileinput:
		fileinput.write(data[i:32+i] + '\n')
