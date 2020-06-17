//wifi credentials. They sould match your network's
const char *ssid = "delgado";
const char *password = "micasa221b";

//OTA credentials. we define those here
const char nombreOTA[]= "termostato";
const char passOTA[]= "admin";

 /**
   * Global variables for your code
   * this is the place to add the global variables you will use later
   * you should add pin definitions aswell as any other variable
   * 
   */
const int heater =17  ;//pin definitions for heater and status led
const int led =16  ;
const int plusButton=15;//and for the buttons
const int minusButton=13;
const int dhtPin = 18; //sensor location

long t;//to keep track of time
long tChange=0;//instant the state changed (turn off or on)
const long tRefresh=5000; //update refresh rate
const long tMinOn= 5000; //minumun on time
const long tMinOff = 10000; //minumun off time
float tObjetive=0.0f; //desired temperature
float tRead=0.0f; //sensor read
float humedad=0.0f; 
boolean heat=false; //to control if the heater is on or off
float lastTemp=0; //last temperature recorded on webthings

bool addT=false;//flags for the interrupts associated with the buttons
bool substractT=false;


//habilita o deshabilita los mensajes de depuracion
boolean verboseOn = false;

//configuración de los parametros para el display en el nodo central
WebThingAdapter *adapter;
const char *capacidades[] = {"Thermostat",nullptr};//lista de parametros que tiene el sensor, debe acabar en nullptr
ThingDevice Thermostat("termostato", "termostato", capacidades);//objeto dispositivo Nombre("","nombre en display",capacidades)
ThingProperty Temperature("Temperature", "Lectura del sensor", NUMBER, "TemperatureProperty");//propiedad 1 del dispositivo
ThingProperty TemperatureObj("TemperatureObj", "Temepratura objetivo", NUMBER, "TargetTemperatureProperty");//propiedad 2 del dispositivo
ThingProperty Humedad("Humedad", "Lectura del sensor", NUMBER, "LevelProperty");


//configuracion de la pantalla integrada
const int sdaOled=5;
const int sclOled=4;
SSD1306Wire display(0x3c, sdaOled, sclOled);

//configuracion del sensor
DHTesp dht;
