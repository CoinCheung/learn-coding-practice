from builtins import range
import numpy as np
import copy

from cs231n.build.liboutput import ffi,lib

def affine_forward(x, w, b):
    """
    Computes the forward pass for an affine (fully-connected) layer.

    The input x has shape (N, d_1, ..., d_k) and contains a minibatch of N
    examples, where each example x[i] has shape (d_1, ..., d_k). We will
    reshape each input into a vector of dimension D = d_1 * ... * d_k, and
    then transform it to an output vector of dimension M.

    Inputs:
    - x: A numpy array containing input data, of shape (N, d_1, ..., d_k)
    - w: A numpy array of weights, of shape (D, M)
    - b: A numpy array of biases, of shape (M,)

    Returns a tuple of:
    - out: output, of shape (N, M)
    - cache: (x, w, b)
    """
    out = None

    ###########################################################################
    # TODO: Implement the affine forward pass. Store the result in out. You   #
    # will need to reshape the input into rows.                               #
    ###########################################################################
    pass
    x_strentch = x.reshape(x.shape[0], -1)
    out = x_strentch.dot(w) + b
    ###########################################################################
    #                             END OF YOUR CODE                            #
    ###########################################################################
    cache = (x, w, b)
    return out, cache


def affine_backward(dout, cache):
    """
    Computes the backward pass for an affine layer.

    Inputs:
    - dout: Upstream derivative, of shape (N, M)
    - cache: Tuple of:
      - x: Input data, of shape (N, d_1, ... d_k)
      - w: Weights, of shape (D, M)

    Returns a tuple of:
    - dx: Gradient with respect to x, of shape (N, d1, ..., d_k)
    - dw: Gradient with respect to w, of shape (D, M)
    - db: Gradient with respect to b, of shape (M,)
    """
    x, w, b = cache
    dx, dw, db = None, None, None
    ###########################################################################
    # TODO: Implement the affine backward pass.                               #
    ###########################################################################
    pass
    shape = x.shape
    dw = x.reshape(shape[0], -1).T.dot(dout)
    dx = dout.dot(w.T)
    db = np.sum(dout, axis=0)
    dx = dx.reshape(shape)
    ###########################################################################
    #                             END OF YOUR CODE                            #
    ###########################################################################
    return dx, dw, db


def relu_forward(x):
    """
    Computes the forward pass for a layer of rectified linear units (ReLUs).

    Input:
    - x: Inputs, of any shape

    Returns a tuple of:
    - out: Output, of the same shape as x
    - cache: x
    """
    out = None
    ###########################################################################
    # TODO: Implement the ReLU forward pass.                                  #
    ###########################################################################
    pass
    out = copy.deepcopy(x)
    out[out <= 0] = 0
    ###########################################################################
    #                             END OF YOUR CODE                            #
    ###########################################################################
    cache = x
    return out, cache


def relu_backward(dout, cache):
    """
    Computes the backward pass for a layer of rectified linear units (ReLUs).

    Input:
    - dout: Upstream derivatives, of any shape
    - cache: Input x, of same shape as dout

    Returns:
    - dx: Gradient with respect to x
    """
    dx, x = None, cache
    ###########################################################################
    # TODO: Implement the ReLU backward pass.                                 #
    ###########################################################################
    pass
    dx = dout
    dx[x <= 0] = 0
    ###########################################################################
    #                             END OF YOUR CODE                            #
    ###########################################################################
    return dx


