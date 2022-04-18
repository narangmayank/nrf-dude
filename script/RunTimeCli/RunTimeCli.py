import sys
import serial

isCmdMode = False
isLogEnabled = False

uartComPort  = sys.argv[1]
uartBaudrate = sys.argv[2]

if(len(sys.argv) >= 4) :
    if(sys.argv[3] == "LogSession") :
        isLogEnabled = True
    else :
        isLogEnabled = False

if(isLogEnabled) :
    f_log_ptr = open("cliLogs.txt","w")

ser = serial.Serial(uartComPort, uartBaudrate)

def getResponse() :

    global f_log_ptr
    global isLogEnabled

    response = ""
    while 1:
        chr = ser.read(1).decode('utf-8')
        if(chr == '$') :
            if(isLogEnabled) :
                f_log_ptr.write(response)
            print(response, end="")
            break
        else :
            response += chr

def doSomething() :

    global f_log_ptr
    global isCmdMode
    global isLogEnabled

    cliStartFrame = "hi bhai"
    cliStopFrame = "bye bhai"
    
    while 1:
        data = input("")
        ser.write(bytes(data, 'utf-8'))

        if(data == cliStartFrame) :
            if(isLogEnabled) :
                f_log_ptr = open("cliLogs.txt","w")
            isCmdMode = True

        if(isCmdMode) :
            if(isLogEnabled) :
                f_log_ptr.write(data + '\n')
            getResponse()
            
            if(data == cliStopFrame) :
                if(isLogEnabled) : 
                    f_log_ptr.close()
                isCmdMode = False

if __name__ == "__main__":
    doSomething()