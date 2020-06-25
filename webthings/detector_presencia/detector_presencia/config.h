//wifi credentials. They sould match your network's
const char *ssid = "delgado";
const char *password = "micasa221b";

//OTA credentials. we define those here
const char nombreOTA[]= "alarm";
const char passOTA[]= "admin";

 /**
   * Global variables for your code
   * this is the place to add the global variables you will use later
   * you should add pin definitions aswell as any other variable
   * 
   */
const int pir=26;
const int led =2 ;

const int numDetections=2;
int detectionCount=0;

boolean triggered=false;

long t=0;
long tReset = 10000;
long tMessages= 15000;
long tLastMessage=0;
long tTriggered=0;
long tRinging= 30000;

//enables/disables debug messages. Should be turned off for the final deployment.
//adding your own messages is as easy as including: if(verboseOn)Serial.print("My debug message");
boolean verboseOn = true;

//parameters for the connection with the main node. Please check the manual for a complete reference on these
const char deviceName[] ="alarm";
WebThingAdapter *adapter;//main objet we will use
const char *capacidades[] = {"Alarm", nullptr};//list of functionality categories
ThingDevice Sensor("alarma", "detector presencia", capacidades);//one device on our project
ThingProperty Detectado("detectado", "persona detectada", BOOLEAN, "AlarmProperty");//define each property of the device
ThingEvent DeteccionEvento("persona","detectada",BOOLEAN, "AlarmEvent");

//telegram bot settings
#define bOTtoken "914632211:AAG1Oe1_9EkHIOqVMQnuoV0X_oWsRoA9FR8"
uTLGBot Bot(bOTtoken);
const int debugLevelBot = 0;
const int numChats=1; //we can specify to send the messages to more than one account
//we specify here the chat ids we want the messages sent to
const char chatID[]={"191552774"};
const char *chatIDs[numChats]={chatID};
