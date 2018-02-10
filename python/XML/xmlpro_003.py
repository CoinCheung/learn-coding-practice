#!/usr/bin/python
# -*- encoding: utf-8 -*-
# filename: xmlpro003.py


'''
    这里面值得关注的两个点:
    1. 如何删除文件的某一行(已知行号)
    2. 如何获取某文件的行数
'''

import os
from lxml import etree
import xlwt


## file names assignment
file1 = 'D3203_BMS_AR2BSW_DSMCTR.arxml'
file2 = 'D3217_BMS_AR2BSW_IF.arxml'
outname = "result_003.xls"


## create temp files and get rid of the disturbing line
pth, tmpfile = {}, {}
pth[1] = ''.join([os.getcwd(), '/', file1])
pth[2] = ''.join([os.getcwd(), '/', file2])
tmpfile[1] = ''.join([os.getcwd(), '/.file1'])
tmpfile[2] = ''.join([os.getcwd(), '/.file2'])

for k,v in pth.items(): # files to read
    with open(v, 'r') as f: # new file to write to
        with open(tmpfile[k], 'w') as t: # 删除某一行的方法
            lines = f.readlines()
            lnum = len(lines) # 获取文件行数的方法
            for i,line in enumerate(lines):
                if i == 1 or i == lnum-1:
                    print(line)
                else:
                    t.write(line)


## open and start parsing the xml files
xml, root = {}, {}
for k,v in tmpfile.items():
    xml[k] = etree.parse(v)
    root[k] = xml[k].getroot()


## open the xls file for write
resbook = xlwt.Workbook(encoding='ascii')
sheet1 = resbook.add_sheet("sheet 1")
line = 1


## pick all the useful information
swcmpnt = root[1].xpath('//APPLICATION-SW-COMPONENT-TYPE')[0]
swcmpnt_name = swcmpnt.xpath('SHORT-NAME')[0].text

runnables = root[1].xpath('//RUNNABLES')
for rnb in runnables:
    runnable_entitys = rnb.xpath('./RUNNABLE-ENTITY')
    for rnen in runnable_entitys:
        rnen_name = rnen.xpath('SHORT-NAME')[0].text
        variable_access = rnen.xpath('//VARIABLE-ACCESS')
        for va in variable_access:
            va_sn = va.xpath('SHORT-NAME')[0].text
            sn_tokens = va_sn.split('_')

            if sn_tokens[0] == 'SendPoint' or sn_tokens[0] == 'ArgRecPoint':
                va_type = 'SenderReceiver'
                va_name = va_sn.replace(sn_tokens[0]+'_', '')
            elif sn_tokens[0][:-1] == 'VariableAccess':
                va_type = 'Internal'
                lvar_ref = va.xpath('//LOCAL-VARIABLE-REF')[0].text
                va_name = lvar_ref.split('/')[-1]
                unitname = va_name.split('/')[-1]
                lc_sn_node = root[1].xpath(''.join(['//*[text()="', va_name, '"]']))[0].getparent().xpath('./TYPE-TREF')[0]
                unittype = lc_sn_node.text.split('/')[-1]

            va_sn_clean = va_name.replace('_' + sn_tokens[-1], '')
            text = ''.join(['//*[text()="', va_sn_clean, '"]'])
            if_name_node = root[2].xpath(text)
            if if_name_node != []:
                data_elements = if_name_node[0].getparent().xpath("./DATA-ELEMENTS")[0]
                unitname = data_elements.xpath('.//SHORT-NAME')[0].text
                unittype = data_elements.xpath('.//TYPE-TREF')[0].text.split('/')[-1]

            sheet1.write(line, 0, swcmpnt_name)
            sheet1.write(line, 1, rnen_name)
            sheet1.write(line, 2, va_type)
            sheet1.write(line, 3, va_name)
            sheet1.write(line, 4, unitname)
            sheet1.write(line, 5, unittype)
            line += 1


## save the sheet into xls file
resbook.save(outname)


## remove the temp files
os.remove(tmpfile[1])
os.remove(tmpfile[2])

