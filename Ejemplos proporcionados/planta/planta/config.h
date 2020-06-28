//wifi credentials. They sould match your network's
const char *ssid = "wifi";
const char *password = "pass";

//OTA credentials. we define those here
const char nombreOTA[]= "planta";
const char passOTA[]= "admin";

 /**
   * Global variables for your code
   * this is the place to add the global variables you will use later
   * you should add pin definitions aswell as any other variable
   * 
   */
const int humSensor = 33;//location of sensor reading pin
const int activateSensor = 18;//location of activation signal

boolean notified = false;//to not notify multiple times

int limWater=80;//threshold to notify the need of watering (0-100)
const int times=50;//numer of measurements to average

const int autoComp=3600000; //1h checking time interval
long tCheck=-autoComp;//last checked time. Initializes to always chack on startup

//enables/disables debug messages. Should be turned off for the final deployment.
//adding your own messages is as easy as including: if(verboseOn)Serial.print("My debug message");
boolean verboseOn = false;

//parameters for the connection with the main module. Please check the manual for a complete reference on these
const char deviceName[] ="girasol";
WebThingAdapter *adapter;//main objet we will use
const char *capacidades[] = {"MultiLevelSensor", nullptr};//list of functionality categories
ThingDevice Sensor("humedad1", "girasol", capacidades);//one device on our project
ThingProperty Humidity("Humidity", "Lectura del sensor", NUMBER, "LevelProperty");//define each property of the device
