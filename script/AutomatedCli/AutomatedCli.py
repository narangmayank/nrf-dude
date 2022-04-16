import sys
import serial

UART_COMPORT  = sys.argv[1]
UART_BAUDRATE = sys.argv[2]

f_log_ptr = open("cliLogs.txt","w")
f_cmd_ptr = open("cliCommands.txt","r")

serial_ptr = serial.Serial(UART_COMPORT, UART_BAUDRATE)

def putCommand():
    cmd  = f_cmd_ptr.readline()

    if not cmd :
        exit()

    if(cmd[-1] == '\n') :
        cmd = cmd[0:-1]
    
    print(cmd)
    serial_ptr.write(bytes(cmd, 'utf-8'))

    f_log_ptr.write(cmd + '\n')

def getResponse():
    res = ""

    while 1:
        chr = serial_ptr.read(1).decode('utf-8')
        if(chr == '$') :
            print(res, end="")
            break
        else :
            res += chr

    f_log_ptr.write(res)

def doSomething() :

    while 1 :    
        putCommand()
        getResponse()
        
if __name__ == "__main__":
    doSomething()