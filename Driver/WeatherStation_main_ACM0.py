#!/usr/bin/python

import sys
import time
import httplib
import urllib
import re
import serial


def upload(temperature, humidity, UV_value, light_value):
        params = urllib.urlencode({'field1': temperature, 'field2': humidity, 'field3': UV_value, 'field4': light_value, 'key':'M108RN6TTVSB0QEB'})
        
        headers = {"Content-type": "application/x-www-form-urlencoded","Accept": "text/plain"}
        conn = httplib.HTTPConnection("api.thingspeak.com:80")
        conn.request("POST", "/update", params, headers)
        response = conn.getresponse()
        print response.status, response.reason
        data = response.read()
        conn.close()

def WriteFile(current_weather):
    fp = open('/home/oxygen/Desktop/NHWS/data.txt','a')
    fp.write(current_weather)    
    fp.close()
    
def GetAnalogIndex():
    #Open Serial Port To Arduino nano
    ser = serial.Serial('/dev/ttyACM0', 9600, timeout=1)
    ser.isOpen()
    
    try:
        while True:
        #print 'RPi is sending request to arduino'
            print ('connecting to Arduino...')
            ser.write('L')
            response1 = ser.readline()
            ser.write('U')
            response2 = ser.readline()
            ser.write('H')
            response3 = float(ser.readline())
            ser.write('T')
            response4 = float(ser.readline())
            #ser.write('D')
            #response5 = ser.readline()
            #print(request) #debug only
            #print (response1) #debug only
            #print (response2) #debug only
            if response1 and response2 and response3 and response4 != '':
                break
            
    except KeyboardInterrupt:
        ser.close()
    return response1,response2,response3,response4



#while True:
light_value, UV_value, humidity, temperature = GetAnalogIndex()
light_value=1023-int(light_value,10)
    
    #if humidity is not None and temperature is not None:
current_weather=time.strftime("%Y/%m/%d %H:%M:%S ")+'Temp={0:0.1f}* Humidity={1:0.1f}% light_value={2:0.1f}'.format(temperature, humidity, light_value)+' UV_value='+UV_value
print(current_weather)
#	print(UV_value)
WriteFile(current_weather+'\n')
upload(temperature, humidity, UV_value, light_value)    	
    #time.sleep(52)

    #else:
    #	print('Failed to get reading. Try again!')
    #	sys.exit(1)
 
