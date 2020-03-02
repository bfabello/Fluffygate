import os

for filename in os.listdir("."):
	if filename.startswith("phase3_packets_"):
		os.rename(filename, filename[:20] + '.pcap')