def batchnorm_forward(x, gamma, beta, bn_param):
    """
    Forward pass for batch normalization.

    During training the sample mean and (uncorrected) sample variance are
    computed from minibatch statistics and used to normalize the incoming data.
    During training we also keep an exponentially decaying running mean of the
    mean and variance of each feature, and these averages are used to normalize
    data at test-time.

    At each timestep we update the running averages for mean and variance using
    an exponential decay based on the momentum parameter:

    running_mean = momentum * running_mean + (1 - momentum) * sample_mean
    running_var = momentum * running_var + (1 - momentum) * sample_var

    Note that the batch normalization paper suggests a different test-time
    behavior: they compute sample mean and variance for each feature using a
    large number of training images rather than using a running average. For
    this implementation we have chosen to use running averages instead since
    they do not require an additional estimation step; the torch7
    implementation of batch normalization also uses running averages.

    Input:
    - x: Data of shape (N, D)
    - gamma: Scale parameter of shape (D,)
    - beta: Shift paremeter of shape (D,)
    - bn_param: Dictionary with the following keys:
      - mode: 'train' or 'test'; required
      - eps: Constant for numeric stability
      - momentum: Constant for running mean / variance.
      - running_mean: Array of shape (D,) giving running mean of features
      - running_var Array of shape (D,) giving running variance of features

    Returns a tuple of:
    - out: of shape (N, D)
    - cache: A tuple of values needed in the backward pass
    """
    mode = bn_param['mode']
    eps = bn_param.get('eps', 1e-5)
    momentum = bn_param.get('momentum', 0.9)

    N, D = x.shape
    running_mean = bn_param.get('running_mean', np.zeros(D, dtype=x.dtype))
    running_var = bn_param.get('running_var', np.zeros(D, dtype=x.dtype))

    out, cache = None, None
    if mode == 'train':
        #######################################################################
        # TODO: Implement the training-time forward pass for batch norm.      #
        # Use minibatch statistics to compute the mean and variance, use      #
        # these statistics to normalize the incoming data, and scale and      #
        # shift the normalized data using gamma and beta.                     #
        #                                                                     #
        # You should store the output in the variable out. Any intermediates  #
        # that you need for the backward pass should be stored in the cache   #
        # variable.                                                           #
        #                                                                     #
        # You should also use your computed sample mean and variance together #
        # with the momentum variable to update the running mean and running   #
        # variance, storing your result in the running_mean and running_var   #
        # variables.                                                          #
        #######################################################################
        pass
        mean = np.mean(x, axis=0).reshape(1, -1)
        var = np.var(x, axis=0, keepdims=True)
        running_mean = momentum * running_mean + (1-momentum) * mean
        running_var = momentum * running_var + (1-momentum) * var

        xnorm = (x - mean) / np.sqrt(var + eps)
        out = gamma * xnorm + beta

        cache = {}
        cache['x'] = x
        cache['xnorm'] = xnorm
        cache['gamma'] = gamma
        cache['var'] = var
        cache['eps'] = eps
        cache['xmean'] = mean
        #######################################################################
        #                           END OF YOUR CODE                          #
        #######################################################################
    elif mode == 'test':
        #######################################################################
        # TODO: Implement the test-time forward pass for batch normalization. #
        # Use the running mean and variance to normalize the incoming data,   #
        # then scale and shift the normalized data using gamma and beta.      #
        # Store the result in the out variable.                               #
        #######################################################################
        out = (x - running_mean) / np.sqrt(running_var + eps)
        out = gamma * out + beta
        #######################################################################
        #                          END OF YOUR CODE                           #
        #######################################################################
    else:
        raise ValueError('Invalid forward batchnorm mode "%s"' % mode)

    # Store the updated running means back into bn_param
    bn_param['running_mean'] = running_mean
    bn_param['running_var'] = running_var

    return out, cache


def batchnorm_backward(dout, cache):
    """
    Backward pass for batch normalization.

    For this implementation, you should write out a computation graph for
    batch normalization on paper and propagate gradients backward through
    intermediate nodes.

    Inputs:
    - dout: Upstream derivatives, of shape (N, D)
    - cache: Variable of intermediates from batchnorm_forward.

    Returns a tuple of:
    - dx: Gradient with respect to inputs x, of shape (N, D)
    - dgamma: Gradient with respect to scale parameter gamma, of shape (D,)
    - dbeta: Gradient with respect to shift parameter beta, of shape (D,)
    """
    dx, dgamma, dbeta = None, None, None
    ###########################################################################
    # TODO: Implement the backward pass for batch normalization. Store the    #
    # results in the dx, dgamma, and dbeta variables.                         #
    ###########################################################################
    pass
    x = cache['x']
    xnorm = cache['xnorm']
    gamma = cache['gamma']
    var = cache['var']
    eps = cache['eps']
    xmean = cache['xmean']

    N, D = x.shape
    gamma = gamma.reshape(1, D)

    dgamma = np.sum(xnorm*dout, axis=0)
    dbeta = np.sum(dout, axis=0)

    dxnorm = gamma * dout
    dvar = np.sum(-1/2*dxnorm*(x-xmean)*((var+eps)**(-3/2)), axis=0)
    dxmean = np.sum(-1/np.sqrt(var+eps)*dxnorm, axis=0) + dvar*np.sum(-2*(x-xmean)/N, axis=0)
    dx = dxnorm/np.sqrt(var+eps) + dvar*2*(x-xmean)/N + dxmean/N

    ###########################################################################
    #                             END OF YOUR CODE                            #
    ###########################################################################

    return dx, dgamma, dbeta


