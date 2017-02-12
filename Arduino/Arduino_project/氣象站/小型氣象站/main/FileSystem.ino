
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
  }
  dataFile.close();
}

void WriteStartInfo()
{
  String StartInfo = "Date\t Time\t\tHumidity\t    Temprature\t\tUV index";
  WriteData(StartInfo);
}

String GetFileName(String Time)
{
  return proto_file_path + Time.substring(6, 8) + Time.substring(0, 2) + Time.substring(3, 5) + ".txt";
}

