//General Firmware
//Format
//{"type":Firmware-Type,"obj1":Tempreture,"obj2":Humidity,"obj3":Light_index,"obj4":UV_index}
//
//2017/07/01

#include <DHT.h>
byte number = 0;
#define DHTPIN 2
#define DHTTYPE DHT22

DHT sensor(DHTPIN, DHTTYPE);

String MakeJson(double obj1, double obj2, double obj3, double obj4)
{
  String JsonStr("{");

  JsonStr += "\"type\":\"General\",";
  
  JsonStr += "\"Temp\":";
  JsonStr += isnan(obj1) ? DtoS(obj1) + "," :"\"NAN\", ";

  JsonStr += "\"Humi\":";
  JsonStr += isnan(obj2) ? DtoS(obj1) + "," :"\"NAN\", ";
  
  JsonStr += "\"light\":" + DtoS(obj3) + ",";
  JsonStr += "\"UV\":" + DtoS(obj4);
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


/*-float TSPsensor()
  {
  int samplingTime = 280;
  int deltaTime = 40;
  int sleepTime = 180;

  float voMeasured = 0;
  float calcVoltage = 0;
  float dustDensity = 0;
  digitalWrite(ledPower, LOW); // power on the LED
  delayMicroseconds(samplingTime);

  voMeasured = analogRead(measurePin); // read the dust value

  delayMicroseconds(deltaTime);
  digitalWrite(ledPower, HIGH); // turn the LED off
  delayMicroseconds(sleepTime);

  // 0 - 5V mapped to 0 - 1023 integer values
  // recover voltage
  calcVoltage = voMeasured * (5.0 / 1024.0);
  dustDensity = 0.17 * calcVoltage - 0.1;

  return dustDensity*1000;
  }*/

void setup() {
  Serial.begin(9600);
  sensor.begin();
}

void loop() {
  if (Serial.available()) {
    number = Serial.read();
    if (number == 'D')
    {
      double Temp = sensor.readTemperature();
      double Humi = sensor.readHumidity();
      double light = analogRead(A1);
      double UV = analogRead(A0);

      if (isnan(Temp)) Temp = -500;
      if (isnan(Humi)) Humi = -1;
      Serial.println(MakeJson(Temp, Humi, light, UV));
    }
  }
  /*else
    Serial.println("FAIL");*/
  delay(10);

}
