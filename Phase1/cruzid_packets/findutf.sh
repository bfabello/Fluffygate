mkdir found
for file in *.plain; 
do 
	if file $file | grep 'Unicode'; 
	then
   		echo "Found $file"
   		cp ~/CMPS122/Lab3/Phase1/cruzid_packets/$file ~/CMPS122/Lab3/Phase1/cruzid_packets/found
   	fi
done
