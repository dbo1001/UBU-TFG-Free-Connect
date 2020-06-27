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
  digitalWrite(led,HIGH);
  digitalWrite(siren,HIGH);
  ThingPropertyValue value;
  value.boolean = true;
  Detected.setValue(value);
  ThingEventObject *ev = new ThingEventObject("DetectionEvent", BOOLEAN, value);
  Sensor.queueEventObject(ev);
}

void untriggerAlarm(){
   triggered=false;
   detectionCount=0;
   digitalWrite(led,LOW);
   digitalWrite(siren,LOW);
   if(Detected.getValue().boolean==true){
    ThingPropertyValue value;
    value.boolean = false;
    Detected.setValue(value);
   }
}

void sendMessagege(){
  tLastMessage=millis();
  for (int i=0; i<numChats; i++) {
       Bot.sendMessage(chatIDs[i], "Intrusion detected");
  }
}

boolean checkStatus(){
  adapter->update();
  return Active.getValue().boolean;
}
