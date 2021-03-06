#!/usr/bin/python
# -*- encoding: utf-8 -*-


import random
from PIL import Image
import PIL.ImageEnhance as ImageEnhance
import numpy as np


class RandomCrop(object):
    def __init__(self, size, *args, **kwargs):
        self.size = size

    def __call__(self, im_lb):
        im = im_lb['im']
        lb = im_lb['lb']
        assert im.size == lb.size
        W, H = self.size
        w, h = im.size

        if (W, H) == (w, h): return dict(im=im, lb=lb)
        if w < W or h < H:
            scale = float(W) / w if w < h else float(H) / h
            w, h = int(scale * w + 1), int(scale * h + 1)
            im = im.resize((w, h), Image.BILINEAR)
            lb = lb.resize((w, h), Image.NEAREST)
        sw, sh = random.random() * (w - W), random.random() * (h - H)
        crop = int(sw), int(sh), int(sw) + W, int(sh) + H
        return dict(
            im=im.crop(crop),
            lb=lb.crop(crop)
            )


class HorizontalFlip(object):
    def __init__(self, p=0.5):
        self.p = p

    def __call__(self, im_lb):
        if random.random() > self.p:
            return im_lb
        im = im_lb['im']
        lb = im_lb['lb']
        return dict(
            im=im.transpose(Image.FLIP_LEFT_RIGHT),
            lb=lb.transpose(Image.FLIP_LEFT_RIGHT),
            )


class RandomScale(object):
    def __init__(self, scales=(1, ), *args, **kwargs):
        self.scales = scales

    def __call__(self, im_lb):
        im = im_lb['im']
        lb = im_lb['lb']
        W, H = im.size
        scale = random.choice(self.scales)
        w, h = int(W * scale), int(H * scale)
        return dict(
            im=im.resize((w, h), Image.BILINEAR),
            lb=lb.resize((w, h), Image.NEAREST),
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
        im = im_lb['im']
        lb = im_lb['lb']
        r_brightness = random.uniform(self.brightness[0], self.brightness[1])
        r_contrast = random.uniform(self.contrast[0], self.contrast[1])
        r_saturation = random.uniform(self.saturation[0], self.saturation[1])
        im = ImageEnhance.Brightness(im).enhance(r_brightness)
        im = ImageEnhance.Contrast(im).enhance(r_contrast)
        im = ImageEnhance.Color(im).enhance(r_saturation)
        return dict(im=im, lb=lb,)


class MultiScale(object):
    def __init__(self, scales):
        self.scales = scales

    def __call__(self, img):
        W, H = img.size
        sizes = [(int(W*ratio), int(H*ratio)) for ratio in self.scales]
        imgs = []
        [imgs.append(img.resize(size, Image.BILINEAR)) for size in sizes]
        return imgs


class ChannelDrop(object):
    def __init__(self, fill_value=0):
        self.fill_value = fill_value

    def __call__(self, im_lb):
        im = im_lb['im']
        lb = im_lb['lb']
        assert im.size == lb.size

        arr = np.array(im)
        n_drops = random.randint(0, 2)
        H, W = arr.shape[:2]
        if n_drops == 1:
            channels = random.sample([0, 1, 2], 1)
            arr[:, :, channels[0]] = self.fill_value
            #  arr[:, :, channels[0]] = np.random.randint(0, 256, arr.shape[:2], dtype=np.uint8)
        elif n_drops == 2:
            channels = random.sample([0, 1, 2], 2)
            arr[:, :, channels[0]] = self.fill_value
            arr[:, :, channels[1]] = self.fill_value
            #  arr[:, :, channels[0]] = np.random.randint(0, 256, arr.shape[:2], dtype=np.uint8)
            #  arr[:, :, channels[1]] = np.random.randint(0, 256, arr.shape[:2], dtype=np.uint8)
        im = Image.fromarray(arr)
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

    im = Image.open(imgpth)
    lb = Image.open(lbpth)

    trans = Compose([
        RandomScale([0.5, 0.7]),
        RandomCrop((512, 512)),
        ColorJitter(
            brightness=0.5,
            contrast=0.5,
            saturation=0.5
        ),
        HorizontalFlip(),
    ])

    inten = dict(im=im, lb=lb)
    #  out = trans(inten)
    #  im, lb = out['im'], out['lb']

    import torchvision.transforms as T
    totensor = T.Compose([
        T.ToTensor(),
        T.Normalize(
            (0.406, 0.456, 0.485),
            (0.225, 0.224, 0.229)
        )
    ])
    im = totensor(im)
    print(im.size())
    print(im[0, 502:504, 766:768])
