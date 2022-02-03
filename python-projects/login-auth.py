#!/usr/bin/python3

import socket

def packetParser(data):
	while data.find(b'\n') != len(data) or data.find(b'\n') != -1:
		tempdata = data[0:data.find('\n')]

	return 0

if __name__ == "__main__":
	databuffer = b''
	socklisten = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
	socklisten.bind(("localhost", 25755))
	socklisten.listen(5)
	print("Server initialized on port 25755")
	while True:
		(connection, address) = socklisten.accept()
		data = connection.recv(1024)

		while data:
			databuffer += data
			data = connection.recv(1024)

		packetParser(databuffer)
		databuffer = b''
