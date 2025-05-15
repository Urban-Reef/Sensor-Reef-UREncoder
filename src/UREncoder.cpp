//
// Created by danie on 28/02/2024.
//

#include "../include/UREncoder.h"

UREncoder::UREncoder(uint8_t size, uint8_t reefId) : maxsize(size), reefId(reefId), cursor(0) {
    memset(buffer, 0, MAX_BUFFER_SIZE);
    addReefId(reefId);
}

void UREncoder::resetCursor() {
    cursor = 0;
}

void UREncoder::reset() {
    memset(buffer, 0, maxsize);
    cursor = 0;
    addReefId(reefId);
}

uint8_t UREncoder::getSize() {
    return cursor;
}

uint8_t* UREncoder::getBuffer() {
    return buffer;
}

bool UREncoder::addReefId(uint8_t id) {
    if ((cursor + REEF_SIZE) > maxsize) return false;
    buffer[cursor++] = REEF;
    buffer[cursor++] = id;
    return true;
}

bool UREncoder::addPoint(uint8_t position) {
    if ((cursor + POINT_SIZE) > maxsize) return false;
    buffer[cursor++] = POINT;
    buffer[cursor++] = position;
    return true;
}

bool UREncoder::addSubpoint(uint8_t subposition) {
    if ((cursor + SUBPOINT_SIZE) > maxsize) return false;
    buffer[cursor++] = SUBPOINT;
    buffer[cursor++] = subposition;
    return true;
}

bool UREncoder::addTemperature(float celsius) {
    if ((cursor + TEMPERATURE_SIZE) > maxsize) return false;
    int16_t val = static_cast<int16_t>(celsius * 10);
    buffer[cursor++] = TEMPERATURE;
    buffer[cursor++] = val >> 8;
    buffer[cursor++] = val & 0xFF;
    return true;
}

bool UREncoder::addRelativeHumidity(float rh) {
    if ((cursor + RELATIVE_HUMIDITY_SIZE) > maxsize) return false;
    uint8_t value = static_cast<uint8_t>(rh * 2); // compress 0–100% in 0.5 steps
    buffer[cursor++] = RELATIVE_HUMIDITY;
    buffer[cursor++] = value;
    return true;
}

bool UREncoder::addSoilMoisture(uint16_t value) {
    if ((cursor + SOIL_MOISTURE_SIZE) > maxsize) return false;
    buffer[cursor++] = SOIL_MOISTURE;
    buffer[cursor++] = value >> 8;
    buffer[cursor++] = value & 0xFF;
    return true;
}