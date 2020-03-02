#!/bin/bash
# sleep 2820
nc 128.114.59.42 5001 | tee -a phase3_dump_march_9_10am.pcap
sleep 2
kill -l 3
