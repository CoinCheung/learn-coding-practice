#!/usr/bin/python
# -*- encoding: utf-8 -*-


import random

import numpy as np
import cv2
import torch


'''
    im are expected to have shape of (H, W, C), and channel order is bgr, which is the standard opencv settings
'''

class RandomCrop(object):
    '''
    size should be a tuple of (H, W)
    '''
    def __init__(self, size):
        self.size = size

    def __call__(self, im_lb):
        im, lb = im_lb['im'], im_lb['lb']
        assert im.shape[:2] == lb.shape[:2]
        H, W = self.size
        h, w, _ = im.shape

        if (W, H) == (w, h): return dict(im=im, lb=lb)
        if w < W or h < H:
            scale = float(W) / w if w < h else float(H) / h
            w, h = int(scale * w + 1), int(scale * h + 1)
            im = cv2.resize(im, (w, h))
            lb = cv2.resize(lb, (w, h), interpolation=cv2.INTER_NEAREST)
        sw, sh = np.random.random(2)
        sw, sh = int(sw*(w-W)), int(sh*(h-H))
        return dict(
            im=im[sh:sh+H, sw:sw+W, :].copy(),
            lb=lb[sh:sh+H, sw:sw+W].copy()
        )


class RandomHorizontalFlip(object):

    def __init__(self, p=0.5):
        self.p = p

    def __call__(self, im_lb):
        if np.random.random() < self.p:
            return im_lb
        im, lb = im_lb['im'], im_lb['lb']
        assert im.shape[:2] == lb.shape[:2]
        return dict(
            im=im[:, ::-1, :],
            lb=lb[:, ::-1],
        )


class RandomScale(object):

    def __init__(self, scales=(1, )):
        self.scales = scales

    def __call__(self, im_lb):
        im, lb = im_lb['im'], im_lb['lb']
        assert im.shape[:2] == lb.shape[:2]
        H, W, _ = im.shape
        scale = random.choice(self.scales)
        w, h = int(W * scale), int(H * scale)
        return dict(
            im=cv2.resize(im, (w, h)).copy(),
            lb=cv2.resize(lb, (w, h), cv2.INTER_NEAREST).copy(),
        )


class ColorJitter(object):

    def __init__(self, brightness=None, contrast=None, saturation=None):
        if not brightness is None and brightness >= 0:
            self.brightness = [max(1-brightness, 0), 1+brightness]
        if not contrast is None and contrast >= 0:
            self.contrast = [max(1-contrast, 0), 1+contrast]
        if not saturation is None and saturation >= 0:
            self.saturation = [max(1-saturation, 0), 1+saturation]

    def __call__(self, im_lb):
        im, lb = im_lb['im'], im_lb['lb']
        assert im.shape[:2] == lb.shape[:2]
        if not self.brightness is None:
            rate = np.random.uniform(*self.brightness)
            im = self.adj_brightness(im, rate)
        if not self.contrast is None:
            rate = np.random.uniform(*self.contrast)
            im = self.adj_contrast(im, rate)
        if not self.saturation is None:
            rate = np.random.uniform(*self.saturation)
            im = self.adj_saturation(im, rate)
        return dict(im=im, lb=lb,)

    def adj_saturation(self, im, rate):
        M = np.float32([
            [1+2*rate, 1-rate, 1-rate],
            [1-rate, 1+2*rate, 1-rate],
            [1-rate, 1-rate, 1+2*rate]
        ])
        shape = im.shape
        im = np.matmul(im.reshape(-1, 3), M).reshape(shape)/3
        im = np.clip(im, 0, 255).astype(np.uint8)
        return im

    def adj_brightness(self, im, rate):
        table = np.array([
            i * rate for i in range(256)
        ]).clip(0, 255).astype(np.uint8)
        return cv2.LUT(im, table)

    def adj_contrast(self, im, rate):
        table = np.array([
            74 + (i - 74) * rate for i in range(256)
        ]).clip(0, 255).astype(np.uint8)
        return cv2.LUT(im, table)



