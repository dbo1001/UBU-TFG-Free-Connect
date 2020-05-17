/* aquí puedes añadir las funciones que tu código necesite*/
//deberas llamarlas desde loop o setup
void actualizarDatos();

void leer(){
  tMedida=dht.getTemperature();
  humedad=dht.getHumidity();
}

void actualizarDatos(){

  char tempMed[5];
  char tempObj[5];
  dtostrf(tMedida,2,1,tempMed);
  dtostrf(tObjetivo,2,1,tempObj);

  display.setTextAlignment(TEXT_ALIGN_LEFT);
  display.setFont(ArialMT_Plain_24);
  display.clear();
  if(verboseOn){
    Serial.println("...");
    Serial.println(tempMed);
    Serial.println(tempObj);
    Serial.println(tMedida);
    Serial.println(tObjetivo);
  }
  display.drawString(0, 0, tempMed);
  //display.drawString(0, 0, "22.0");
  display.drawString(50, 0,"/");
  display.drawString(70, 0, tempObj);
  //display.drawString(65, 0, "23.5");
  if(calentar){
    display.drawString(0, 30, "on");    
  } else{
    display.drawString(0, 30, "off");  
  }

  char hume[4];
  dtostrf(humedad,2,0,hume);
  display.drawString(60, 30, hume);
  display.drawString(85, 30, "%");
  /*
  int calidad=dht.getComfortRatio(tMedida,humedad,false);
  switch (calidad){
    case 0:
      display.drawString(40, 30, "ok");
      break;
    case 1:
      display.drawString(40, 30, "calor");
      break; 
    case 2:
      display.drawString(40, 30, "frio");
      break;      
    case 3:
      display.drawString(40, 30, "seco");
      break;
    case 4:
      display.drawString(40, 30, "humedo");
      break;  
    case 5:
      display.drawString(40, 30, "calorSec");
      break;  
    case 6:
      display.drawString(40, 30, "frioSec");
      break;
    case 8:
      display.drawString(40, 30, "humedo");
      break;
    case 9:
      display.drawString(40, 30, "calorHum");
      break;  
    case 10:
      display.drawString(40, 30, "frioHum");
      break;  
  }
  */
  display.display();
  adapter->update();
  tObjetivo=TemperaturaObj.getValue().number;
  ThingPropertyValue tempProp;
  ThingPropertyValue humProp;
  tempProp.number = tMedida;
  humProp.number = humedad;
  Temperatura.setValue(tempProp);
  //Humedad.setValue(humProp);
  adapter->update();
}
