#!/usr/bin/python3
import socket

if __name__ == "__main__":
	print("Client initialized")
	socksend = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
	socksend.bind(("localhost", 25765))
	socksend.connect(("127.0.0.1", 25755))
	print("Connected to server")
	try:
		while True:
			data = input("Send some data:")
			socksend.send(bytearray(data, "utf-8"))
	except KeyboardInterrupt:
		socksend.shutdown(socket.SHUT_RDWR)
		socksend.close()
		print("Disconnected from server")
		print("Exiting...")
		exit(0)
