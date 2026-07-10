 # ifndef NRF52_Servo_CPP
 # define NRF52_Servo_CPP

 # include "nrf52_servo.hpp"

 # define DEFAULT_NRF52_TIMER_NO NRF_TIMER_1

bool NRF52_Servo::init(const uint8_t pin) {
    for (int i = 0; i < HWPWM_MODULE_NUM; i++) {
        if (!HwPWMx[i]->isOwner(SERVO_TOKEN)) HwPWMx[i]->takeOwnership(SERVO_TOKEN);
        if (HwPWMx[i]->isOwner(SERVO_TOKEN) && HwPWMx[i]->addPin(pin)) {
			this->pin = pin;
            hardware_pwm = HwPWMx[i];
            hardware_pwm->setMaxValue(MAXVALUE);
			hardware_pwm->setClockDiv(CLOCKDIV);
			enable = true;
            return enable;
        }
    }
	return false;
}


void NRF52Servo::write(uint16_t value) {
	uint16_t constrained_value = constrain(value, 0, 180);
	constrained_value = map(value, 0, 180, minPulseUs, maxPulseUs);
    writeMicroseconds(constrained_value);
}

void NRF52Servo::writeMicroseconds(uint16_t value) {
	uint16_t constrained_value = constrain(value, minPulseUs, maxPulseUs);
    uint32_t dutyCycle = (constrained_value * MAXVALUE) / 20000; // 20000 = 20ms
    hardware_pwm->writePin(pin, dutyCycle);
    current_value = constrained_value;
}

# endif // NRF52_Servo_CPP
