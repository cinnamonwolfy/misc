#!/usr/bin/python3
#
# server-login.py, A server-side login checker
# (c) 2021 pocketlinux32, Under GPLv3
#
# This script requires the setuid bit to be set to
# function properly. Or you could just run it as root.
#

import sys, crypt, spwd, os

def checkLoginCred(user, passwd):
	hashed_passwd = spwd.getspnam(user)[1]
	if crypt.crypt(passwd, hashed_passwd) == hashed_passwd:
		exit(0)
	exit(2)

if __name__ == "__main__":
	if len(sys.argv) < 3:
		print("Usage: " + sys.argv[0] + " [username] [password]")
		exit(1)
	checkLoginCred(sys.argv[1], sys.argv[2])
