from builtins import object
import numpy as np

from cs231n.layers import *
from cs231n.fast_layers import *
from cs231n.layer_utils import *


class ThreeLayerConvNet(object):
    """
    A three-layer convolutional network with the following architecture:

    conv - relu - 2x2 max pool - affine - relu - affine - softmax

    The network operates on minibatches of data that have shape (N, C, H, W)
    consisting of N images, each with height H and width W and with C input
    channels.
    """

    def __init__(self, input_dim=(3, 32, 32), num_filters=32, filter_size=7,
                 hidden_dim=100, num_classes=10, weight_scale=1e-3, reg=0.0,
                 dtype=np.float64):
        """
        Initialize a new network.

        Inputs:
        - input_dim: Tuple (C, H, W) giving size of input data
        - num_filters: Number of filters to use in the convolutional layer
        - filter_size: Size of filters to use in the convolutional layer
        - hidden_dim: Number of units to use in the fully-connected hidden layer
        - num_classes: Number of scores to produce from the final affine layer.
        - weight_scale: Scalar giving standard deviation for random initialization
          of weights.
        - reg: Scalar giving L2 regularization strength
        - dtype: numpy datatype to use for computation.
        """
        self.params = {}
        self.reg = reg
        self.dtype = dtype

        ############################################################################
        # TODO: Initialize weights and biases for the three-layer convolutional    #
        # network. Weights should be initialized from a Gaussian with standard     #
        # deviation equal to weight_scale; biases should be initialized to zero.   #
        # All weights and biases should be stored in the dictionary self.params.   #
        # Store weights and biases for the convolutional layer using the keys 'W1' #
        # and 'b1'; use keys 'W2' and 'b2' for the weights and biases of the       #
        # hidden affine layer, and keys 'W3' and 'b3' for the weights and biases   #
        # of the output affine layer.                                              #
        ############################################################################
        C, H, W = input_dim
        W1 = np.zeros((num_filters, C, filter_size, filter_size))
        b1 = np.zeros(num_filters)
        for f in range(num_filters):
            W1[f] = weight_scale * np.random.randn(C, filter_size, filter_size)
            b1[f] = 0

        cH = H // 2
        cW = W // 2
        cC = num_filters
        cdim = cH * cW * cC
        W2 = weight_scale * np.random.randn(cdim, hidden_dim)
        b2 = np.zeros((1, hidden_dim))

        W3 = weight_scale * np.random.randn(hidden_dim, num_classes)
        b3 = np.zeros((1, num_classes))

        self.params['W1'] = W1
        self.params['b1'] = b1
        self.params['W2'] = W2
        self.params['b2'] = b2
        self.params['W3'] = W3
        self.params['b3'] = b3
        ############################################################################
        #                             END OF YOUR CODE                             #
        ############################################################################

        for k, v in self.params.items():
            self.params[k] = v.astype(dtype)


    def loss(self, X, y=None):
        """
        Evaluate loss and gradient for the three-layer convolutional network.

        Input / output: Same API as TwoLayerNet in fc_net.py.
        """
        W1, b1 = self.params['W1'], self.params['b1']
        W2, b2 = self.params['W2'], self.params['b2']
        W3, b3 = self.params['W3'], self.params['b3']

        # pass conv_param to the forward pass for the convolutional layer
        filter_size = W1.shape[2]
        conv_param = {'stride': 1, 'pad': (filter_size - 1) // 2}

        # pass pool_param to the forward pass for the max-pooling layer
        pool_param = {'pool_height': 2, 'pool_width': 2, 'stride': 2}

        scores = None
        ############################################################################
        # TODO: Implement the forward pass for the three-layer convolutional net,  #
        # computing the class scores for X and storing them in the scores          #
        # variable.                                                                #
        ############################################################################
        N, C, H, W = X.shape
        outCov, cache_conv = conv_forward_naive(X, W1, b1, conv_param)
        outCovRelu, cache_convrelu = relu_forward(outCov)
        outMaxPool, cache_maxpool = max_pool_forward_naive(outCovRelu, pool_param)
        maxPoolshape = outMaxPool.shape
        outMaxPool = outMaxPool.reshape(N, -1)
        outAffine, cache_affine = affine_forward(outMaxPool, W2, b2)
        outAffRelu, cache_affrelu = relu_forward(outAffine)
        scores, cache_fc = affine_forward(outAffRelu, W3, b3)

        #  print(scores)
        ############################################################################
        #                             END OF YOUR CODE                             #
        ############################################################################

        if y is None:
            return scores

        loss, grads = 0, {}
        ############################################################################
        # TODO: Implement the backward pass for the three-layer convolutional net, #
        # storing the loss and gradients in the loss and grads variables. Compute  #
        # data loss using softmax, and make sure that grads[k] holds the gradients #
        # for self.params[k]. Don't forget to add L2 regularization!               #
        ############################################################################
        num_filters = self.params['W1'].shape[0]
        loss, dscores = softmax_loss(scores, y)
        loss_reg = 0
        for i in range(num_filters):
            loss_reg +=  np.sum(W1[i]*W1[i])
        loss_reg += np.sum(W2*W2)
        loss_reg += np.sum(W3*W3)
        loss += 0.5 * self.reg * loss_reg

        doutAffRelu, grads['W3'], grads['b3'] = affine_backward(dscores, cache_fc)
        doutAffine = relu_backward(doutAffRelu, cache_affrelu)
        doutMaxPool, grads['W2'], grads['b2'] = affine_backward(doutAffine, cache_affine)
        doutMaxPool = doutMaxPool.reshape(maxPoolshape)
        doutCovRelu = max_pool_backward_naive(doutMaxPool, cache_maxpool)
        doutCov = relu_backward(doutCovRelu, cache_convrelu)
        dx, grads['W1'], grads['b1'] = conv_backward_naive(doutCov, cache_conv)

        grads['W3'] += self.reg * W3
        grads['W2'] += self.reg * W2
        grads['W1'] += self.reg * W1


        ############################################################################
        #                             END OF YOUR CODE                             #
        ############################################################################

        return loss, grads
