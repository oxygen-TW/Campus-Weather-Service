String DHTstrForSD(String Temp,String Humi)
{
  String dataString="";
  dataString += "Humidity: ";
  dataString += Humi;
  dataString += "\tTemperature: ";
  dataString += Temp;

  return dataString;
}

