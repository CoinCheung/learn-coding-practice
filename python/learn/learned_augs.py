import random

import numpy as np
import cv2


class RandomApply(object):

    def __init__(self, p=0.1):
        self.p = p

    def __call__(self, p, img, bboxes):
        if np.random.random() < p:
            img, bboxes = self.trans_func(img, bboxes)
        return img, bboxes


def get_valid_bboxes(gt_bboxes):
    n_boxes = gt_bboxes.shape[0]
    ws = gt_bboxes[:, 2] - gt_bboxes[:, 0]
    hs = gt_bboxes[:, 3] - gt_bboxes[:, 1]
    ws, hs = ws.astype(np.int32), hs.astype(np.int32)
    valid_idx = np.logical_and(ws>=1, hs>=1)
    gt_bboxes = gt_bboxes[valid_idx]
    #
    #  for box in gt_bboxes:
    #      x1, y1, x2, y2 = box.tolist()
    #      w, h = x2-x1, y2-y1
    #      if w <= 0 or h <= 0:
    #          print('abnormal bbox: {}'.format(box))

    return gt_bboxes


def do_learned_augs(img, gt_bboxes):
    gt_bboxes = get_valid_bboxes(gt_bboxes)
    aug_obj = LearnedAugs()
    img, gt_bboxes = aug_obj(img, gt_bboxes)
    return img, gt_bboxes


class LearnedAugs(object):
    def __init__(self):
        self.policies = []
        self.policies.append(SubPolicy1())
        self.policies.append(SubPolicy2())
        self.policies.append(SubPolicy3())
        self.policies.append(SubPolicy4())
        self.policies.append(SubPolicy5())

    def __call__(self, img, gt_bboxes):
        idx = random.choice(range(5))
        img, gt_bboxes = self.policies[idx](img, gt_bboxes)
        return img, gt_bboxes


def warp_image_and_bbox(img, gt_bboxes, M):
    rows, cols, _ = img.shape
    n_boxes = gt_bboxes.shape[0]
    # warp image
    img = cv2.warpAffine(img, M, (cols, rows))
    # warp bboxes
    x1 = gt_bboxes[:, 0].reshape(-1, 1)
    y1 = gt_bboxes[:, 1].reshape(-1, 1)
    x2 = gt_bboxes[:, 2].reshape(-1, 1)
    y2 = gt_bboxes[:, 3].reshape(-1, 1)
    xys = np.hstack([
        x1, y1, x1, y2, x2, y2, x2, y1
    ]).reshape(-1, 2)
    xys = np.hstack([xys, np.ones((4*n_boxes, 1))]).T
    xys = np.matmul(M, xys).T
    xys = xys[:, :2].reshape(-1, 8)
    xs = xys[:, [0, 2, 4, 6]]
    ys = xys[:, [1, 3, 5, 7]]
    xmin = np.clip(np.min(xs, 1).reshape(-1, 1), 0, cols-1)
    xmax = np.clip(np.max(xs, 1).reshape(-1, 1), 0, cols-1)
    ymin = np.clip(np.min(ys, 1).reshape(-1, 1), 0, rows-1)
    ymax = np.clip(np.max(ys, 1).reshape(-1, 1), 0, rows-1)
    gt_bboxes = np.hstack([xmin, ymin, xmax, ymax]).astype(np.float32)
    return img, gt_bboxes


def bbox_only_translate_y(img, gt_bboxes, p, mm):
    n_boxes = gt_bboxes.shape[0]
    for i in range(n_boxes):
        x1, y1, x2, y2 = [int(el) for el in gt_bboxes[i].tolist()]
        if random.random() < p:
            m = random.choice([-mm, mm])
            M = np.float32([[1, 0, 0], [0, 1, m]])
            rows, cols = y2 - y1, x2 - x1
            img[y1:y2, x1:x2, :] = cv2.warpAffine(
                img[y1:y2, x1:x2, :], M, (cols, rows)
            )
    return img, gt_bboxes


class SubPolicy1(object):
    '''
    translateX and equalize
    '''
    def __init__(self):
        self.p1, self.p2 = 0.6, 0.8
        self.m1, self.m2 = -30, 10

    def __call__(self, img, gt_bboxes):
        rows, cols = img.shape[0], img.shape[1]
        if random.random() < self.p1:
            m = random.choice([self.m1, -self.m1])
            M = np.float32([[1, 0, m], [0, 1, 0]])
            img = cv2.warpAffine(img, M, (cols, rows))
            gt_bboxes[..., 0] += m
            gt_bboxes[..., 2] += m
            gt_bboxes[..., 0] = np.clip(gt_bboxes[..., 0], 0, cols-1)
            gt_bboxes[..., 2] = np.clip(gt_bboxes[..., 2], 0, cols-1)

        if random.random() < self.p2:
            im_yuv = cv2.cvtColor(img, cv2.COLOR_BGR2YUV)
            im_yuv[:, :, 0] = cv2.equalizeHist(im_yuv[:, :, 0])
            img = cv2.cvtColor(im_yuv, cv2.COLOR_YUV2BGR)
        return img, gt_bboxes


