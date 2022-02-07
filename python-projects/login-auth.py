#!/usr/bin/python3

import socket

bport = 25755
rlapver = b'0.01'
startcomm = False
connection = ('', '')
address = ('', '')

def packetSender(data):
	if len(b'RLAP SERVER 0.01\n' + data) < 4096:
		connection.send(b'RLAP SERVER 0.01\n' + data)

def packetParser(data):
	packettokens = data.split(b'\n')
	datatokens = packettokens.split()

	if type(datatokens) is not list and not startcomm:
		print("RLAP Error 1: Invalid packet")
		packetSend(b'E1: RLAP_ERR_INV_PKT\nRLAP_ENDCONN')
		return 1
	elif type(datatokens) is list and not startcomm:
		if datatokens[0] != b'RLAP':
			print("RLAP Error 2: Incompatible protocol")
			packetSend(b'E2: RLAP_ERR_INCOMPAT_PROT\nRLAP_ENDCONN')
			return 2
		else:
			if datatokens[1] != b'CLIENT' or datatokens[2] != rlapver:
				print("RLAP Error 3: Incompatible version")
				packetSend(b'E3: RLAP_ERR_INCOMPAT_VER\nRLAP_ENDCONN')
				return 3
			else:
				startcomm = True
	else:
		print("Data received, yet to write an actual authenticator")

	print(repr(datatokens))
	return 0

if __name__ == "__main__":
	data = b'begin'

	socklisten = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
	socklisten.bind(("localhost", bport))
	socklisten.listen(5)
	print("PocketRLAP Server, v0.01")
	print("(c)2022 pocketlinux32, Under GPLv3")
	print("Server initialized on port", bport)
	while True:
		(connection, address) = socklisten.accept()
		print("Connection established with host", address[0], "on port", address[1])

		while data:
			data = connection.recv(4096)
			if packetParser(data):
				break

		print("Ended connection with host", address[0])
		startcomm = False
