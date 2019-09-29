#!/usr/bin/python

#==================================================================#
#FileName: drawshapes.py
#-> To draw some shapes with wx
#==================================================================#

import math
import wx
import abc


# The class of Point
class Point(object):
    def __init__(self,x,y):
        self.x=x
        self.y=y

    def __add__(self,other):    # redefine the operator '+'
        return Point(self.x+other.x,self.y+other.y)

    def pointxy(self):
        return (self.x,self.y)

    @staticmethod
    def dist(a,b):
        return math.sqrt((a.x-b.x)**2+(a.y-b.y)**2)


# The class of polygon which consists of points
class Polygon(object):
    __metaclass__ = abc.ABCMeta

    def __init__(self,point_list,**kwargs):
        for point in point_list: # Check if the inputs are real points
            assert isinstance(point,Point),'input must be point'
        self.points = point_list[:] # Copy all the input or there will be only one reference
        self.points.append(point_list[0]) # Encircle the shape
        self.color = kwargs.get('color','#000000') # assign the color of the shape with default to be #0000

    @abc.abstractmethod
    def area(self):
        pass

    def drawPoints(self):
        point_xy=[]
        for point in self.points:
            point_xy.append(point.pointxy())

        return tuple(point_xy)


# The class of Rectangle inherited from the class of polygon
class Rectangle(Polygon):
    def __init__(self,startpoint,width,height,**args):
        self.width=width
        self.height=height
        super(Rectangle,self).__init__([startpoint,startpoint+Point(width,0),startpoint+Point(width,height),startpoint+Point(0,height)],**args)

    def area(self): # Compute the area of the rectangle
        return self.width * self.height


# The class of Triangle which is a subclass of Polygon
class Triangle(Polygon):
    def __init__(self,point_list,**kwargs):
        self.a = point_list[0]
        self.b = point_list[1]
        self.c = point_list[2]
        self.m = Point.dist(self.a,self.b)
        self.n = Point.dist(self.b,self.c)
        self.l = Point.dist(self.a,self.c)
        assert (self.a.x-self.b.x)*(self.c.y-self.b.y) != (self.a.y-self.b.y)*(self.c.x-self.b.x), 'The three points should not be on the same line'
        super(Triangle,self).__init__(point_list,**kwargs)

    def area(self): # compute the area of the triangle
        p = (self.m+self.n+self.l) >> 1
        return math.sqrt(p*(p-a)*(p-b)*(p-c))



# The class of the Window
class Panel(wx.Frame):
    def __init__(self,title,Shape):
        super(Panel,self).__init__(None,-1,title=title,pos=(300,300),size=(400,400))
        self.Center()
        self.Show()
        self.Bind(wx.EVT_PAINT,self.OnPaint)
        self.shape=Shape

    def OnPaint(self,e):
       dc = wx.PaintDC(self)

       for shape in self.shape:
           dc.SetPen(wx.Pen(shape.color,5))
           dc.DrawLines(shape.drawPoints())


if __name__ == '__main__':

    startpoint=Point(30,40)
    rt = Rectangle(startpoint,50,40,color='#ff3453')

    pl=[Point(100,110),Point(100,40),Point(50,300)]
    ta = Triangle(pl)

    app = wx.App()
    Panel('draw someshape',[rt,ta])
    app.MainLoop()

