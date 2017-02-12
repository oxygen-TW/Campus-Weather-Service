/*
  SD card datalogger

 This example shows how to log data from three analog sensors
 to an SD card mounted on the YunShield/Yún using the Bridge library.

 The circuit:
 * analog sensors on analog pins 0, 1 and 2
 * SD card attached to SD card slot of the YunShield/Yún

 Prepare your SD card creating an empty folder in the SD root
 named "arduino". This will ensure that the Yún will create a link
 to the SD to the "/mnt/sd" path.

 You can remove the SD card while the Linux and the
 sketch are running but be careful not to remove it while
 the system is writing to it.

 created  24 Nov 2010
 modified 9 Apr 2012
 by Tom Igoe
 adapted to the Yún Bridge library 20 Jun 2013
 by Federico Vanzati
 modified  21 Jun 2013
 by Tom Igoe

 This example code is in the public domain.

 http://www.arduino.cc/en/Tutorial/YunDatalogger

 */

#include <FileIO.h>
#include<DHT.h>

#define dhtpin 8
#define dhttype DHT11
#define delayTime 30000
DHT dht11( dhtpin, dhttype );
uint8_t dhtbuf[2];
String getTimeStamp();
void setup() {
  // Initialize the Bridge and the Serial
  Bridge.begin();
  Serial.begin(9600);
  FileSystem.begin();

  while (!SerialUSB); // wait for Serial port to connect.
  SerialUSB.println("Filesystem datalogger\n");
}


void loop() {
  // make a string that start with a timestamp for assembling the data to log:
  String dataString;
  char buf[3];
  char file_path[22]="/mnt/sda1/datalog.txt";
  String HH, TT;
  dataString += getTimeStamp();
  dataString += " = ";

  // read three sensors and append to the string:
  dhtbuf[0] = dht11.readHumidity();
  dhtbuf[1] = dht11.readTemperature();

    buf[0] = 0x30 + dhtbuf[1] / 10;
    buf[1] = 0x30 + dhtbuf[1] % 10;
    TT = (String(buf)).substring( 0, 2 );
    buf[0] = 0x30 + dhtbuf[0] / 10;
    buf[1] = 0x30 + dhtbuf[0] % 10;
    HH = (String(buf)).substring( 0, 2 );
  // open the file. note that only one file can be open at a time,
  // so you have to close this one before opening another.
  // The FileSystem card is mounted at the following "/mnt/FileSystema1"
  File dataFile = FileSystem.open(file_path, FILE_APPEND);

  // if the file is available, write to it:
  if (dataFile) {
    if ( isnan(dhtbuf[0]) || isnan(dhtbuf[1]) )
  {
    dataFile.println( "Failed to read form DHT11" );
  }
  else
  {
    dataString+="Humidity: ";
    dataString+=HH;
    dataString+="\tTemperature: ";
    dataString+=TT;
    dataFile.println(dataString);
  }
    // print to the serial port too:
    SerialUSB.println(dataString);
  }
  // if the file isn't open, pop up an error:
  else {
    SerialUSB.println("error opening datalog.txt");
  }
  delay(delayTime);
}

// This function return a string with the time stamp
String getTimeStamp() {
  String result;
  Process time;
  // date is a command line utility to get the date and the time
  // in different formats depending on the additional parameter
  time.begin("date");
  time.addParameter("+%D-%T");  // parameters: D for the complete date mm/dd/yy
  //             T for the time hh:mm:ss
  time.run();  // run the command

  // read the output of the command
  while (time.available() > 0) {
    char c = time.read();
    if (c != '\n') {
      result += c;
    }
  }

  return result;
}
