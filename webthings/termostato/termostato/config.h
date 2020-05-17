
//credenciales del acceso a wifi
const char *ssid = "delgado";
const char *password = "micasa221b";

//credenciales para la actualizacion inalámbrica
const char nombreOTA[]= "termostato";
const char passOTA[]= "admin";

// variables globales de usuario
//aquí pudes añadir las que necesites
long t;
float tObjetivo=0.0f;
float tMedida=0.0f;
float humedad=0.0f;
boolean calentar=false;
float ultiTemp=0;

//habilita o deshabilita los mensajes de depuracion
boolean verboseOn = true;

//configuración de los parametros para el display en el nodo central
WebThingAdapter *adapter;
const char *capacidades[] = {"Thermostat", nullptr};//lista de parametros que tiene el sensor, debe acabar en nullptr
ThingDevice Termostato("termostato", "termostato", capacidades);//objeto dispositivo Nombre("","nombre en display",capacidades)
ThingProperty Temperatura("Temperatura", "Lectura del sensor", NUMBER, "TemperatureProperty");//propiedad 1 del dispositivo
ThingProperty TemperaturaObj("TemperaturaObj", "Temepratura objetivo", NUMBER, "TargetTemperatureProperty");//propiedad 2 del dispositivo
//ThingProperty Humedad("Humedad %", "Lectura del sensor", NUMBER, nullptr);


//configuracion de la pantalla integrada
const int sdaOled=5;
const int sclOled=4;
SSD1306Wire display(0x3c, sdaOled, sclOled);

//configuracion del sensor
DHTesp dht;
int dhtPin = 18;
