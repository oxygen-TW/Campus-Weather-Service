#include <LiquidCrystal_I2C.h>
#include <SoftwareSerial.h>

#include "DHT.h"
#define DEBUG
#define Wait_time 296000
#define _ledpin     13

LiquidCrystal_I2C lcd(0x27, 16, 2);

const String crlf="\r\n";
void sendDebug(String);
void updateDHT11( String , String  );
boolean connectWiFi(void);
//*-- Hardware Serial
#define _baudrate   115200
#define _rxpin      4
#define _txpin      5
SoftwareSerial debug( _rxpin, _txpin ); // RX, TX

//*-- DHT11
#define _dhtpin     8
#define _dhttype    DHT11

DHT dht11( _dhtpin, _dhttype );
uint8_t dhtbuf[2];

//*-- IoT Information
#define SSID "iPad" 
#define PASS "001002003"
#define IP "api.thingspeak.com" // ThingSpeak IP Address: 184.106.153.149
// 使用 GET 傳送資料的格式
// GET /update?key=[THINGSPEAK_KEY]&field1=[data 1]&filed2=[data 2]...;
String THINGSPEAK_KEY = "M108RN6TTVSB0QEB";
String GET = "GET /update?key="+THINGSPEAK_KEY;

void setup() {
    Serial.begin( _baudrate );
    debug.begin( _baudrate );
    lcd.begin();
    
    sendDebug("AT\r\n");
     delay(1500);
    if(debug.find("OK"))
    {
        lcd.print("Setup AT OK");
        Serial.println("RECEIVED: OK\nData ready to sent!");
        connectWiFi();
    }
    else
    {
      lcd.print("Setup AT ERROR");
      Serial.println("RECEIVED: ERROR");
    }
       

    // DHT11
    dht11.begin();

    pinMode( _ledpin, OUTPUT );
    digitalWrite( _ledpin, LOW );
}

void loop() {
    lcd.clear();
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

    delay(Wait_time);   // 60 second
}

void updateDHT11( String T, String H )
{
    // 設定 ESP8266 作為 Client 端
    String cmd = "AT+CIPSTART=\"TCP\",\"";
    cmd += IP;
    cmd += "\",80";
    sendDebug(cmd);
    delay(2000);
    if( debug.find( "Error" ) )
    {
        Serial.print( "RECEIVED: Error\nExit1" );
        return;
        //goto Start;
    }

    cmd = GET + "&field1=" + T + "&field2=" + H +"\r\n";
    debug.print( "AT+CIPSEND=" );
    debug.println( cmd.length() );
    if(debug.find( ">" ) )
    {
        Serial.print(">");
        debug.print(cmd);
        Serial.print(cmd);
        lcd.clear();
        lcd.print("TCP UPLOAD");
    }
    else
    {
      lcd.print("TCP ERROR");
        sendDebug( "AT+CIPCLOSE" );
    }
    if( debug.find("OK") )
    {
         lcd.setCursor(0, 1);
         lcd.print("Return OK");
        Serial.println( "RECEIVED: OK" );
    }
    else
    {
      lcd.print("Return ERROR");
        Serial.println( "RECEIVED: Error\nExit2" );
    }
}

void sendDebug(String cmd)
{
    Serial.print("SEND: ");
    debug.println(cmd);
    Serial.println(cmd);
} 
 
boolean connectWiFi()
{

    sendDebug("AT+CWMODE=1"+crlf);
    delay(2000);
    String cmd="AT+CWJAP=\"";
    cmd+=SSID;
    cmd+="\",\"";
    cmd+=PASS;
    cmd+="\"";
    sendDebug(cmd+crlf);
    delay(8000);
    Serial.println("time chk");
    String data = String(debug.read());
    Serial.print(data);  //讀取後寫入硬體序列埠 Tx (PC)

    lcd.clear();
    if(debug.find("OK"))
    {
       lcd.print("WIFI OK");
        Serial.println("RECEIVED: OK");
        return true;
    }
    else
    {
      lcd.print("WIFI ERROR");
        Serial.println("RECEIVED: Error");
        return false;
    }

    cmd = "AT+CIPMUX=0"+crlf;
    sendDebug( cmd );
    if( debug.find( "ERROR") )
    {
      lcd.clear();
      lcd.print("CIPMUX ERROR");
        Serial.print( "RECEIVED: Error" );
        return false;
    }
}
