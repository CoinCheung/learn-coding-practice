#!/usr/bin/python
# -*- encoding: utf-8 -*-


import mxnet as mx
import mxnet.gluon as gluon
import numpy as np



densenet_pretrained = gluon.model_zoo.vision.densenet121(pretrained=True, ctx=mx.gpu(), prefix='densenet121_')
densenet = gluon.model_zoo.vision.densenet121(classes=10, prefix='densenet121_')

densenet.features = densenet_pretrained.features


#  transform = lambda data, label:(mx.nd.transpose(data, (2,1,0)).astype(np.float32), label)
def transform(img, label):
    print(img.shape)
    return mx.img.ResizeAug(224)(img).transpose((2,0,1)).astype(np.float32) ,label

cifar10 = gluon.data.vision.datasets.CIFAR10(root="~/.mxnet/datasets/cifar10", transform=transform)
ds = gluon.data.DataLoader(cifar10, batch_size=1, shuffle=True)

resnet18 = gluon.model_zoo.vision.resnet18_v1(pretrained=True,
        ctx=mx.gpu(), prefix='resnet_base_')

for data, label in ds:
    data = data.as_in_context(mx.gpu())
    print(data.shape)
    out = densenet_pretrained(data)
    #  print(out)
    #  print(densenet.features)
    print(type(densenet.output))
    densenet.output.initialize(init=mx.init.Xavier(), ctx=mx.gpu())
    out = densenet.features(data)
    print(out.shape)

    #  print(resnet18.output)
    #  print(resnet18.features)
    #  print(resnet18.features[7])

    resnet = gluon.model_zoo.vision.resnet18_v1(pretrained=True,
            ctx=mx.gpu(), prefix='resnet_base_')
    net = gluon.nn.HybridSequential()
    for i in range(8):
        net.add(resnet.features[i])

    out = net(data)
    print(out.shape)
    #  print(densenet.features[0])
    break


#########
def base_network():
    resnet = gluon.model_zoo.vision.resnet18_v1(pretrained=True,
            ctx=mx.gpu(), prefix='resnet_base_')
    net = gluon.nn.HybridSequential()
    for i in range(8):
        net.add(resnet.features[i])
    #  print(net)
    return net


class rpn_network(gluon.nn.HybridBlock):
    def __init__():
        super(rpn, self).__init__()
        self.base = gluon.nn.HybridSequential()
        self.cls_branch = gluon.nn.HybridSequential()
        self.loc_branch = gluon.nn.HybridSequential()
        self.base.add(gluon.nn.Conv2D(512, kernel_size=3, strides=(1,1), padding=(1,1)))
        self.cls_branch.add(gluon.nn.Conv2D(18, kernel_size=1, strides=(1,1), padding=(0,0)))
        self.loc_branch.add(gluon.nn.Conv2D(36, kernel_size=1, strides=(1,1), padding=(0,0)))

    def forward(self, F, x):  # x is a feature map from the base network
        fm = self.base(x)
        cls_scores = self.cls_branch(fm)
        loc_scores = self.loc_branch(fm)


class RPN(object):
    def __init__():
        self.rpn_network = rpn_network
        self.ProposalLayer = ProposalLayer



class ProposalLayer(object):
    def __init__(width, height, feat_stride=32, scales=[8,16,32], ratios=[0.5,1,2]):
        self.width = width
        self.height = height
        self.feat_stride = feat_stride
        self.scales = scales
        self.ratios = ratios

    def get_anchors():
        pass


def train():
    base_net = base_network()
    rpn_net = rpn_network
    proposal_layer = ProposalLayer



if __name__ == "__main__":
    train()
