#!/usr/bin/python


import mxnet as mx
from mxnet import gluon, nd
import numpy as np



# parameters
batch_size = 256
path = "./params"


# prepare data iterator
def transform(data, label):
    return nd.transpose(data.astype(np.float32),(2,0,1))/255, label.astype(np.float32)
cifar10_train = gluon.data.vision.CIFAR10('../cifar10/train', train=True, transform = transform)
cifar10_test = gluon.data.vision.CIFAR10('../cifar10/test', train=False, transform = transform)
train_data = gluon.data.DataLoader(cifar10_train, batch_size, shuffle=True)



# load sym
sym = mx.sym.load(path+'/model-symbol.json')


#  # create Module and load parameters
#  net = mx.mod.Module(sym, data_names=['data'], label_names=['label'], context=mx.gpu())
#  net.bind(data_shapes=[('data',(batch_size,3,32,32))], label_shapes=[('label',(batch_size,10))],inputs_need_grad=True)
#  net.load_params(path+'/model-0001.params')
#  net.init_optimizer(optimizer='adam', optimizer_params=(('learning_rate', 1e-3),('beta1',0.99), ('beta2',0.999)))
#  #  net.init_optimizer(optimizer='sgd', optimizer_params=(('learning_rate', 1e-1),))
#  net.load_optimizer_states(path+'/model-0001.states')

net = mx.mod.Module.load(path+'/model', 1, True, context=mx.gpu(), data_names=['data'], label_names=['label'])
net.bind(data_shapes=[('data',(batch_size,3,32,32))], label_shapes=[('label',(batch_size,10))],inputs_need_grad=True)
net.init_optimizer(optimizer='adam', optimizer_params=(('learning_rate', 1e-1),('beta1',0.9), ('beta2',0.399)))
#  net.init_optimizer(optimizer='sgd', optimizer_params=(('learning_rate', 1e-1),))



# metric
metric = mx.metric.Accuracy()
def Accuracy(pred, label):
    pred = pred.asnumpy()
    label = label.asnumpy()
    len = pred.shape[0]
    same = 0
    for i in range(len):
        if np.array_equal(pred[i],label[i]):
            same += 1

    return same / len


# start to train
for e in range(10):
    metric.reset()
    i = 0
    for data,label in train_data:
        label = nd.one_hot(label,10)
        batch = mx.io.DataBatch([data],label=[label])
        net.forward(batch)
        net.backward()
        net.update()

        out = net.get_outputs()
        pred = out[1]
        acc = Accuracy(pred, label)

    #  print(out)
        if i % 10 == 0:
            print("epoch {}, iter {}, train loss is: {}, train acc is: {}".format(e, i, net.get_outputs()[0].asnumpy(),acc))
        i += 1



