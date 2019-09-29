#!/usr/bin/python


from model import cnn
import mxnet as mx
import numpy as np
from mxnet import gluon, nd
from collections import namedtuple


# prepare data iterator
batch_size = 256

def transform(data, label):
    return nd.transpose(data.astype(np.float32),(2,0,1))/255, label.astype(np.float32)
cifar10_train = gluon.data.vision.CIFAR10('../cifar10/train', train=True, transform = transform)
cifar10_test = gluon.data.vision.CIFAR10('../cifar10/test', train=False, transform = transform)
train_data = gluon.data.DataLoader(cifar10_train, batch_size, shuffle=True)


# get symbol
#  sym = cnn() / batch_size
sym = cnn(batch_size=batch_size)

# create mod
mod = mx.mod.Module(sym, context=mx.gpu(), data_names=['data'], label_names=['label'])
label_shapes = [('label',(batch_size,10)), ('label',(batch_size,10))]
mod.bind(data_shapes=[('data',(batch_size,3,32,32))],label_shapes=label_shapes)
#  mod.bind(data_shapes=[('data',(batch_size,3,32,32)), ('label',(batch_size,))])
mod.init_params(initializer=mx.init.Uniform(scale=0.01))
mod.init_optimizer(optimizer='adam', optimizer_params=(('learning_rate', 1e-3),('beta1',0.99), ('beta2',0.999)))


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


# train some time
for e in range(2):
    i = 0
    for data,label in train_data:
        label = nd.one_hot(label,10)
        metric.reset()
        batch = mx.io.DataBatch([data],label=[label])

        mod.forward(batch)

        out = mod.get_outputs()
        pred = out[1]
        #  acc = metric.get()
        acc = Accuracy(pred, label)

        mod.backward()
        mod.update()
        if i % 10 == 0:
            print("epoch {}, iter {}, train loss is: {}, train acc is: {}".format(e, i, mod.get_outputs()[0].asnumpy(),acc))
            #  para = mod.get_params()
            #  print(para)
            #  break
        i += 1




# save mod
mod.save_checkpoint("./params/model", 1, True)


