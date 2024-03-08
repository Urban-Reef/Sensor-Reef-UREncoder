//
// Created by danie on 28/02/2024.
//

#include "../include/UREncoder.h"

//Pass the size of byte array and reef id.
UREncoder::UREncoder(uint8_t size, uint8_t reefId) : maxsize(size) {
    //creates a buffer of a specific size.
    buffer = (uint8_t*) malloc(size);
    cursor = 0;
    addReefId(reefId);
}

UREncoder::~UREncoder() {
    free(buffer);
}

//resets cursor to 0 position. Does not clear buffer.
void UREncoder::resetCursor(void) {
    cursor = 0;
}

//returns the cursor position.
uint8_t UREncoder::getSize(void) {
    return cursor;
}

//returns the buffer.
uint8_t *UREncoder::getBuffer(void) {
    return buffer;
}

uint8_t UREncoder::addReefId(uint8_t id) {
    if ((cursor + REEF_SIZE) > maxsize) {
        return 0;
    }

    buffer[cursor++] = REEF;
    buffer[cursor++] = id;

    return cursor;
}

uint8_t UREncoder::addPoint(uint8_t position) {
    if ((cursor + POINT_SIZE) > maxsize) {
        return 0;
    }

    buffer[cursor++] = POINT;
    buffer[cursor++] = position;

    return cursor;
}

uint8_t UREncoder::addTemperature(float celsius) {
    if ((cursor + TEMPERATURE_SIZE) > maxsize) {
        return 0;
    }
    //multiply by ten to move the decimal up to convert float to a 16bit signed integer.
    //Ex: 18.6 * 10 = 186
    int16_t val = celsius * 10;
    buffer[cursor++] = TEMPERATURE;
    //Split the 16bit unsigned int into 2 unsigned 8 bit int.
    //Store the two bits in Big Endian order.
    buffer[cursor++] = val >> 8;
    buffer[cursor++] = val;

    return cursor;
}

uint8_t UREncoder::addRelativeHumidity(float rh) {
    if ((cursor + RELATIVE_HUMIDITY_SIZE) > maxsize) {
        return 0;
    }

    //Humidity is measured in steps of 0.5 and has a range of 0 - 100
    //This allows us to store it in a single 8-bit unsigned int by multiplying by 2 as this removes the decimal.
    //Ex: 25.5 * 2 = 50
    buffer[cursor++] = RELATIVE_HUMIDITY;
    buffer[cursor++] = rh * 2;

    return cursor;
}

uint8_t UREncoder::addLuminosity(uint16_t lux) {
    if ((cursor + LUMINOSITY_SIZE) > maxsize) {
        return 0;
    }
    //write flag to buffer.
    buffer[cursor++] = LUMINOSITY;
    //Split the 16-bit unsigned int into 2 unsigned 8-bit int.
    //Store the two bits in Big Endian order.
    buffer[cursor++] = lux >> 8;
    buffer[cursor++] = lux;

    return cursor;
}
