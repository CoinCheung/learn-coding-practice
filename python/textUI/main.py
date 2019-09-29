#!/usr/bin/python


from PyQt5 import QtWidgets
from PyQt5.QtWidgets import QFileDialog, QMessageBox
import os
import sys


class MainWin(QtWidgets.QWidget):
    def __init__(self):
        super(MainWin, self).__init__()
        self.resize(200,200)
        self.button1 = QtWidgets.QPushButton(self)
        self.button1.setObjectName('button1')
        self.button1.setText("select file")
        self.button1.setGeometry(60,75,80,40)
        self.button1.clicked.connect(self.msg)

    def msg(self):
        filename, filetype = QFileDialog.getOpenFileName(self,
                                                         "Choose a file",
                                                         '/home/coin/learn-coding/projects/python/textUI',
                                                         "All Files(*);; Text Files(*.txt)"
        )

        self.convert(filename)
        QMessageBox.information(self, "information", "file converted successfully")

    def get_output_path(self, path1):
        path2 = path1.split(os.sep)
        fns = path2[-1].split(os.extsep)
        path2 = path2[:-1]
        if len(fns) == 1:
            fns = fns + ["_out"]
            fns = ''.join(fns)
        else:
            prefx = fns[:-1]
            fmt = fns[-1]
            fns = prefx + ["_out", os.extsep, fmt]
            fns = "".join(fns)

        pth = []
        for el in path2:
            print(el)
            pth += [el]
            pth += [os.sep]
        path2 = "".join(pth + [fns])
        return path2

    def convert(self, path1):
        path2 = self.get_output_path(path1)
        result=[]
        with open(path1) as f_obj:
            for line in f_obj:
                sub = []
                tokens = line.split()
                for el in tokens:
                    sub.append(''.join([str(round(float(el))),'.0F, ']))
                result.append(''.join(sub))

        with open(path2, 'w') as wf:
            for strg in result:
                wf.write(strg)
                wf.write('\n')


if __name__ == "__main__":
    app = QtWidgets.QApplication(sys.argv)
    mw = MainWin()
    mw.show()
    sys.exit(app.exec_())
