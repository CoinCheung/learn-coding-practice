#!/usr/bin/python
#filename: frame.py

import wx

'''
create a window 
'''
#-------------------------------------------#
#method one: use wx.Frame()
#app=wx.App()
#
#frame=wx.Frame(None,-1,title='wx00.py',pos=(300,400),size=(300,300))
#
#frame.Show()
#
#frame.Centre()
#
#app.MainLoop()

#----------------------------------------------#
#method two: use successor of wx.Frame()

class Window(wx.Frame):
	def __init__(self,title):
		super(Window,self).__init__(None,-1,title=title,pos=(300,300),size=(400,400))
		self.Center()
		self.Show()
		self.Bind(wx.EVT_PAINT, self.OnPaint)
		#draw a line with paintDC
	#	dc=wx.ClientDC(self)
	#	dc.DrawLine(30,30,100,100)

	def OnPaint(self,e):
		dc=wx.PaintDC(self)
		dc.DrawLines(((50,60),(150,160),(30,130)))
		dc.DrawLine(150,160,250,260)

if __name__=='__main__':
	app=wx.App()
	Window('pythonWindow2')
	app.MainLoop()
