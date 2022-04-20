import sys
import serial
from colored import fg

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

f_cmd_ptr = open("cliCommands.txt","r")
ser = serial.Serial(uartComPort, uartBaudrate)

def putCommand():

    global f_log_ptr
    global isLogEnabled

    cmd  = f_cmd_ptr.readline()

    if not cmd :
        exit()

    if(cmd[-1] == '\n') :
        cmd = cmd[0:-1]
    
    print(cmd)
    ser.write(bytes(cmd, 'utf-8'))

    if(isLogEnabled) : 
        f_log_ptr.write(cmd + '\n')

def getResponse():

    global f_log_ptr
    global isLogEnabled

    response = ""
    while 1:
        chr = ser.read(1).decode('utf-8')
        if(chr == '$') :
            if(isLogEnabled) : 
                f_log_ptr.write(response)

            magicIdx = response.find('\n')
            actualRes = response[0:magicIdx]
            cliPrompt = response[magicIdx:]

            if(actualRes[0:8] == "Shandaar") :
                print(fg('green') + actualRes + fg('white'), end="")
            elif(actualRes[0:4] == "Arre") :
                print(fg('red') + actualRes + fg('white'), end="")
            else :
                print(actualRes, end="")
            
            print(cliPrompt, end="")
            
            break
        else :
            response += chr

def doSomething() :

    while 1 :    
        putCommand()
        getResponse()
        
if __name__ == "__main__":
    doSomething()