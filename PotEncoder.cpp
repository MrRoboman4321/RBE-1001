#include "PotEncoder.h"

PotEncoder::PotEncoder(int pin) {
    _pin = pin;

    //Set the pin that the pot is connected to as INPUT
    pinMode(_pin, INPUT);
}

/**
 * The current posiiton of the potentiometer
 * @return current position
 */
float PotEncoder::getPosition() {
    return _position;
}

/**
 * Update the position of the potentiometer
 */
void PotEncoder::update() {
    _position = analogRead(_pin);
}