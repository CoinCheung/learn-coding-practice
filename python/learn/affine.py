import numpy as np
import cv2


imgpth = '/home/coin/Documents/Work/MZ/projects-bak/GEDeeplab-rollback/data/leftImg8bit/train/aachen/aachen_000086_000019_leftImg8bit.png'
im = cv2.imread(imgpth)
im = cv2.resize(im, (1024, 512))
H, W, _ = im.shape

cv2.imshow('org', im)
r_shearx = 0.2
r_sheary = 0.0
M1 = np.float32([[-1, 0, W-1], [0, 1, 0], [0, 0, 1]])
M2 = np.float32([[1, r_shearx, -int(r_shearx*H)//2], [r_sheary, 1, -int(r_sheary*W)//2], [0, 0, 1]])


M = np.matmul(M1, M2)
#  M = M1 + M2
M = M[:2]
aff = cv2.warpAffine(im, M, (W, H))
cv2.imshow('affine', aff)

aff1 = cv2.warpAffine(im, M1[:2], (W, H))
aff2 = cv2.warpAffine(aff1, M2[:2], (int(1.0*W), int(1.0*H)))
cv2.imshow('affine2', aff2)
cv2.waitKey(0)

print(np.sum(aff2 - aff))
