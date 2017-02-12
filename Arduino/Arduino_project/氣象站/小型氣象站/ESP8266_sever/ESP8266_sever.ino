#include <SoftwareSerial.h>
#define DEBUG true
#define timeout_short 1000
#define timeout_long 2000
SoftwareSerial esp8266(4, 5); //(RX,TX)

void setup() {
  Serial.begin(9600); //start hardware serial port
  esp8266.begin(115200); //start soft serial port
  sendData("AT+RST\r\n", timeout_long, DEBUG); // reset module
  sendData("AT+CWMODE=3\r\n", timeout_short, DEBUG); // configure as STA+AP
  sendData("AT+CIFSR\r\n", timeout_short, DEBUG); // get ip address
  sendData("AT+CIPMUX=1\r\n", timeout_short, DEBUG); // configure for multiple connections
  sendData("AT+CIPSERVER=1,80\r\n", timeout_short, DEBUG); // turn on server on port 80
}

void loop() {
  if (esp8266.available()) { // check if the esp is sending a message
    /*
      while(esp8266.available())
      {
      // The esp has data so display its output to the serial window
      char c = esp8266.read(); // read the next character.
      Serial.write(c);
      } */

    if (esp8266.find("+IPD,")) {  //收到客戶端的連線要求, 進行回應
      delay(timeout_short);
      // +IPD, 後的字元是連線 ID (ASCII碼), 用 read() 讀取後減 48 為數字
      int connectionId = esp8266.read() - 48;
      //subtract 48 because the read() function returns
      //the ASCII decimal value and 0 (the first decimal number) starts at 48
      String webpage = "<html><form method=get>SSID <input name=ssid type=text><br>";
      String cipSend = "AT+CIPSEND=";
      cipSend += connectionId;
      cipSend += ",";
      cipSend += webpage.length();
      cipSend += "\r\n";
      sendData(cipSend, timeout_short, DEBUG);
      sendData(webpage, timeout_long, DEBUG);

      webpage = "PWD <input name=password type=text> ";
      cipSend = "AT+CIPSEND=";
      cipSend += connectionId;
      cipSend += ",";
      cipSend += webpage.length();
      cipSend += "\r\n";
      sendData(cipSend, timeout_short, DEBUG);
      sendData(webpage, timeout_long, DEBUG);

      webpage = "<input type=submit value=Connect></form></html>";
      cipSend = "AT+CIPSEND=";
      cipSend += connectionId;
      cipSend += ",";
      cipSend += webpage.length();
      cipSend += "\r\n";
      sendData(cipSend, timeout_short, DEBUG);
      sendData(webpage, timeout_long, DEBUG);

      String closeCommand = "AT+CIPCLOSE=";
      closeCommand += connectionId; // append connection id
      closeCommand += "\r\n";
      sendData(closeCommand, 3000, DEBUG);
    }
  }
}

String sendData(String command, const int timeout, boolean debug) {
  String response = "";
  esp8266.print(command); // send the read character to the esp8266
  long int time = millis();
  while ((time + timeout) > millis()) {
    while (esp8266.available()) {
      // The esp has data so display its output to the serial window
      char c = esp8266.read(); // read the next character.
      response += c;
    }
  }
  if (debug) {
    Serial.print(response);
  }
  return response;
}
