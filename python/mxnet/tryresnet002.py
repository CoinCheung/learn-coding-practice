#!/usr/bin/python
# -*- encoding: utf-8 -*-
# filename: tryresnet002.py


'''
    * gluon.Cov2D()的时候，需要加上in_channel，表示输入的symbol的channel是多少
    * 在图的定义后加上hybridize()可以让图静态化。
    * 可以将静态化的图保存起来，保存成json和params的格式的模型
    * 关于保模型的方法，转成symbol之后，再symbol.save(path)和先j = symbol.tojson()，再把j写到文件里面去是一样的，得到结果相同。
'''

import mxnet as mx
from mxnet import nd, autograd, gluon
import numpy as np
import matplotlib
import matplotlib.pyplot as plt
mx.random.seed(1)


# running context
ctx_cpu = mx.cpu()
ctx_gpu = mx.gpu()

# get datasets
batch_size = 256



def data_pre_deal(data, label):
    return nd.transpose(data.astype(np.float32),(2,0,1)), label.astype(np.float32)


cifar10_train = gluon.data.vision.CIFAR10('./cifar10/train', train=True, transform = data_pre_deal)
cifar10_test = gluon.data.vision.CIFAR10('./cifar10/test', train=False, transform = data_pre_deal)

# define data iterators
train_data = gluon.data.DataLoader(cifar10_train, batch_size=batch_size, shuffle=True)
test_data = gluon.data.DataLoader(cifar10_test, shuffle=True, batch_size=batch_size)


# construction the bottleneck resnet unit
class bottleneck(gluon.HybridBlock):
    def __init__(self, filter_num, in_channels, stride=(1,1), prefix=None, params=None):
        super(bottleneck, self).__init__(prefix=prefix, params=params)
        self.stride = stride
        self.filter_num = filter_num
        self.in_channels = in_channels

        # create a sequential for residual
        self.res = gluon.nn.HybridSequential(prefix='')
        with self.res.name_scope():
            # add the first convolution layer
            self.res.add(gluon.nn.BatchNorm(axis=1))
            self.res.add(gluon.nn.Activation(activation='relu'))
            self.res.add(gluon.nn.Conv2D(channels=filter_num//4, in_channels=in_channels, kernel_size=1, strides=(1,1), layout='NCHW'))
            # add the second convolution layer
            self.res.add(gluon.nn.BatchNorm(axis=1))
            self.res.add(gluon.nn.Activation(activation='relu'))
            self.res.add(gluon.nn.Conv2D(channels=filter_num//4, in_channels=filter_num//4, kernel_size=3, strides=stride, padding=(1,1), layout='NCHW'))
            # add the third convolution layer
            self.res.add(gluon.nn.BatchNorm(axis=1))
            self.res.add(gluon.nn.Activation(activation='relu'))
            self.res.add(gluon.nn.Conv2D(channels=filter_num, in_channels=filter_num//4, kernel_size=1, strides=(1,1), layout='NCHW'))

            # create a sequential for shortcut
            if self.stride != (1,1) or self.filter_num != in_channels:
                self.shortcut = gluon.nn.HybridSequential(prefix='')
                self.shortcut.add(gluon.nn.Conv2D(channels=filter_num,in_channels=in_channels, kernel_size=1, strides=stride, layout='NCHW'))


    def hybrid_forward(self, F, x):
        res = self.res(x)
        if self.stride != (1,1) or self.filter_num != self.in_channels:
            sc = self.shortcut(x)
        else:
            sc = x

        out = sc + res
        return out


# construct the last few layers
class lastDense(gluon.HybridBlock):
    def __init__(self, units, prefix=None, params=None):
        super(lastDense, self).__init__(prefix=prefix, params=params)

        # create a sequential
        self.last = gluon.nn.HybridSequential(prefix='')
        with  self.last.name_scope():
            self.last.add(gluon.nn.BatchNorm(axis=1))
            self.last.add(gluon.nn.Activation('relu'))
            self.last.add(gluon.nn.GlobalAvgPool2D(layout='NCHW'))
            self.last.add(gluon.nn.Dense(units))

    def hybrid_forward(self, F, x):
        return self.last(x)



# method to construct the model
resnet = gluon.nn.HybridSequential()
with resnet.name_scope():
    resnet.add(bottleneck(64, in_channels=3)) # 28x28x64
    resnet.add(bottleneck(128, in_channels=64, stride=(2,2))) # 14x14x128
    resnet.add(bottleneck(128, in_channels=128)) # 14x14x128
    resnet.add(bottleneck(256, in_channels=128, stride=(2,2))) # 7x7x256
    resnet.add(bottleneck(256, in_channels=256)) # 7x7x256
    resnet.add(lastDense(10))
    #  resnet.add(gluon.nn.Dense(10))

resnet.hybridize()
print('after hybridize')

# create the model and initialization
resnet.collect_params().initialize(mx.init.Xavier(magnitude=2.24),ctx=ctx_gpu)


# definition of loss function and trainer
loss_fun = gluon.loss.SoftmaxCrossEntropyLoss()
trainer = gluon.Trainer(resnet.collect_params(), 'adam', {'learning_rate':1e-3, 'beta1':0.9, 'beta2':0.999, 'epsilon':1e-7, 'wd':1e-2})
#  trainer = gluon.Trainer(resnet.collect_params(), 'sgd', {'learning_rate': 0.01})


# train the model
epoch = 1
print_each_iters = 20
acc = mx.metric.Accuracy()
loss_arr = []
accuracy_arr = []
for e in range(epoch):
    for i, (data, label) in enumerate(train_data):
        # move the training data to gpu memory
        data = data.as_in_context(ctx_gpu)
        label = label.as_in_context(ctx_gpu)
        # forward and derive gradient
        with autograd.record():
            output = resnet(data)
            loss = loss_fun(output, label)
        # backward combining the gradients
        loss.backward()
        # update the network parameters
        trainer.step(data.shape[0])

        # compute loss and accuracy
        loss_avg = nd.mean(loss).asscalar()
        pred = nd.argmax(output, axis=1)
        acc.reset()
        acc.update(pred, label)
        rate = acc.get()[1]
        loss_arr.append(loss_avg)
        accuracy_arr.append(rate)

        # print to track the process
        if i%print_each_iters == 0:
            print("epoch {}, iteration {}, loss is {}".format(e, i, loss_avg))

    print('epoch {}, validation accuracy: {}'.format(e, rate))



### save the model
import os
savepath = 'resnet'
absdir = ''.join([os.getcwd(), os.path.sep, savepath])
if os.path.exists(absdir):
    print('dir exists: {}, update its contents'.format(absdir))
else:
    print('create new directory: {}'.format(absdir))
    os.mkdir(absdir)

#  resnet.hybridize()
x = mx.sym.var('data')
y = resnet(x)
y.save(absdir+'/resnet.json')
resnet.save_params(absdir+'/resnet.params')


### plot the loss and accuracy in the training process
x = np.arange(len(loss_arr))
y_loss = np.array(loss_arr)
y_acc = np.array(accuracy_arr)
_, axarr = plt.subplots(2, sharex=True)
axarr[0].plot(x, y_loss)
axarr[0].set_title("training loss")
axarr[1].plot(x, y_acc)
axarr[1].set_title("training accuracy")
plt.show()




### predict
acc.reset()
for data, label in test_data:
    data = data.as_in_context(ctx_gpu)
    label = label.as_in_context(ctx_gpu)

    scores = resnet(data)
    pred = nd.argmax(scores, axis=1)
    acc.update(label, pred)

result = acc.get()[1]
print("the final classification result is: {}".format(result))





