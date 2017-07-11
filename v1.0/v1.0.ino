#include <DHT.h>
byte number = 0;
#define DHTPIN 2
#define DHTTYPE DHT22

DHT sensor(DHTPIN, DHTTYPE);


void setup() {
  Serial.begin(9600);
  sensor.begin();
}

void loop() {
  if (Serial.available()) {
    number = Serial.read();
    if (number == 'L')
      Serial.print(analogRead(A0));//light_value
    else if (number == 'U')
      Serial.print(analogRead(A1));//UV_value
    else if (number == 'R')
      Serial.print(analogRead(A2));//Rain_value
    else if (number == 'T')
      Serial.print(sensor.readTemperature());//Temperature_value
    else if (number == 'H')
      Serial.print(sensor.readHumidity());//Humidity_value
   // else if (number == 'D')
//      Serial.print(TSPsensor());//Humidity_value
    //Serial.print("ok");

  }
  /*else
    Serial.println("FAIL");*/
  delay(10);

}
