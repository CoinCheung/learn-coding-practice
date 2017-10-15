import numpy as np
from random import shuffle
from past.builtins import xrange

def softmax_loss_naive(W, X, y, reg):
  """
  Softmax loss function, naive implementation (with loops)

  Inputs have dimension D, there are C classes, and we operate on minibatches
  of N examples.

  Inputs:
  - W: A numpy array of shape (D, C) containing weights.
  - X: A numpy array of shape (N, D) containing a minibatch of data.
  - y: A numpy array of shape (N,) containing training labels; y[i] = c means
    that X[i] has label c, where 0 <= c < C.
  - reg: (float) regularization strength

  Returns a tuple of:
  - loss as single float
  - gradient with respect to weights W; an array of same shape as W
  """
  # Initialize the loss and gradient to zero.
  loss = 0.0
  dW = np.zeros_like(W)

  num_train = X.shape[0]
  num_class = W.shape[1]

  scores = X.dot(W)
  scores = scores - np.max(scores, axis = 1).reshape(num_train,1)
  scores_correct = scores[np.arange(num_train), y].reshape(num_train, 1)
  for i in range(X.shape[0]):
    # loss
    #  score_diff = scores[i]* 2
    score_diff = scores[i] - scores_correct[i]
    score_diff_exp = np.exp(score_diff)
    score_diff_exp_sum = np.sum(score_diff_exp)
    loss += np.log(score_diff_exp_sum) - np.log(score_diff_exp[y[i]])

    # grad
    for j in range(num_class):
        dW[:,j] += (score_diff_exp[y[i]]/score_diff_exp_sum) * X[i].T
    dW[:,y[i]] -= X[i].T


  loss = loss/num_train + 0.5*reg*np.sum(W*W)
  dW = dW/num_train + reg*W


  #############################################################################
  # TODO: Compute the softmax loss and its gradient using explicit loops.     #
  # Store the loss in loss and the gradient in dW. If you are not careful     #
  # here, it is easy to run into numeric instability. Don't forget the        #
  # regularization!                                                           #
  #############################################################################
  pass
  #############################################################################
  #                          END OF YOUR CODE                                 #
  #############################################################################

  return loss, dW


def softmax_loss_vectorized(W, X, y, reg):
  """
  Softmax loss function, vectorized version.

  Inputs and outputs are the same as softmax_loss_naive.
  """
  # Initialize the loss and gradient to zero.
  loss = 0.0
  dW = np.zeros_like(W)

  num_train = X.shape[0]
  num_class = W.shape[1]

  # loss function
  scores = X.dot(W)
  scores = scores - np.max(scores, axis = 1).reshape(num_train,1)

  scores_exp = np.exp(scores)
  scores_exp_sum = np.sum(scores_exp, axis = 1).reshape(num_train,1)
  prob = scores_exp/scores_exp_sum
  prob_correct = prob[np.arange(num_train), y].reshape(num_train,1)
  loss = np.sum(-np.log(prob_correct))/num_train + 0.5*reg*np.sum(W*W)


  # gradient
  scores_exp_correct = scores_exp[np.arange(num_train),y].reshape(num_train,1)
  scale = scores_exp_correct/scores_exp_sum
  dW += scale.T.dot(X).T

  tempW = np.zeros((num_train, num_class))
  tempW[np.arange(num_train),y] = 1
  dW -= X.T.dot(tempW)
  dW = dW/num_train + reg*W



  #############################################################################
  # TODO: Compute the softmax loss and its gradient using no explicit loops.  #
  # Store the loss in loss and the gradient in dW. If you are not careful     #
  # here, it is easy to run into numeric instability. Don't forget the        #
  # regularization!                                                           #
  #############################################################################
  pass
  #############################################################################
  #                          END OF YOUR CODE                                 #
  #############################################################################

  return loss, dW

