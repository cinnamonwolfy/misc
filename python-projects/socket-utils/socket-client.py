#!/usr/bin/python3
import socket

if __name__ == "__main__":
	print("Client initialized")
	socksend = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
	socksend.bind(("localhost", 25765))
	socksend.connect(("127.0.0.1", 25755))
	print("Connected to server")
	
