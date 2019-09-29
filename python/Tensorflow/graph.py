#!/usr/bin/python
#filename: graph.py
# -*-encoding: utf-8 -*-


import tensorflow as tf
import numpy as np


c1 = tf.constant([1,2,3], name='c1')
v1 = tf.Variable([1,2,3], name='v1')
g1 = tf.get_default_graph()

print(c1.graph)
print(tf.get_default_graph())
#  with tf.Graph().as_default() as g:
with tf.Graph().as_default() as g:
    c2 = tf.constant([4,5,6], name='c2')
    v2 = tf.Variable([4,5,6], name='v2')

dg = tf.get_default_graph()
print(v1.graph)
print(v2.graph)

print(g1)
print(g)

with g.as_default():
    with tf.Session() as sess:
    #  print(c1*2)
    #  print(c2)
    #  print(v1)
    #  print(v2)
    #  print(sess.run(v1+v2))
        sess.run([c2])#, c2])
        c2 = c2+1
        print(sess.run(c2))
        print('fuck\n\n\n')
        sess.run([v2.initializer])#, v2.initializer])
    #  print(sess.run(v1+v2))
    #  print(c1)
    #  print(c2)
    #  print(v1)
    #  print(v2)

    sess.close()

with g1.as_default():
    with tf.Session() as sess:
        sess.run([c1])#, c2])
        sess.run(c1)
        sess.run([v1.initializer])#, v2.initializer])
        sess.close()


with g.as_default():
    with tf.Session() as sess:
    #  print(c1*2)
    #  print(c2)
    #  print(v1)
    #  print(v2)
    #  print(sess.run(v1+v2))
        sess.run([c2])#, c2])
        c2 = c2+1
        print(sess.run(c2))
        print('fuck\n\n\n')
        sess.run([v2.initializer])#, v2.initializer])
    #  print(sess.run(v1+v2))
    #  print(c1)
    #  print(c2)
    #  print(v1)
    #  print(v2)

    sess.close()
