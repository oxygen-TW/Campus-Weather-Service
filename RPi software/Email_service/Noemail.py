#!/usr/bin/python
#bcoding=UTF-8

import smtplib
from email.mime.text import MIMEText
from email.mime.multipart import MIMEMultipart

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
 
msg['Subject']="校園氣象服務自動發報->170624"
msg["From"]= fromaddr
msg["To"]= ','.join(toaddrs)

part = MIMEText("\u20ac\n中文測試","plain",_charset="UTF-8")
msg.attach(part)
smtpserver.sendmail(fromaddr, toaddrs, msg.as_string())

smtpserver.quit()