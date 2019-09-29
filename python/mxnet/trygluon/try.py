import mxnet as mx
from mxnet import gluon

se = gluon.nn.HybridSequential()
se.add(gluon.nn.Conv2D(channels=64, in_channels=32, kernel_size=4, strides=(2,2), padding=(1,1)))
se.add(gluon.nn.Conv2DTranspose(channels=32, in_channels=64, kernel_size=4, strides=(2,2), padding=(1,1)))
se.collect_params().initialize()

in_ten = mx.nd.ones((1, 32, 256, 256))

out = se(in_ten)
print(out.shape)
print(se)
