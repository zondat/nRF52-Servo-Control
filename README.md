nRF52 has a greate advantage on create DIY flight controller by communicating directly with nrf24l01 board which is cheap and has good performance.
The disadvantage of nRF52 boards is the lack of peripheral libraries such as servo control, ppm and the pin name of each board. The board that I use in my project is nice!nano v2. 
In the code, the pin's name is totally different from what is written in the board (e.g., p0.02), the used name is D+ a number, we must consult the datasheet to have this name.

Another problem of nRF52 board is to upload code from Arduino IDE. Solution is to add these instructions:

#include "Adafruit_TinyUSB.h"

void setup() {
  Serial.begin(115200);
  ...
}
