#!/usr/bin/python3

import socket
rlpver = '0.01'

def packetParser(data):
	datatokens = data.split();

	if()

	print(repr(datatokens))

	return 0

if __name__ == "__main__":
	data = b'begin'
	socklisten = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
	socklisten.bind(("localhost", 25755))
	socklisten.listen(5)
	print("PocketRLP Server initialized on port 25755")
	while True:
		(connection, address) = socklisten.accept()
		print("Connection established with", address[0], "on port", address[1])

		while data:
			data = connection.recv(4096)
			packetParser(data)
