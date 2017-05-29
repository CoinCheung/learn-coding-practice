#!/usr/bin/python
# -*- coding: utf-8 -*-
# filename: runsetup.py


from cx_Freeze import setup, Executable
import sys

#=================================================
# run when the platform is win32
#=================================================
if sys.platform == 'win32':
    setup(
        name = 'build',
        version = '0.1',
        description = 'try to create exe with cxFreeze',
        author = 'Coin',
        executables = [Executable(
            script = 'main.py', # replace with the source files, must the file that the program starts
            base = 'win32gui',
            targetName = 'seePics.exe' # replace this with the name of the output
            )]
        )

# run when the system platform is others (linux mainly)
else:
    setup(
        name = 'build',
        version = '0.1',
        description = 'try to create exe with cxFreeze',
        author = 'Coin',
        executables = [Executable(
            script = 'main.py', # replace with the source files, must the file that the program starts
            targetName = 'seePics' # replace this with the name of the output
            )]
        )
