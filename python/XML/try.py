#!/usr/bin/python
# -*- encoding: utf-8 -*-
# filename: xmlpro001.py


import os
from lxml import etree


path1 = "".join([os.getcwd(), "/D3203_BMS_AR2BSW_DSMCTR.arxml"])

xmlparse = etree.parse(path1)

root = xmlparse.getroot()

node = root.getchildren()[0]
print(node.tag)
