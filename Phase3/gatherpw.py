import re

out = open ("passwords.txt", "a")
for i in xrange(66):
	file = open("%02d" % i + '-1_password.bin', "r")
	for line in file:
	    print >> out, line,