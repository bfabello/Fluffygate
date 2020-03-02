import re
import os

out = open ("passwords.txt", "a")
for i in xrange(66):
	file = open("%02d" % i + '-1_password.bin', "r")
	for line in file:
	    print >> out, line,

# out = open ("iv.txt", "a")
# for i in xrange(66):
# 	file = open("%02d" % i + '-3_iv.bin', "r")
# 	for line in file:
# 	    print >> out, line,

# for filename in os.listdir("."):
# 	if filename.endsswith("-key"):
# 		for i in xrange(66):
# 			file = open(filename, "r").read()
# 			for i in range(0, len(data)-31):
# 				with open("%02d" % i + '-key.txt', 'a') as fileinput:
# 					fileinput.write(file[i:32+i] + '\n')
