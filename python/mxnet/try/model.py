#!/usr/bin/python

import mxnet as mx
import numpy as np
from mxnet import gluon, nd, autograd
from collections import namedtuple


def cnn(batch_size, dataName='data', labelName='label', test=False, eps=0.0001):
    data = mx.sym.var(dataName)
    label = mx.sym.var(labelName)

    train = not test
    conv1 = mx.sym.Convolution(data,num_filter=32,kernel=(3,3),stride=(1,1),pad=(1,1),no_bias=True,name='conv1')
    bn1 = mx.sym.BatchNorm(conv1,fix_gamma=False,use_global_stats=test,eps=eps,name='bn1')
    relu1 = mx.sym.Activation(bn1,act_type='relu',name='relu1')

    conv2 = mx.sym.Convolution(relu1,num_filter=32,kernel=(3,3),stride=(1,1),pad=(1,1),no_bias=True,name='conv2')
    bn2 = mx.sym.BatchNorm(conv2,fix_gamma=False,use_global_stats=test,eps=eps,name='bn2')
    relu2 = mx.sym.Activation(bn2,act_type='relu',name='relu2')

    pool1 = mx.sym.Pooling(relu2,kernel=(2,2),stride=(2,2),pad=(0,0),pool_type='max',name='pool1')

    conv3 = mx.sym.Convolution(pool1,num_filter=64,kernel=(3,3),stride=(1,1),pad=(1,1),no_bias=True,name='conv3')
    bn3 = mx.sym.BatchNorm(conv3,fix_gamma=False,use_global_stats=test,eps=eps,name='bn3')
    relu3 = mx.sym.Activation(bn3,act_type='relu',name='relu3')

    conv4 = mx.sym.Convolution(relu3,num_filter=64,kernel=(3,3),stride=(1,1),pad=(1,1),no_bias=True,name='conv4')
    bn4 = mx.sym.BatchNorm(conv4,fix_gamma=False,use_global_stats=test,eps=eps,name='bn4')
    relu4 = mx.sym.Activation(bn4,act_type='relu',name='relu4')

    pool2 = mx.sym.Pooling(relu4,kernel=(2,2),stride=(2,2),pad=(0,0),pool_type='max',name='pool2')

    #  conv4 = mx.sym.Convolution(relu3,num_filter=64,kernel=(3,3),stride=(1,1),pad=(1,1),no_bias=True,name='conv4')
    #  bn4 =
    #  mx.sym.BatchNorm(conv4,fix_gamma=False,use_global_stats=test,eps=eps,name='bn4')
    #  relu4 = mx.sym.Activation(bn4,act_type='relu',name='relu4')

    fc1 = mx.sym.FullyConnected(pool2,num_hidden=1024,no_bias=False,flatten=True,name='fc1')
    relu5 = mx.sym.Activation(fc1,act_type='relu',name='relu5')
    scores = mx.sym.FullyConnected(relu5,num_hidden=10,no_bias=False,flatten=False,name='scores')

    #  sym = mx.sym.SoftmaxOutput(scores, label)
    if train:
        softmax = mx.sym.softmax(scores, axis=1)
        ce_parse = label*mx.sym.log(softmax)
        ce = - mx.sym.sum(ce_parse) / batch_size
        loss = mx.sym.MakeLoss(ce)
        #  loss = ce

        cls = mx.sym.one_hot(mx.sym.argmax(softmax, axis=1), 10)
        cls = mx.sym.BlockGrad(cls)
        out = mx.sym.Group([loss, cls])
        #  out = loss
    else:
        out = mx.sym.softmax(scores, axis=1)

    return out



if __name__ == "__main__":

    data = np.array([[1,1,1,1],[2,2,2,2],[3,3,3,3],[4,4,4,4]])
    label = mx.ndarray.one_hot(mx.nd.array([1,1,1,1]), 4)

    data_iter = mx.io.NDArrayIter(data=data, label=label, batch_size=1, label_name='led')

    dataout = mx.sym.var("data")
    labelout = mx.sym.var('led')
    fc1 = mx.sym.FullyConnected(dataout,num_hidden=4,no_bias=False,flatten=True,name='fc1')
    #  sym = mx.sym.softmax_cross_entropy(fc1, labelout, name='loss')
    sym = mx.sym.SoftmaxOutput(fc1, labelout, multi_output=False, name='smax')
    #  sym = mx.sym.SoftmaxOutput(fc1, name='softmax')

    mod = mx.mod.Module(symbol=sym, context=mx.cpu(),data_names=['data'],label_names=['led'])
    mod.bind(data_shapes=data_iter.provide_data, label_shapes=data_iter.provide_label,inputs_need_grad=True)
    mod.init_params(initializer=mx.init.Uniform(scale=.1))
    mod.init_optimizer(optimizer='sgd', optimizer_params=(('learning_rate', 1e-3),))

    metric = mx.metric.Accuracy()
    batch = data_iter.next()
    print(batch)
    mod.forward(batch)
    mod.backward()
    mod.update()

    #  out = mod.score(data_iter, metric)
    #  print(out)

    #  out =  mod.get_outputs()
    #  print(out)
    #  in_grad = mod.get_input_grads()[0].asnumpy()
    #  print(in_grad)

    #  out = mod.predict(data_iter)
    #  print(out.asnumpy())

    #  mod.save_checkpoint("model", 19, True)







