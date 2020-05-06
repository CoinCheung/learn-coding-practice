#! /usr/local/bin/python3
#-*- coding: utf8 -*-
# filename: client.py


##### with INET(TCP or UDP) communication

import socket

server_addr_file = ('127.0.0.1',4000)

## establish client socket
client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
client_socket.connect(server_addr_file)

## send the request and receive the response
client_socket.sendall('client: this is a request from client'.encode('utf8'))
message = client_socket.recv(1024)
print(message)

client_socket.close()


#########################################
## with UNIX IPC

#  import socket
#  import os
#
#  server_addr_file = ''.join([os.getcwd(),os.path.sep,'socket_file'])
#
#  ## establish client socket
#  client_socket = socket.socket(socket.AF_UNIX, socket.SOCK_STREAM)
#  client_socket.connect(server_addr_file)
#
#  ## send the request and receive the response
#  client_socket.sendall('client: this is a request from client'.encode('utf8'))
#  message = client_socket.recv(1024)
#  print(message)
#
#  client_socket.close()
