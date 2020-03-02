import os

for filename in os.listdir("."):
	if filename.startswith("2018-03-09"):
		os.rename(filename, 'phase4_dump-' + filename[38:] + '.pcap')
