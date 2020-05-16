
//credenciales del acceso a wifi
const char *ssid = "delgado";
const char *password = "micasa221b";

//credenciales para la actualizacion inalámbrica
const char nombreOTA[]= "termostato";
const char passOTA[]= "admin";

// variables globales de usuario
//aquí pudes añadir las que necesites
long t;
float tObjetivo=22.2f;
float tMedida=11.1f;
boolean calentar=false;


//habilita o deshabilita los mensajes de depuracion
boolean verboseOn = true;

//configuración de los parametros para el display en el nodo central
WebThingAdapter *adapter;
const char *capacidades[] = {"TemperatureSensor", nullptr};//lista de parametros que tiene el sensor, debe acabar en nullptr
ThingDevice Termostato("termostato", "termostato", capacidades);//objeto dispositivo Nombre("","nombre en display",capacidades)
ThingProperty Temperatura("Temperatura", "Lectura del sensor", NUMBER, "TemperatureProperty");//propiedad 1 del dispositivo


//configuracion para telegram
const int debugLevelBot = 0;
#define bOTtoken "914632211:AAG1Oe1_9EkHIOqVMQnuoV0X_oWsRoA9FR8"
uTLGBot Bot(bOTtoken);
const int numChats=1;
const char chatID[]={"191552774"};
const char* chatIDs[numChats]={chatID};


//pines utilizados en el bus i2c de la pantalla
const int sdaOled=5;
const int sclOled=4;
SSD1306Wire display(0x3c, sdaOled, sclOled);
