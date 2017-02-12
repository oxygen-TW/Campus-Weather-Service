#include <DHT.h>

#define DHTtype DHT22
#define DHTpin 8
#define Delaytime 2000
DHT dht(DHTpin, DHTtype);

bool DHTchk(float,float,float);
void DHTprint(float,float,float);

void setup() {
  // put your setup code here, to run once:
  dht.begin();
}

void loop() {
  delay(Delaytime);
  // put your main code here, to run repeatedly:
 float h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  float t = dht.readTemperature();
  // Read temperature as Fahrenheit (isFahrenheit = true)
  float f = dht.readTemperature(true);
  
  if(!DHTchk(h,t,f))
  {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }
  DHTprint(h,t,f);
}


