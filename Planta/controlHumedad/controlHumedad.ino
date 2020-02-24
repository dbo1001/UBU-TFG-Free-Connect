
#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h>
#include "QuickSortLib.h"
#include <ESPmDNS.h>
#include <WiFiUdp.h>
#include <ArduinoOTA.h>

// Initialize Wifi connection to the router
const char ssid[] = "delgado";     // your network SSID (name)
const char password[] = "micasa221b"; // your network key
const int Shumedad = 33;
const int activarH = 18;

boolean sonado = false;

boolean verboseOn = false;
boolean banderaRegar=false;
int limRegar=3700;
const int autoComp=3600000; //1h

const String miId="191552774";

// Initialize Telegram BOT
#define BOTtoken "914632211:AAG1Oe1_9EkHIOqVMQnuoV0X_oWsRoA9FR8"  // your Bot Token (Get from Botfather)

WiFiClientSecure client;
UniversalTelegramBot bot(BOTtoken, client);

const int Bot_mtbs = 1000; //mean time between scan messages
long Bot_lasttime=0;   //last time messages' scan has been done
long tComprobacion=-autoComp;

void setup() {
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

  // Port defaults to 3232
  // ArduinoOTA.setPort(3232);

  // Hostname defaults to esp3232-[MAC]
   ArduinoOTA.setHostname("agni");

  // No authentication by default
   ArduinoOTA.setPassword("221b");

  // Password can be set with it's md5 value as well
  // MD5(admin) = 21232f297a57a5a743894a0e4a801fc3
  // ArduinoOTA.setPasswordHash("21232f297a57a5a743894a0e4a801fc3");
  ArduinoOTA.onStart([]() {
      String type;
      if (ArduinoOTA.getCommand() == U_FLASH)
        type = "sketch";
      else // U_SPIFFS
        type = "filesystem";

      // NOTE: if updating SPIFFS this would be the place to unmount SPIFFS using SPIFFS.end()
      if(verboseOn)Serial.println("Start updating " + type);
    })
    .onEnd([]() {
      if(verboseOn)Serial.println("\nEnd");
    })
    .onProgress([](unsigned int progress, unsigned int total) {
      if(verboseOn)Serial.printf("Progress: %u%%\r", (progress / (total / 100)));
    })
    .onError([](ota_error_t error) {
      if(verboseOn){
        Serial.printf("Error[%u]: ", error);
        if (error == OTA_AUTH_ERROR) Serial.println("Auth Failed");
        else if (error == OTA_BEGIN_ERROR) Serial.println("Begin Failed");
        else if (error == OTA_CONNECT_ERROR) Serial.println("Connect Failed");
        else if (error == OTA_RECEIVE_ERROR) Serial.println("Receive Failed");
        else if (error == OTA_END_ERROR) Serial.println("End Failed");
      }
    });

  ArduinoOTA.begin();
  
  pinMode(Shumedad,INPUT);
  pinMode(activarH,OUTPUT);
  if(verboseOn){
    Serial.println("");
    Serial.println("WiFi connected");
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());
  }
   
   
  //bot.sendMessage(miId, "Iniciado", "");
}

void loop() {
  if (millis() > Bot_lasttime + Bot_mtbs)  {
    menuMensaje();
  }
  if (millis()> tComprobacion + autoComp){
    if(verboseOn)bot.sendMessage(miId, String(leer()), "");
    if(regar()){
      if(!sonado)bot.sendMessage(miId, "NECESITO AGUAAA", "");
      sonado=true;
    }
    tComprobacion=millis();
  }
  ArduinoOTA.handle();
}

int leer(){
  int siz=50;
  int  lectura[siz];
  digitalWrite(activarH,HIGH);
  delay(500);
  for(int i=0;i<siz;i++){
    lectura[i]=analogRead(Shumedad);
    if(verboseOn)Serial.print(lectura[i]);
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
  return media/conta;
}

void menuMensaje(){
  String mensaje;
  boolean reiniciar = false;
  int numNewMessages = bot.getUpdates(bot.last_message_received + 1);
    while(numNewMessages) {
      if(verboseOn)Serial.println("got response");
      for (int i=0; i<numNewMessages; i++) { 
        mensaje=bot.messages[i].text;
        if(mensaje=="/estado"){
          bot.sendMessage(miId, String(leer()), "");
        }else{
          if(mensaje=="/reset"){
            reiniciar=true;
          }else{
            bot.sendMessage(miId, "No se reconoce el comando, texto:", "");
            bot.sendMessage(miId,mensaje , "");
         }
       }
      numNewMessages = bot.getUpdates(bot.last_message_received + 1);
      }
    }
    Bot_lasttime = millis();
    if(reiniciar)ESP.restart();
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
