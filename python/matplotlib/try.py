#!/usr/bin/python
# -*- encoding: utf-8 -*-
# filename: try.py


import numpy as np
import matplotlib
import matplotlib.pyplot as plt


x = np.arange(100)
y = np.sin(x)

_, ax = plt.subplots(2,2, num=1)
plt.ion()
ax[0][0].plot(x,y)
ax[0][0].set_title("ddd")
ax[1][0].plot(x,y)
ax[1][0].set_title("ddd")
ax[0][1].plot(x,y)
ax[0][1].set_title("ddd")
ax[1][1].plot(x,y)
ax[1][1].set_title("ddd")
plt.show()


fig = plt.figure(1)
plt.subplot(121)
plt.plot(x,y)
plt.subplot(122)
plt.plot(x,y)
plt.show()
#  plt.ion()

import time
#  time.sleep(2)
plt.pause(0.3)

yy = np.arange(100)
fig = plt.figure(1)
plt.subplot(121)
plt.plot(x,yy)
plt.subplot(122)
plt.plot(x,yy)

time.pause(2)
