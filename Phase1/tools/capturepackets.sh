while true; 
do nc 128.114.59.42 5001 | tshark -i - 2 -w ~/CMPS122/Lab3/Phase1/out.pcap >/dev/null; 
done