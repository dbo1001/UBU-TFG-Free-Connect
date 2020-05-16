/* aquí puedes añadir las funciones que tu código necesite*/
//deberas llamarlas desde loop o setup
void actualizarDatos();
void leer(){
  tMedida=22.5;
  actualizarDatos();
}

void actualizarDatos(){
  if(verboseOn){
    Serial.println(tMedida);
  }
  ThingPropertyValue value;
  value.number = tMedida;
  Temperatura.setValue(value);
  char tempMed[4];
  char tempObj[4];
  dtostrf(tMedida,4,1,tempMed);
  dtostrf(tObjetivo,4,1,tempObj);
  display.setTextAlignment(TEXT_ALIGN_LEFT);
  display.setFont(ArialMT_Plain_10);
  display.drawString(0, 0, tempMed);
  display.drawString(50, 0,"/");
  display.drawString(100, 0, tempObj);
  if(calentar){
    display.drawString(0, 30, "encendido");    
  } else{
    display.drawString(0, 30, "prupru");    
  }
  display.display();
}
