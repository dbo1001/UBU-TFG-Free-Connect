//wifi credentials. They sould match your network's
const char *ssid = "delgado";
const char *password = "micasa221b";

//OTA credentials. we define those here
const char nombreOTA[]= "esp32pruebas";
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
boolean waterFlag=false;//to keep track if watering is needed

int limWater=80;//threshold to notify the need of watering (0-100)
const int times=50;//numer of measurements to average

const int autoComp=10000; //1h checking time interval
long tCheck=-autoComp;//last checked time. Initializes to always chack on startup

//enables/disables debug messages. Should be turned off for the final deployment.
//adding your own messages is as easy as including: if(verboseOn)Serial.print("My debug message");
boolean verboseOn = false;

//parameters for the connection with the main module. Please check the manual for a complete reference on these
const char deviceName[] ="girasol";
WebThingAdapter *adapter;//main objet we will use
const char *capacidades[] = {"MultiLevelSensor", nullptr};//list of functionality categories
ThingDevice Sensor("humedad1", "girasol", capacidades);//one device on our project
ThingProperty Humidity("Humidity", "dryness level", NUMBER, "LevelProperty");//define each property of the device
ThingEvent NeedWater("Not enough moisture","Need to water",BOOLEAN, "AlarmEvent");

//telegram bot settings
#define bOTtoken "914632211:AAG1Oe1_9EkHIOqVMQnuoV0X_oWsRoA9FR8"
uTLGBot Bot(bOTtoken);
const int debugLevelBot = 0;
const int numChats=2; //we can specify to send the messages to more than one account
//we specify here the chat ids we want the messages sent to
const char chatID[]={"191552774"};
const char chatID2[]={"191552774"};
const char *chatIDs[numChats]={chatID,chatID2};
