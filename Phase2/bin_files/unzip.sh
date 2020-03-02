filename=decrypted_passwords.txt
counter=00
while IFS='' read -r line || [ -n "$line" ]; 
do
	unzip -p -P $line $(printf %02d $counter)-2_zip.zip > $(printf %02d $counter)-key
	counter=$((counter+1))
done <"$filename"