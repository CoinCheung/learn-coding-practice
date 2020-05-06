from PIL import Image
import numpy as np
import random

def drop_channels(img):
    arr = np.array(img)
    n_drops = random.randint(0, 2)
    H, W = arr.shape[:2]
    if n_drops == 1:
        channels = random.sample([0, 1, 2], 1)
        arr[:, :, channels[0]] = 255
        #  arr[:, :, channels[0]] = np.random.randint(0, 256, (H, W), dtype=np.uint8)
    elif n_drops == 2:
        channels = random.sample([0, 1, 2], 2)
        arr[:, :, channels[0]] = 255
        arr[:, :, channels[1]] = 255
        #  arr[:, :, channels[0]] = np.random.randint(0, 256, (H, W), dtype=np.uint8)
        #  arr[:, :, channels[1]] = np.random.randint(0, 256, (H, W), dtype=np.uint8)
    img = Image.fromarray(arr)
    return img


img = Image.open('image.jpg')
out = drop_channels(img)
out.show()
