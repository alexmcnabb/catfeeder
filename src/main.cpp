#include <Arduino.h>

// # Using fuses 0xFF, 0xD8, 0xCB

#include "SendOnlySoftwareSerial.h"

const uint8_t PIN_MOTOR_A = 7;
const uint8_t PIN_MOTOR_B = 8;
const uint8_t PIN_MOTOR_PWM = 9; // Must match timer1 output A
const uint8_t PIN_MOTOR_SEL = 4;
const uint8_t PIN_CURRENT_SENSE = A0;
const uint8_t PIN_EN_LED = 13;

const uint16_t PWM_RANGE = 800; // Defines maximum frequency and resolution of PWM (800 => 20kHz)
const uint32_t MOTOR_UPDATE_PERIOD = 10; // Motor update period in milliseconds

void initPWM(){
    pinMode(PIN_MOTOR_A, OUTPUT);
    pinMode(PIN_MOTOR_B, OUTPUT);
    pinMode(PIN_MOTOR_PWM, OUTPUT);
    // Using Timer1, Output A, Mode 14 (Fast PWM, TOP=ICR1), Clear on match, set on TOP, prescaler 1:1
    TCCR1A = _BV(COM1A1) | _BV(WGM11);
    TCCR1B = _BV(WGM12) | _BV(WGM13) | _BV(CS10);
    ICR1 = PWM_RANGE; // TOP
}

void setPWMOutput(int32_t setpoint){
    // Setpoint will be constrained to +PWM_RANGE to -PWM_RANGE
    digitalWrite(PIN_MOTOR_A, setpoint > 0);
    digitalWrite(PIN_MOTOR_B, setpoint < 0);
    setpoint = abs(setpoint);
    setpoint = setpoint > PWM_RANGE ? PWM_RANGE : setpoint;
    OCR1A = setpoint;
}

void setup() {
    initPWM();
    Serial.setTimeout(200);
    Serial.begin(1);
}

uint32_t prevDisplay;
uint32_t interval = 1000;

void loop() {
    int32_t setpoint = Serial.parseInt();
    setPWMOutput(setpoint);
    Serial.print("Setting motor to: ");
    Serial.println(setpoint);
}
