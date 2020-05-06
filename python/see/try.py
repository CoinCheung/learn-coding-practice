
import cv2
import numpy as np
import pickle

impth = './02_03_03_144.jpg'
respth = './res.pkl'

with open(respth, 'rb') as fr:
    res = pickle.load(fr)

im = cv2.imread(impth)
#  cv2.imshow('org', im)
#  cv2.waitKey(0)

print(res)
for el in res:
    if el.shape[0] == 0: continue
    coors = el[:, :4]
    for xys in coors:
        xys = xys.astype(np.int64).tolist()
        x1, y1, x2, y2 = xys
        #  xys = xys.tolist()
        #  print(xys.tolist()[:2])
        #  cv2.rectangle(im, xys[:2], xys[2:], (155, 0, 0), 3)
        cv2.rectangle(im, (x1, y1), (x2, y2), (155, 0, 0), 3)

im = cv2.resize(im, (768, 768))
cv2.imshow('draw', im)
cv2.waitKey(0)