def batchnorm_backward_alt(dout, cache):
    """
    Alternative backward pass for batch normalization.

    For this implementation you should work out the derivatives for the batch
    normalizaton backward pass on paper and simplify as much as possible. You
    should be able to derive a simple expression for the backward pass.

    Note: This implementation should expect to receive the same cache variable
    as batchnorm_backward, but might not use all of the values in the cache.

    Inputs / outputs: Same as batchnorm_backward
    """
    dx, dgamma, dbeta = None, None, None
    ###########################################################################
    # TODO: Implement the backward pass for batch normalization. Store the    #
    # results in the dx, dgamma, and dbeta variables.                         #
    #                                                                         #
    # After computing the gradient with respect to the centered inputs, you   #
    # should be able to compute gradients with respect to the inputs in a     #
    # single statement; our implementation fits on a single 80-character line.#
    ###########################################################################
    pass
    x = cache['x']
    xnorm = cache['xnorm']
    gamma = cache['gamma']
    var = cache['var']
    eps = cache['eps']
    xmean = cache['xmean']

    N, D = x.shape
    gamma = gamma.reshape(1, D)

    dgamma = np.sum(xnorm*dout, axis=0)
    dbeta = np.sum(dout, axis=0)

    dxnorm = gamma * dout
    dvar = np.sum(-1/2*dxnorm*(x-xmean)*((var+eps)**(-3/2)), axis=0)
    dxmean = np.sum(-1/np.sqrt(var+eps)*dxnorm, axis=0)
    dx = dxnorm/np.sqrt(var+eps) + dvar*2*(x-xmean)/N + dxmean/N
    ###########################################################################
    #                             END OF YOUR CODE                            #
    ###########################################################################

    return dx, dgamma, dbeta


def dropout_forward(x, dropout_param):
    """
    Performs the forward pass for (inverted) dropout.

    Inputs:
    - x: Input data, of any shape
    - dropout_param: A dictionary with the following keys:
      - p: Dropout parameter. We drop each neuron output with probability p.
      - mode: 'test' or 'train'. If the mode is train, then perform dropout;
        if the mode is test, then just return the input.
      - seed: Seed for the random number generator. Passing seed makes this
        function deterministic, which is needed for gradient checking but not
        in real networks.

    Outputs:
    - out: Array of the same shape as x.
    - cache: tuple (dropout_param, mask). In training mode, mask is the dropout
      mask that was used to multiply the input; in test mode, mask is None.
    """
    p, mode = dropout_param['p'], dropout_param['mode']
    if 'seed' in dropout_param:
        np.random.seed(dropout_param['seed'])

    mask = None
    out = None

    if mode == 'train':
        #######################################################################
        # TODO: Implement training phase forward pass for inverted dropout.   #
        # Store the dropout mask in the mask variable.                        #
        #######################################################################
        mask = np.random.binomial(1, 1-p, size=x.shape)
        out = x * mask / (1-p)
        #######################################################################
        #                           END OF YOUR CODE                          #
        #######################################################################
    elif mode == 'test':
        #######################################################################
        # TODO: Implement the test phase forward pass for inverted dropout.   #
        #######################################################################
        out = x * (1-p)
        #######################################################################
        #                            END OF YOUR CODE                         #
        #######################################################################

    cache = (dropout_param, mask)
    #  out = out.astype(x.dtype, copy=False)

    return out, cache


