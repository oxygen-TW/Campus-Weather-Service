
void WriteData(String data)
{
  //char file_path[] = "/mnt/sda1/Datalog.txt";
  File dataFile = FileSystem.open(file_path, FILE_APPEND);

  // if the file is available, write to it:
  if (dataFile) {
    dataFile.println(data);
    Serial.println(data);
    delay(1000);
  }
  // if the file isn't open, pop up an error:
  else {
    Serial.println("error opening datalog.txt");
    delay(500);
  }
}

void WriteStartInfo()
{
  String StartInfo = "Date\t Time\t\tHumidity\t    Temprature\t\tUV index";
  WriteData(StartInfo);
}

