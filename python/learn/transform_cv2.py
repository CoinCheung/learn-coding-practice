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
        sw, sh = int(random.random()*(w-W)), int(random.random()*(h-H))
        crop = int(sw), int(sh), int(sw) + W, int(sh) + H
        return dict(
            im=im[sh:sh+H, sw:sw+W, :],
            lb=lb[sh:sh+H, sw:sw+W]
        )


class RandomHorizontalFlip(object):
    def __init__(self, p=0.5):
        self.p = p

    def __call__(self, im_lb):
        if random.random() > self.p:
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
            im=cv2.resize(im, (w, h)),
            lb=cv2.resize(lb, (w, h), cv2.INTER_NEAREST),
        )


class RandomEqualization(object):
    def __init__(self, p=0.5):
        self.p = p

    def __call__(self, im_lb):
        im, lb = im_lb['im'], im_lb['lb']
        assert im.shape[:2] == lb.shape[:2]
        yuv = cv2.cvtColor(im, cv2.COLOR_BGR2YUV)
        yuv[:, :, 0] = cv2.equalizeHist(yuv[:, :, 0])
        im = cv2.cvtColor(yuv, cv2.COLOR_YUV2BGR)
        return dict(im=im, lb=lb,)


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
            rate = random.uniform(*self.brightness)
            im = self.adj_brightness(im, rate)
        if not self.contrast is None:
            rate = random.uniform(*self.contrast)
            im = self.adj_contrast(im, rate)
        if not self.saturation is None:
            rate = random.uniform(*self.saturation)
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
        H, W, _ = im.shape
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
        im = im.transpose(2, 0, 1).astype(np.float32)
        im = torch.from_numpy(im).div_(255)
        norm = lambda t, m, s: t.sub_(m).div_(s)
        list(map(norm, im, self.mean, self.std))
        lb=torch.from_numpy(lb.astype(np.int64))
        return dict(im=im, lb=lb)


class Compose(object):
    def __init__(self, do_list):
        self.do_list = do_list

    def __call__(self, im_lb):
        for comp in self.do_list:
            im_lb = comp(im_lb)
        return im_lb




if __name__ == '__main__':
    flip = HorizontalFlip(p = 1)
    crop = RandomCrop((321, 321))
    rscales = RandomScale((0.75, 1.0, 1.5, 1.75, 2.0))
    img = Image.open('data/img.jpg')
    lb = Image.open('data/label.png')
