import os
import subprocess

directory = '/afs/cats.ucsc.edu/users/y/bfabello/CMPS122/Lab3/Phase2/bin_files'

for i in xrange(66):
	cipher_file = "/afs/cats.ucsc.edu/users/y/bfabello/CMPS122/Lab3/Phase2/bin_files/" + "%02d" % i + '-4_ciphertext.cipher'""
	key_file = "/afs/cats.ucsc.edu/users/y/bfabello/CMPS122/Lab3/Phase2/bin_files/" + "%02d" % i + '-key'""
	iv_file = "/afs/cats.ucsc.edu/users/y/bfabello/CMPS122/Lab3/Phase2/bin_files/" + "%02d" % i + '-3_iv.bin'""
	iv = open(iv_file,"r").read();
	# print(cipher_file)
	# print(key_file)
	# print(iv_file)
	# print ("./crypto " + " " + cipher_file + " " + key_file + " " + iv + " " + str(i))
	os.system("./crypto " + " " + cipher_file + " " + key_file + " " + iv)

# for subdir, dirs, files in os.walk(rootdir):
#     for file in files:
#         f = open(file,'r')
#         lines=f.read()
#         f.close()
#         f=open(file,'w')
#         for line in lines:
#             newline = "No you are not"
#             f.write(newline)
#         f.close()

# for subdir, dirs, files in os.walk(rootdir):
#     for file in files:
#         print os.path.join(subdir, file)

# for filename in os.listdir("."):
# 	if filename.startswith("phase3_packets_"):
# 		os.rename(filename, filename[:20] + '.pcap')

# for filename in os.listdir(directory):
#     if filename.endswith(".asm") or filename.endswith(".py"): 
#         # print(os.path.join(directory, filename))
#         continue
#     else:
#         continue