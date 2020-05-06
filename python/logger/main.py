
import logging
from mod import fun


def main():
    FORMAT = '%(levelname)s %(filename)s:%(lineno)d: %(message)s'
    logging.basicConfig(level=logging.INFO,
            format=FORMAT, filename = './log_message.log')
    logger_main = logging.getLogger()

    logger_main.info('fuck you from main before handler')
    fun()
    logging.root.addHandler(logging.StreamHandler())
    logger_main.info('fuck you from main after handler')
    fun()
    logger = logging.getLogger()
    logger.info('fuck you from new logger')


if __name__ == '__main__':
    main()
