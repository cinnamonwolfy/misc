#!/usr/bin/python3
#
# PocketRLAP, a Remote Login-Auth Protocol server
# (c)2022 pocketlinux32, Under GPLv3
# Version 0.01, Reference implementation
#
# Notice: To use the internal authenticator, please run this program
# as root or superuser
#

import socket, spwd, crypt

bport = 25755
rlapver = b'1.0'
startconn = False
datastream = False
isrlap = False
connection = ('', '')
address = ('', '')

def internalAuth(user, password, passwdtype):
	try:
		profile = spwd.getspnam(user)
		if passwdtype == b'HASHPASS':
			if password != profile[1]:
				print("InternalAuth: Password is incorrect")
				return 2
		elif passwdtype == b'PLAINPASS':
			if crypt.crypt(password, profile[1]) != profile[1]:
				print("InternalAuth: Password is incorrect")
				return 2
		elif passwdtype == b'SSHPASS':
			print("InternalAuth: Currently unimplemented, still finding a way to make this option secure")
			return 2
		else:
			print("InternalAuth Error: Unrecognized password type")
			return 3

		return 0
	except KeyError:
		print("InternalAuth: User is non-existent")
		return 1

def packetSender(data):
	global connection

	if len(b'RLAP SERVER ' + rlapver + b'\n' + data) < 4096:
		connection.send(b'RLAP SERVER ' + rlapver + b'\n' + data)

def packetParser(data):
	global startconn
	global datastream
	global address
	global rlapver
	global isrlap

	packetbuf = b''
	entrynum = 0

	if len(data) == 0:
		return -1

	packettokens = data.split(b'\n')

	for datatoken in packettokens:
		datatokens = datatoken.split()
		if len(datatokens) == 0:
			break

		if not isrlap:
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
					print("Packet from host", address[0], "is an RLAP packet from a compatible client")
					isrlap = True
		else:
			if datatokens[0] == b'RLAP_STARTCONN':
				print("Host", address[0], "acknowledged the connection")
				startconn = True
			elif datatokens[0] == b'RLAP_STARTLIST':
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
			elif chr(datatokens[0][0]) == 'E':
				print("Host had a protocol error")
				return -1
			else:
				print("Login data received, validating...")
				if len(datatokens) != 4 or datatokens[0] != b'USER' or datatokens[2].find(b'PASS') == -1:
					print("RLAP Error 3: Invalid data")
					packetSender(b'E3: RLAP_ERR_INV_DATA\nRLAP_ENDCONN')
					return 3
				else:
					print("Login data validated. Passed over to InternalAuth")
					entrynum = entrynum + 1
					retval = internalAuth(datatokens[1].decode(), datatokens[3].decode(), datatokens[2])
					if retval == 0:
						packetbuf += b'ENTRY ' + bytearray(str(entrynum), 'utf-8') + b' USER YES PASS YES\n'
					elif retval == 1:
						packetbuf += b'ENTRY ' + bytearray(str(entrynum), 'utf-8') + b' USER NO\n'
					elif retval == 2:
						packetbuf += b'ENTRY ' + bytearray(str(entrynum), 'utf-8') + b' USER YES PASS NO\n'
					else:
						print("RLAP Error 4: InternalAuth had an error")
						packetSender(b'E4: RLAP_ERR_INTAUTH_ERR\nRLAP_ENDCONN')
						return 4

	if packetbuf != b'':
		packetSender(b'RLAP_STARTLIST\n' + packetbuf + b'RLAP_ENDLIST\nRLAP_ENDCONN')

	return 0

if __name__ == "__main__":
	socklisten = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
	socklisten.bind(("localhost", bport))
	socklisten.listen(10)
	print("PocketRLAP Server, v0.01")
	print("(c)2022 pocketlinux32, Under GPLv3")
	print("Server initialized on port", bport)
	while True:
		try:
			data = b'begin'
			(connection, address) = socklisten.accept()
			print("Connection established with host", address[0], "on port", address[1])
			packetSender(b'RLAP_STARTCONN')

			while data:
				isrlap = False
				data = connection.recv(4096).replace(b'\\n', b'\n')
				if packetParser(data):
					break

			print("Ended connection with host", address[0])
			connection.shutdown(socket.SHUT_RDWR)
			connection.close()
			startconn = False
			datastream = False
		except KeyboardInterrupt:
			print("Keyboard Interrupt detected")
			print("Shutting down socket...")
			socklisten.shutdown(socket.SHUT_RDWR)
			socklisten.close()
			print("Exiting...")
			exit(0)
