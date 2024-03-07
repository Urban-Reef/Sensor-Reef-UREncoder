#include <UREncoder.h>

//Create a byte array to send via Lorawan
uint8_t* createPayload(){
    auto* encoder = new UREncoder(58, 1);
    encoder->addPoint(1); // create first point
    encoder->addTemperature(26.5); // belongs to point 1
    encoder->addRelativeHumidity(55.5); // belongs to point 1
    encoder->addPoint(2); // create second point
    encoder->addTemperature(24.3); // belongs to point 2
    encoder->addRelativeHumidity(40); // belongs to point 2

    //Get a pointer to the buffer. This is your payload.
    return encoder->getBuffer();
}