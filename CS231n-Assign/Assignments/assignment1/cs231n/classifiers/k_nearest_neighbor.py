import numpy as np
from past.builtins import xrange


class KNearestNeighbor(object):
  """ a kNN classifier with L2 distance """

  def __init__(self):
    pass

  def train(self, X, y):
    """
    Train the classifier. For k-nearest neighbors this is just
    memorizing the training data.

    Inputs:
    - X: A numpy array of shape (num_train, D) containing the training data
      consisting of num_train samples each of dimension D.
    - y: A numpy array of shape (N,) containing the training labels, where
         y[i] is the label for X[i].
    """
    self.X_train = X
    self.y_train = y

  def predict(self, X, k=1, num_loops=0):
    """
    Predict labels for test data using this classifier.

    Inputs:
    - X: A numpy array of shape (num_test, D) containing test data consisting
         of num_test samples each of dimension D.
    - k: The number of nearest neighbors that vote for the predicted labels.
    - num_loops: Determines which implementation to use to compute distances
      between training points and testing points.

    Returns:
    - y: A numpy array of shape (num_test,) containing predicted labels for the
      test data, where y[i] is the predicted label for the test point X[i].
    """
    if num_loops == 0:
      dists = self.compute_distances_no_loops(X)
    elif num_loops == 1:
      dists = self.compute_distances_one_loop(X)
    elif num_loops == 2:
      dists = self.compute_distances_two_loops(X)
    else:
      raise ValueError('Invalid value %d for num_loops' % num_loops)

    return self.predict_labels(dists, k=k)

  def compute_distances_two_loops(self, X):
    """
    Compute the distance between each test point in X and each training point
    in self.X_train using a nested loop over both the training data and the
    test data.

    Inputs:
    - X: A numpy array of shape (num_test, D) containing test data.

    Returns:
    - dists: A numpy array of shape (num_test, num_train) where dists[i, j]
      is the Euclidean distance between the ith test point and the jth training
      point.
    """
    #  def cal_vector_dis(v1,v2): this method is kind of slow
    #    len = v1.shape[0]
    #    sum = 0
    #    for i in range(len):
    #      sum += np.power((v1[i]-v2[i]),2)
    #    return np.power(sum,0.5)

    print('in sub function')
    import sys
    sys.path.append('./coin')
    from mylib import ffi, lib

    num_test = X.shape[0]
    num_train = self.X_train.shape[0]

    dists = np.zeros((num_test, num_train),dtype = np.float64)


## with partial cffi optimized method
    #  for i in xrange(num_test):
    #    print('looping with i to be {0}'.format(i))
    #    for j in xrange(num_train):
    #      #  dists[i][j] = cal_vector_dis(X[i],self.X_train[j])
    #      v1 = ffi.new('double []', list(X[i]))
    #      v2 = ffi.new('double []', list(self.X_train[j]))
    #      dists[i][j] = lib.cal_vector_dis(v1,v2, X[i].shape[0])
    #
    #  print('calculation done')

