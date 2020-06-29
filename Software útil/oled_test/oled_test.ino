/**
 * Simple piece of code to check your OLED settings
 * Complete information can be found at projects website.
 * Author: Daniel Delgado Santamaría
 * Project: https://freeconnectproject.com
 * License is GPL 3.0
 * 
 */

#include "SSD1306Wire.h" 


SSD1306Wire display(0x3c, 5, 4);
void setup() {
    display.init();// obligatorio
    
    display.setTextAlignment(TEXT_ALIGN_LEFT);
    display.setFont(ArialMT_Plain_24);
    display.drawString(0, 0, "Pruebas");
    display.display();
}

void loop() {
  // put your main code here, to run repeatedly:

}
