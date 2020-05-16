//#include "Arduino.h"
//#include "Thing.h"
#include "WebThingAdapter.h"
#include "ArduinoOTA.h"
#include "utlgbotlib.h"
#include "config.h"
#include "funciones.h"
//#include "SSD1306Wire.h" 


void setup(void) {   
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
  adapter = new WebThingAdapter("Termostato", WiFi.localIP());
  Termostato.addProperty(&Temperatura);
  adapter->addDevice(&Termostato);
  adapter->begin();

  //
  Bot.set_debug(debugLevelBot);
  Bot.getMe();
  t=millis();

  //
  display.init();
  
}

void loop(void) {
  ArduinoOTA.handle();
  adapter->update();
  if(millis()>t+5000){
    leer();
    t=millis();
  }
  if(tObjetivo>tMedida){
    calentar=true;
  }else{
    calentar=false;
  }
}
