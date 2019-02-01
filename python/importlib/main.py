import importlib
import os

import mod1


def main():
    print(os.getcwd())
    mod_name = os.getcwd().replace('/', '.') + '.function'
    print(mod_name)
    #  module = importlib.import_module(mod_name)
    #  module.sayhello()

    mod1.funA()


if __name__ == '__main__':
    main()
