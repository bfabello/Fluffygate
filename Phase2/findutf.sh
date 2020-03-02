mkdir found
for file in *.plain; 
do 
	if file $file | grep 'ASCII'; 
	then
   		echo "Found $file"
   		cp ~/CMPS122/Lab3/Phase2/tommy/$file ~/CMPS122/Lab3/Phase2/tommy/found
   	fi
done
