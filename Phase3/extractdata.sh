#!/bin/bash
#nc 128.114.59.42 5001 | tee -a packets.pcap
# editcap -c 6 phase3_packets.pcap phase3_packets.pcap
for num in $(seq -w 00 65);
do
	echo "extracting $num contents"
	tshark -r phase3_packets_000$num.pcap -Y "frame.number == 1" -T fields -e data | tr -d '\n' | perl -pe 's/([0-9a-f]{2})/chr hex $1/gie' > $num-1_password.bin
	tshark -r phase3_packets_000$num.pcap -Y "frame.number == 2" -T fields -e data | tr -d '\n' | perl -pe 's/([0-9a-f]{2})/chr hex $1/gie' > $num-2_zip.zip
	tshark -r phase3_packets_000$num.pcap -Y "frame.number == 3" -T fields -e data | tr -d '\n' | perl -pe 's/([0-9a-f]{2})/chr hex $1/gie' > $num-3_iv.bin
	tshark -r phase3_packets_000$num.pcap -Y "frame.number == 4" -T fields -e data | tr -d '\n' | perl -pe 's/([0-9a-f]{2})/chr hex $1/gie' > $num-4_ciphertext1.cipher
	tshark -r phase3_packets_000$num.pcap -Y "frame.number == 5" -T fields -e data | tr -d '\n' | perl -pe 's/([0-9a-f]{2})/chr hex $1/gie' > $num-5_ciphertext2.cipher
	tshark -r phase3_packets_000$num.pcap -Y "frame.number == 6" -T fields -e data | tr -d '\n' | perl -pe 's/([0-9a-f]{2})/chr hex $1/gie' > $num-6_ciphertext3.cipher
done
# cd ../../
# cd bin_files
# mkdir march_6_data
mv ~/CMPS122/Lab3/Phase3/cruzid_specific/final_dump/*.bin ~/CMPS122/Lab3/Phase3/cruzid_specific/final_dump
mv ~/CMPS122/Lab3/Phase3/cruzid_specific/final_dump/*.zip ~/CMPS122/Lab3/Phase3/cruzid_specific/final_dump
mv ~/CMPS122/Lab3/Phase3/cruzid_specific/final_dump/*.cipher ~/CMPS122/Lab3/Phase3/cruzid_specific/final_dump
echo "done"
