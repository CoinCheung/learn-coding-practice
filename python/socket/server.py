#!/usr/local/bin/python3
#-*- coding:utf8 -*-
# filename: server.py

##### with INET(TCP or UDP) communication

import socket

## establish server socket, and start listening
socket_server = socket.socket(socket.AF_INET,socket.SOCK_STREAM) # TCP 网络
socket_server.bind(('0.0.0.0',4000))
socket_server.listen(5)
socket_client, client_addr = socket_server.accept()

## recieve message from client and send response
client_message = socket_client.recv(1024)
print('%s'%client_message)
socket_client.send('server: message recieved, thanks'.encode('utf8'))

## close the socket
socket_server.close()
socket_client.close()

#########################################
## with AF_UNIX(IPC) communication


#  import socket
#  import os
#
#
#  server_addr_file = ''.join([os.getcwd(),os.path.sep,'socket_file'])
#  os.unlink(server_addr_file)
#
#  ## establish a server socket, and start listening
#  socket_server = socket.socket(socket.AF_UNIX,socket.SOCK_STREAM) # UNIX IPC
#  socket_server.bind(server_addr_file)
#  socket_server.listen(5)
#  socket_client, client_addr = socket_server.accept()
#
#
#  ## recieve message from client and send response
#  client_message = socket_client.recv(1024)
#  print('%s'%client_message)
#  socket_client.send('server: message recieved, thanks'.encode('utf8'))
#
#  ## close the socket
#  socket_server.close()
#  socket_client.close()
