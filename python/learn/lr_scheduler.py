#!/usr/bin/python
# -*- encoding: utf-8 -*-


import logging
import torch


class WarmupPolyLrScheduler(torch.optim.lr_scheduler._LRScheduler):
    def __init__(
            self,
            optimizer,
            power,
            max_iter,
            warmup_iter,
            warmup_ratio=0.1,
            warmup='exp',
            last_epoch=-1,
     ):
        self.power = power
        self.max_iter = max_iter
        self.warmup_iter = warmup_iter
        self.warmup_ratio = warmup_ratio
        self.warmup = warmup
        super(WarmupPolyLrScheduler, self).__init__(optimizer, last_epoch)

    def get_lr(self):
        if self.last_epoch < self.warmup_iter:
            ratio = self.get_warmup_ratio()
        else:
            real_iter = self.last_epoch - self.warmup_iter
            real_max_iter = self.max_iter - self.warmup_iter
            alpha = real_iter / real_max_iter
            ratio = (1 - alpha) ** self.power
        lrs = [ratio * lr for lr in self.base_lrs]
        return lrs

    def get_warmup_ratio(self):
        assert warmup in ('linear', 'exp')
        alpha = self.last_epoch / self.warmup_iter
        if warmup == 'linear':
            ratio = self.warmup_ratio + (1 - self.warmup_ratio) * alpha
        elif warmup == 'exp':
            ratio = self.warmup_ratio ** (1. - alpha)
        return ratio
