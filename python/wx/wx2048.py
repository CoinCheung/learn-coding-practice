#!/usr/bin/python
# FileName: wx2048.py
# -> To implement the game of 2048 with a gui


import wx
import os
import random


class Frame(wx.Frame):
    def __init__(self,title):
        super(Frame,self).__init__(None,-1,title=title,size=(500,500))
        #process of initializing the game
        self.InitGameStatus()
        self.InitGameUI()
        self.SetIcon()

        self.Center()
        self.Show()

    def InitGameStatus(self): # initialize the state of the game
        self.CurrentSocore = 0
        self.BestScore = 0
        self.LoadScore()

        self.KeyData = [[0,0,0,0],[0,0,0,0],[0,0,0,0],[0,0,0,0]]
        count = 0
        while count < 2: # set two blocks as initial blocks with values of 2 or 4
            row = random.randint(0,len(self.KeyData)-1)
            colomn = random.randint(0,len(self.KeyData[0])-1)
            if self.KeyData[row][colomn] != 0:
                continue
            else:
                num = random.sample([2,4],1)
                self.KeyData[row][colomn] = num
            count = count + 1


    def LoadScore(self): # to load the best score
        pass

    def InitGameUI(self): # initialize the UI of the game
        vbox = wx.BoxSizer(wx.VERTICAL)


        pass

    def SetIcon(self):
        pass


if __name__ == '__main__':
    app = wx.App()
    frame = Frame('2048 with python')
    app.MainLoop()

