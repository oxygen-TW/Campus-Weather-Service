/********************************************/
/*********************************************
 * *******************************************
 * ********Declare Function Prototype*********
 * *******************************************
 * *******************************************
 ********************************************/

//*****DHT22System.ino***********************
String DHTstrForSD(String ,String);

//*****FileSystem.ino************************
void WriteData(String);
void WriteStartInfo();
String GetFileName(String);

//*****HttpSystem.ino************************
void postToThinspeak(String , String , String);

//*****TimeSystem****************************
String TimeStampAndGetMinutes();

//*****UVSystem******************************
String UVstrForSD(String);
