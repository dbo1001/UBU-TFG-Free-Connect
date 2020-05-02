//credenciales del acceso a wifi
const char *ssid = "delgado";
const char *password = "micasa221b";

//credenciales para la actualizacion inalámbrica
const char nombreOTA[]= "esp32pruebas";
const char passOTA[]= "admin";

// variables globales de usuario
//aquí pudes añadir las que necesites

//habilita o deshabilita los mensajes de depuracion
boolean verboseOn = true;

//configuración de los parametros para el display en el nodo central
const char *capacidades[] = {"MultiLevelSensor", nullptr};//lista de parametros que tiene el sensor, debe acabar en nullptr
ThingDevice Sensor("humedad1", "girasol", capacidades);//objeto dispositivo Nombre("","nombre en display",capacidades)
ThingProperty Propiedad1("Propiedad1", "Lectura del sensor", NUMBER, "LevelProperty");//propiedad 1 del dispositivo

//configuracion para telegram

#define bOTtoken "914632211:AAG1Oe1_9EkHIOqVMQnuoV0X_oWsRoA9FR8"
const int numChats=1;
const char chatID[]={"191552774"};
const char* chatIDs[numChats]={chatID};
