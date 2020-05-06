file_path0='E:\Python_files\CurrMap.txt'
file_path1='E:\Python_files\CurrMap_out.txt'


result=[]
with open(file_path0) as f_obj:
    for line in f_obj:
       sub = []
       tokens = line.split()
       for el in tokens:
           sub.append(''.join([str(round(float(el))),'.0F, ']))
       result.append(''.join(sub))
       #    print(result[-1])
        #result.append(list(map(float,line.split(','))))
    print(result)

with open(file_path1, 'w') as wf:
    for strg in result:
        wf.write(strg)
        wf.write('\n')


   
        
