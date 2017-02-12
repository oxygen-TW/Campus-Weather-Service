#include <SoftwareSerial.h>
SoftwareSerial debug(2, 3); //(RX,TX)
#define _baudrate 9600

void sendDebug(String cmd)
{   cmd="AT";
    Serial.print("SEND: ");
    debug.println(cmd);
    Serial.println(cmd);
} 
void setup()
{
  debug.begin(115200);  //軟體序列埠速率 (與硬體同步調整)
  Serial.begin(9600);    //硬體序列埠速率 (與軟體同步調整)
  Serial.println("SoftSerial to ESP8266 AT commands test ...");
  debug.println("AT+CIOBAUD=9600");
  debug.begin(9600);
}

void loop()
{
  sendDebug("AT");  //讀取後寫入軟體序列埠 Tx (ESP8266)
  delay(1000);
  if (debug.available())   //若軟體序列埠 Rx 收到資料 (來自 ESP8266)
  {
    String data = String(debug.read());
    Serial.println(data);  //讀取後寫入硬體序列埠 Tx (PC)
  }

  if (Serial.available())  //若硬體序列埠 Rx 收到資料 (來自 PC)
  {
    String data = String(Serial.read());
    debug.println(data);  //讀取後寫入軟體序列埠 Tx (ESP8266)
  }
}
