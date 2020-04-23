#include "Arduino.h"
#include "Thing.h"
#include "WebThingAdapter.h"
#include "QuickSortLib.h"
#include "ArduinoOTA.h"
#include "WiFiClientSecure.h"
#include "UniversalTelegramBot.h"
#include "config.h"
#include "funciones.h"

WebThingAdapter *adapter;

WiFiClientSecure client;
UniversalTelegramBot Bot(bOTtoken, client);


void setup(void) {
  pinMode(ledPin, OUTPUT);
  Serial.begin(115200);
  if(verboseOn){
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
  //
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



  //
  adapter = new WebThingAdapter("Girasol", WiFi.localIP());
  Sensor.addProperty(&Humedad);
  Sensor.addEvent(&Regar);
  Sensor.addEvent(&Overheated);
  adapter->addDevice(&Sensor);
  adapter->begin();

  //
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
        for (int i=0; i<numChats; i++) {
          Bot.sendMessage(chatID[i], "necesario regar","");
        }
      }
      sonado=true;
    }
    tComprobacion=millis();
  }
  adapter->update();
}
