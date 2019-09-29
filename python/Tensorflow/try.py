#!/usr/bin/python
#filename: try.py
#-*-encoding: utf-8 -*-


import tensorflow as tf


def model():
    with tf.device('/gpu:0'):
        a = tf.constant([1,2,3], name='a')
        b = tf.constant([4,5,6], name='b')
        c = tf.add(a,b)

    with tf.device('/cpu:0'):
        d = tf.constant([2,3,4], name='d')
        f = tf.add(d,c)

    return f # return the node of the graph


if __name__ == '__main__':
    node = model()
    with tf.Session() as sess:
        writer = tf.summary.FileWriter('./graphs', sess.graph)
        res = sess.run(node)
    sess.close()

    print(res)


