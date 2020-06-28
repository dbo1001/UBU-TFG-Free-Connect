/* place here any additional functions to use in your code*/
//they should be called from loop or setup


int readSensor(){
  int  readings[times];
  digitalWrite(activateSensor,HIGH);
  for(int i=0;i<times;i++){
    readings[i]=analogRead(humSensor);
    delay(10);
  }
  digitalWrite(activateSensor,LOW);
  QuickSort<int>::SortAscending(readings, 0, times-1);
  int avg=0;
  int count=0;
  for(int i =10;i<times-10;i++){//discard the 10 highest and lowest readings and average the rest
    avg+=readings[i];
    count++;
  }
  ThingPropertyValue value;
  int calculatedValue=map(avg/count, 0, 4096, 0, 100);
  value.number = calculatedValue;
  Humidity.setValue(value);
  if(verboseOn)Serial.println(calculatedValue);
  return calculatedValue;
}

boolean water(){
  return readSensor()>limWater;
}