def dropout_backward(dout, cache):
    """
    Perform the backward pass for (inverted) dropout.

    Inputs:
    - dout: Upstream derivatives, of any shape
    - cache: (dropout_param, mask) from dropout_forward.
    """
    dropout_param, mask = cache
    mode = dropout_param['mode']

    dx = None
    if mode == 'train':
        #######################################################################
        # TODO: Implement training phase backward pass for inverted dropout   #
        #######################################################################
        pass
        p = dropout_param['p']
        dx = dout * mask / (1-p)
        #######################################################################
        #                          END OF YOUR CODE                           #
        #######################################################################
    elif mode == 'test':
        dx = dout
    return dx


def conv_forward_naive(x, w, b, conv_param):
    """
    A naive implementation of the forward pass for a convolutional layer.

    The input consists of N data points, each with C channels, height H and
    width W. We convolve each input with F different filters, where each filter
    spans all C channels and has height HH and width WW.

    Input:
    - x: Input data of shape (N, C, H, W)
    - w: Filter weights of shape (F, C, HH, WW)
    - b: Biases, of shape (F,)
    - conv_param: A dictionary with the following keys:
      - 'stride': The number of pixels between adjacent receptive fields in the
        horizontal and vertical directions.
      - 'pad': The number of pixels that will be used to zero-pad the input.

    Returns a tuple of:
    - out: Output data, of shape (N, F, H', W') where H' and W' are given by
      H' = 1 + (H + 2 * pad - HH) / stride
      W' = 1 + (W + 2 * pad - WW) / stride
    - cache: (x, w, b, conv_param)
    """
    out = None
    ###########################################################################
    # TODO: Implement the convolutional forward pass.                         #
    # Hint: you can use the function np.pad for padding.                      #
    ###########################################################################
    stride = conv_param['stride']
    pad = conv_param['pad']
    x_pad = np.pad(x, ((0,0), (0,0), (pad, pad), (pad, pad)), 'constant')
    N, C, H, W = x_pad.shape
    F, CC, HH, WW = w.shape
    HO = int((H-HH) / stride + 1)
    WO = int((W-WW) / stride + 1)

    #  out = np.zeros((N, F, HO, WO))
    #  for n in range(N):
    #      xx = x_pad[n]
    #      for f in range(F):
    #          fltr = w[f]
    #          hpos = 0
    #          for i in range(HO):
    #              wpos = 0
    #              for j in range(WO):
    #                  area = xx[:, hpos:hpos+HH, wpos:wpos+WW]
    #                  out[n, f, i, j] = np.sum(area*fltr)
    #                  wpos = wpos + stride
    #              hpos = hpos + stride
    #          out[n, f] += b[f]

    out = np.zeros((N, F, HO, WO),dtype=np.float64)

    xpad_p = ffi.cast("double *", x_pad.ctypes.data)
    out_p = ffi.cast("double *", out.ctypes.data)
    w_p = ffi.cast("double *", w.ctypes.data)
    b_p = ffi.cast('double *', b.ctypes.data)
    lib.conv_forward(xpad_p, out_p, w_p, b_p, N, C, H, W, F, HO, WO, HH, WW, stride)
    ###########################################################################
    #                             END OF YOUR CODE                            #
    ###########################################################################
    cache = (x, w, b, conv_param)
    return out, cache


