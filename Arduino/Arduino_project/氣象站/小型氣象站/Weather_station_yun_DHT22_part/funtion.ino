bool DHTchk(float h,float t,float f)
{
  if (isnan(h) || isnan(t) || isnan(f)) 
    return false;
  else
    return true;
}

void DHTprint(float h,float t,float f)
{
  Serial.print("Humidity: ");
  Serial.print(h);
  Serial.print(" %\t");
  Serial.print("Temperature: ");
  Serial.print(t);
  Serial.print(" *C ");
  Serial.print(f);
  Serial.print(" *F\t");
  Serial.println("By DHT22");
}
