/* place here any additional functions to use in your code*/
//they should be called from loop or setup

void alerta(){
  if(detectionCount==0){
    t=millis();
  }
  if(!triggered){
    detectionCount++;
  }
}

void triggerAlarm(){
  triggered=true;
  tTriggered=millis();
  ThingPropertyValue value;
  value.boolean = true;
  Detectado.setValue(value);
  ThingEventObject *ev = new ThingEventObject("DeteccionEvento", BOOLEAN, value);
  Sensor.queueEventObject(ev);
  digitalWrite(led,HIGH);
}


void sendMessagege(){
  tLastMessage=millis();
  for (int i=0; i<numChats; i++) {
       Bot.sendMessage(chatIDs[i], "Intrusion detected");
  }
}
