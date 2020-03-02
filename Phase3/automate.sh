# nc 128.114.59.42 5001 | tee -a phase3_dump_march_9_2am.pcap

editcap -c 6 phase3_final_dump.pcap phase3_packets.pcap
python rename.py
sh extractdata.sh
python gatherpw.py

sh passwordcracker.sh
python clean_decrypted.py
sh unzip.sh
python decrypt_script.py