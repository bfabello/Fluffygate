import os
import subprocess

directory = '/afs/cats.ucsc.edu/users/y/bfabello/CMPS122/Lab3/Phase3/cruzid_specific/bin_files/march_7_data/'

for i in xrange(66):
	cipher_file1 = directory + "%02d" % i + '-4_ciphertext1.bin'""
	cipher_file2 = directory + "%02d" % i + '-5_ciphertext2.bin'""
	cipher_file3 = directory + "%02d" % i + '-6_ciphertext3.bin'""
	key_file = directory + "%02d" % i + '-key'""
	iv_file = directory + "%02d" % i + '-3_iv.bin'""
	iv = open(iv_file,"r").read();
	os.system("./crypto " + " " + cipher_file1 + " " + key_file + " " + iv)
	os.system("./crypto " + " " + cipher_file2 + " " + key_file + " " + iv)
	os.system("./crypto " + " " + cipher_file3 + " " + key_file + " " + iv)