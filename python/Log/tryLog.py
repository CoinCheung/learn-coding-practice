


def doreturn(x=None):
    return 0 if x is None else 1
    #  val = 0 if x is None else 1
    #  return val

i = 0
#  while True:
#      i += 1
#      print(i)

print(doreturn())


import sys
import logging


FORMAT = '%(levelname)s %(filename)s:%(lineno)4d: %(message)s'
logging.basicConfig(level=logging.INFO,
        format=FORMAT,
        filename="./process.log"
        )
logger = logging.getLogger(__name__)
logger.addHandler(logging.StreamHandler())
logger.info('log information on the screen')

