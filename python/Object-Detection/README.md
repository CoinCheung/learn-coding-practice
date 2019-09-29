# Object-Detection

notes:
1. input images should be resized to [600(short edge)-1000(long edge)]

2. methods to generate anchor: 
* compute downsample stride from original image to the lastest feature map.
* use the size of latest feature map (w,h) and stride to compute all the locations of anchor base on the original image
* compute anchors at one location according to the anchor base size and the ratios and scales
* add the locations to the anchors at one place to derive all the anchors on the original image

3. training is performed with batch_size = 1, namely, the training samples are fed into the network one by one

4. tricks used in rpn predicting bbox
1) clip bbox according to the boundary of the image
2) remove predicted bbox whose height or width less than a threshold
3) choose top K bbox from the prediction according to the front ground scores computed from rpn
4) perform nms to reduce overlapped bbox
5) another round of topK accroding to the scores after nms
6) generate 128 bbox proposals from each image (background and front ground in total), known as batch size with ratio between fg and bg to be 0.25.


5. training and loss
1) before training, positive and negative samples should be chosen from the generated proposals. positive samples are those with highest IoU to any ground truths, and those have IoU with any ground truths higher than 0.7. As for the negative samples, they are those proposals with IoU to all ground thuths lower than 0.3. proposals that are assigned neither positive nor negative are not considered.

2) rpn loss is combined with two portions: one is cross entropy loss computed with classification outputs (with positive samples to be 1 and negative ones to be 0). The other one is smooth L1 loss between t_i and t_i^star, where t_i and t_i^star are the 4 numbers tuples of offset and scale between chosen proposals and anchors and those between ground truth and anchors.




