#include <Arduino.h>
#include "Adafruit_TinyUSB.h"
#include "nrf52_servo.hpp"

NRF52_Servo servo;

void setup() {
  Serial.begin(115200);
  servo.init(18);
}
void loop() {
  if (servo.isEnabled()) {
    servo.writeMicroseconds(800);
    delay(1000);
    servo.writeMicroseconds(2000);
    delay(1000);
  }
}