

import os
import cv2

#  pth = os.environ['HOME'] + '/draw.jpg'
#  pth = '/home/coin/Documents/Work/MZ/projects-bak/GEDeeplab-rollback/data/leftImg8bit/train/aachen/aachen_000086_000019_leftImg8bit.png'
pth = './pic.jpg'

im = cv2.imread(pth)
cv2.imshow('org', im)
cv2.waitKey(0)

cv2.imwrite('pic.jpg', im)

yuv = cv2.cvtColor(im, cv2.COLOR_BGR2YCrCb)
yuv[:, :, 0] = cv2.equalizeHist(yuv[:, :, 0])
im = cv2.cvtColor(yuv, cv2.COLOR_YCrCb2BGR)
cv2.imshow('equ', im)
cv2.waitKey(0)
