import sys
import serial

isCmdMode = False
cliStartFrame = "hi bhai"
cliStopFrame = "bye bhai"

UART_COMPORT  = sys.argv[1]
UART_BAUDRATE = sys.argv[2]

f_log_ptr = open("cliLogs.txt","w")
ser = serial.Serial(UART_COMPORT, UART_BAUDRATE)

def getResponse() :
    response = ""
    while 1:
        chr = ser.read(1).decode('utf-8')
        if(chr == '$') :
            f_log_ptr.write(response)
            print(response, end="")
            break
        else :
            response += chr

def doSomething() :

    global f_log_ptr
    global isCmdMode
    global cliStartFrame
    global cliStopFrame
    
    while 1:
        data = input("")
        ser.write(bytes(data, 'utf-8'))

        if(data == cliStartFrame) :
            f_log_ptr = open("cliLogs.txt","w")
            isCmdMode = True

        if(isCmdMode) :
            f_log_ptr.write(data + '\n')
            getResponse()
            
            if(data == cliStopFrame) :
                f_log_ptr.close()
                isCmdMode = False

if __name__ == "__main__":
    doSomething()