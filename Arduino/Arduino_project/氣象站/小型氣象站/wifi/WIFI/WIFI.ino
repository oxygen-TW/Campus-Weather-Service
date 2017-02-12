#include <SoftwareSerial.h>
#include "DHT.h"

#define DEBUG

#define _ledpin     13

void sendDebug(String);
void updateDHT11( String , String  );
boolean connectWiFi(void);
//*-- Hardware Serial
#define _baudrate   115200
#define _rxpin      2
#define _txpin      3
SoftwareSerial debug( _rxpin, _txpin ); // RX, TX

//*-- DHT11
#define _dhtpin     8
#define _dhttype    DHT11

DHT dht11( _dhtpin, _dhttype );
uint8_t dhtbuf[2];

//*-- IoT Information
#define SSID "Oxygen" 
#define PASS "12345678"
#define IP "api.thingspeak.com" // ThingSpeak IP Address: 184.106.153.149
// 使用 GET 傳送資料的格式
// GET /update?key=[THINGSPEAK_KEY]&field1=[data 1]&filed2=[data 2]...;
String THINGSPEAK_KEY = "1WYVQRDB8J2H3XQH";
String GET = "GET /update?key="+THINGSPEAK_KEY;

void setup() {
    Serial.begin( _baudrate );
    debug.begin( _baudrate );

    sendDebug("AT");
    delay(5000);
    if(Serial.find("OK\r\n"))
    {
        Serial.println("RECEIVED: OK\nData ready to sent!");
        connectWiFi();
    }
   

    // DHT11
    dht11.begin();

    pinMode( _ledpin, OUTPUT );
    digitalWrite( _ledpin, LOW );
}

void loop() {
    dhtbuf[0] = dht11.readHumidity();
    dhtbuf[1] = dht11.readTemperature();

    // 確認取回的溫溼度數據可用
    if( isnan(dhtbuf[0]) || isnan(dhtbuf[1]) )
    {
        Serial.println( "Failed to read form DHT11" );
    }
    else
    {
        digitalWrite( _ledpin, HIGH );
        char buf[3];
        String HH, TT;
        buf[0] = 0x30 + dhtbuf[1] / 10;
        buf[1] = 0x30 + dhtbuf[1] % 10;
        TT = (String(buf)).substring( 0, 2 );
        buf[0] = 0x30 + dhtbuf[0] / 10;
        buf[1] = 0x30 + dhtbuf[0] % 10;
        HH = (String(buf)).substring( 0, 2 );

        updateDHT11( TT, HH );
        #ifdef DEBUG
            Serial.print("Humidity: "); 
            Serial.print( HH );
            Serial.print(" %\t");
            Serial.print("Temperature: "); 
            Serial.print( TT );
            Serial.println(" *C\t");
        #endif
        digitalWrite( _ledpin, LOW );
    }

    delay(60000);   // 60 second
}

void updateDHT11( String T, String H )
{
    // 設定 ESP8266 作為 Client 端
    String cmd = "AT+CIPSTART=\"TCP\",\"";
    cmd += IP;
    cmd += "\",80";
    sendDebug(cmd);
    delay(2000);
    if( Serial.find( "Error" ) )
    {
        Serial.print( "RECEIVED: Error\nExit1" );
        return;
    }

    cmd = GET + "&field1=" + T + "&field2=" + H +"\r\n";
    debug.print( "AT+CIPSEND=" );
    debug.println( cmd.length() );
    if(Serial.find( ">" ) )
    {
        debug.print(">");
        debug.print(cmd);
        Serial.print(cmd);
    }
    else
    {
        sendDebug( "AT+CIPCLOSE" );
    }
    if( Serial.find("OK") )
    {
        Serial.println( "RECEIVED: OK" );
    }
    else
    {
        Serial.println( "RECEIVED: Error\nExit2" );
    }
}

void sendDebug(String cmd)
{
    debug.print("SEND: ");
    debug.println(cmd);
    Serial.println(cmd);
} 
 
boolean connectWiFi()
{
    debug.println("AT+CWMODE=1");
    delay(2000);
    String cmd="AT+CWJAP=\"";
    cmd+=SSID;
    cmd+="\",\"";
    cmd+=PASS;
    cmd+="\"";
    sendDebug(cmd);
    delay(5000);
    if(Serial.find("OK\r\n"))
    {
        Serial.println("RECEIVED: OK");
        return true;
    }
    else
    {
        Serial.println("RECEIVED: Error");
        return false;
    }

    cmd = "AT+CIPMUX=0";
    sendDebug( cmd );
    if( Serial.find( "Error") )
    {
        Serial.print( "RECEIVED: Error" );
        return false;
    }
}
