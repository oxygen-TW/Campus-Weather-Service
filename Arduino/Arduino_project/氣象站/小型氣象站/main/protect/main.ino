#include <Bridge.h>
#include <HttpClient.h>
#include <FileIO.h>
#include<Process.h>
#include<DHT.h>
#include"string.h"
#include"Prototype.h"

//**********DHT22 Parameters**********
#define dhtpin 8
#define dhttype DHT22
DHT dht( dhtpin, dhttype );
//************************************
//**********Time Parameters***********
int Date = 0, minutes = 0;
//************************************
//**********File Parameters***********
//const char *proto_file_path = "/mnt/sda1/";
const char  *file_path = "/mnt/sda1/Datalog.txt";
//************************************

void setup() {
  // Initialize Objects
  Bridge.begin();
  Serial.begin(9600);
  FileSystem.begin();
  dht.begin();

  SerialUSB.println("System start\nPlease check WI-FI parameters and if terminal online!");
  /*file_path = proto_file_path;
  strcat(file_path, GetDateFileName());
  WriteStartInfo();*/
  Serial.println(file_path);
}


void loop() {
  String dataString = TimeStampAndGetMinutes();
  static int min_rec = minutes;
  static int date_rec = Date;

  //Serial.println(minutes);
  if (minutes == min_rec) //minutes%5 == 0&& seconds==0
  {
    min_rec = (minutes >= 55 ? minutes - 55 : minutes + 5);

    //char file_path[] = "/mnt/sda1/Datalog.txt";
    String Humi, Temp;

    dataString += " = ";
    // read three sensors and append to the string:
    Humi = dht.readHumidity();
    Temp = dht.readTemperature();

    //Call HTTPGet funtion
    postToThinspeak(Temp, Humi);

    dataString += DHTstrForSD(Temp, Humi);
    WriteData(dataString);
  }

  /*if (Date != date_rec)
  {
    file_path = proto_file_path;
    strcat(file_path, GetDateFileName());
    WriteStartInfo();
  }*/
}
