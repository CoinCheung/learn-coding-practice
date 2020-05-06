#!/usr/bin/python
#filename: tensorboard.py
#-*- encoding: utf-8 -*-


import tensorflow as tf


#  with tf.name_scope('nnn'):
#      w1 = tf.Variable([1,2,3], name='node1')
#      w2 = tf.Variable([4,5,6], name='node2')

w1 = tf.Variable([1,2,3], name='node1')
w2 = tf.Variable([4,5,6], name='node2')

w4 = tf.Variable([4,5,6], name='node4')

with tf.device('/gpu:0'):
    #  w1 = tf.constant([1,2,3], name='a')
    #  w2 = tf.constant([4,5,6], name='b')

    op = tf.add(w1,w2, name='op')

    w3 = tf.constant([1,2,3], name='w3')
    op2 = w3 + 1

    ini = tf.global_variables_initializer()

#  tf.summary.histogram('w1', w1)
#  tf.summary.histogram('w2', w2)
tf.summary.histogram('op', op) # 必须有summary 结点
tf.summary.histogram('w3', w3)



with tf.Session() as sess:
    sess.run(ini)
    #  merged = tf.summary.merge_all() # 合并 也需要在session里面run()一下才行。
    sess.run(op)
    sess.run(w3)

    #  summ = tf.summary.histogram('w4', w4)
    #  sess.run(merged)
    op4 = w4 + 1
    sess.run(op4)
    writer = tf.summary.FileWriter('./tblog', sess.graph)
    #  writer.add_summary(summ)

writer.close()