class RandomChannelDrop(object):

    def __init__(self, fill_value=0):
        self.fill_value = fill_value

    def __call__(self, im_lb):
        im, lb = im_lb['im'], im_lb['lb']
        assert im.shape[:2] == lb.shape[:2]

        n_drops = random.randint(0, 2)
        #  H, W, _ = im.shape
        if n_drops == 1:
            channels = random.sample([0, 1, 2], 1)
            im[:, :, channels[0]] = self.fill_value
            #  im[:, :, channels[0]] = np.random.randint(
            #      0, 256, (H, W), dtype=np.uint8
            #  )
        elif n_drops == 2:
            channels = random.sample([0, 1, 2], 2)
            im[:, :, channels[0]] = self.fill_value
            im[:, :, channels[1]] = self.fill_value
            #  im[:, :, channels[0]] = np.random.randint(
            #      0, 256, (H, W), dtype=np.uint8
            #  )
            #  im[:, :, channels[1]] = np.random.randint(
            #      0, 256, (H, W), dtype=np.uint8
            #  )
        return dict(im=im, lb=lb)


class RandomEqualize(object):

    def __init__(self, p=0.2):
        self.p = p

    def __call__(self, im_lb):
        im, lb = im_lb['im'], im_lb['lb']
        assert im.shape[:2] == lb.shape[:2]
        if np.random.random() < self.p:
            yuv = cv2.cvtColor(im, cv2.COLOR_BGR2YCrCb)
            yuv[:, :, 0] = cv2.equalizeHist(yuv[:, :, 0])
            im = cv2.cvtColor(yuv, cv2.COLOR_YCrCb2BGR)
        return dict(im=im, lb=lb)


