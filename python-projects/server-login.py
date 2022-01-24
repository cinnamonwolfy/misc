#!/usr/bin/python3
#
# server-login.py, A server-side login checker (daemon)
# (c) 2021-2022 pocketlinux32, Under GPLv3
#
# This script requires to be ran as root.
#

import sys, crypt, spwd, os, socket

def checkLoginCred(user, passwd):
	hashed_passwd = spwd.getspnam(user)[1]
	if crypt.crypt(passwd, hashed_passwd) == hashed_passwd:
		exit(0)
	exit(2)

def parsePacket(data):
	

if __name__ == "__main__":
	sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
	sock.bind("localhost", 25664)
	sock.listen(5)
	while true:
		()
