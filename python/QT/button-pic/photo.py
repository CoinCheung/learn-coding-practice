# -*- coding: utf-8 -*-

# Form implementation generated from reading ui file 'button-photo.ui'
#
# Created by: PyQt5 UI code generator 5.8.2
#
# WARNING! All changes made in this file will be lost!

from PyQt5 import QtCore, QtGui, QtWidgets

class Ui_MainWindow(object):
    def setupUi(self, MainWindow):
        MainWindow.setObjectName("MainWindow")
        MainWindow.resize(650, 529)
        self.centralwidget = QtWidgets.QWidget(MainWindow)
        self.centralwidget.setObjectName("centralwidget")
        self.frame = QtWidgets.QFrame(self.centralwidget)
        self.frame.setGeometry(QtCore.QRect(0, 0, 651, 511))
        self.frame.setCursor(QtGui.QCursor(QtCore.Qt.UpArrowCursor))
        self.frame.setFrameShape(QtWidgets.QFrame.StyledPanel)
        self.frame.setFrameShadow(QtWidgets.QFrame.Raised)
        self.frame.setObjectName("frame")
        self.verticalLayoutWidget = QtWidgets.QWidget(self.frame)
        self.verticalLayoutWidget.setGeometry(QtCore.QRect(20, 90, 160, 92))
        self.verticalLayoutWidget.setObjectName("verticalLayoutWidget")
        self.verticalLayout = QtWidgets.QVBoxLayout(self.verticalLayoutWidget)
        self.verticalLayout.setContentsMargins(0, 0, 0, 0)
        self.verticalLayout.setObjectName("verticalLayout")
        self.FirstPage = QtWidgets.QPushButton(self.verticalLayoutWidget)
        self.FirstPage.setObjectName("FirstPage")
        self.verticalLayout.addWidget(self.FirstPage)
        self.SecondPage = QtWidgets.QPushButton(self.verticalLayoutWidget)
        self.SecondPage.setObjectName("SecondPage")
        self.verticalLayout.addWidget(self.SecondPage)
        self.ThirdPage = QtWidgets.QPushButton(self.verticalLayoutWidget)
        self.ThirdPage.setObjectName("ThirdPage")
        self.verticalLayout.addWidget(self.ThirdPage)
        self.Pictures = QtWidgets.QStackedWidget(self.frame)
        self.Pictures.setGeometry(QtCore.QRect(210, 20, 351, 361))
        self.Pictures.setStyleSheet("")
        self.Pictures.setObjectName("Pictures")
        self.page1 = QtWidgets.QWidget()
        self.page1.setObjectName("page1")
        self.graphicsView1 = QtWidgets.QGraphicsView(self.page1)
        self.graphicsView1.setGeometry(QtCore.QRect(10, 20, 331, 311))
        self.graphicsView1.setStyleSheet("border-image: url(:/newPrefix/3.jpg);\n"
"alternate-background-color: qradialgradient(spread:pad, cx:0.5, cy:0.5, radius:0.5, fx:0.5, fy:0.5, stop:0 rgba(255, 235, 235, 206), stop:0.35 rgba(255, 188, 188, 80), stop:0.4 rgba(255, 162, 162, 80), stop:0.425 rgba(255, 132, 132, 156), stop:0.44 rgba(252, 128, 128, 80), stop:1 rgba(255, 255, 255, 0));")
        self.graphicsView1.setObjectName("graphicsView1")
        self.label1 = QtWidgets.QLabel(self.page1)
        self.label1.setGeometry(QtCore.QRect(170, 340, 58, 14))
        self.label1.setObjectName("label1")
        self.Pictures.addWidget(self.page1)
        self.page2 = QtWidgets.QWidget()
        self.page2.setObjectName("page2")
        self.graphicsView2 = QtWidgets.QGraphicsView(self.page2)
        self.graphicsView2.setGeometry(QtCore.QRect(10, 20, 331, 311))
        self.graphicsView2.setStyleSheet("border-image: url(:/newPrefix/1.jpg);")
        self.graphicsView2.setObjectName("graphicsView2")
        self.label2 = QtWidgets.QLabel(self.page2)
        self.label2.setGeometry(QtCore.QRect(170, 340, 58, 14))
        self.label2.setObjectName("label2")
        self.Pictures.addWidget(self.page2)
        self.page3 = QtWidgets.QWidget()
        self.page3.setObjectName("page3")
        self.graphicsView3 = QtWidgets.QGraphicsView(self.page3)
        self.graphicsView3.setGeometry(QtCore.QRect(10, 20, 331, 311))
        self.graphicsView3.setStyleSheet("border-image: url(:/newPrefix/2.jpg);\n"
"font: 9pt \"DejaVu Sans\";\n"
"border-color: rgb(85, 85, 0);")
        self.graphicsView3.setObjectName("graphicsView3")
        self.label3 = QtWidgets.QLabel(self.page3)
        self.label3.setGeometry(QtCore.QRect(170, 340, 58, 14))
        self.label3.setObjectName("label3")
        self.Pictures.addWidget(self.page3)
        MainWindow.setCentralWidget(self.centralwidget)
        self.menubar = QtWidgets.QMenuBar(MainWindow)
        self.menubar.setGeometry(QtCore.QRect(0, 0, 650, 19))
        self.menubar.setObjectName("menubar")
        MainWindow.setMenuBar(self.menubar)
        self.statusbar = QtWidgets.QStatusBar(MainWindow)
        self.statusbar.setObjectName("statusbar")
        MainWindow.setStatusBar(self.statusbar)

        self.retranslateUi(MainWindow)
        self.Pictures.setCurrentIndex(2)
        self.FirstPage.clicked.connect(self.setFirstPage)
        self.SecondPage.clicked.connect(self.setSecondPage)
        self.ThirdPage.clicked.connect(self.setThirdPage)
        QtCore.QMetaObject.connectSlotsByName(MainWindow)

    def retranslateUi(self, MainWindow):
        _translate = QtCore.QCoreApplication.translate
        MainWindow.setWindowTitle(_translate("MainWindow", "MainWindow"))
        self.FirstPage.setText(_translate("MainWindow", "First Page"))
        self.SecondPage.setText(_translate("MainWindow", "Second Page"))
        self.ThirdPage.setText(_translate("MainWindow", "Third Page"))
        self.label1.setText(_translate("MainWindow", "Picture1"))
        self.label2.setText(_translate("MainWindow", "Picture2"))
        self.label3.setText(_translate("MainWindow", "Picture3"))


