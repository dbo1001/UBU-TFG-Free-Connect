#include "Arduino.h"
#include "Thing.h"
#include "WebThingAdapter.h"
#include "QuickSortLib.h"
#include <ArduinoOTA.h>

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

const char nombreOTA[]= "esp32pruebas";
const char passOTA[]= "admin";
const char *capacidades[] = {"MultiLevelSensor", nullptr};
ThingDevice Sensor("humedad1", "girasol", capacidades);
ThingProperty Humedad("Humedad", "Lectura del sensor", NUMBER, "LevelProperty");
ThingEvent Regar("regar","Es necesario regar",BOOLEAN, "AlarmEvent");
ThingEvent Overheated("overheated","The lamp has exceeded its safe operating temperature",NUMBER, "OverheatedEvent");

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
  ArduinoOTA.setHostname(nombreOTA);
  ArduinoOTA.setPassword(passOTA);
  ArduinoOTA.onStart([]() {
      String type;
      if (ArduinoOTA.getCommand() == U_FLASH)
        type = "sketch";
      else // U_SPIFFS
        type = "filesystem";
      Serial.println("Start updating " + type);
    }).onEnd([]() {
      Serial.println("\nEnd");
    }).onProgress([](unsigned int progress, unsigned int total) {
      Serial.printf("Progress: %u%%\r", (progress / (total / 100)));
    }).onError([](ota_error_t error) {
      Serial.printf("Error[%u]: ", error);
      if (error == OTA_AUTH_ERROR) Serial.println("Auth Failed");
      else if (error == OTA_BEGIN_ERROR) Serial.println("Begin Failed");
      else if (error == OTA_CONNECT_ERROR) Serial.println("Connect Failed");
      else if (error == OTA_RECEIVE_ERROR) Serial.println("Receive Failed");
      else if (error == OTA_END_ERROR) Serial.println("End Failed");
    });
  ArduinoOTA.begin();
  
  adapter = new WebThingAdapter("Girasol", WiFi.localIP());
  Sensor.addProperty(&Humedad);
  Sensor.addEvent(&Regar);
  Sensor.addEvent(&Overheated);
  adapter->addDevice(&Sensor);
  adapter->begin();
}

void loop(void) {
  ArduinoOTA.handle();
  if (millis()> tComprobacion + autoComp){
    if(regar()){
      if(!sonado){
        //ThingDataValue val;
        //val.boolean = true;
        if(verboseOn)Serial.println("evento regar");
        //ThingEventObject *ev = new ThingEventObject("Regar", BOOLEAN, val);
        //Sensor.queueEventObject(ev);
        ThingDataValue val;
        val.number = 102;
        ThingEventObject *ev = new ThingEventObject("overheated", NUMBER, val);
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
    //lectura[i]=analogRead(shumedad);
    lectura[i]=3800;
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
