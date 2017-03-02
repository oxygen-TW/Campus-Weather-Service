#include <DHT.h>
byte number = 0;
#define DHTPIN 2
#define DHTTYPE DHT22

DHT sensor(DHTPIN, DHTTYPE);

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
