#!/usr/bin/python
#filename:main.py


import os
import argparse
from PIL import Image

#--------------------------------------------------------#
#use argparse to interact with the user, get the user command
#--------------------------------------------------------#
parse=argparse.ArgumentParser() #create a option assignment object
#define the parameters
parse.add_argument('file')
parse.add_argument('--height','-ht',type=int)
parse.add_argument('--width','-wd',type=int)
parse.add_argument('--out','-o')
#obtain the parameters from the user
args=parse.parse_args()

#--------------------------------------------------------#
#method name: getimagechar()
#
#--------------------------------------------------------#
asciilist=list("$@B%8&WM#*oahkbdpqwmZO0QLCJUYXzcvunxrjft/\|()1{}[]?-_+~<>i!lI;:,\"^`'.") #the syntaxes used as pixels

def getimagechar(pixel):
	gray=int(0.2126*pixel[0]+0.7152*pixel[1]+0.0722*pixel[2]) #calculate the gray scale of the pixel and extract the integer portion
	pos=int(len(asciilist)*gray/(256+1))
	return asciilist[pos]



#--------------------------------------------------------#
#main script
#	open the image and read the pixels
#	convert the pixels to gray values and use getimagechar() to pick out their associated syntaxes
#--------------------------------------------------------#
if __name__=='__main__':
	image=Image.open('photo.jpg')
	if args.height and args.width:
		image=image.resize((args.width,args.height))
	else:
		args.height=image.size[0]#height is image.size[0]
		args.width=image.size[1]
	# get the picture of characters	
	print image.format
	print image.mode
	txt=[]
	for i in range(args.height):
		for j in range(args.width):
			ch=getimagechar(image.getpixel((j,i)))
			#txt.append(ch)
			print ch,
		print os.linesep
		#txt.append(os.linesep)
		
	#print the ascii image in the consolo
	#print txt
