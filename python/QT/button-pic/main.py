#!/usr/bin/python
# -*- coding: utf-8 -*-


import photo
import pics
from PyQt5 import QtWidgets


class subUI(QtWidgets.QMainWindow,photo.Ui_MainWindow):
    def __init__(self):
        super(subUI,self).__init__()
        self.setupUi(self)

    def setFirstPage(self):
        self.Pictures.setCurrentWidget(self.page1) #qstackwidget的用法，表示将当前显示的控件设为page1，这个page1必须是以前已经加到stackwidget里面的才行，不然不能用

    def setSecondPage(self):
        self.Pictures.setCurrentWidget(self.page2)

    def setThirdPage(self):
        self.Pictures.setCurrentWidget(self.page3)


if __name__ == '__main__':
    import sys
    app = QtWidgets.QApplication(sys.argv)
    mw = subUI()
    mw.show()
    sys.exit(app.exec_())
