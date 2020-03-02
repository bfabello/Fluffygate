echo "merching packet contents"
count=0000

for num in $(seq -w 0000 2639);
do
	for file in $(seq -w 000 680);
		mergecap -w phase4_dump-00$file.pcap phase4_dump-$(printf %04d $num).pcap phase4_dump-$(printf %04d $num+1).pcap phase4_dump-$(printf %04d $num+2).pcap phase4_dump-$(printf %04d $num3).pcap
		counter=$((counter+1))

done
