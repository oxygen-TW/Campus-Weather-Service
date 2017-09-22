#!/usr/bin/python
#-*- coding=utf-8 -*-

'''
School Weather Service Project 2016-2017
Github https://github.com/oxygen-TW/Weather-Station
E-mail weatherstationTW@gmail.com
Service Website http://weather.nhsh.tp.edu.tw
Lisence: BSD-3 clause

'''
import sys
import time
import httplib
import urllib
import re
import serial
import json
from time import sleep
import database #Service Upload

# Format python ToDB_Driver.py [USB PORT] [DataLog]

def WriteFile(current_weather,_File):
    try:
        fp = open(_File,'a')
        fp.write(current_weather)    
    except IOError:
        print('File Open Error')
    finally:
        fp.close()
    
def GetJsonData():
#Open Serial Port To Arduino nano
    ser = serial.Serial(str(sys.argv[1]), 9600, timeout=1)
    ser.isOpen()
    
    try:
        while True:
        #print 'RPi is sending request to arduino'
            print ('connecting to MCU...')
            ser.write('D')
            sleep(0.5) #Wait for MCU processing
            response = ser.readline()
            
            #print (response) #debug only
            if response != '':
                break
            
    except KeyboardInterrupt:
        ser.close()
    finally:
        ser.close()
    return response

def main():
    #Check Argv
    if len(sys.argv) != 3:
        print("argv Error")
        exit()

    print ("Detector on "+sys.argv[1])
    print ("Data log in "+sys.argv[2])
    
    LogFile = sys.argv[2]
    
    #Get ang Resolve data
    JsonData = GetJsonData()
    print (JsonData)
    data = json.loads(JsonData)
    temperature = data['Temp']
    humidity = data['Humi']
    light_value = data['light']
    UV_value = data['UV']
    RainFall = data['Rain']

    RainFall = 1023 - RainFall  #Fixed RainFall Value
    
    #Get Time
    UploadTime = time.strftime("%Y/%m/%d %H:%M:%S")
    current_weather= UploadTime +' '
    
    #Start Data Check
    if temperature == "NAN":
        current_weather+='Temp=Err'
    else:
        current_weather+='Temp='+str(temperature)+'*'

    if humidity == "NAN":
        current_weather+=' Humidity=Err'
    else:
        current_weather+=' Humidity='+str(humidity)+'%'
    
    if light_value > 1023 or light_value < 0:
        light_value = "Err"

    if UV_value > 1023 or UV_value < 0:
        UV_value = "Err"

    if RainFall > 1023 or RainFall < 0:
        RainFall = "Err"
 
    current_weather += ' light_value='+ str(light_value) + ' UV=' + str(UV_value) + ' Rain=' + str(RainFall) 

    print(current_weather)
    #因增加系統穩定性，暫時移除本機Log
    #WriteFile(current_weather+'\n',LogFile) 

    #Call Connect to Weather Service DataBase
    database.insert_weather((UploadTime,temperature, float(humidity), float(UV_value), light_value,RainFall))

if __name__ == "__main__":
    main()

#開發為何如此艱辛，每一個成功的作品背後，難道都是這樣的壓力與煎熬嗎?