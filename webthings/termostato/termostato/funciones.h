/* aquí puedes añadir las funciones que tu código necesite*/
//deberas llamarlas desde loop o setup
void actualizarDatos();

void leer(){
  
  
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
  display.drawString(65, 0, tempObj);
  //display.drawString(65, 0, "23.5");
  if(calentar){
    display.drawString(0, 30, "calentando");    
  } else{
    display.drawString(0, 30, "parado");    
  }
  display.display();
  ThingPropertyValue value;
  value.number = tMedida;
  Temperatura.setValue(value);
  adapter->update();
}
