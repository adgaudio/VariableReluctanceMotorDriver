import firmata
import argparse


def main(ns):
    print(("Connecting to %s" % ns.port))
    board = firmata.Arduino(ns.port, ns.baud)
    print(board)  # TODO
    global board


parser = argparse.ArgumentParser()
parser.add_argument(
    'port', help=("the filepath to the arduino device. "
                  " ie /dev/tty.SLAB_USBtoUART"))
parser.add_argument(
    'baud', help=("baud rate. ie 19200"), type=int)

if __name__ == '__main__':
    NS = parser.parse_args()
    main(NS)
