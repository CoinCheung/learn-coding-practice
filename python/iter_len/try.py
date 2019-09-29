#!/usr/bin/python
#! -*- encoding: utf-8 -*-


class clss(object):
    def __init__(self, strng):
        self.strng = strng
        self.pos = 0

    def __len__(self):
        return len(self.strng)

    def __iter__(self):
        self.pos = 0
        return self

    def __next__(self):
        if self.pos < len(self.strng):
            val = self.strng[self.pos]
            self.pos += 1
            return val
        else: raise StopIteration


if __name__ == "__main__":
    c = clss("1234567");
    print(len(c))

    for el in c:
        print(el)
        break
    print(c.__next__())
    print(next(c))
    for el in c:
        print(el)
    for el in c:
        print(el)