def conv_backward_naive(dout, cache):
    """
    A naive implementation of the backward pass for a convolutional layer.

    Inputs:
    - dout: Upstream derivatives.
    - cache: A tuple of (x, w, b, conv_param) as in conv_forward_naive

    Returns a tuple of:
    - dx: Gradient with respect to x
    - dw: Gradient with respect to w
    - db: Gradient with respect to b
    """
    dx, dw, db = None, None, None
    ###########################################################################
    # TODO: Implement the convolutional backward pass.                        #
    ###########################################################################
    x, w, b, conv_param = cache
    N, C, H, W = x.shape
    F, CC, HH, WW = w.shape
    N, F, OH, OW = dout.shape
    stride = conv_param['stride']
    pad = conv_param['pad']

    #  x_pad = np.pad(x, ((0,0),(0,0),(pad,pad),(pad,pad)), 'constant')
    #  dw = np.zeros(w.shape)
    #  db = np.zeros(b.shape)
    #  dx_pad = np.pad(np.zeros(x.shape), ((0,0),(0,0),(pad,pad),(pad,pad)), 'constant')
    #
    #  for n in range(N):
    #      for f in range(F):
    #          hpos = 0
    #          for i in range(OH):
    #              wpos = 0
    #              for j in range(OW):
    #                  window = x_pad[n, :, hpos:hpos+HH, wpos:wpos+WW]
    #                  dw[f] += dout[n, f, i, j] * window
    #                  db[f] += dout[n, f, i, j]
    #                  #  print(window)
    #                  dx_pad[n,:, hpos:hpos+HH, wpos:wpos+WW] += dout[n, f, i, j] * w[f]
    #                  wpos += stride
    #              hpos += stride

    x_pad = np.pad(x, ((0,0),(0,0),(pad,pad),(pad,pad)), 'constant')
    dw = np.zeros(w.shape)
    db = np.zeros(b.shape)
    #  dx_pad = np.pad(np.zeros(x.shape), ((0,0),(0,0),(pad,pad),(pad,pad)), 'constant')
    dx_pad = np.zeros((N, C, H+pad+pad, W+pad+pad))

    PN, PC, PH, PW = x_pad.shape

    xpad_p = ffi.cast('double*', x_pad.ctypes.data)
    dout_p = ffi.cast('double*', dout.ctypes.data)
    w_p = ffi.cast('double*', w.ctypes.data)
    dw_p = ffi.cast("double*", dw.ctypes.data)
    db_p = ffi.cast('double*', db.ctypes.data)
    dxpad_p = ffi.cast('double*', dx_pad.ctypes.data)

    lib.conv_backward(xpad_p, dout_p, w_p, dw_p, db_p, dxpad_p, N, C, PH, PW, F, HH, WW, OH, OW, stride)

    dx = dx_pad[:, :, pad:pad+H, pad:pad+W]
    ###########################################################################
    #                             END OF YOUR CODE                            #
    ###########################################################################
    return dx, dw, db


def max_pool_forward_naive(x, pool_param):
    """
    A naive implementation of the forward pass for a max pooling layer.

    Inputs:
    - x: Input data, of shape (N, C, H, W)
    - pool_param: dictionary with the following keys:
      - 'pool_height': The height of each pooling region
      - 'pool_width': The width of each pooling region
      - 'stride': The distance between adjacent pooling regions

    Returns a tuple of:
    - out: Output data
    - cache: (x, pool_param)
    """
    out = None
    ###########################################################################
    # TODO: Implement the max pooling forward pass                            #
    ###########################################################################
    pass
    pool_height = pool_param['pool_height']
    pool_width = pool_param['pool_width']
    stride = pool_param['stride']
    N, C, H, W = x.shape

    hnum = int((H-pool_height) / stride + 1)
    wnum = int((W-pool_width) / stride + 1)

    #  out = np.zeros((N, C, hnum, wnum))
    #
    #  hpos = 0
    #  for h in range(hnum):
    #      wpos = 0
    #      for w in range(wnum):
    #          window = x[:, :, hpos:hpos+pool_height, wpos:wpos+pool_width]
    #          out[:, :, h, w] = np.max(np.max(window, axis=2), axis=2)
    #          wpos += stride
    #      hpos += stride


    out = np.zeros((N, C, hnum, wnum))

    out_p = ffi.cast('double*', out.ctypes.data)
    x_p = ffi.cast('double*', x.ctypes.data)

    lib.pooling_forward(x_p, out_p, N, C, H, W, hnum, wnum, pool_height, pool_width, stride)

    ###########################################################################
    #                             END OF YOUR CODE                            #
    ###########################################################################
    cache = (x, pool_param)
    return out, cache


