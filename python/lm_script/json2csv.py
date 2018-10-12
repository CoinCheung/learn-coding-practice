import json


with open('testset_filename_to_id.json', 'r') as fr:
    jobj = json.load(fr)

ann = jobj['annotation']

with open('res.csv', 'w') as fw:
    fw.write('filename,image_id\n')
    for i, el in enumerate(ann):
        fw.write('{},{}\n'.format(el['filename'], el['image_id']))
        print('\rprocess {}'.format(i), end = "", flush = True)
    print()
