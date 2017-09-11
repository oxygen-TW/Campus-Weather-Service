/*
 * School Weather Service Project 2016-2017
 * Github https://github.com/oxygen-TW/Weather-Station
 * E-mail weatherstationTW@gmail.com
 * Service Website http://weather.nhsh.tp.edu.tw
 * License: BSD-3 clause
 */

#include "config.h"
#include <SoftwareSerial.h>
#include <DHT.h>


//General Firmware
//Format
//{"type":Firmware-Type,"obj1":Tempreture,"obj2":Humidity,"obj3":Light_index,"obj4":UV_index, "obj5":RainFall}
//
//2017/07/01
//2017/08/29
//2017/09/11

byte number = 0;
#define LENG 31   //0x42 + 31 bytes equal to 32 bytes
unsigned char buf[LENG];

int PM01Value=0;          //define PM1.0 value of the air detector module
int PM2_5Value=0;         //define PM2.5 value of the air detector module
int PM10Value=0;         //define PM10 value of the air detector module
SoftwareSerial PMSerial(10,11);
DHT sensor(DHTPIN, DHTTYPE);


String MakeJson(double obj1, double obj2, double obj3, double obj4, double obj5)
{
  String JsonStr("{");

  JsonStr += "\"type\":\"General\",";
  
  JsonStr += "\"Temp\":";
  JsonStr += isnan(obj1) ? "\"NAN\", ":DtoS(obj1) + ",";

  JsonStr += "\"Humi\":";
  JsonStr += isnan(obj2) ? "\"NAN\", ":DtoS(obj2) + ",";
  
  JsonStr += "\"light\":" + DtoS(obj3) + ",";
  JsonStr += "\"UV\":" + DtoS(obj4) + ",";
  JsonStr += "\"Rain\":" + DtoS(obj5);
  JsonStr += "}";
  return JsonStr;
}

//convert Double to String
String DtoS(double num)
{
  char x[10] = {""};
  dtostrf(num, 5, 2, x);
  String objstr(x);
  return objstr;
}


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
      double Temp = sensor.readTemperature();
      double Humi = sensor.readHumidity();
      double light = analogRead(Light_Pin);
      double UV = analogRead(UV_Pin);
      double Rain = analogRead(Rain_Pin);
      
      if (isnan(Temp)) Temp = -500;
      if (isnan(Humi)) Humi = -1;
      Serial.println(MakeJson(Temp, Humi, light, UV, Rain));
    }
  }
  /*else
    Serial.println("FAIL");*/
  delay(10);

}
