#!/usr/bin/python3
# -*- coding: utf8 -*-
# filename: image.py

from PIL import Image

im = Image.new('RGB',(100,100))
im.filename = 'ff'
print(im.filename)