def max_pool_backward_naive(dout, cache):
    """
    A naive implementation of the backward pass for a max pooling layer.

    Inputs:
    - dout: Upstream derivatives
    - cache: A tuple of (x, pool_param) as in the forward pass.

    Returns:
    - dx: Gradient with respect to x
    """
    dx = None
    ###########################################################################
    # TODO: Implement the max pooling backward pass                           #
    ###########################################################################
    pass
    x, pool_param = cache
    pool_height = pool_param['pool_height']
    pool_width = pool_param['pool_width']
    stride = pool_param['stride']

    N, C, H, W = x.shape
    N, C, hnum, wnum = dout.shape

    dx = np.zeros(x.shape)

    #  for n in range(N):
    #      for c in range(C):
    #          hpos = 0
    #          for h in range(hnum):
    #              wpos = 0
    #              for w in range(wnum):
    #                  area = dout[n, c, h, w]
    #                  window = x[n, c, hpos:hpos+pool_height, wpos:wpos+pool_width]
    #                  window_max = np.max(window)
    #                  dtemp = np.zeros(window.shape)
    #                  dx[n, c, hpos:hpos+pool_height, wpos:wpos+pool_width][window_max == window] = area
    #                  wpos += stride
    #              hpos += stride


    dout_p = ffi.cast('double*', dout.ctypes.data)
    dx_p = ffi.cast('double*', dx.ctypes.data)
    x_p = ffi.cast('double*', x.ctypes.data)

    lib.max_pool_backward(dout_p, dx_p, x_p, N, C, H, W, hnum, wnum, pool_height, pool_width, stride)


    ###########################################################################
    #                             END OF YOUR CODE                            #
    ###########################################################################
    return dx


def spatial_batchnorm_forward(x, gamma, beta, bn_param):
    """
    Computes the forward pass for spatial batch normalization.

    Inputs:
    - x: Input data of shape (N, C, H, W)
    - gamma: Scale parameter, of shape (C,)
    - beta: Shift parameter, of shape (C,)
    - bn_param: Dictionary with the following keys:
      - mode: 'train' or 'test'; required
      - eps: Constant for numeric stability
      - momentum: Constant for running mean / variance. momentum=0 means that
        old information is discarded completely at every time step, while
        momentum=1 means that new information is never incorporated. The
        default of momentum=0.9 should work well in most situations.
      - running_mean: Array of shape (D,) giving running mean of features
      - running_var Array of shape (D,) giving running variance of features

    Returns a tuple of:
    - out: Output data, of shape (N, C, H, W)
    - cache: Values needed for the backward pass
    """
    out, cache = None, None

    ###########################################################################
    # TODO: Implement the forward pass for spatial batch normalization.       #
    #                                                                         #
    # HINT: You can implement spatial batch normalization using the vanilla   #
    # version of batch normalization defined above. Your implementation should#
    # be very short; ours is less than five lines.                            #
    ###########################################################################
    N, C, H, W = x.shape
    gamma = gamma.reshape(1,-1,1,1)
    beta = beta.reshape(1,-1,1,1)
    mode = bn_param.get('mode', 'train')
    eps = bn_param.get('eps', 1e-5)
    momentum = bn_param.get('momentum', 0.9)
    running_mean = bn_param.get('running_mean', np.ones((1, C, 1, 1)))
    running_var = bn_param.get('running_var', np.zeros((1, C, 1, 1)))

    if mode == 'train':
        xmean = np.mean(x, axis=(0,2,3), keepdims=True)
        xvar = np.var(x, axis=(0,2,3), keepdims=True)
        running_mean = momentum * running_mean + (1-momentum) * xmean
        running_var = momentum * running_var + (1-momentum) * xvar
        xnorm = (x - xmean) / np.sqrt(xvar + eps)
        out = gamma * xnorm + beta
        cache = (x, gamma, xmean, xvar, xnorm, eps)

    elif mode == 'test':
        xnorm = (x - running_mean) / np.sqrt(running_var + eps)
        out = gamma * xnorm + beta

    bn_param['running_mean'] = running_mean
    bn_param['running_var'] = running_var
    ###########################################################################
    #                             END OF YOUR CODE                            #
    ###########################################################################

    return out, cache


