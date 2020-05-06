#!/usr/bin/python
# -*- coding: utf-8 -*-
# filename: setupforwin.py
# this is the setup file for window platform created to build executable files with python script


from cx_Freeze import setup, Executable
import msilib
import sys

target_name = 'view-pictures.exe'
product_name = u'异体'.encode('gbk')
product_code = msilib.gen_uuid() # uuid code needed for uninstallation
unproduct_name = u'卸载异体'.encode('gbk')
product_desc = u"异体客户端程序 Ver1.0".encode("gbk")

# shortcut_table = [
#
#      #1、桌面快捷方式
#     ("DesktopShortcut",           # Shortcut
#      "DesktopFolder",             # Directory_ ，必须在Directory表中
#      product_name,                # Name
#      "TARGETDIR",                 # Component_，必须在Component表中
#      "[TARGETDIR]"+target_name,   # Target
#      None,                        # Arguments
#      product_desc,                # Description
#      None,                        # Hotkey
#      None,                        # Icon
#      None,                        # IconIndex
#      None,                        # ShowCmd
#      'TARGETDIR'                  # WkDir
#      ),
#
#     #2、开始菜单快捷方式
#     ("StartupShortcut",           # Shortcut
#      "MenuDir",                   # Directory_
#      product_name,                # Name
#      "TARGETDIR",                 # Component_
#      "[TARGETDIR]"+target_name,   # Target
#      None,                        # Arguments
#      product_desc,                # Description
#      None,                        # Hotkey
#      None,                        # Icon
#      None,                        # IconIndex
#      None,                        # ShowCmd
#      'TARGETDIR'                  # WkDir
#      ),
#
#     #3、程序卸载快捷方式
#     ("UniShortcut",              # Shortcut
#      "MenuDir",                  # Directory_
#      unproduct_name,             # Name
#      "TARGETDIR",                # Component_
#      "[System64Folder]msiexec.exe",  # Target
#      r"/x"+product_code,         # Arguments
#      product_desc,               # Description
#      None,                       # Hotkey
#      None,                       # Icon
#      None,                       # IconIndex
#      None,                       # ShowCmd
#      'TARGETDIR'                 # WkDir
#      )
#     ]

#===========================================#
# configuration of the option needed to build the msi installation file
#============================================#
msi_data = {
#        'Shortcut':shortcut_table
        }

directories = {}

bdist_msi_options = {
#        'data': msi_data,
       # 'upgrade_code': product_code
       'add_to_path': False,
       'directories': directories,
       'product_code': product_code,
       'initial_target_dir':r'[ProgramFilesFolder]\%s'%(product_name)
        }


#===========================================#
# options for creating executable files
#============================================#
base = None;
if sys.platform == 'win32':
    base = 'Win32GUI'

setup(
        name = 'create executable file for win',
        author = 'Coin',
        version = '0.1',
        description = product_desc.decode('gbk'),
        options = {'bdist_msi': bdist_msi_options},
        executables = [
                Executable('main.py',
                targetName = target_name,
                compress = True,
                base = base
                )
            ])
