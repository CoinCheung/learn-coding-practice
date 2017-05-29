#!/usr/bin/python
# -*- coding: utf-8 -*-


import os
import random
import ui2048
from PyQt5 import QtWidgets


#======================================================
# The class to implement the game
#======================================================
class Implement2048(QtWidgets.QMainWindow,ui2048.Ui_MainWindow):
    def __init__(self):
        super(Implement2048,self).__init__()
        self.initGameStatus()
        self.setupUi(self)


    def initGameStatus(self):
        def loadScore():
            if os.path.exists('bestScore.ini'):
                f = open('bestScore.ini')
                self.bestScore = f.read()
                f.close()

        def initNumbers():

        self.score = 0

    def keyPressEvent(self,event):
        print('key is pressed')
        print(event.key())


#===============================================================
# entrance of the program
#===============================================================
if __name__ == '__main__':
    import sys
    app = QtWidgets.QApplication(sys.argv)
    obj = Implement2048()
    obj.show()
    sys.exit(app.exec_())
