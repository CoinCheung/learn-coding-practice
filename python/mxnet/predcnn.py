#!/usr/bin/bash
# -*- encoding: utf-8 -*-
# filename: predcnn.py


import mxnet as mx
from mxnet import gluon, nd, autograd
import numpy as np
import matplotlib
import matplotlib.pyplot as plt
from collections import namedtuple



ctx_gpu = mx.gpu()


batch_size = 256
num_inputs = 784
num_outputs = 10
num_fc = 512
def transform(data, label):
    return nd.transpose(data.astype(np.float32),(2,0,1))/255, label.astype(np.float32)
cifar10_test = gluon.data.vision.CIFAR10('./cifar10/test', train=False, transform = transform)
test_data = gluon.data.DataLoader(cifar10_test, batch_size, shuffle=True)

cifar10_train = gluon.data.vision.CIFAR10('./cifar10/train', train=True, transform = transform)
train_data = gluon.data.DataLoader(cifar10_train, batch_size, shuffle=True)


# import the model
import os
savedir = 'trycnn_save_export'
abspath = ''.join([os.getcwd(), os.path.sep, savedir])
if not os.path.exists(abspath):
    print('no such path: {}'.format(abspath))
    os._exit(0)
else:
    print("existing path found: {}".format(abspath))

netsym = mx.sym.load(abspath+'/trycnn-symbol.json')






net = mx.mod.Module(symbol=netsym, label_names=None, context=ctx_gpu)
net.bind(data_shapes=[('data',(1,3,32,32))], for_training=True)
net.load_params(abspath+'/trycnn-0000.params')
batch = namedtuple('batch', ['data'])



###  predict
#  acc = mx.metric.Accuracy()
#  for data, label in test_data:
#      data = data.as_in_context(ctx_gpu)
#      label = label.as_in_context(ctx_gpu)
#
#      net.forward(batch([data]))
#      scores = net.get_outputs()[0]
#
#      pred = nd.argmax(scores, axis=1)
#      acc.update(label, pred)
#
#  result = acc.get()[1]
#
#  print('final accuracy is: {}'.format(result))
#



## one more epoch of training
loss_fun = gluon.loss.SoftmaxCrossEntropyLoss()
#  net.init_optimizer(optimizer='adam', optimizer_params=(('learning_rate',1e-3), ('beta1',0.9), ('beta2', 0.999), ('epsilon', 1e-7), ('wd', 1e-3)))

print_each_iters = 20
accuracy = mx.metric.Accuracy()
for i, (data, label) in enumerate(train_data):
    data = data.as_in_context(ctx_gpu)
    label = label.as_in_context(ctx_gpu)

    net.forward(batch([data]))
    scores = net.get_outputs()[0]

    print(scores)

    #  scores.attach_grad()
    #  with autograd.record():
    #      loss = loss_fun(scores, label)
    #      loss_avg = nd.mean(loss)
    #  loss_avg.backward()
    #
    #  print(type(scores.grad))
    #
    #  net.backward()
    #  net.update()
    #
    #  accuracy.update(pred, label)
    #  rate = accuracy.get()[1]
    #
    #  if i % print_each_iters == 0:
    #      print("epoch {}, iterator {}, loss is: {}".format(e, i, loss_avg))




