import os

for filename in os.listdir("."):
	if filename.endswith("-key"):
		for i in xrange(66):
			file = open(filename, "r").read()
			for i in range(0, len(file)-31):
				with open("%02d" % i + '-key.txt', 'a') as fileinput:
					fileinput.write(file[i:32+i] + '\n')
