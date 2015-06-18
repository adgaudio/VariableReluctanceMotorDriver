import argparse
import serial
import sys
import termios
import tty


def getch():
    fd = sys.stdin.fileno()
    old_settings = termios.tcgetattr(fd)
    try:
        tty.setraw(sys.stdin.fileno())
        ch = sys.stdin.read(1)
    finally:
        termios.tcsetattr(fd, termios.TCSADRAIN, old_settings)
    return ch


def main(ns):
    print(("Connecting to %s" % ns.port))
    board = serial.Serial(ns.port, ns.baud)
    print("Connected")
    print("Hit ENTER to exit")
    global board
    while True:
        inpt = getch()
        if inpt == '\r' or inpt == '\n':
            break
        if inpt == 'a':
            board.write('4')
        elif inpt == 's':
            board.write('3')
        elif inpt == 'w':
            board.write('1')
        elif inpt == 'd':
            board.write('2')
        elif inpt == ' ':
            board.write('5')
        # diagonal directions
        elif inpt == 'q':
            board.write('4')
            board.write('1')
        elif inpt == 'e':
            board.write('1')
            board.write('2')
        elif inpt == 'z':
            board.write('4')
            board.write('3')
        elif inpt == 'c':
            board.write('2')
            board.write('3')
        board.flush()


parser = argparse.ArgumentParser()
parser.add_argument(
    'port', help=("the filepath to the arduino device. "
                  " ie /dev/tty.SLAB_USBtoUART"))
parser.add_argument(
    'baud', help=("baud rate. ie 19200"), type=int)

if __name__ == '__main__':
    NS = parser.parse_args()
    main(NS)