## with completely cffi optimized method
    lib.printhello()
    vlive1 = [ffi.new('double []',list(X[i])) for i in range(num_test)]
    vlive2 = [ffi.new('double []',list(self.X_train[j])) for j in range(num_train)]
    dislive = ffi.new('double *')

    v1 = ffi.new('double *[]', vlive1)
    v2 = ffi.new('double *[]', vlive2)


    dislive = lib.cal_dists(v1,v2,X.shape[0],X.shape[1],self.X_train.shape[0],self.X_train.shape[1])

    dis2d = ffi.cast('double (*)[{0}]'.format(num_train), dislive)

    print(dislive[100000])
    print(dir(dislive))

    for i in range(num_test):
        for j in range(num_train):
            dists[i][j] = dis2d[i][j]

    lib.freeheap(dislive)

    print('done')

        #####################################################################
        # TODO:                                                             #
        # Compute the l2 distance between the ith test point and the jth    #
        # training point, and store the result in dists[i, j]. You should   #
        # not use a loop over dimension.                                    #
        #####################################################################
        #####################################################################
        #                       END OF YOUR CODE                            #
        #####################################################################
    return dists

  def compute_distances_one_loop(self, X):
    """
    Compute the distance between each test point in X and each training point
    in self.X_train using a single loop over the test data.

    Input / Output: Same as compute_distances_two_loops
    """

    import sys
    sys.path.append('./coin')
    from mylib import ffi, lib

    num_test = X.shape[0]
    num_train = self.X_train.shape[0]

    dists = np.zeros((num_test, num_train),dtype = np.float64)

    #  dists = np.array([]).reshape(-1,num_train)

    for i in range(num_test):
        test_vec = X[i]
        diff_mtrx = test_vec - self.X_train
        diff_mtrx_sqr = np.square(diff_mtrx)
        sum_mtrx = np.sum(diff_mtrx_sqr, axis = 1)
        dis_one_row = np.sqrt(sum_mtrx).T
        dists[i,:] = dis_one_row
        #  print('done with {}'.format(i))

    print(dists.shape)

    print('done')
      #######################################################################
      # TODO:                                                               #
      # Compute the l2 distance between the ith test point and all training #
      # points, and store the result in dists[i, :].                        #
      #######################################################################
      #######################################################################
      #                         END OF YOUR CODE                            #
      #######################################################################
    return dists

  def compute_distances_no_loops(self, X):
    """
    Compute the distance between each test point in X and each training point
    in self.X_train using no explicit loops.

    Input / Output: Same as compute_distances_two_loops
    """
    num_test = X.shape[0]
    num_train = self.X_train.shape[0]
    dists = np.zeros((num_test, num_train))

    test_sqr_vec = np.sum(np.square(X),axis = 1).reshape(num_test,1)
    train_sqr_vec = np.sum(np.square(self.X_train),axis = 1).reshape(1,num_train)
    test_train_cross = np.dot(X, self.X_train.T)*(-2)#.reshape(num_test,num_train)
    print('cross')
    dists = dists + test_sqr_vec
    dists = dists + train_sqr_vec
    dists = dists + test_train_cross
    dists = np.sqrt(dists)

    #########################################################################
    # TODO:                                                                 #
    # Compute the l2 distance between all test points and all training      #
    # points without using any explicit loops, and store the result in      #
    # dists.                                                                #
    #                                                                       #
    # You should implement this function using only basic array operations; #
    # in particular you should not use functions from scipy.                #
    #                                                                       #
    # HINT: Try to formulate the l2 distance using matrix multiplication    #
    #       and two broadcast sums.                                         #
    #########################################################################
    pass
    #########################################################################
    #                         END OF YOUR CODE                              #
    #########################################################################
    return dists

  def predict_labels(self, dists, k=1):
    """
    Given a matrix of distances between test points and training points,
    predict a label for each test point.

    Inputs:
    - dists: A numpy array of shape (num_test, num_train) where dists[i, j]
      gives the distance betwen the ith test point and the jth training point.

    Returns:
    - y: A numpy array of shape (num_test,) containing predicted labels for the
      test data, where y[i] is the predicted label for the test point X[i].
    """

    import copy

    num_test = dists.shape[0]
    y_pred = np.zeros(num_test)

    # calcultate the labels of the nearest points
    closest_y = []
    test_dicts = []
    #  print('k is {}'.format(k))
    for i in xrange(num_test):
      res_row = []
      label_dict = dict()
      dis_vec_copy = copy.copy(dists[i])
      for j in range(k):
        indmin = np.argmin(dis_vec_copy)
        res_row.append(self.y_train[indmin])
        dis_vec_copy = np.delete(dis_vec_copy,indmin,axis = 0)

        if self.y_train[indmin] in label_dict:
          label_dict[self.y_train[indmin]] += 1
        else:
          label_dict[self.y_train[indmin]] = 1
      test_dicts.append(label_dict)

    # analyze and pick the highest vote
    for i in range(num_test):
      y_pred[i] = max(test_dicts[i],key = test_dicts[i].get)





      # A list of length k storing the labels of the k nearest neighbors to
      # the ith test point.
      #########################################################################
      # TODO:                                                                 #
      # Use the distance matrix to find the k nearest neighbors of the ith    #
      # testing point, and use self.y_train to find the labels of these       #
      # neighbors. Store these labels in closest_y.                           #
      # Hint: Look up the function numpy.argsort.                             #
      #########################################################################
      pass
      #########################################################################
      # TODO:                                                                 #
      # Now that you have found the labels of the k nearest neighbors, you    #
      # need to find the most common label in the list closest_y of labels.   #
      # Store this label in y_pred[i]. Break ties by choosing the smaller     #
      # label.                                                                #
      #########################################################################
      pass
      #########################################################################
      #                           END OF YOUR CODE                            #
      #########################################################################

    return y_pred

  def split_folds(self,num_folds):
    import numpy as np
    return np.split(self.X_train,num_folds, axis = 0), np.split(self.y_train,num_folds)

  def cross_validation(self, x_train_folds, y_train_folds, k_choises):
    import numpy as np
    subclassifier = KNearestNeighbor()

    k_to_accuracies = dict()
    for k in k_choises:
      k_to_accuracies[k] = []
      for i in range(len(x_train_folds)):
        print('k is {} and i is {}'.format(k,i))
        valid_x = x_train_folds[i]
        valid_y = y_train_folds[i]
        train_x = np.vstack(tuple(x_train_folds[:i]) + tuple(x_train_folds[i+1:]))
        train_y = np.hstack(tuple(y_train_folds[:i]) + tuple(y_train_folds[i+1:]))
        num_test = valid_y.shape[0]

        subclassifier.train(train_x, train_y)

        sub_y_test_pred = subclassifier.predict(valid_x, k = k)
        num_correct = np.sum(sub_y_test_pred == valid_y)
        accuracy = float(num_correct) / num_test

        k_to_accuracies[k].append(accuracy)

    return k_to_accuracies