class RandomShear(object):

    def __init__(self, p=0.5, rate=0.3):
        self.p = p
        self.rate = rate

    def __call__(self, im_lb):
        im, lb = im_lb['im'], im_lb['lb']
        assert im.shape[:2] == lb.shape[:2]
        p, direction = np.random.random(2)
        if p < self.p:
            m = np.random.uniform(-self.rate, self.rate)
            print(m)
            H, W, _ = im.shape
            if direction < 0.5:
                M = np.float32([[1, m, -int(m*H)//2], [0, 1, 0]])
            else:
                M = np.float32([[1, 0, 0], [m, 1, -int(m*W)//2]])
            im = cv2.warpAffine(im, M, (W, H)).astype(np.uint8)
            lb = cv2.warpAffine(
                lb, M, (W, H), borderValue=255, flags=cv2.INTER_NEAREST
            ).astype(np.uint8)
        return dict(im=im, lb=lb)


class RandomRotate(object):

    def __init__(self, p=0.5, degree=0.3):
        self.p = p
        self.rate = degree

    def __call__(self, im_lb):
        im, lb = im_lb['im'], im_lb['lb']
        assert im.shape[:2] == lb.shape[:2]
        if np.random.random() < self.p:
            H, W, _ = im.shape
            m = np.random.uniform(-self.rate, self.rate)
            M = cv2.getRotationMatrix2D((W/2, H/2), m, 1.)
            im = cv2.warpAffine(im, M, (W, H)).astype(np.uint8)
            lb = cv2.warpAffine(
                lb, M, (W, H), borderValue=255, flags=cv2.INTER_NEAREST
            ).astype(np.uint8)
        return dict(im=im, lb=lb)


class ChannelShuffle(object):

    def __init__(self, p=0):
        self.p = p

    def __call__(self, im_lb):
        im, lb = im_lb['im'], im_lb['lb']
        assert im.shape[:2] == lb.shape[:2]
        if np.random.random() < self.p:
            idx = np.array([0, 1, 2], dtype=np.int64)
            np.random.shuffle(idx)
            im = im[:, :, idx].astype(np.uint8)
        return dict(im=im, lb=lb)


class RandomErasing(object):

    def __init__(self, p=0, size=(16, 16)):
        self.p = p
        self.size = size

    def __call__(self, im_lb):
        im, lb = im_lb['im'], im_lb['lb']
        assert im.shape[:2] == lb.shape[:2]
        H, W, _ = im.shape
        h, w = self.size
        if h > H or w > W: return im_lb

        if np.random.random() < self.p:
            sw, sh = np.random.random(2)
            sw, sh = int(sw*(W-w)), int(sh*(H-h))
            im[sh:sh+h, sw:sw+w, :] = (
                np.random.random(3*w*h)*255).reshape(h, w, 3).astype(np.uint8)
        return dict(im=im, lb=lb)


class RandomShearRotate(object):

    def __init__(self, p_shear=0, p_rot=0, rate_shear=0.3, rot_degree=0.3):
        self.p_shear = p_shear
        self.p_rot = p_rot
        self.rate_shear = rate_shear
        self.rate_rot = rot_degree

    def __call__(self, im_lb):
        im, lb = im_lb['im'], im_lb['lb']
        assert im.shape[:2] == lb.shape[:2]
        H, W, _ = im.shape
        M = np.eye(3, dtype=np.float32)
        if np.random.random() < self.p_rot:
            m = np.random.uniform(-self.rate_rot, self.rate_rot)
            M1 = np.eye(3, dtype=np.float32)
            M1[:2] = cv2.getRotationMatrix2D((W/2, H/2), m, 1.)
            M = np.matmul(M1, M)

        p_shear, direction = np.random.random(2)
        if p_shear < self.p_shear:
            m = np.random.uniform(-self.rate_shear, self.rate_shear)
            M2 = np.eye(3, dtype=np.float32)
            if direction < 0.5:
                M2[0] = np.array([1, m, -int(m*H)//2])
            else:
                M2[1] = np.array([m, 1, -int(m*W)//2])
            M = np.matmul(M2, M)
        M = M[:2]
        im = cv2.warpAffine(im, M, (W, H)).astype(np.uint8)
        lb = cv2.warpAffine(
            lb, M, (W, H), borderValue=255, flags=cv2.INTER_NEAREST
        ).astype(np.uint8)

        return dict(im=im, lb=lb)


class RandomHFlipShearRotate(object):

    def __init__(self, p_flip=0.5, p_shear=0, p_rot=0, rate_shear=0.3, rot_degree=0.3):
        self.p_flip = p_flip
        self.p_shear = p_shear
        self.p_rot = p_rot
        self.rate_shear = rate_shear
        self.rate_rot = rot_degree

    def __call__(self, im_lb):
        im, lb = im_lb['im'], im_lb['lb']
        assert im.shape[:2] == lb.shape[:2]
        H, W, _ = im.shape
        M = np.eye(3, dtype=np.float32)
        if np.random.random() < self.p_flip:
            M1 = np.eye(3, dtype=np.float32)
            M1[0] = np.float32([-1, 0, W-1])
            M = np.matmul(M1, M)

        if np.random.random() < self.p_rot:
            M2 = np.eye(3, dtype=np.float32)
            m = np.random.uniform(-self.rate_rot, self.rate_rot)
            M2[:2] = cv2.getRotationMatrix2D((W/2, H/2), m, 1.)
            M = np.matmul(M2, M)

        p_shear, direction = np.random.random(2)
        if p_shear < self.p_shear:
            M3 = np.eye(3, dtype=np.float32)
            m = np.random.uniform(-self.rate_shear, self.rate_shear)
            if direction < 0.5:
                M3[0] = np.array([1, m, -int(m*H)//2])
            else:
                M3[1] = np.array([m, 1, -int(m*W)//2])
            M = np.matmul(M3, M)

        M = M[:2]
        im = cv2.warpAffine(im, M, (W, H)).astype(np.uint8).copy()
        lb = cv2.warpAffine(
            lb, M, (W, H), borderValue=255, flags=cv2.INTER_NEAREST
        ).astype(np.uint8).copy()

        return dict(im=im, lb=lb)


class ToTensor(object):
    '''
    mean and std should be of the channel order 'bgr'
    '''
    def __init__(self, mean=(0, 0, 0), std=(1., 1., 1.)):
        self.mean = mean
        self.std = std

    def __call__(self, im_lb):
        im, lb = im_lb['im'], im_lb['lb']
        assert im.shape[:2] == lb.shape[:2]
        im = im[:, :, ::-1].transpose(2, 0, 1).astype(np.float32) # to rgb order
        im = torch.from_numpy(im).div_(255)
        dtype, device = im.dtype, im.device
        mean = torch.as_tensor(self.mean, dtype=dtype, device=device)[:, None, None]
        std = torch.as_tensor(self.std, dtype=dtype, device=device)[:, None, None]
        im = im.sub_(mean).div_(std).clone()
        lb = torch.from_numpy(lb.astype(np.int64)).clone()
        return dict(im=im, lb=lb)


class Compose(object):
    def __init__(self, do_list):
        self.do_list = do_list

    def __call__(self, im_lb):
        for comp in self.do_list:
            im_lb = comp(im_lb)
        return im_lb




if __name__ == '__main__':
    imgpth = '/home/coin/Documents/Work/MZ/projects-bak/GEDeeplab-rollback/data/leftImg8bit/train/aachen/aachen_000086_000019_leftImg8bit.png'
    lbpth = '/home/coin/Documents/Work/MZ/projects-bak/GEDeeplab-rollback/data/gtFine/train/aachen/aachen_000086_000019_gtFine_labelIds.png'
    #  from PIL import Image
    #  im = Image.open(imgpth)
    #  lb = Image.open(lbpth)
    #  print(lb.size)
    #  im.show()
    #  lb.show()
    import cv2
    im = cv2.imread(imgpth)
    lb = cv2.imread(lbpth, 0)
    lb = lb * 10

    trans = Compose([
        RandomHorizontalFlip(),
        RandomShear(p=0.5, rate=3),
        RandomRotate(p=0.5, degree=5),
        RandomScale([0.5, 0.7]),
        RandomCrop((768, 768)),
        RandomErasing(p=1, size=(36, 36)),
        ChannelShuffle(p=1),
        ColorJitter(
            brightness=0.3,
            contrast=0.3,
            saturation=0.5
        ),
        #  RandomEqualize(p=0.1),
    ])
    #  inten = dict(im=im, lb=lb)
    #  out = trans(inten)
    #  im = out['im']
    #  lb = out['lb']
    #  cv2.imshow('lb', lb)
    #  cv2.imshow('org', im)
    #  cv2.waitKey(0)


    ### try merge rotate and shear here
    im = cv2.imread(imgpth)
    lb = cv2.imread(lbpth, 0)
    im = cv2.resize(im, (1024, 512))
    lb = cv2.resize(lb, (1024, 512), interpolation=cv2.INTER_NEAREST)
    lb = lb * 10
    inten = dict(im=im, lb=lb)
    trans1 = Compose([
        RandomShear(p=1, rate=0.15),
        #  RandomRotate(p=1, degree=10),
    ])
    trans2 = Compose([
        #  RandomShearRotate(p_shear=1, p_rot=0, rate_shear=0.1, rot_degree=9),
        RandomHFlipShearRotate(p_flip=0.5, p_shear=1, p_rot=0, rate_shear=0.1, rot_degree=9),
    ])
    out1 = trans1(inten)
    im1 = out1['im']
    lb1 = out1['lb']
    #  cv2.imshow('lb', lb1)
    cv2.imshow('org1', im1)
    out2 = trans2(inten)
    im2 = out2['im']
    lb2 = out2['lb']
    #  cv2.imshow('lb', lb1)
    #  cv2.imshow('org2', im2)
    cv2.waitKey(0)
    print(np.sum(im1-im2))
    print('====')
    ####


    totensor = ToTensor(
        mean=(0.406, 0.456, 0.485),
        std=(0.225, 0.224, 0.229)
    )
    #  print(im[0, :2, :2])
    print(lb[:2, :2])
    out = totensor(out)
    im = out['im']
    lb = out['lb']
    print(im.size())
    #  print(im[0, :2, :2])
    #  print(lb[:2, :2])

    out = totensor(inten)
    im = out['im']
    print(im.size())
    print(im[0, 502:504, 766:768])

