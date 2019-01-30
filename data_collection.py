import serial
import time

ser = serial.Serial(3, 115200)

while True :
    try :
        print(ser.readline())
    except ser.SerialTimeoutException :
        print('data could not be read')
    time.sleep(1e-5)