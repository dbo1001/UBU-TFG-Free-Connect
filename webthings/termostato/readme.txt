Ejemplo de modulo termostato

Incluye webthings, ota y oled

Se comenzo utilizando un sensor analógico LM36, este presentaba el problema de trabajar on logoca de 5V mientras que el esp32 utiliza logica de 3.3V. Observe que las mediciones no eran buenas y opté por utilizar un conversor de nivel.
Esto añadia piezas al proyecto, complejidad y error en la medida. Finalmente decidí utilizar un sensor digital DHT 11 que ademas nos indica la humedad relativa del ambiente.
libreria https://github.com/beegee-tokyo/DHTesp
