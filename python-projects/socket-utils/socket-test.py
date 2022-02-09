#!/usr/bin/python3

import socket

def packetParser(data):
	return 0

if __name__ == "__main__":
	socklisten = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
	socklisten.bind(("localhost", 25755))
	socklisten.listen(5)
	print("Server initialized on port 25755")
	try:
		while True:
			(connection, address) = socklisten.accept()
			data = connection.recv(1024)
			while data:
				print("Received data: ", repr(data))
				data = connection.recv(1024)
	except KeyboardInterrupt:
		socklisten.shutdown(socket.SHUT_RDWR)
		socklisten.close()
		print("Server stopped")
		exit(0)
