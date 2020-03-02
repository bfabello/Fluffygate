import socket
import sys 
 
try:
    s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    print "Socket successfully created"
except socket.error as err:
    print "socket creation failed with error %s" %(err)
 
# default port for socket
port = 5001
 
try:
    host_ip = socket.gethostbyname('128.114.59.42')
except socket.gaierror:
    # this means could not resolve the host
    print "there was an error resolving the host"
    sys.exit()
 
# connecting to the server
s.connect((host_ip, port))
print "the socket has successfully connected on port == %s" %(host_ip)

# Next bind to the port
# we have not typed any ip in the ip field
# instead we have inputted an empty string
# this makes the server listen to requests 
# coming from other computers on the network
s.bind(('',port))
print "socket binded to %s" %(port)

# put the socket into listening mode
s.listen(5)     
print "socket is listening"           
 
# a forever loop until we interrupt it or 
# an error occurs
while True:
	c, addr = s.accept()     
   	print 'Got connection from', addr
 
   	# send a thank you message to the client. 
   	c.send('Thank you for connecting')
 
   	# Close the connection with the client
   	c.close()
   	#Close the connection
