#pragma once

#include <Arduino.h>

/**
 * The Encoder class represents a VEX 3-wire encoder.
 */
class Encoder {
private:
    //The A and B channel pins of the encoder
    int _pinA, _pinB;

    //Current position of the encoder
    int _pos = 0;

    //Used for the update() method
    int _lastPosition = LOW;
public:
    Encoder();
    Encoder(int pinA, int pinB);

    virtual float getPosition();
    void update();
};
