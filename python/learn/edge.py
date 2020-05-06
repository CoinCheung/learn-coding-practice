import os
import os.path as osp
import numpy as np

import cv2
from PIL import Image, ImageFilter
from tqdm import tqdm

#  imroot = './train/'
#
#  folders = os.listdir(imroot)
#  folders = [osp.join(imroot, el) for el in folders]

#  imgs = []
#  for folder in folders:
#      if osp.isfile(folder): continue
#      imgs += [osp.join(folder, el) for el in os.listdir(folder)]
#
#  n_imgs = len(imgs)
#  imgs = imgs[n_imgs*7//8:n_imgs*15//16]
#  for impth in imgs:
#      try:
#          im = Image.open(impth)#.convert('RGB')
#          print(impth)
#          im.close()
#      except Exception as e:
#          print(e)

#  impth = './train/n04152593/n04152593_17460.JPEG'
impth = './n04152593_12111.JPEG'
#  im = Image.open(impth).convert('RGB')
#  label = im.filter(ImageFilter.FIND_EDGES)
#  im.save('im.jpg')
#  label.save('label.jpg')
#  label.convert('1').save('label_01.jpg')
#  gray = label.convert('L')
#  gray.save('label_gray.jpg')
#
#  label = np.array(label)
#  gray = np.array(gray)
#  print(label.shape)
#  print(np.unique(label))
#  print(np.unique(gray))
#  print(label.shape)
#  print(label[:4, :4, :])
#  print(np.sum(label[:,:,0] - label[:,:,1]))
#  cv2.imwrite('one.jpg', label[:, :, 0])
#  cv2.imwrite('two.jpg', label[:, :, 1])
#  cv2.imwrite('three.jpg', label[:, :, 2])
#  cv2.imwrite('two-three.jpg', label[:, :, 1] - label[:, :, 2])
#
#  print(gray.shape)
#  n_classes = 10
#  interval = (255 / (n_classes - 1))
#  gray_map = (gray / interval).astype(np.uint64) # * 25
#  print(np.unique(gray_map))
#  cv2.imwrite('gray_map.jpg', gray_map)
#  print(gray_map.shape)
#

im = cv2.imread(impth)
gray = cv2.cvtColor(im, cv2.COLOR_BGR2GRAY)
th_h, th_im = cv2.threshold(gray, 0, 255, cv2.THRESH_BINARY + cv2.THRESH_OTSU)
th_l = th_h / 2
label = cv2.Canny(im, 200, 300)
#  label = cv2.Canny(im, th_l, th_h)
cv2.imwrite('./res/label.jpg', label)
print(label.shape)

kernel = cv2.getStructuringElement(cv2.MORPH_RECT, (3, 3))
#  erode = cv2.erode((label/255).astype(np.uint8), kernel)
#  cv2.imwrite('./res/erode.jpg', label*255)
#  print(np.unique(erode))
dilate = cv2.dilate((label/255).astype(np.uint8), kernel) * 255
cv2.imwrite('./res/dilate.jpg', dilate)
dilate = cv2.dilate((dilate/255).astype(np.uint8), kernel) * 255
cv2.imwrite('./res/dilatedilate.jpg', dilate)
print(np.unique(dilate))

kernel = cv2.getStructuringElement(cv2.MORPH_RECT, (5, 5))
dilate = cv2.dilate((label/255).astype(np.uint8), kernel) * 255
cv2.imwrite('./res/dilate5.jpg', dilate)
