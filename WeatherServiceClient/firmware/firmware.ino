/*
 * School Weather Service Project 2016-2017
 * Github https://github.com/oxygen-TW/Weather-Station
 * E-mail weatherstationTW@gmail.com
 * Service Website http://weather.nhsh.tp.edu.tw
 */

#include "config.h"
#include <SoftwareSerial.h>
#include <Adafruit_Sensor.h>
#include <DHT.h>


//General Firmware
//Format
//{"type":Firmware-Type,"obj1":Tempreture,"obj2":Humidity,"obj3":Light_index,"obj4":UV_index, "obj5":RainFall}
//
//2017/07/01
//2017/08/29

byte number = 0;
#define LENG 31   //0x42 + 31 bytes equal to 32 bytes
unsigned char buf[LENG];

int PM01Value=0;          //define PM1.0 value of the air detector module
int PM2_5Value=0;         //define PM2.5 value of the air detector module
int PM10Value=0;         //define PM10 value of the air detector module
SoftwareSerial PMSerial(10,11);
DHT sensor(DHTPIN, DHTTYPE);

char checkValue(unsigned char *thebuf, char leng)
{  
  char receiveflag=0;
  int receiveSum=0;

  for(int i=0; i<(leng-2); i++){
  receiveSum=receiveSum+thebuf[i];
  }
  receiveSum=receiveSum + 0x42;
 
  if(receiveSum == ((thebuf[leng-2]<<8)+thebuf[leng-1]))  //check the serial data 
  {
    receiveSum = 0;
    receiveflag = 1;
  }
  return receiveflag;
}

int transmitPM01(unsigned char *thebuf)
{
  int PM01Val;
  PM01Val=((thebuf[3]<<8) + thebuf[4]); //count PM1.0 value of the air detector module
  return PM01Val;
}

//transmit PM Value to PC
int transmitPM2_5(unsigned char *thebuf)
{
  int PM2_5Val;
  PM2_5Val=((thebuf[5]<<8) + thebuf[6]);//count PM2.5 value of the air detector module
  return PM2_5Val;
  }

//transmit PM Value to PC
int transmitPM10(unsigned char *thebuf)
{
  int PM10Val;
  PM10Val=((thebuf[7]<<8) + thebuf[8]); //count PM10 value of the air detector module  
  return PM10Val;
}

String MakeJson(double obj1, double obj2, double obj3, double obj4, double obj5)
{
  String JsonStr("{");

  JsonStr += "\"type\":\"General\",";
  
  JsonStr += "\"Temp\":";
  JsonStr += isnan(obj1) ? DtoS(obj1) + "," :"\"NAN\", ";

  JsonStr += "\"Humi\":";
  JsonStr += isnan(obj2) ? DtoS(obj1) + "," :"\"NAN\", ";
  
  JsonStr += "\"light\":" + DtoS(obj3) + ",";
  JsonStr += "\"UV\":" + DtoS(obj4) + ",";
  JsonStr += "\"Rain\":" + DtoS(obj5);
  JsonStr += "}";
  return JsonStr;
}

String DtoS(double num)
{
  char x[10] = {""};
  dtostrf(num, 5, 2, x);
  String objstr(x);
  return objstr;
}


/*void GetPMData()
{
  PMSerial.readBytes(buf,LENG);
  Serial.println(buf[0]);
  if(buf[0] == 0x4d){
      if(checkValue(buf,LENG)){
        PM01Value=transmitPM01(buf); //count PM1.0 value of the air detector module
        PM2_5Value=transmitPM2_5(buf);//count PM2.5 value of the air detector module
        PM10Value=transmitPM10(buf); //count PM10 value of the air detector module 
      }          
}
}*/
void setup() {
  Serial.begin(9600);
  PMSerial.begin(9600);
  sensor.begin();
}

void loop() {
  if (Serial.available()) {
    number = Serial.read();
    if (number == 'D')
    {
      /*GetPMData();
      Serial.println(PM01Value);
      Serial.println(PM2_5Value);
      Serial.println(PM10Value);*/
      double Temp = sensor.readTemperature();
      double Humi = sensor.readHumidity();
      double light = analogRead(A1);
      double UV = analogRead(A0);
      double Rain = analogRead(A2);
      
      if (isnan(Temp)) Temp = -500;
      if (isnan(Humi)) Humi = -1;
      Serial.println(MakeJson(Temp, Humi, light, UV, Rain));
    }
  }
  /*else
    Serial.println("FAIL");*/
  delay(10);

}
