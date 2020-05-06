#!/usr/bin/bash
# -*- encoding: utf-8 -*-
# filename: trycnn.py


import mxnet as mx
from mxnet import gluon, nd, autograd
import numpy as np
import matplotlib
import matplotlib.pyplot as plt


ctx_gpu = mx.gpu()


batch_size = 256
num_inputs = 784
num_outputs = 10
num_fc = 512
print('fuck')
a = np.arange(10)
def transform(data, label):
    return nd.transpose(data.astype(np.float32),(2,0,1))/255, label.astype(np.float32)
cifar10_train = gluon.data.vision.CIFAR10('./cifar10/train', train=True, transform = transform)
cifar10_test = gluon.data.vision.CIFAR10('./cifar10/test', train=False, transform = transform)
train_data = gluon.data.DataLoader(cifar10_train, batch_size, shuffle=True)
test_data = gluon.data.DataLoader(cifar10_test, batch_size, shuffle=True)


net = gluon.nn.HybridSequential()
with net.name_scope():
    net.add(gluon.nn.Conv2D(channels=20, kernel_size=5, activation='relu'))
    net.add(gluon.nn.MaxPool2D(pool_size=2, strides=2))
    net.add(gluon.nn.Conv2D(channels=50, kernel_size=5, activation='relu'))
    net.add(gluon.nn.MaxPool2D(pool_size=2, strides=2))
    net.add(gluon.nn.Flatten())
    net.add(gluon.nn.Dense(num_fc, activation='relu'))
    net.add(gluon.nn.Dense(num_outputs))

net.hybridize()



net.collect_params().initialize(mx.init.Xavier(magnitude=2.24),ctx=ctx_gpu)
#  net.collect_params().load('./trycnn_save.params', ctx=ctx_gpu)
loss_fun = gluon.loss.SoftmaxCrossEntropyLoss()
#  trainer = gluon.Trainer(net.collect_params(), 'sgd', {'learning_rate': 0.01})
trainer = gluon.Trainer(net.collect_params(), 'adam', {'learning_rate':1e-3, 'beta1':0.9, 'beta2':0.999, 'epsilon':1e-7, 'wd':1e-3})



epoch = 2
print_each_iters = 20
accuracy = mx.metric.Accuracy()
loss_arr = []
accuracy_arr = []
for e in range(epoch):
    for i, (data, label) in enumerate(train_data):
        data = data.as_in_context(ctx_gpu)
        label = label.as_in_context(ctx_gpu)
        with autograd.record():
            out = net(data)
            loss = loss_fun(out, label)
        loss.backward()
        trainer.step(data.shape[0])
        loss_avg = nd.mean(loss).asscalar()

        # print the losses
        if i % print_each_iters == 0:
            print("epoch {}, iterator {}, loss is: {}".format(e, i, loss_avg))

        pred = nd.argmax(out, axis=1)
        accuracy.reset()
        accuracy.update(label, pred)
        rate = accuracy.get()[1]

        loss_arr.append(loss_avg)
        accuracy_arr.append(rate)

    print('epoch {}, accuracy is: {}'.format(e, rate))


net.collect_params().save('./trycnn_save')

# export the model
import os
savedir = 'trycnn_save_export'
abspath = ''.join([os.getcwd(), os.path.sep, savedir])
if not os.path.exists(abspath):
    print('create new path: {}'.format(abspath))
    os.mkdir(abspath)
else:
    print("using existing path: {}".format(abspath))

net.export("./trycnn_save_export/trycnn")


#  # plot the training process
#  x_values = np.arange(len(loss_arr))
#  y_loss = np.array(loss_arr)
#  y_accuracy = np.array(accuracy_arr)
#  _, axarr = plt.subplots(2, sharex=True)
#  axarr[0].plot(x_values, loss_arr)
#  axarr[0].set_title('train loss')
#  axarr[1].plot(x_values, accuracy_arr)
#  axarr[1].set_title('validation accuracy')
#  plt.show()


###  predict
acc = mx.metric.Accuracy()
for data, label in test_data:
    data = data.as_in_context(ctx_gpu)
    label = label.as_in_context(ctx_gpu)
    #  print(label.shape)

    scores = net(data)
    pred = nd.argmax(scores, axis=1)
    acc.update(label, pred)

result = acc.get()[1]

print('final accuracy is: {}'.format(result))

