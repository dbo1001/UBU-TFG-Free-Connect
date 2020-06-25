#include "WebThingAdapter.h"//webthings main library
#include "ArduinoOTA.h" // OTA functionality

#include "SSD1306Wire.h"//oled display library
#include "DHTesp.h"//temp and humidity sensor

//it's important that this two are the last ones to be called. That way we ensure we can use in them any function from the ones above
#include "config.h"
#include "functions.h"


void setup(void) {   
  Serial.begin(115200);
  //wifi Setup
  if(verboseOn){
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
  
  //webthings setup
  adapter = new WebThingAdapter(deviceName, WiFi.localIP());
  Thermostat.addProperty(&Temperature);
    
  Thermostat.addProperty(&TemperatureObj);
  adapter->addDevice(&Thermostat);
  adapter->begin();
  lastTemp=TemperatureObj.getValue().number;//get the set temperature
  
  //OLED settings  
  display.init();

  //sensor settings
  dht.setup(dhtPin, DHTesp::DHT22);
  
  //buttons settings
  touchAttachInterrupt(minusButton, decrementObjective, 20);
  touchAttachInterrupt(plusButton, incrementObjective, 20);
  
  //
  pinMode(heater, OUTPUT);
  digitalWrite(heater, LOW);
  pinMode(led, OUTPUT);
  digitalWrite(led, HIGH);
  t=millis();
}

void loop(void) {
  ArduinoOTA.handle();
  //Moved adapter->update() function to one of the custom functions for better control on the sync
  if(millis()>t+tRefresh){//refreshing function
    readSensor();
    updateData();
    t=millis();
  }
  if(tObjetive>tRead){//check if heating is needed
    if(!heat&&millis()>tChange+tMinOff){
      digitalWrite(heater, HIGH);
       digitalWrite(led, LOW);
      heat=true;  
      updateData();
      tChange=millis();
    }
  }else{
    if(heat&&millis()>tChange+tMinOn){
      digitalWrite(heater, LOW);
      digitalWrite(led, HIGH);
      heat=false; 
      updateData();
      tChange=millis();
    }
  }
  if(addT){//plus button press
    tObjetive+=0.5;
    addT=false;
    updateData();
  }
  if(substractT){//minus button press
    tObjetive-=0.5;
    substractT=false;
    updateData();
  }
}
