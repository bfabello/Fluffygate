#!/bin/bash
#nc 128.114.59.42 5001 | tee -a packets.pcap
# editcap -r phase3_packets.pcap password_packets.pcap 1-100
# editcap -c 6 phase3_packets.pcap phase3_packets.pcap
for num in $(seq -w 00 65);
do
	echo "extracting $num contents"
	tshark -r phase2_packets_000$num.pcap -Y "frame.number == 1" -T fields -e data | tr -d '\n' | perl -pe 's/([0-9a-f]{2})/chr hex $1/gie' > $num-1_password.bin
	tshark -r phase2_packets_000$num.pcap -Y "frame.number == 2" -T fields -e data | tr -d '\n' | perl -pe 's/([0-9a-f]{2})/chr hex $1/gie' > $num-2_zip.zip
	tshark -r phase2_packets_000$num.pcap -Y "frame.number == 3" -T fields -e data | tr -d '\n' | perl -pe 's/([0-9a-f]{2})/chr hex $1/gie' > $num-3_iv.bin
	tshark -r phase2_packets_000$num.pcap -Y "frame.number == 4" -T fields -e data | tr -d '\n' | perl -pe 's/([0-9a-f]{2})/chr hex $1/gie' > $num-4_ciphertext.cipher
done
cd ../
mkdir bin_files
mv ~/CMPS122/Lab3/Phase2/pcap_packets/*.bin ~/CMPS122/Lab3/Phase2/bin_files
mv ~/CMPS122/Lab3/Phase2/pcap_packets/*.zip ~/CMPS122/Lab3/Phase2/bin_files
mv ~/CMPS122/Lab3/Phase2/pcap_packets/*.cipher ~/CMPS122/Lab3/Phase2/bin_files

echo "done"