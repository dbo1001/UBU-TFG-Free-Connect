/* aquí puedes añadir las funciones que tu código necesite*/
//deberas llamarlas desde loop o setup


int leer(){
  int siz=50;
  int  lectura[siz];
  digitalWrite(activarH,HIGH);
  delay(500);
  for(int i=0;i<siz;i++){
    //lectura[i]=analogRead(shumedad);
    lectura[i]=3100;
    delay(10);
  }
  digitalWrite(activarH,LOW);
  QuickSort<int>::SortAscending(lectura, 0, siz-1);
  int media=0;
  int conta=0;
  for(int i =10;i<siz-10;i++){
    media+=lectura[i];
    conta++;
  }
  ThingPropertyValue value;
  value.number = media/conta;
  Humedad.setValue(value);
  if(verboseOn)Serial.println(media/conta);
  return media/conta;
}

boolean regar(){
  if(leer()>limRegar){
    if(banderaRegar){
      banderaRegar=false;
      return true;  
    }
    banderaRegar=true;
  }
  return false;
}
