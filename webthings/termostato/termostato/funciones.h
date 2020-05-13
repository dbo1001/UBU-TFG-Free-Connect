/* aquí puedes añadir las funciones que tu código necesite*/
//deberas llamarlas desde loop o setup

void leer(){
  float grados=analogRead(termistor);
  Serial.println(grados);
  grados=grados/2048;
  grados=grados*3300;
  Serial.println(grados);
  Serial.println("..........");
  ThingPropertyValue value;
  value.number = 22;
  Temperatura.setValue(value);
}
