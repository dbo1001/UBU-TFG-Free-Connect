//wifi credentials. They sould match your network's
const char *ssid = "wifi";
const char *password = "pass";

//OTA credentials. we define those here
const char nombreOTA[]= "awesomeModule";
const char passOTA[]= "admin";

 /**
   * Global variables for your code
   * this is the place to add the global variables you will use later
   * you should add pin definitions aswell as any other variable
   * 
   */




//enables/disables debug messages. Should be turned off for the final deployment.
//adding your own messages is as easy as including: if(verboseOn)Serial.print("My debug message");
boolean verboseOn = true;

//parameters for the connection with the main node. Please check the manual for a complete reference on these
const char deviceName[] ="deviceName";
WebThingAdapter *adapter;//main objet we will use
const char *capacidades[] = {"MultiLevelSensor", nullptr};//list of functionality categories
ThingDevice Sensor("humedad1", "girasol", capacidades);//one device on our project
ThingProperty Propiedad1("Propiedad1", "readings", NUMBER, "LevelProperty");//define each property of the device


//telegram bot settings
#define bOTtoken "token"
uTLGBot Bot(bOTtoken);
const int debugLevelBot = 0;
const int numChats=2; //we can specify to send the messages to more than one account
//we specify here the chat ids we want the messages sent to
const char chatID[]={"chatId1"};
const char chatID2[]={"chatId2"};
const char *chatIDs[numChats]={chatID,chatID2};
