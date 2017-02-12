#include "Bridge.h"
#include "HttpClient.h"

//Thingspeak parameters
String thingspeak_update_API    = "http://api.thingspeak.com/update?";
String thingspeak_write_API_key = "key=M108RN6TTVSB0QEB";//Insert Your Write API key here
String thingspeakfieldname      = "&field1=";

void postToThinspeak(int);
void setup() {
  // Initialize Bridge
  Bridge.begin();
  // Initialize Serial
  Serial.begin(9600);
  // Wait until a Serial Monitor is connected.
  while (!Serial);
  //Data to be sent to thingspeak, change this variable value and post accordingly

}

void loop() {
  int data=240;
  // run various example processes
  postToThinspeak(data);
  // Ensure the last bit of data is sent.
  Serial.flush();
}

void postToThinspeak(int data) {
  HttpClient client;

    String request_string =  thingspeak_update_API + thingspeak_write_API_key + thingspeakfieldname + data;
    // Make a HTTP request:
    client.get(request_string);

  // if there are incoming bytes available
  // from the server, read them and print them:
  while (client.available()) {
    char c = client.read();
    Serial.print(c);
  }

  delay(15000);
  }

