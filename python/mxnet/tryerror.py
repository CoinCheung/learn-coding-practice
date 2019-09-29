#!/usr/bin/bash
# -*- encoding: utf-8 -*-
# filename: tryerror.py



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
cifar10_train = gluon.data.vision.CIFAR10('./cifar10/train', train=True, transform = transform)
train_data = gluon.data.DataLoader(cifar10_train, batch_size, shuffle=True)


# import the model
netsym = mx.sym.load('./trycnn-symbol.json')
net = mx.mod.Module(symbol=netsym, label_names=None, context=ctx_gpu)
net.bind(data_shapes=[('data',(1,3,32,32))], for_training=True)
net.load_params('./trycnn-0000.params')
batch = namedtuple('batch', ['data'])



## one more epoch of training
loss_fun = gluon.loss.SoftmaxCrossEntropyLoss()

print_each_iters = 20
accuracy = mx.metric.Accuracy()
for i, (data, label) in enumerate(train_data):
    data = data.as_in_context(ctx_gpu)
    label = label.as_in_context(ctx_gpu)

    net.forward(batch([data]))
    scores = net.get_outputs()[0]

    scores.attach_grad()
    with autograd.record():
        loss = loss_fun(scores, label)
        loss_avg = nd.mean(loss)
    loss_avg.backward()

    print(type(scores.grad))

    net.backward(out_grads=scores.grad)
    net.update()

    accuracy.update(pred, label)
    rate = accuracy.get()[1]

    if i % print_each_iters == 0:
        print("epoch {}, iterator {}, loss is: {}".format(e, i, loss_avg))




