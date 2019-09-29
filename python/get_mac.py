import uuid

#  addr = hex(uuid.getnode())[2:]
#  mac = '-'.join(addr[i:i+2] for i in range(0, len(addr), 2))
#  print(mac)

print(hex(uuid.getnode()))
