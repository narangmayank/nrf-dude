import serial

isCmdMode = False
cliStartFrame = "hi bhai"
cliStopFrame = "bye bhai"

ser = serial.Serial("COM6", 115200)

def getResponse() :
    response = ""
    while 1:
        chr = ser.read(1).decode('utf-8')
        if(chr == '$') :
            print(response, end="")
            break
        else :
            response += chr
while 1:
    data = input("")
    ser.write(bytes(data, 'utf-8'))

    if(data == cliStartFrame) :
        isCmdMode = True

    if(isCmdMode) :
        getResponse()
        
        if(data == cliStopFrame) :
            isCmdMode = False