#include <LiquidCrystal_I2C.h>
#include <DHT.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

int DHdata = 8;
int sw = 2;
byte dat[5];

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

void setup() {
  pinMode(sw, INPUT);
  pinMode(DHdata, OUTPUT);
  lcd.begin();
}

void loop() {
  // put your main code here, to run repeatedly:
  if (digitalRead(sw) == HIGH)
  {
    start_test();
    lcd.print("Current temperature = ");
    lcd.print(dat[2], DEC);
    lcd.println('C');

    lcd.setCursor(0, 1);

    lcd.print("Current humdity = ");
    lcd.print(dat[0], DEC);
    lcd.println('%');
    delay(400);
  }
}
