mkdir found
for file in *.plain; 
do 
	if file $file | grep 'ASCII\|Unicode'; 
	then
   		cp ~/CMPS122/Lab3/Phase1/cruzid_packets/$file ~/CMPS122/Lab3/Phase1/cruzid_packets/found
   	fi
done
