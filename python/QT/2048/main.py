#!/usr/bin/python
# -*- coding: utf-8 -*-


import os
import so2048
import ui2048
from PyQt5 import QtWidgets


#======================================================
# The class to implement the game
#======================================================
class Implement2048(QtWidgets.QMainWindow,ui2048.Ui_MainWindow):
    #initialization of the Class
    def __init__(self):
        super(Implement2048,self).__init__()
        self.initGameStatus()
        self.setupUi(self)

    #initialization of the Status of the game
    def initGameStatus(self):
        # load the best Score from the storage file
        def loadScore():
            if os.path.exists('bestScore.ini'):
                f = open('bestScore.ini')
                so2048.cvar.bestScore = int(f.read())
                f.close()

        so2048.initGame()
        loadScore()
        self.score = so2048.cvar.currentScore;
        print(so2048.cvar.fields)


    # update the UI
    def updateUI(self):
        pass

    # response method when any key is pressed
    def keyPressEvent(self,event):
        print('key is pressed')
        print(event.key())

    # reponse method when the button 'NewGame' is clicked
    def NewGame(self):
        pass


#===============================================================
# entrance of the program
#===============================================================
if __name__ == '__main__':
    import sys
    app = QtWidgets.QApplication(sys.argv)
    obj = Implement2048()
    obj.show()
    sys.exit(app.exec_())
