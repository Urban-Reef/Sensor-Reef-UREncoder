#ifndef UR_ENCODER_H
#define UR_ENCODER_H

#include <cstdint>
#include <cstring>

#define MAX_BUFFER_SIZE 200

// Type flags
#define REEF                1
#define POINT               2
#define SUBPOINT            3
#define TEMPERATURE         4
#define RELATIVE_HUMIDITY   5
#define SOIL_MOISTURE       6

// Sizes
#define REEF_SIZE               2
#define POINT_SIZE              2
#define SUBPOINT_SIZE           2
#define TEMPERATURE_SIZE        3
#define RELATIVE_HUMIDITY_SIZE  2
#define SOIL_MOISTURE_SIZE      3

class UREncoder {
public:
    explicit UREncoder(uint8_t size, uint8_t reefId);
    void resetCursor();
    void reset();
    uint8_t getSize();
    uint8_t* getBuffer();

    bool addPoint(uint8_t position);
    bool addSubpoint(uint8_t subposition);
    bool addTemperature(float celsius);
    bool addRelativeHumidity(float rh);
    bool addSoilMoisture(uint16_t value);

private:
    uint8_t buffer[MAX_BUFFER_SIZE] = {0};
    uint8_t maxsize;
    uint8_t cursor;
    uint8_t reefId;

    bool addReefId(uint8_t id);
};

#endif // UR_ENCODER_H