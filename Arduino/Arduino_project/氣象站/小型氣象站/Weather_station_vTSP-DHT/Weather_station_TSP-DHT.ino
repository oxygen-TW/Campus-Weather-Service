#include <DHT.h>
#include <LiquidCrystal_I2C.h>

int measurePin = 0; //Connect dust sensor to Arduino A0 pin
int ledPower = 2;   //Connect 3 led driver pins of dust sensor to Arduino D2
int DHdata = 8;
int sw = 9;
byte dat[5];

int samplingTime = 280;
int deltaTime = 40;
int sleepTime = 9680;

float voMeasured = 0;
float calcVoltage = 0;
float dustDensity = 0;

byte read_data()
{
  byte data;
  for (int i = 0; i < 8; i++)
  {
    if (digitalRead(DHdata) == LOW)
    {
      while (digitalRead(DHdata) == LOW);
      delayMicroseconds(30);
      if (digitalRead(DHdata) == HIGH) data |= (1 << (7 - i));
      while (digitalRead(DHdata) == HIGH);
    }
  }
  return data;
}

void start_test()
{
  digitalWrite(DHdata, LOW);
  delay(30);
  digitalWrite(DHdata, HIGH);
  delayMicroseconds(40);
  pinMode(DHdata, INPUT);
  while (digitalRead(DHdata) == HIGH);
  delayMicroseconds(80);
  if (digitalRead(DHdata) == LOW);
  delayMicroseconds(80);
  for (int i = 0; i < 4; i++) dat[i] = read_data();
  pinMode(DHdata, OUTPUT);
  digitalWrite(DHdata, HIGH);
}

LiquidCrystal_I2C lcd(0x27, 16, 2);
void setup() {
  Serial.begin(9600);
  lcd.begin();
  pinMode(ledPower, OUTPUT);
  pinMode(sw, INPUT);
  pinMode(DHdata, OUTPUT);
}

void loop() {
  if (digitalRead(sw) == LOW)
  {
    digitalWrite(ledPower, LOW); // power on the LED
    delayMicroseconds(samplingTime);

    voMeasured = analogRead(measurePin); // read the dust value

    delayMicroseconds(deltaTime);
    digitalWrite(ledPower, HIGH); // turn the LED off
    delayMicroseconds(sleepTime);

    // 0 - 5V mapped to 0 - 1023 integer values
    // recover voltage
    calcVoltage = voMeasured * (5.0 / 1024.0);

    // linear eqaution taken from http://www.howmuchsnow.com/arduino/airquality/
    // Chris Nafis (c) 2012
    dustDensity = (0.172 * calcVoltage) - 0.0999;

    /*Serial.print("Raw Signal Value (0-1023): ");
      Serial.print(voMeasured);

      Serial.print(" - Voltage: ");
      Serial.print(calcVoltage);

      Serial.print(" - Dust Density: ");
      Serial.print(dustDensity * 1000); // 這裡將數值呈現改成較常用的單位( ug/m3 )
      Serial.println(" ug/m3 ");*/
    //***************************
    lcd.clear();
    lcd.print("Dust Density:");
    lcd.setCursor(0, 1);
    lcd.print(dustDensity * 1000); // 這裡將數值呈現改成較常用的單位( ug/m3 )
    lcd.print(" ug/m3");
    delay(3000);
  }
  else if (digitalRead(sw) == HIGH)
  {
    start_test();
    lcd.clear();
    lcd.print("Temperature= ");
    lcd.print(dat[2], DEC);
    lcd.println('C');

    lcd.setCursor(0, 1);

    lcd.print("Humdity = ");
    lcd.print(dat[0], DEC);
    lcd.print('%');
    delay(400);
  }
}
