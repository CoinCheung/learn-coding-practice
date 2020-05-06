#!/usr/bin/python
# -*- encoding: utf-8 -*-


import os
import random
from lxml import etree


## TODO: start from downloading the datasets


root_path = os.path.expandvars('$HOME') + '/.mxnet/datasets/VOCdevkit/VOC2012/'
xml_path = root_path + '/Annotations/'



class Sample(object):
    def __init__(self, img_path, ann_lst):
        self.img_path = img_path
        self.ann_lst = ass_lst


class DataIter(object):
    def __init__(self, name_path, ann_dir, img_dir):
        self.name_path = name_path
        self.ann_dir = ann_dir
        self.img_dir = img_dir
        self.pos = 0
        self.samples = self.get_samples()

    def get_samples(self):
        with open(self.name_path, 'r') as rf:
            fns = rf.read().split('\n')
        img_fns = [''.join([self.img_dir, el, '.jpg']) for el in fns]
        ann_fns = [''.join([self.ann_dir, el, '.xml']) for el in fns]
        list(map(self.make_one_sample, img_fns, ann_fns))

        #  print(len(fns))
        #  print(fns[0:10])
        #  print(len(ann_fns))
        #  print(ann_fns[0:10])
        #  print(len(img_fns))
        #  print(img_fns[0:10])

    def make_one_sample(self, img_fn, ann_fn):
        xml_par = etree.parse(ann_fn)
        root = xml_par.getroot()
        pass

    def reset(self):
        self.pos = 0
        random.shuffle(self.samples)

    def get_next(self):
        pass

    def shuffle(self):
        pass


def main():

    root_path = os.path.expandvars('$HOME') + '/.mxnet/datasets/VOCdevkit/VOC2012/'
    train_path = root_path + '/ImageSets/Main/train.txt'
    ann_dir = root_path + '/Annotations/'
    img_dir = root_path + '/JPEGImages/'

    train_it = DataIter(train_path, ann_dir, img_dir)



if __name__ == '__main__':
    #  ar = dict(zip([1,2,3,4,5], [1,2,3,4,5]))
    ar = [1,2,3,4,5]
    random.shuffle(ar)
    print(ar)
    main()
