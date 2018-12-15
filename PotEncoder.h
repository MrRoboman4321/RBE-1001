#pragma once

#include "Encoder.h"

/**
 * Helper class that inherits from Encoder
 * Allows us to treat Potentiometers as encoders
 */
class PotEncoder : public Encoder {
private:
    //Pin that the potentiometer is connected to
    int _pin;

    //Current position of the potentiometer
    int _position;
public:
    PotEncoder(int pin);
    float getPosition();
    void update();
};