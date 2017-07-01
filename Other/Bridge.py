#!/usr/bin/python

import sys
import time
import httplib
import urllib
import re
import serial
import json

APIKEY = 'Y1JUZC930YOKH5JA'

def upload(temperature, humidity, UV_value, light_value):
        params = urllib.urlencode({'field1': temperature, 'field2': humidity, 'field3': UV_value, 'field4': light_value, 'key': APIKEY})
        
        headers = {"Content-type": "application/x-www-form-urlencoded","Accept": "text/plain"}
        conn = httplib.HTTPConnection("api.thingspeak.com:80")
        conn.request("POST", "/update", params, headers)
        response = conn.getresponse()
        print response.status, response.reason
        data = response.read()
        conn.close()

def WriteFile(current_weather):
    fp = open('Data/data.txt','a')
    fp.write(current_weather)    
    fp.close()
    
def GetJsonData():
#Open Serial Port To Arduino nano
    ser = serial.Serial('/dev/ttyUSB0', 9600, timeout=1)
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
    finally:
        ser.close()
    return response

#while True:
JsonData = GetJsonData()
print (JsonData)
data = json.loads(JsonData)
temperature = data['Temp']
humidity = data['Humi']
light_value = data['light']
UV_value = data['UV']

#light_value=1023-light_value
    
    #if humidity is not None and temperature is not None:
current_weather=time.strftime("%Y/%m/%d %H:%M:%S ")
if temperature != "NAN":
    current_weather+='Temp=NAN'
else:
    current_weather+='Temp='+str(temperature)+'*'

if humidity != "NAN":
    current_weather+=' Humidity=NAN'
else:
    current_weather+=' Humidity='+str(humidity)+'%'
    
current_weather+= ' light_value={0:0.1f} UV={1:0.1f}'.format(light_value, UV_value)
print(current_weather)
#	print(UV_value)
#WriteFile(current_weather+'\n')
upload(temperature, humidity, UV_value, light_value)    	
