#!/usr/bin/python
# -*- encoding: utf-8 -*-
# filename: xmlpro002.py


import os
from lxml import etree
import xlwt


pth1 = ''.join([os.getcwd(), '/DSMCTR.arxml'])
xml_dsmctr = etree.parse(pth1)
root_dsmctr = xml_dsmctr.getroot()

pth2 = ''.join([os.getcwd(), '/IF.arxml'])
xml_if = etree.parse(pth2)
root_if = xml_if.getroot()

#  print(dir(autosar_root))
print(root_dsmctr.getchildren()[0].getchildren())
print("here")

# / means the root node, // means all the
# recursive sublings from the current node
#  print(runnables)


# parse APPLICATION-SW-COMPONENT name

#  var_acc = root_dsmctr.xpath("//VARIABLE-ACCESS")
#  vas = var_acc[0]
#  txt = root_dsmctr.xpath("//*[text()='ArgRecPoint_VOnc_FltInd_Array']")
#  print(txt)

resbook = xlwt.Workbook(encoding='ascii')
sheet1 = resbook.add_sheet("sheet 1")
line = 1

swcmpnt = root_dsmctr.xpath('//APPLICATION-SW-COMPONENT-TYPE')[0]
swcmpnt_name = swcmpnt.xpath('SHORT-NAME')[0].text

runnables = root_dsmctr.xpath('//RUNNABLES')
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
                lc_sn_node = root_dsmctr.xpath(''.join(['//*[text()="', va_name, '"]']))[0].getparent().xpath('./TYPE-TREF')[0]
                unittype = lc_sn_node.text.split('/')[-1]

            va_sn_clean = va_name.replace('_' + sn_tokens[-1], '')
            text = ''.join(['//*[text()="', va_sn_clean, '"]'])
            if_name_node = root_if.xpath(text)
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


resbook.save("result_002.xls")

##
#  Write to xls file

#  for vas in var_acc:
#      sn = vas.xpath("./SHORT-NAME")[0].text
#      tokens = sn.split('_')
#      sn = sn.replace(tokens[0]+'_', '')
#      sn = sn.replace('_'+tokens[-1], '')
#
#      text = ''.join(['//*[text()="', sn, '"]'])
#      if_name_node = root_if.xpath(text)
#      if if_name_node != []:
#          #  print(if_name_node[0].text)
#          data_elements = if_name_node[0].getparent().xpath("./DATA-ELEMENTS")[0]
#          #  data_elements = if_name_node[0].xpath("./parent::node()")[0].xpath("./DATA-ELEMENTS")[0]
#          unitname = data_elements.xpath('.//SHORT-NAME')[0].text
#          unittype = data_elements.xpath('.//TYPE-TREF')[0].text.split('/')[-1]
#
#          sheet1.write(line, 0, swcmpnt_name)
#          sheet1.write(line, 1, sn)
#          sheet1.write(line, 2, unitname)
#          sheet1.write(line, 3, unittype)
        #  print(unitname)
        #  print(unittype)



#  for subnode in root:
#      print(subnode.tag)
    #  print(subnode.tag)
    #  print(subnode.attrib)
    #  print(subnode.items)


#  sheet1.write(0, 0, 'label of (0,0)')


pth3 = ''.join([os.getcwd(), '/D3217_BMS_AR2BSW_IF.arxml'])
xml_ifall = etree.parse(pth3)
#  print(xml_ifall.getroot().getchildren())
root_ifall = xml_ifall.getroot().getchildren()[0].getchildren()[1]
#  node = root_ifall.xpath("//SW-CALIBRATION-ACCESS/text()")
print("root")
#  print(node)
print(root_ifall.attrib)
print(root_ifall.text)
print(root_ifall.tag)
