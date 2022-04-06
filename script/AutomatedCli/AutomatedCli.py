import time
import serial

cmd = ""
response = ""

f_cmd_ptr = open("cliCommands.txt","r")
serial_ptr = serial.Serial("COM6", 115200)

def getResponse() :
    global response
    response = ""
    while 1:
        chr = serial_ptr.read(1).decode('utf-8')
        if(chr == '$') :
            break
        else :
            response += chr

while 1:
    cmd = f_cmd_ptr.readline()

    if(not cmd) :
        break

    if(cmd[-1] == '\n') :
        cmd = cmd[0:-1]

    print(cmd)
    serial_ptr.write(bytes(cmd, 'utf-8'))
    getResponse()
    print(response, end="")

    time.sleep(1)