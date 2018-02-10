
import mxnet as mx
import numpy as np
from mxnet import gluon, nd


## data iterators
batch_size = 1
num_inputs = 784
num_outputs = 10
num_fc = 512

def transform(data, label):
    return nd.transpose(data.astype(np.float32),(2,0,1))/255, label.astype(np.float32)
cifar10_train = gluon.data.vision.CIFAR10('../cifar10/train', train=True, transform = transform)
cifar10_test = gluon.data.vision.CIFAR10('../cifar10/test', train=False, transform = transform)
train_data = gluon.data.DataLoader(cifar10_train, batch_size, shuffle=True)

# mnist
mnist_train = gluon.data.vision.CIFAR10('~/.mxnet/datasets/mnist', train=True, transform = transform)
cifar10_test = gluon.data.vision.CIFAR10('../cifar10/test', train=False, transform = transform)
train_data = gluon.data.DataLoader(mnist_train, batch_size, shuffle=True)

for batch in train_data:
    print(batch)
    break


## symbols
dataout = mx.sym.var("data")
labelout = mx.sym.var('led')
indata = mx.sym.flatten(dataout)
fc1 = mx.sym.FullyConnected(indata,num_hidden=4,no_bias=False,flatten=True,name='fc1')
sym = mx.sym.SoftmaxOutput(fc1, labelout, multi_output=False, name='smax')




## modules
net = mx.mod.Module(symbol=sym, context=mx.cpu(),data_names=['data'],label_names=['led'])
net.bind(data_shapes=[('data',(batch_size,3,32,32))], label_shapes=[('led',(batch_size,))],inputs_need_grad=True)
net.init_params(initializer=mx.init.Uniform(scale=.1))
net.init_optimizer(optimizer='sgd', optimizer_params=(('learning_rate', 1e-3),))

for data,label in train_data:
    batch = mx.io.DataBatch([data],label=[label])
    net.forward(batch)
    net.backward()
    in_grad = net.get_input_grads()
    #  print(in_grad)
    break




