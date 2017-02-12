// This function return a string with the time stamp
String TimeStampAndGetMinutes() {
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
  minutes = (result.substring(12, 14)).toInt();
  //minutes = (10 * (result[12] - 48) + (result[13] - 48)); // Fix Ascii
  Date = (result.substring(3, 5)).toInt();
  //Serial.println(tmp);

  return result;
}


