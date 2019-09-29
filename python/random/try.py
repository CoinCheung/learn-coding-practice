
import pickle
import random
import numpy as np
import torch

random.seed(123)
np.random.seed(123)
torch.manual_seed(123)

#  for _ in range(10):
#      _ = random.random()
#
#  st = random.getstate()
#  with open('random.pkl', 'wb') as fw:
#      pickle.dump(st, fw)

#  with open('random.pkl', 'rb') as fr:
#      st = pickle.load(fr)
#  random.setstate(st)
#  for _ in range(5):
#      print(random.random())

### torch
for _ in range(10):
    _ = torch.randn(1)

st = torch.get_rng_state()
with open('random.pkl', 'wb') as fw:
    pickle.dump(st, fw)

with open('random.pkl', 'rb') as fr:
    st = pickle.load(fr)
torch.set_rng_state(st)
for _ in range(5):
    print(torch.randn(1))

