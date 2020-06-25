soporte para placas con pantalla oled integrada

Incluye webthings, ota, telegram

La libreria elegida es https://github.com/ThingPulse/esp8266-oled-ssd1306
ya que la ofiacil de espressif carece de documentacion lo que la hace mucho mas dificil de usar


funciones utiles


SSD1306Wire display(DIRECCION I2C, SDA, SCL); para crear el objeto

init(); inicializa el modulo

clear();

invertDisplay();

flipScreenVertically()

setTextAlignment(TEXT_ALIGN_LEFT);
TEXT_ALIGN_LEFT, TEXT_ALIGN_CENTER, TEXT_ALIGN_RIGHT, TEXT_ALIGN_CENTER_BOTH

setFont(FUENTE);
ArialMT_Plain_10, ArialMT_Plain_16, ArialMT_Plain_24

drawString(POSX, POSY, TEXTO);