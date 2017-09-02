#!/usr/bin/python
import json
import sys
import time
import httplib
import urllib
import re
import serial

def GetJson():
#Open Serial Port To Arduino nano
    ser = serial.Serial('/dev/ttyACM0', 9600, timeout=1)
    ser.isOpen()
    
    try:
        while True:
        #print 'RPi is sending request to arduino'
            print ('connecting to Arduino...')
            ser.write('D')
            response = ser.readline()
            
            #print (response) #debug only
            if response != '':
                break
            
    except KeyboardInterrupt:
        ser.close()
    return response

JsonData = GetJson()
print(JsonData)

data = json.loads(JsonData)
print(data['type'])
print(data['Temp'])
print(data['Humi'])