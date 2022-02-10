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

	

if __name__ == '__main__':
	
