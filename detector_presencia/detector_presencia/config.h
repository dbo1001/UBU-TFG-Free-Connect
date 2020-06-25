//wifi credentials. They sould match your network's
const char *ssid = "wifi";
const char *password = "pass";

//OTA credentials. we define those here
const char nombreOTA[]= "alarm";
const char passOTA[]= "admin";

 /**
   * Global variables for your code
   * this is the place to add the global variables you will use later
   * you should add pin definitions aswell as any other variable
   * 
   */
const int pir=26;//pin configuration
const int led=2;

const int numDetections=2;//required numbre of detections to go off
int detectionCount=0;

boolean active=false;

boolean triggered=false;

long t=0;//time instant
const long tReset = 10000;//time to consider the detection was a false positive
const long tMessages= 15000;//time between sent alert messages
long tLastMessage=0;//time since the last message was sent
long tTriggered=0;//time instant when fisrt detected
const long tRinging= 60000;//time to be alerting when triggered

//enables/disables debug messages. Should be turned off for the final deployment.
//adding your own messages is as easy as including: if(verboseOn)Serial.print("My debug message");
boolean verboseOn = true;

//parameters for the connection with the main node. Please check the manual for a complete reference on these
const char deviceName[] ="alarm";
WebThingAdapter *adapter;//main objet we will use
const char *capacidades[] = {"Alarm", nullptr};//list of functionality categories
ThingDevice Sensor("alarma", "detector presencia", capacidades);//one device on our project
ThingProperty Detectado("detectado", "persona detectada", BOOLEAN, "AlarmProperty");//define each property of the device
ThingProperty Activado("activado", "alarma ready", BOOLEAN, "BooleanProperty");//define each property of the device
ThingEvent DeteccionEvento("persona","detectada",BOOLEAN, "AlarmEvent");

//telegram bot settings
#define bOTtoken "token"
uTLGBot Bot(bOTtoken);
const int debugLevelBot = 0;
const int numChats=1; //we can specify to send the messages to more than one account
//we specify here the chat ids we want the messages sent to
const char chatID[]={"chat"};
const char *chatIDs[numChats]={chatID};
