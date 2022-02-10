#!/usr/bin/python3
#
# PocketRLAP Client, a Remote Login-Auth Protocol client
# (c)2022 pocketlinux32, Under GPLv3
# Version 0.01, Reference implementation
#

import socket

bport = 25765
connection = ('', '')
address = ('', '')
rlapver = b'0.01'
isconnected = False
datastream = False

def packetSender(data):
	global connection

	if len(b'RLAP CLIENT ' + rlapver + b'\n' + data) < 4096:
		connection.send(b'RLAP CLIENT ' + rlapver + b'\n' + data)

def packetParser(data):
	global isconnected
	global datastream
	global address
	global rlapver

if __name__ == "__main__":
	socksend = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
	socksend.bind(("localhost", 25765))
	socksend.connect(("127.0.0.1", 25755))
	print("PocketRLAP Client, v0.01")
	print("(c)2022 pocketlinux32, Under GPLv3")
	print("Connected to host 127.0.0.1 on port 25755")
	try:
		databuf = b''
		while True:
			print("Waiting for packet...")
			recdata = socksend.recv(4096)
			packetParser(recdata)
			data = input("Send some data:").replace('\\n', '\n')
			if data == 'send':
				socksend.send(databuf)
			else:
				databuf += bytearray(data, "utf-8")
	except KeyboardInterrupt:
		socksend.shutdown(socket.SHUT_RDWR)
		socksend.close()
		print("Disconnected from server")
		print("Exiting...")
		exit(0)

