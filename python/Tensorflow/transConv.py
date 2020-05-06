#!/usr/bin/python
# -*- encoding: utf-8 -*-
# filename: transConv.py


import tensorflow as tf
import numpy as np



##### s=1, p=0
x = tf.Variable(np.arange(9, dtype=np.float32).reshape(3,3))
x = tf.reshape(x, shape=[1,3,3,1])
y = tf.layers.conv2d_transpose(x, 1, [2,2], strides=1, padding='valid', kernel_initializer=tf.ones_initializer())
x_pad = tf.pad(x, tf.constant([[0,0],[1,1],[1,1],[0,0]]))
y_eq = tf.layers.conv2d(x_pad, 1, [2,2], strides=1, padding='valid', kernel_initializer=tf.ones_initializer())

with tf.Session() as sess:
    sess.run(tf.global_variables_initializer())
    convd = sess.run(y)
    convd_eq = sess.run(y_eq)
    sess.close()

print(convd.shape)
print(convd_eq.shape)
print(convd == convd_eq)
#  print(convd)



##### s=1, p!=0(p=2)
x = tf.Variable(np.arange(16, dtype=np.float32).reshape(4,4))
x = tf.reshape(x, shape=[1,4,4,1])
x_pad1 = tf.pad(x, tf.constant([[0,0],[2,2],[2,2],[0,0]]))
y = tf.layers.conv2d_transpose(x_pad1, 1, [3,3], strides=1, padding='valid', kernel_initializer=tf.ones_initializer())
x_pad2 = tf.pad(x, tf.constant([[0,0],[0,0],[0,0],[0,0]]))
y_eq = tf.layers.conv2d(x_pad2, 1, [3,3], strides=1, padding='valid', kernel_initializer=tf.ones_initializer())

with tf.Session() as sess:
    sess.run(tf.global_variables_initializer())
    convd = sess.run(y)
    convd_eq = sess.run(y_eq)
    sess.close()

print(convd.shape)
print(convd_eq.shape)
print(convd == convd_eq)
#  print(convd)



##### s=1, p!=0(p=2)
x = tf.Variable(np.arange(16, dtype=np.float32).reshape(4,4))
x = tf.reshape(x, shape=[1,4,4,1])
x_pad1 = tf.pad(x, tf.constant([[0,0],[2,2],[2,2],[0,0]]))
y = tf.layers.conv2d_transpose(x_pad1, 1, [3,3], strides=1, padding='valid', kernel_initializer=tf.ones_initializer())
x_pad2 = tf.pad(x, tf.constant([[0,0],[0,0],[0,0],[0,0]]))
y_eq = tf.layers.conv2d(x_pad2, 1, [3,3], strides=1, padding='valid', kernel_initializer=tf.ones_initializer())

with tf.Session() as sess:
    sess.run(tf.global_variables_initializer())
    convd = sess.run(y)
    convd_eq = sess.run(y_eq)
    sess.close()

print(convd.shape)
print(convd_eq.shape)
print(convd == convd_eq)
#  print(convd)
