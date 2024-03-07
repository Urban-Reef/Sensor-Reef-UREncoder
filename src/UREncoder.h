#ifndef UR_ENCODER
#define UR_ENCODER

#include <cstdint>
#include <cstdlib>
#include <cstring>

//Type flags used during decoding to identify what data is being read.
#define REEF                1
#define POINT               2
#define TEMPERATURE         3
#define RELATIVE_HUMIDITY   4
#define LUMINOSITY          5

//total byte size of flag and value.
#define REEF_SIZE               2
#define POINT_SIZE              2
#define TEMPERATURE_SIZE        3
#define RELATIVE_HUMIDITY_SIZE  3
#define LUMINOSITY_SIZE         3

class UREncoder {
public:
    explicit UREncoder(uint8_t size, uint8_t reefId);
    ~UREncoder();

    void resetCursor(void);
    uint8_t getSize(void);
    uint8_t* getBuffer(void);

    uint8_t addPoint(uint8_t position);
    uint8_t addTemperature(float celsius);
    uint8_t addRelativeHumidity(float rh);
    uint8_t addLuminosity(uint16_t lux);

private:
    uint8_t *buffer;
    uint8_t maxsize;
    uint8_t cursor;
    uint8_t addReefId(uint8_t id);
};

#endif //UR_ENCODER