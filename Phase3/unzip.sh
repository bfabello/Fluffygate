# unzip -p -P hC0s1B 00-2_zip.zip > 00-key
filename=decrypted_passwords_.txt
counter=00
while IFS='' read -r line || [ -n "$line" ]; 
do
	echo "unzipping $counter"
	unzip -p -P $line $(printf %02d $counter)-2_zip.zip > $(printf %02d $counter)-key
	counter=$((counter+1))
done <"$filename"