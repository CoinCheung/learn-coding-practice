
import time
import base64
import requests

bd_url = 'http://10.128.122.172:20039/griddefectdetection/substation'
sd_url = 'http://10.128.122.172:20039/griddefectdetection/powerline'

with open('./1_070323.jpg', 'rb') as fr:
    img_base64 = base64.b64encode(fr.read())
data = {
    "app_id": "system",
    "app_secret": "12345",
    "img": img_base64,
}

#  for i in range(20):
#      req = requests.post(sd_url, data)
#      req = requests.post(sd_url, data)
#  print(req)

n_reqs = 50
t1 = time.time()
for i in range(n_reqs):
    req = requests.post(bd_url, data)
for i in range(n_reqs):
    req = requests.post(sd_url, data)
t2 = time.time()
for i in range(n_reqs):
    req = requests.post(bd_url, data)
    req = requests.post(sd_url, data)
t3 = time.time()

print('100 call without model switching time: {}'.format(t2-t1))
print('100 call with model switching time: {}'.format(t3-t2))