class SubPolicy2(object):
    '''
    bbox_only_translate_y and cutout
    '''
    def __init__(self):
        self.p1, self.p2 = 0.2, 0.8
        self.m1, self.m2 = 10, 20

    def __call__(self, img, gt_bboxes):
        img, gt_bboxes = bbox_only_translate_y(
                img, gt_bboxes, self.p1, self.m1
        )
        # TODO: try to set the area to grayscale rather than 0
        if random.random() < self.p2:
            h, w, _ = img.shape
            x, y = np.random.randint(w), np.random.randint(h)
            x1 = np.clip(x - self.m2//2, 0, w)
            x2 = np.clip(x + self.m2//2, 0, w)
            y1 = np.clip(y - self.m2//2, 0, h)
            y2 = np.clip(y + self.m2//2, 0, h)
            img[y1:y2+1, x1:x2+1, :] = 0
        return img, gt_bboxes


class SubPolicy3(object):
    '''
    sheary and bbox_only_translate_y
    '''
    def __init__(self):
        self.p1, self.p2 = 1, 0.6
        self.m1, self.m2 = 2, 6

    def __call__(self, img, gt_bboxes):
        rows, cols = img.shape[0], img.shape[1]
        if random.random() < self.p1:
            m = random.choice([self.m1, -self.m1])
            m = m * np.pi / 180
            M = np.float32([[1, 0, 0], [m, 1, 0]])
            img, gt_bboxes = warp_image_and_bbox(img, gt_bboxes, M)

        img, gt_bboxes = bbox_only_translate_y(
                img, gt_bboxes, self.p2, self.m2
        )
        return img, gt_bboxes


class SubPolicy4(object):
    '''
    rotate and color
    '''
    def __init__(self):
        self.p1, self.p2 = 0.6, 1.0
        self.m1, self.m2 = 20, 0.6

    def __call__(self, img, gt_bboxes):
        rows, cols = img.shape[0], img.shape[1]
        if random.random() < self.p1:
            m = random.choice([self.m1, -self.m1])
            M = cv2.getRotationMatrix2D((cols/2, rows/2), m, 1.)
            img, gt_bboxes = warp_image_and_bbox(img, gt_bboxes, M)

        if random.random() < self.p2:
            M = np.float32([
                [1+2*self.m2, 1-self.m2, 1-self.m2],
                [1-self.m2, 1+2*self.m2, 1-self.m2],
                [1-self.m2, 1-self.m2, 1+2*self.m2],
                ])
            shape = img.shape
            img = np.matmul(img.reshape(-1, 3), M).reshape(shape)/3
            img = img.astype(np.uint8)
        return img, gt_bboxes


class SubPolicy5(object):
    '''
    do nothing
    '''
    def __init__(self):
        self.p1, self.p2 = 0.6, 1.0
        self.m1, self.m2 = 10, 6

    def __call__(self, img, gt_bboxes):
        return img, gt_bboxes



if __name__ == '__main__':
    im = cv2.imread('./leon.jpg')
    poly = SubPolicy1()
    im, _ = poly(im, np.empty((10, 4)))

    import json
    jpth = '/home/coin/Documents/Work/Haishen/log/detectron/lib/datasets/data/coco/annotations/instances_minival2014.json'
    imgpth = '/home/coin/Documents/Work/Haishen/detectron/detectron/lib/datasets/data/coco/coco_val2014/'
    with open(jpth, 'r') as fr:
        jobj = json.load(fr)
        img = jobj['images'][2]
        imid = img['id']
        anns = [ann for ann in jobj['annotations'] if ann['image_id'] == imid]
    impath = imgpth + img['file_name']
    im = cv2.imread(impath)
    gt_bboxes = []
    for ann in anns:
        x1, y1, w, h = [int(el) for el in ann['bbox']]
        x2, y2 = x1 + w, y1 + h
        gt_bboxes.append([x1, y1, x2, y2])
        #  print(x1, y1, x2, y2)
        #  cv2.rectangle(im, (x1, y1), (x2, y2), (155, 0, 0), 3)
    gt_bboxes = np.array(gt_bboxes)

    #  poly = SubPolicy3()
    #  poly.p1 = 1
    #  poly.m1 = 20
    #  poly.p2 = 1
    #  #  poly.m2 = 0.5
    #  im, gt_bboxes = poly(im, gt_bboxes)
    im, gt_bboxes = do_learned_augs(im, gt_bboxes)
    for box in gt_bboxes:
        x1, y1, x2, y2 = box
        cv2.rectangle(im, (x1, y1), (x2, y2), (155, 0, 0), 3)

    cv2.imshow('org', im)
    cv2.waitKey(0)


