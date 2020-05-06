import numpy as np
import cv2


###
# affine
###
imgpth = '/home/coin/Documents/Work/MZ/projects-bak/GEDeeplab-rollback/data/leftImg8bit/train/aachen/aachen_000086_000019_leftImg8bit.png'
#  im = cv2.imread(imgpth)
#  im = cv2.resize(im, (1024, 512))
#  H, W, _ = im.shape
#
#  cv2.imshow('org', im)
#  r_shearx = 0.2
#  r_sheary = 0.0
#  M1 = np.float32([[-1, 0, W-1], [0, 1, 0], [0, 0, 1]])
#  M2 = np.float32([[1, r_shearx, -int(r_shearx*H)//2], [r_sheary, 1, -int(r_sheary*W)//2], [0, 0, 1]])
#
#
#  M = np.matmul(M1, M2)
#  #  M = M1 + M2
#  M = M[:2]
#  aff = cv2.warpAffine(im, M, (W, H))
#  cv2.imshow('affine', aff)
#
#  aff1 = cv2.warpAffine(im, M1[:2], (W, H))
#  aff2 = cv2.warpAffine(aff1, M2[:2], (int(1.0*W), int(1.0*H)))
#  cv2.imshow('affine2', aff2)
#  cv2.waitKey(0)
#
#  print(np.sum(aff2 - aff))

###
#
###
from PIL import ImageOps
from PIL import Image
im = Image.open(imgpth)
impil = np.array(im)
imcv = cv2.imread(imgpth)[:, :, ::-1].copy()
print(np.sum(imcv - impil))

#  impil_invert = np.array(ImageOps.invert(im))
#  imcv_invert = 255 - imcv
#  print(np.sum(impil_invert - imcv_invert))
#  # 结论1: invert就是255减去每一个像素

#  impil_sol = np.array(ImageOps.solarize(im, threshold=128))
#  imcv_sol = imcv.copy()
#  #  gray = cv2.imread(imgpth, 0)
#  idx = imcv >= 128
#  print(idx.shape)
#  imcv_sol[idx] = 255 - imcv_sol[idx]
#  print(np.sum(impil_sol - imcv_sol))

#  bits = 5
#  impil_pos = np.array(ImageOps.posterize(im, bits))
#  imcv_pos = np.bitwise_and(imcv, np.uint8(255<<(8-bits)))
#  print(np.sum(impil_pos - imcv_pos))
#  ## 结论3: posterize的做法

#  from PIL import ImageEnhance
#  enhancer = ImageEnhance.Sharpness(im)
#  en_pil = enhancer.enhance(2.)

#  from PIL import ImageFilter
#  impil_fil = np.array(im.filter(ImageFilter.SMOOTH))
#
#  kernel = np.ones((3, 3), dtype=np.float32)
#  kernel[1, 1] = 5
#  kernel /= 13
#  imcv_fil = cv2.filter2D(imcv, -1, kernel)
#
#  print(np.sum(imcv_fil - impil_fil))
#  print(np.where(imcv_fil != impil_fil)[0].shape)
#  print(imcv_fil[0][1][0])
#  print(impil_fil[0][1][0])

#  h, s, v = im.convert("HSV").split()
#  h_pil = np.array(h, dtype=np.uint8)
#  hsv = cv2.cvtColor(cv2.imread(imgpth), cv2.COLOR_BGR2HSV)
#  h_cv = hsv[:, :, 0]
#  print(np.sum(h_cv - h_pil))
#  print(h_cv[:3, :3])
#  print(h_pil[:3, :3])

####
#  im_pil = np.array(im.convert("L").convert("RGB"))
#  im_cv = cv2.cvtColor(imcv, cv2.COLOR_RGB2HLS)
#  L = im_cv[:, :, 1]
#  im_cv = cv2.merge([L, L, L])
#  #  im_cv = cv2.cvtColor(cv2.cvtColor(imcv, cv2.COLOR_RGB2GRAY), cv2.COLOR_GRAY2RGB)

## convert to gray
#  im_pil = np.array(Image.open(imgpth).convert("L"))
#  im_cv = cv2.cvtColor(cv2.imread(imgpth), cv2.COLOR_BGR2GRAY)
#  print(np.sum(im_pil - im_cv))
#
#  ## convert to hsv
#  im_pil = np.array(Image.open(imgpth).convert("HSV").split()[0])
#  im_cv = cv2.cvtColor(cv2.imread(imgpth), cv2.COLOR_BGR2HSV)[:, :, 0]
#  print(np.sum(im_pil - im_cv))


im = Image.open(imgpth)
impil = np.array(im)
im1 = impil[:512, :1024, :]
im2 = impil[512:, 1024:, :]
impil1 = Image.fromarray(im1)
impil2 = Image.fromarray(im2)
im_pil_m = np.array(Image.blend(impil1, impil2, 0.1))

im_cv_m = cv2.addWeighted(im1, 0.9, im2, 0.1, 0)
#  im_cv_m = ((im1/255. * 0.9 + im2/255. * 0.1) * 255).astype(np.uint8)

print(np.sum(im_cv_m - im_pil_m))
print(im_cv_m[:3, :3, 0])
print(im_pil_m[:3, :3, 0])
#
#  print(len(im.histogram()))
#  print()
#  cv2.histogram(impil)
