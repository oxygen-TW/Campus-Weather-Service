#!/usr/bin/python
#bcoding=UTF-8

import smtplib
from email.mime.text import MIMEText
from email.mime.multipart import MIMEMultipart
import urllib2
import json

def GetJson():
	_url = "https://api.thingspeak.com/channels/148353/feeds.json?results=1"

	response = urllib2.urlopen(_url)
	json_data = response.read()
	pre_data = json.loads(json_data)
	sec_data = pre_data['feeds']
	pre_list = sec_data[0]
	data = pre_list
	#data = json.loads(pre_data['channel'])

	return data

	response.close()

def WeatherString(data):
	useful_list=[data['field1'],data['field2'],data['field3'],data['field4'],data['created_at']]
	weatherstr='氣溫： %s\n溼度： %s\n紫外線： %s\n光強度： %s\n'%(str(useful_list[0]),str(useful_list[1]),str(useful_list[2]),str(useful_list[3]))
	return weatherstr

msg = MIMEMultipart('alternative')

gmail_user = 'weatherstationtw@gmail.com'
gmail_pwd = 'NHWS1234'

smtpserver = smtplib.SMTP("smtp.gmail.com",587)
smtpserver.ehlo()
smtpserver.starttls()
smtpserver.ehlo()

smtpserver.login(gmail_user, gmail_pwd)


fromaddr = "weatherstationtw@gmail.com"

toaddrs = ['s10400119@nhsh.tp.edu.tw', 'howard2805@gmail.com']
 
msg['Subject']="校園氣象服務自動發報->TEST"
msg["From"]= fromaddr
msg["To"]= ','.join(toaddrs)

weather_data = GetJson()
sendText="早安!\n氣象站團隊提醒您\n目前天氣狀況如下：\n%s\n\n氣象站團隊祝您順心愉快！" % WeatherString(weather_data)
#print (sendText)
part = MIMEText(sendText,"plain",_charset="UTF-8")
part2 = MIMEText(WeatherString(weather_data),"plain",_charset="UTF-8")
part3 = MIMEText("\n\n氣象站團隊祝您順心愉快！","plain",_charset="UTF-8")
#print (part)
msg.attach(part)

smtpserver.sendmail(fromaddr, toaddrs, msg.as_string())

smtpserver.quit()