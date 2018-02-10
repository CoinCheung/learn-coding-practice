#!/usr/bin/python
# -*- encoding: utf-8 -*-
# filename: tryresnet001.py


import mxnet as mx
from mxnet import nd, autograd, gluon


# running context
ctx_cpu = mx.cpu()
ctx_gpu = mx.gpu()

# get datasets
batch_size = 256
cifar10_train = gluon.data.vision.CIFAR10('./cifar10/train', train=True)
cifar10_test = gluon.data.vision.CIFAR10('./cifar10/test', train=False)

# define data iterators
train_data = gluon.data.DataLoader(cifar10_train, batch_size=batch_size, shuffle=True)
test_data = gluon.data.DataLoader(cifar10_test, shuffle=True, batch_size=batch_size)


#  for data,label in cifar10_train:
#      print(data.shape)
#      print(label.shape)

# construction the bottleneck resnet unit
def bottleneck(X, filter_num, stride=(1,1)):
    # create a sequential
    out = gluon.nn.Sequential()
    # add the first convolution layer
    out.add(gluon.nn.BatchNorm(axis=3))
    out.add(gluon.nn.Activation(activation='relu'))
    out.add(gluon.nn.Conv2D(channel=int(filter_num/4), kernel_size=1, strides=(1,1), layout='NHWC'))
    # add the second convolution layer
    out.add(gluon.nn.BatchNorm(axis=3))
    out.add(gluon.nn.Activation(activation='relu'))
    out.add(gluon.nn.Conv2D(channel=int(filter_num/4), kernel_size=3, strides=stride, padding=(1,1), layout='NHWC'))
    # add the third convolution layer
    out.add(gluon.nn.BatchNorm(axis=3))
    out.add(gluon.nn.Activation(activation='relu'))
    out.add(gluon.nn.Conv2D(channel=filter_num, kernel_size=1, strides=(1,1), layout='NHWC'))
    # compute the residual F(x)
    fx = out(X)

    # compute the shortcut
    if stride == (1,1):
        shortcut = X
    else:
        downsample = gluon.nn.Sequential()
        downsample.add(gluon.nn.Conv2D(channel=filter_num, kernel_size=1, strides=stride, layout='NHWC'))
        shortcut = downsample(X)

    return fx+shortcut


# layers after residual layers and the dense layer
def dense(X):
    out = gluon.nn.Sequential()
    out.add(gluon.nn.BatchNorm(axis=3))
    out.add(gluon.nn.Activation('relu'))
    out.add(gluon.nn.flatten())
    out.add(gluon.nn.Dense(10))
    return out(X)


# construct the model
def resnet(X):
    body = bottleneck(X, 64) # 28x28x64
    body = bottleneck(body, 128, stride=(2,2)) # 14x14x128
    body = bottleneck(body, 128, stride=(1,1)) # 14x14x128
    body = bottleneck(body, 256, stride=(2,2)) # 7x7x128
    body = bottleneck(body, 256, stride=(1,1)) # 7x7x128
    body = dense(body)
    return body


# initialize the network parameters
#  net = resnet()

