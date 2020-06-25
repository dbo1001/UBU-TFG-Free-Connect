/* aquí puedes añadir las funciones que tu código necesite*/
//deberas llamarlas desde loop o setup
void actualizarDatos();



void readSensor(){
  tRead=dht.getTemperature();
  humedad=dht.getHumidity();
}

void updateData(){
  char tempRead[5];//values in string format for display
  char tempObj[5];
  dtostrf(tRead,2,1,tempRead);
  dtostrf(tObjetive,2,1,tempObj);
  display.setTextAlignment(TEXT_ALIGN_LEFT);//oled settigns
  display.setFont(ArialMT_Plain_24);
  display.clear();
  if(verboseOn){
    Serial.println("...");
    Serial.println(tempObj);
  }
  display.drawString(0, 0, tempRead);
  display.drawString(47, 0,"/");
  display.drawString(55, 0, tempObj);
  display.drawString(103, 0, "ºC");
  if(heat){
    display.drawString(0, 30, "on");    
  } else{
    display.drawString(0, 30, "off");  
  }
  char hume[4];//value in string format for display
  dtostrf(humedad,2,0,hume);
  display.drawString(60, 30, hume);
  display.drawString(85, 30, "%");
 
  display.display();//refresh the screen values
  adapter->update();//refresh the values on webthings
  float tObjNod=TemperatureObj.getValue().number;
  if (tObjetive!=tObjNod){//determines if the user changed the desired temperature on the interface
    if(tObjNod!=lastTemp){
        lastTemp=tObjNod;
        tObjetive=tObjNod;
    }else{
      ThingPropertyValue newTempObj;
      newTempObj.number=tObjetive;
      TemperatureObj.setValue(newTempObj);
    }
  }
  ThingPropertyValue tempProp;
  tempProp.number = tRead;
  Temperature.setValue(tempProp);
  adapter->update();
}

void incrementObjective(){
  addT=true;
}

void decrementObjective(){
  substractT=true;
}