def spatial_batchnorm_backward(dout, cache):
    """
    Computes the backward pass for spatial batch normalization.

    Inputs:
    - dout: Upstream derivatives, of shape (N, C, H, W)
    - cache: Values from the forward pass

    Returns a tuple of:
    - dx: Gradient with respect to inputs, of shape (N, C, H, W)
    - dgamma: Gradient with respect to scale parameter, of shape (C,)
    - dbeta: Gradient with respect to shift parameter, of shape (C,)
    """
    dx, dgamma, dbeta = None, None, None

    ###########################################################################
    # TODO: Implement the backward pass for spatial batch normalization.      #
    #                                                                         #
    # HINT: You can implement spatial batch normalization using the vanilla   #
    # version of batch normalization defined above. Your implementation should#
    # be very short; ours is less than five lines.                            #
    ###########################################################################
    pass
    N, C, H, W = dout.shape
    x, gamma, xmean, xvar, xnorm, eps = cache

    dbeta = np.sum(dout, axis=(0,2,3))
    dgamma = np.sum(xnorm*dout, axis=(0,2,3))

    dxnorm = gamma * dout
    dxvar = np.sum(-1/2*dxnorm*(x-xmean)*((xvar+eps)**(-3/2)), axis=(0,2,3), keepdims=True)
    dxmean = np.sum(-1/np.sqrt(xvar+eps)*dxnorm, axis=(0,2,3), keepdims=True)
    dx = dxnorm/np.sqrt(xvar+eps) + dxvar*2*(x-xmean)/N/H/W + dxmean/N/H/W

#############
    #  dout = dout.transpose(0,2,3,1).reshape(-1,C)
    #  cache = {}
    #  cache['x'] = x.transpose(0,2,3,1).reshape(-1,C)
    #  cache['xnorm'] = xnorm.transpose(0,2,3,1).reshape(-1,C)
    #  cache['gamma'] = gamma.reshape(1,-1)
    #  cache['var'] = xvar.reshape(1,-1)
    #  cache['eps'] = eps
    #  cache['xmean'] = xmean.reshape(1,-1)
    #  dx, dgamma, dbeta = batchnorm_backward(dout, cache)
    #  dx = dx.reshape(N, H, W, C).transpose(0,3,1,2)
#############
    ###########################################################################
    #                             END OF YOUR CODE                            #
    ###########################################################################

    return dx, dgamma, dbeta


def svm_loss(x, y):
    """
    Computes the loss and gradient using for multiclass SVM classification.

    Inputs:
    - x: Input data, of shape (N, C) where x[i, j] is the score for the jth
      class for the ith input.
    - y: Vector of labels, of shape (N,) where y[i] is the label for x[i] and
      0 <= y[i] < C

    Returns a tuple of:
    - loss: Scalar giving the loss
    - dx: Gradient of the loss with respect to x
    """
    N = x.shape[0]
    correct_class_scores = x[np.arange(N), y]
    margins = np.maximum(0, x - correct_class_scores[:, np.newaxis] + 1.0)
    margins[np.arange(N), y] = 0
    loss = np.sum(margins) / N
    num_pos = np.sum(margins > 0, axis=1)
    dx = np.zeros_like(x)
    dx[margins > 0] = 1
    dx[np.arange(N), y] -= num_pos
    dx /= N
    return loss, dx


def softmax_loss(x, y):
    """
    Computes the loss and gradient for softmax classification.

    Inputs:
    - x: Input data, of shape (N, C) where x[i, j] is the score for the jth
      class for the ith input.
    - y: Vector of labels, of shape (N,) where y[i] is the label for x[i] and
      0 <= y[i] < C

    Returns a tuple of:
    - loss: Scalar giving the loss
    - dx: Gradient of the loss with respect to x
    """
    shifted_logits = x - np.max(x, axis=1, keepdims=True)
    Z = np.sum(np.exp(shifted_logits), axis=1, keepdims=True)
    log_probs = shifted_logits - np.log(Z)
    probs = np.exp(log_probs)
    N = x.shape[0]
    loss = -np.sum(log_probs[np.arange(N), y]) / N
    dx = probs.copy()
    dx[np.arange(N), y] -= 1
    dx /= N
    return loss, dx
