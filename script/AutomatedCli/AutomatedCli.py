import time
import serial

f_log_ptr = open("cliLogs.txt","w")
f_cmd_ptr = open("cliCommands.txt","r")
serial_ptr = serial.Serial("COM6", 115200)

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
        #time.sleep(1)

doSomething()