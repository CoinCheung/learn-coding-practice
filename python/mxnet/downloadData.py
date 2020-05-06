#!/usr/bin/python
# filename: downloadData.py

import os
import tarfile
from mxnet import gluon

data_root = '/home/coin/.mxnet/datasets'
voc_root = data_root + '/VODdevkit/VOC2012'
url = ('http://host.robots.ox.ac.uk/pascal/VOC/voc2012''/VOCtrainval_11-May-2012.tar')
sha1 = '4e443f8a2eca6b1dac8a6c57641b67dd40621a49'

fname = gluon.utils.download(url, data_root, sha1_hash=sha1)

if not os.path.isfile(voc_root + '/ImageSets/Segmentation/train.txt'):
    with tarfile.open(fname, 'r') as f:
        f.extractall(data_root)
