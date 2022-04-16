import sys
import serial

isCmdMode = False
cliStartFrame = "hi bhai"
cliStopFrame = "bye bhai"

UART_COMPORT  = sys.argv[1]
UART_BAUDRATE = sys.argv[2]

ser = serial.Serial(UART_COMPORT, UART_BAUDRATE)

def getResponse() :
    response = ""
    while 1:
        chr = ser.read(1).decode('utf-8')
        if(chr == '$') :
            print(response, end="")
            break
        else :
            response += chr

def doSomething() :

    global isCmdMode
    global cliStartFrame
    global cliStopFrame
    
    while 1:
        data = input("")
        ser.write(bytes(data, 'utf-8'))

        if(data == cliStartFrame) :
            isCmdMode = True

        if(isCmdMode) :
            getResponse()
            
            if(data == cliStopFrame) :
                isCmdMode = False

if __name__ == "__main__":
    doSomething()