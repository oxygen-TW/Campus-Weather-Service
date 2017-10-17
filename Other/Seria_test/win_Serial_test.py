# -*- coding: utf-8 -*-
import serial
import os

ser = serial.Serial('COM4',9600)
s = [0]
while True:
	read_serial=ser.readline()
	os.system("cls")
	#s[0] = str(int (ser.readline(),16))
	#print (s[0])
	print (read_serial.decode("utf-8"))
