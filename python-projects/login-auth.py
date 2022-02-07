#!/usr/bin/python3

import socket

bport = 25755
rlapver = b'0.01'
startconn = False
datastream = False
connection = ('', '')
address = ('', '')

def packetSender(data):
	global connection

	if len(b'RLAP SERVER 0.01\n' + data) < 4096:
		connection.send(b'RLAP SERVER 0.01\n' + data)

def packetParser(data):
	global startconn
	global datastream
	global address
	global rlapver

	packettokens = data.split(b'\n')

#	print(str(data.split(b'\n')))
#	print(str(packettokens))

	for datatoken in packettokens:
		datatokens = datatoken.split()
#		print(repr(datatokens))

		if not startconn:
			if datatokens[0] != b'RLAP':
				print("RLAP Error 1: Incompatible protocol")
				packetSender(b'E1: RLAP_ERR_INCOMPAT_PROT\nRLAP_ENDCONN')
				return 1
			else:
				if datatokens[1] != b'CLIENT' or datatokens[2] != rlapver:
					print("RLAP Error 2: Incompatible version")
					packetSender(b'E2: RLAP_ERR_INCOMPAT_VER\nRLAP_ENDCONN')
					return 2
				else:
					print("Host", address[0], "is a compatible RLAP client")
					startconn = True
		else:
			if datatokens[0] == b'RLAP_STARTLIST':
				if not datastream:
					print("Host", address[0], "has started a Data Stream")
					datastream = True
				else:
					print("RLAP Warning 1: Data Stream already started")
			elif datatokens[0] == b'RLAP_ENDLIST':
				if datastream:
					print("Host", address[0], "has ended a Data Stream")
					datastream = False
				else:
					print("RLAP Warning 2: Data Stream already ended")
			elif datatokens[0] == b'RLAP_ENDCONN':
				print("Host", address[0], "requested to end connection")
				return -1
			else:
				print("Data received, yet to write an actual authenticator")

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
		startconn = False
		datastream = False
