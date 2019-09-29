#!/usr/bin/python


import mxnet as mx




## data and vars
v1 = mx.nd.array([1, 2])
v2 = mx.nd.array([0, 1])
a = mx.sym.var('a')
b = mx.sym.var('b')
c = mx.sym.var('c')

## network and loss
c = 3 * b
b_stop_grad = mx.sym.BlockGrad(c)
#  b_stop_grad = c
loss = mx.sym.MakeLoss(b_stop_grad + a)

executor = loss.simple_bind(ctx=mx.cpu(), a=(2,), b=(2,))

executor.forward(is_train=True, a=v1, b=v2)
print('outputs:')
print(executor.outputs)

executor.backward()
print("grads: ")
print(executor.grad_arrays)

