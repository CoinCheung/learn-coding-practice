#!/usr/bin/python


import numpy as np

a = np.arange(12).reshape((4,3))

w1 = np.arange(12).reshape((3,4))/10
w2 = np.arange(20).reshape((4,5))/10
w3 = np.arange(30).reshape((5,6))/10

print('scores:')
fc1 = a.dot(w1)
relu1 = fc1.copy()
relu1[relu1<0] = 0
fc2 = relu1.dot(w2)
relu2 = fc2.copy()
relu2[relu2<0] = 0
scores = relu2.dot(w3)
print(scores)

def softmax(scores):
    scores = scores - np.max(scores, axis=1, keepdims=True)
    exp = np.exp(scores)
    exp_sum = np.sum(exp, axis=1, keepdims=True)
    return exp/exp_sum

sftmx = softmax(scores)
print("softmax")
print(sftmx)

label = np.array([1,1,1,1])
def ce_loss(softmax, label):
    def one_hot(label, num):
        oh = np.zeros((label.size, num))
        oh[:,label] = 1
        return oh

    onehot = one_hot(label, sftmx.shape[1])
    print("one hot")
    print(onehot)
    ce = np.sum(np.log(sftmx+1e-12) * onehot, axis=1)
    print("ce before mean")
    print(ce)
    ce = -np.mean(ce)
    return ce

ce = ce_loss(sftmx, label)
print("loss")
print(ce)


### backward
sftmx[:,label] -= 1
grad_fc3 = sftmx
grad_relu2 = grad_fc3.dot(w3.T)
grad_fc2 = grad_relu2.copy()
grad_fc2[fc2<0] = 0
grad_relu1 = grad_fc2.dot(w2.T)
grad_fc1 = grad_relu1.copy()
grad_fc1[fc1<0] = 0
grad_in = grad_fc1.dot(w1.T)
print(grad_in)



