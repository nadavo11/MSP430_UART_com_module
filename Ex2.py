import serial as ser
from time import sleep
from GUI import *


import sys
from PyQt5.QtWidgets import QApplication, QMainWindow, QWidget, QPushButton, QSlider, QLabel, QVBoxLayout
from PyQt5.QtCore import Qt
from time import sleep

MENU ='''
  __  __  ______  _   _  _    _ 
 |  \/  ||  ____|| \ | || |  | |
 | \  / || |__  ||  \| || |  | |
 | |\/| ||  __| || . ` || |  | |
 | |  | || |____|| |\  || |__| |
 |_|  |_||______||_| \_||\____/ 
                             
                             
1. Blink RGB LED, color by color with delay of X[ms]
2. Count up onto LCD screen with delay of X[ms]
3. Circular tone series via Buzzer with delay of X[ms]
4. Get delay time X[ms]
5. LDR 3-digit value [v] onto LCD
6. Clear LCD screen
7. Show menu
8. Sleep
'''

def printMenu():
    print(MENU)


# def processChar(char):
#     if char == 'm':
#         printMenu()
#     if char == 'x':
#         print("please enter delay time in ms")
#     else:
#         print(f'char: {char} received')

"""
_____________________________________________________________________________________
*                                                                                   *
*                                                                                   *
*                           Main function                                           *
*                                                                                   *
*___________________________________________________________________________________*
                         

"""
def main():
    s = ser.Serial('COM14', baudrate=9600, bytesize=ser.EIGHTBITS,
                   parity=ser.PARITY_NONE, stopbits=ser.STOPBITS_ONE,
                   timeout=1)   # timeout of 1 sec where the read and write operations are blocking,
                                # after the timeout the program continues
    enableTX = False
    # clear buffers
    s.reset_input_buffer()
    s.reset_output_buffer()
    app = QApplication(sys.argv)

    g = GUI(s)
    g.show()

    sys.exit(app.exec_())
    printMenu()

    while(True):

        # Read from the input buffer
        while (s.in_waiting > 0):  # while the input buffer isn't empty
            line = s.read_until(expected='\n')  # read  from the buffer until the terminator is received,
            # readline() can also be used if the terminator is '\n'
            print(line.decode("ascii"))


if __name__ == '__main__':
    main()