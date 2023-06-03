import serial as ser
from time import sleep
pingPongNum = 10

#in this example we sends a character and ping pong the input character "pingPongNum" times before the port closes

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


def processChar(char):
    if char == 'm':
        printMenu()
    if char == 'x':
        print("please enter delay time in ms")
    else:
        print(f'char: {char} received')

"""
_____________________________________________________________________________________
*                                                                                   *
*                                                                                   *
*                           Main function                                           *
*                                                                                   *
*___________________________________________________________________________________*
                         

"""

def main():
    s = ser.Serial('COM15', baudrate=9600, bytesize=ser.EIGHTBITS,
                   parity=ser.PARITY_NONE, stopbits=ser.STOPBITS_ONE,
                   timeout=1)   # timeout of 1 sec where the read and write operations are blocking,
                                # after the timeout the program continues
    enableTX = False
    # clear buffers
    s.reset_input_buffer()
    s.reset_output_buffer()
    count = 1
    char = ''

    printMenu()
    while(True):

        inChar = input("Enter char:")

        for c in inChar:
            bytesChar = bytes(c, 'ascii')
            print("bytes:",bytesChar)
            s.write(bytesChar)
            sleep(0.5)
        s.write(bytes('\n', 'ascii'))
        sleep(0.2)

        while (s.in_waiting > 0):  # while the input buffer isn't empty
            char = s.read(size=1).decode("ascii")  # read 1 char from the input buffer
            processChar(char)

    while(1):
        while (s.in_waiting > 0):  # while the input buffer isn't empty
            char = s.read(size = 1).decode("ascii")  # read 1 char from the input buffer
            print(char)

            if (s.in_waiting == 0):
                enableTX = True  # enable transmission to echo the received data
        while (s.out_waiting > 0 or enableTX):
            s.write(char)
            count = count + 1
            if (s.out_waiting == 0):
                enableTX = False
        if count == pingPongNum + 1:
            s.close()
            break


if __name__ == '__main__':
    main()