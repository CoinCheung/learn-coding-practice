#!/usr/bin/python
#FileName: calculator.py
#-> To implement a calculator with a gui in wx


import wx
from math import pi


class CalFrame(wx.Frame):
    def __init__(self,title):
        super(CalFrame,self).__init__(None,title=title,size=(300,250))
        self.InitUI()
        self.Centre()
        self.Show()
        self.Bind(wx.EVT_CLOSE,self.ExitMessage)

        self.equation = ''

    def InitUI(self):
        vbox = wx.BoxSizer(wx.VERTICAL) # Boxsizer is designed to place the controls vertically or horizontally
        self.tc = wx.TextCtrl(self,style=wx.TE_RIGHT)
        vbox.Add(self.tc,flag=wx.EXPAND|wx.TOP|wx.BOTTOM,border=4)

        gridbox = wx.GridSizer(5,4,4,4) # GridSizer is designed to place the controls in grids, the four parameters are rows, colomns, distance between rows and distance between colomns
        labels=['AC','DEL','pi','CLOSE','7','8','9','/','4','5','6','*','1','2','3','-','0','.','=','+']
        for label in labels:
            buttonItem = wx.Button(self,label=label) # create a botton with the text given in 'label'
            self.creatHandler(buttonItem,label)
            gridbox.Add(buttonItem,proportion=0,flag=wx.EXPAND)
        vbox.Add(gridbox,proportion=1,flag=wx.EXPAND)

        self.SetSizer(vbox) # add the sizer of text control and buttons to the frame

    def creatHandler(self,button,label): # Bind the callback methods to the button events
        expItem = ['DEL','AC','CLOSE','=']
        if label not in expItem:
            self.Bind(wx.EVT_BUTTON,self.OnAppend,button)
        elif label == 'DEL':
            self.Bind(wx.EVT_BUTTON,self.OnDel,button)
        elif label == 'AC':
            self.Bind(wx.EVT_BUTTON,self.OnAC,button)
        elif label == 'CLOSE':
            self.Bind(wx.EVT_BUTTON,self.OnClose,button)
        else:
            self.Bind(wx.EVT_BUTTON,self.OnEqual,button)

    def OnAppend(self,event):
        buttonevent = event.GetEventObject() # get the button event
        label =  buttonevent.GetLabel() # get the label of the button (knowing which button is pressed)
        self.equation = ''.join([self.equation,label]) # combine the newly pressed button with the valued determined via the previous buttons
        self.tc.SetValue(self.equation) # show the values and operators in the text control

    def OnDel(self,event):
        self.equation = self.equation[:-1]
        self.tc.SetValue(self.equation)

    def OnAC(self,event):
        self.equation = ''
        self.tc.SetValue(self.equation)

    def OnClose(self,event):
        self.Close() # self.Close() is the method called when the x is clicked

    def OnEqual(self,event):
        string = self.equation
        try: # if the equation is not computable
            self.equation = str(eval(string)) # use the method of eval() to calculate the equation in string form, and convert it to string format to be assigned to the text control
            self.tc.SetValue(self.equation)
        except: # throw a message box
            mb = wx.MessageDialog(self,'The equation is not computable','Error',wx.ICON_ERROR|wx.OK)
            mb.ShowModal()
            mb.Destroy()

    def ExitMessage(self,event):
        md = wx.MessageDialog(self,'Are you sure you want to exit?','Closing',wx.YES_NO)
        res = md.ShowModal()
        if res == wx.ID_YES:
            event.Skip() # Skip() means to continue the process of closing
        else:
            pass


if __name__ == '__main__':
    app=wx.App()
    CalFrame('my calculator with wx')
    app.MainLoop()

