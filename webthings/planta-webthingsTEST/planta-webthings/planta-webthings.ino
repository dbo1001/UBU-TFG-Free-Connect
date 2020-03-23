#include "Arduino.h"
#include "Thing.h"
#include "WebThingAdapter.h"
#include "QuickSortLib.h"

const char *ssid = "delgado";
const char *password = "micasa221b";

const int ledPin = 2;
const int shumedad = 33;
const int activarH = 18;

boolean sonado = false;

boolean verboseOn = true;
boolean banderaRegar=false;
int limRegar=3700;
const int autoComp=10000; //1h
long tComprobacion=-autoComp;
WebThingAdapter *adapter;

const char *capacidades[] = {"MultiLevelSensor", nullptr};
ThingDevice Sensor("humedad1", "girasol", capacidades);
ThingProperty Humedad("Humedad", "Lectura del sensor", NUMBER, "LevelProperty");
ThingEvent Regar("regar","Es necesario regar",BOOLEAN, "AlarmEvent");

void setup(void) {
  pinMode(ledPin, OUTPUT);
  Serial.begin(115200);
  if(verboseOn){
    Serial.begin(115200);
  
    // Attempt to connect to Wifi network:
    Serial.print("Connecting Wifi: ");
    Serial.println(ssid);
  }
  // Set WiFi to station mode and disconnect from an AP if it was Previously
  // connected
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    if(verboseOn)Serial.print(".");
    delay(500);
  }
  pinMode(shumedad,INPUT);
  pinMode(activarH,OUTPUT);
  if(verboseOn){
    Serial.println("");
    Serial.println("WiFi connected");
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());
  }
  
  adapter = new WebThingAdapter("Girasol", WiFi.localIP());
  Sensor.addProperty(&Humedad);
  Sensor.addEvent(&Regar);
  adapter->addDevice(&Sensor);
  adapter->begin();
}

void loop(void) {
  if (millis()> tComprobacion + autoComp){
    if(regar()){
      if(!sonado){
        ThingDataValue val;
        val.boolean = true;
        if(verboseOn)Serial.println("evento regar");
        ThingEventObject *ev = new ThingEventObject("regar", BOOLEAN, val);
        Sensor.queueEventObject(ev);
      }
      sonado=true;
    }
    tComprobacion=millis();
  }
  adapter->update();
}

int leer(){
  int siz=50;
  int  lectura[siz];
  digitalWrite(activarH,HIGH);
  delay(500);
  for(int i=0;i<siz;i++){
    lectura[i]=analogRead(shumedad);
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
