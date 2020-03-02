#!/bin/bash
#nc 128.114.59.42 5001 | tee -a packets.pcap
# editcap -c 6 phase3_packets.pcap phase3_packets.pcap
count=00
tuple=00
echo "extracting packet contents"
for num in $(seq -w 00 2639);
do
	tshark -r phase3_packets_000$num.pcap -Y "frame.number == 1" -T fields -e data | tr -d '\n' | perl -pe 's/([0-9a-f]{2})/chr hex $1/gie' > $(printf %02d $counter)-$(printf %02d $tuple).bin
	counter=$((counter+1))
	tuple=$((tuple+1))
	if [tuple -gt 4]
		tuple=0
done
# cd ../../
# cd bin_files
# mkdir march_6_data
mv ~/CMPS122/Lab3/Phase3/cruzid_specific/final_dump/*.bin ~/CMPS122/Lab3/Phase3/cruzid_specific/final_dump
mv ~/CMPS122/Lab3/Phase3/cruzid_specific/final_dump/*.zip ~/CMPS122/Lab3/Phase3/cruzid_specific/final_dump
mv ~/CMPS122/Lab3/Phase3/cruzid_specific/final_dump/*.cipher ~/CMPS122/Lab3/Phase3/cruzid_specific/final_dump
echo "done"
