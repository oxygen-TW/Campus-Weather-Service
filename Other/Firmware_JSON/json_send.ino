//General Firmware
String MakeJson(double obj1,double obj2,double obj3,double obj4)
{
  String JsonStr("{");

  JsonStr+="\"type\":\"General\", ";
  JsonStr+="\"Temp\":"+ DtoS(obj1) +", ";
  JsonStr+="\"Humi\":"+DtoS(obj2)+", ";
  JsonStr+="\"light\":"+DtoS(obj3)+", ";
  JsonStr+="\"UV\":"+DtoS(obj4);
  JsonStr+="}";
  return JsonStr;
}

String DtoS(double num)
{
  char x[10]={""};
  dtostrf(num,5,2,x);
  String objstr(x);
  return objstr;
} 

void setup()
{
  Serial.begin(9600);
  //Serial.println("Start");
}

void loop()
{
  char resv='\0';
  double Temp = 10.1;
  double Humi = 20.87;
  double light = 30.78;
  double UV = 40.54;
  
  if(Serial.available())
    resv = Serial.read();
      
  if(resv == 'D')
    Serial.println(MakeJson(Temp,Humi,light,UV));
    //Serial.println(DtoS(Temp));
}
