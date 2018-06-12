import importlib
import os


def main():
    print(os.getcwd())
    mod_name = os.getcwd().replace('/', '.') + '.function'
    print(mod_name)
    module = importlib.import_module(mod_name)
    module.sayhello()


if __name__ == '__main__':
    main()
