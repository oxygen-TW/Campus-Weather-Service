void postToThinspeak(String data1, String data2, String data3) {
  HttpClient client;
  String thingspeak_update_API    = "http://api.thingspeak.com/update?";
  String thingspeak_write_API_key = "key=M108RN6TTVSB0QEB";//Insert Your Write API key here
  String thingspeakfieldname1     = "&field1=";
  String thingspeakfieldname2     = "&field2=";
  String thingspeakfieldname3	  = "&field3=";

  String request_string =  thingspeak_update_API + thingspeak_write_API_key + thingspeakfieldname1 + data1 + thingspeakfieldname2 + data2
						+ thingspeakfieldname3+data3;
  // Make a HTTP request:
  client.get(request_string);

  // if there are incoming bytes available
  // from the server, read them and print them:
  while (client.available()) {
    char c = client.read();
    Serial.print(c);
  }
}

