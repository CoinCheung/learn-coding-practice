#!/usr/bin/python


import mxnet as mx
import numpy as np



## data
data = np.array([[1,1,1,1],[2,2,2,2],[3,3,3,3],[4,4,4,4]])
#  label = mx.nd.array([1,1,1,1])
label = mx.ndarray.one_hot(mx.nd.array([1,1,1,1]), 4)

data_iter = mx.io.NDArrayIter(data=data, label=label, batch_size=1, label_name='led')


## symbol
dataout = mx.sym.var("data")
labelout = mx.sym.var('label')

fc1 = mx.sym.FullyConnected(dataout,num_hidden=4,no_bias=False,flatten=True,name='fc1')
softmax = mx.sym.softmax(fc1, axis=1)
ce = -mx.sym.sum(labelout*mx.sym.log(softmax) + (1-labelout)*mx.sym.log(1-softmax))
loss = mx.sym.MakeLoss(ce)


## mod
mod = mx.mod.Module(loss, data_names=['data'], label_names=['label'])
mod.bind(data_shapes=[('data',(1,4))], label_shapes=[('label',(1,4))])
mod.init_params(initializer=mx.init.Uniform(scale=0.1))
#  mod = mx.mod.Module(softmax, data_names=['data'], label_names=None)
#  mod.bind(data_shapes=[('data',(1,4))], label_shapes=None)
#  mod.init_params(initializer=mx.init.Uniform(scale=0.1))



##
batch =  data_iter.next()
mod.forward(batch)
out = mod.get_outputs()

sum = mx.ndarray.sum(out[0])
print(sum)



