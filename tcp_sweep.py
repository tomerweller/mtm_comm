import socket
import time

TCP_IP = '10.0.1.34'
TCP_PORT = 8090
BUFFER_SIZE = 1024

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.connect((TCP_IP, TCP_PORT))

print "packet number, response time"
for i in range(128):
	start = time.time()	
	s.send(unichr(i));
	data = s.recv(BUFFER_SIZE)
	print i, time.time()-start


s.close()
