#include "Encoder.h"

Encoder::Encoder() {}

Encoder::Encoder(int pinA, int pinB) {
    _pinA = pinA;
    _pinB = pinB;

    pinMode(_pinA, INPUT);
    pinMode(_pinB, INPUT);
}

/**
 * Updates the position of the encoder.
 * IMPORTANT: Must be called as fast as possible by any user of the Encoder class
 * Code based on example from http://playground.arduino.cc/Main/RotaryEncoders
 */
void Encoder::update() {
    int n = digitalRead(_pinA);
    if ((_lastPosition == LOW) && (n == HIGH)) {
        if (digitalRead(_pinB) == LOW) {
            _pos--;
        } else {
            _pos++;
        }
    }
    _lastPosition = n;
}

/**
 * Gets the current ticks of the encoder
 * @return current encoder position
 */
float Encoder::getPosition() {
    return _pos;
}