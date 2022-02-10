#!/usr/bin/python3
#
# PocketRLAP Client, a Remote Login-Auth Protocol client
# (c)2022 pocketlinux32, Under GPLv3
# Version 0.01, Reference implementation
#

import socket

bport = 25765
rlapver = b'1.0'
socksend = socket.socket()
isconnected = False
datastream = False
isrlap = False

def packetSender(data):
	global socksend

	if len(b'RLAP CLIENT ' + rlapver + b'\n' + data) < 4096:
		socksend.send(b'RLAP CLIENT ' + rlapver + b'\n' + data)

def packetParser(data):
	global isconnected
	global datastream
	global rlapver
	global isrlap

	packetbuf = b''
	entrynum = 0

	if len(data) == 0:
		return -1

	packettokens = data.split(b'\n')

	for datatoken in packettokens:
		datatokens = datatoken.split()

		if not isrlap:
			if datatokens[0] != b'RLAP':
				print("RLAP Error 1: Incompatible protocol")
				packetSender(b'E1: RLAP_ERR_INCOMPAT_PROT\nRLAP_ENDCONN')
				return 1
			else:
				if datatokens[1] != b'SERVER' or datatokens[2] != rlapver:
					print("RLAP Error 2: Incompatible version")
					packetSender(b'E2: RLAP_ERR_INCOMPAT_VER\nRLAP_ENDCONN')
					return 2
				else:
					print("Packet from server is an RLAP packet from a compatible server")
					isrlap = True
		else:
			if datatokens[0] == b'RLAP_STARTCONN':
				print("Server accepted the connection")
				isconnected = True
			elif datatokens[0] == b'RLAP_STARTLIST':
				if not datastream:
					print("Server has started a Data Stream")
					datastream = True
				else:
					print("RLAP Warning 1: Data Stream already started")
			elif datatokens[0] == b'RLAP_ENDLIST':
				if datastream:
					print("Server has ended a Data Stream")
					datastream = False
				else:
					print("RLAP Warning 2: Data Stream already ended")
			elif datatokens[0] == b'RLAP_ENDCONN':
				print("Server requested to end connection")
				return -1
			elif chr(datatokens[0][0]) == 'E' and datatokens[0] != b'ENTRY':
				print("Server had a protocol error")
				return -1
			else:
				print("Auth data received. Parsing...")
				if datatokens[0] != b'ENTRY' or datatokens[2] != b'USER':
					print("RLAP Error 3: Invalid data")
					packetSender(b'E3: RLAP_ERR_INV_DATA\nRLAP_ENDCONN')
					return 3

				print("Entry", datatokens[1])
				print("Does user exist:", datatokens[3])
				if datatokens[3] == b'YES':
					print("Is password correct:", datatokens[5])
	return 0

if __name__ == "__main__":
	socksend.bind(("localhost", 25765))
	socksend.connect(("127.0.0.1", 25755))
	print("PocketRLAP Client, v0.01")
	print("(c)2022 pocketlinux32, Under GPLv3")
	print("Connected to host 127.0.0.1 on port 25755")
	try:
		databuf = b''
		while True:
			retainInInputLoop = False
			print("Waiting for packet...")
			isrlap = False
			recdata = socksend.recv(4096).replace(b'\\n', b'\n')
			if packetParser(recdata):
				raise KeyboardInterrupt("The parser errored out and this program stops when it detects a KeyboardInterrupt, so...")
			retainInInputLoop = True
			while retainInInputLoop:
				data = input("Send some data:").replace('\\n', '\n')
				if data == 'send':
					packetSender(databuf)
					retainInInputLoop = False
				elif data == 'clear':
					databuf = b''
				else:
					if data.find('\n') != -1:
						databuf += bytearray(data, "utf-8")
					else:
						databuf += bytearray(data, "utf-8") + b'\n'

	except KeyboardInterrupt:
		socksend.close()
		print("Disconnected from server")
		print("Exiting...")
		exit(0)

