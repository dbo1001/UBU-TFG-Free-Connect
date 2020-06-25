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


//enables/disables debug messages. Should be turned off for the final deployment.
//adding your own messages is as easy as including: if(verboseOn)Serial.print("My debug message");
boolean verboseOn = false;

//parameters for the connection with the main module. Please check the manual for a complete reference on these
const char deviceName[] ="termostato";
WebThingAdapter *adapter;//main objet we will use
const char *capabilities[] = {"Thermostat",nullptr};//list of functionality categories
ThingDevice Thermostat("termostato", "termostato", capabilities);//one device on our project
ThingProperty Temperature("Temperature", "Lectura del sensor", NUMBER, "TemperatureProperty");//define property 1 of the device
ThingProperty TemperatureObj("TemperatureObj", "Temepratura objetivo", NUMBER, "TargetTemperatureProperty");//define property 2 of the device



//screen parameters
const int sdaOled=5;
const int sclOled=4;
SSD1306Wire display(0x3c, sdaOled, sclOled);

//sensor setup
DHTesp dht;
