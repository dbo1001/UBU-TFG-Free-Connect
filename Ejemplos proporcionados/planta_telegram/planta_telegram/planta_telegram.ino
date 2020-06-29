/**
 * Code 3/3 for example "plant water lever monitor" Adds telegram notifications
 * Complete information can be found at projects website.
 * Author: Daniel Delgado Santamaría
 * Project: https://freeconnectproject.com
 * License is GPL 3.0
 * 
 */
#include "WebThingAdapter.h"//webthings main library
#include "ArduinoOTA.h" // OTA functionality
#include "utlgbotlib.h" // telegram bot library

#include "QuickSortLib.h"//library for sorting operations

//it's important that this two are the last ones to be called. That way we ensure we can use in them any function from the ones above
#include "config.h"
#include "functions.h"



void setup(void) {
  Serial.begin(115200);
  
  //wifi Setup
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
  
  //OTA setup
  ArduinoOTA.setHostname(nombreOTA);
  ArduinoOTA.setPassword(passOTA);
  ArduinoOTA.onStart([]() {
      String type;
      if (ArduinoOTA.getCommand() == U_FLASH)
        type = "sketch";
      else 
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

  //webthings setup
  adapter = new WebThingAdapter(deviceName, WiFi.localIP());
  Sensor.addProperty(&Humidity);
  Sensor.addEvent(&NeedWater);
  adapter->addDevice(&Sensor);
  adapter->begin();
  Humidity.unit= "percent";

  //telegram bot settings
  Bot.set_debug(debugLevelBot);
  Bot.getMe();
  
/**
   * Add here any pinMode definitions
   * all parameters are taken from config.h file. Any changes should be made there
   * 
   */
 /**
   * If you wish to execute any code during setup
   * you shuold place the code in a function inside functions.h and call it here
   * 
   */
  pinMode(humSensor,INPUT);
  pinMode(activateSensor,OUTPUT);
}

void loop(void) {
  /**
   * Add here any calls to your own functions
   * it's very important to keep cumputing times as low as possible to mantain the systems vivacity
   * for timing control use the millis() method instead of delays
   * 
   */
  ArduinoOTA.handle();
  if (millis()> tCheck + autoComp){
    if(water()){//reads the sensor and checks if the level is below threshold
      if(!notified){
        if(verboseOn)Serial.println("Watering needed");
        ThingPropertyValue value;
        value.boolean = true;
        ThingEventObject *ev = new ThingEventObject("NeedWater", BOOLEAN, value);
        Sensor.queueEventObject(ev);
        for (int i=0; i<numChats; i++) {
          Bot.sendMessage(chatIDs[i], "Water the plant");
        }
      }
      notified=true;
    }else{
      notified=false;
    }
    tCheck=millis();
  }
  adapter->update();
}
