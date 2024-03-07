# Urban Reef Encoder
Library used to encode data into a byte array to be sent via LoRaWan.

## Installation

### Arduino
1. Place `UREncoder.ccp` and `UREncoder.h` inside the sketch folder.
2. Include the header file at the top op the `.ino` file. `include "UREncoder.h"`.

### PlatformIO
1. In `platformio.ini` place the link to the repository. When this repo is updated the updates will automatically be
installed by PlatformIO
```
lib_deps = https://github.com/Urban-Reef/Sensor-Reef-UREncoder.git
```
## Usage
Instantiate a `UREncoder` object. Pass the size of the buffer in bytes and the `id` of the Reef. 
```c++
auto* encoder = new UREncoder(size, reefId);
```
### Encoding points
To add a point use:
```c++
encoder->addPoint(position);
```
`position` is an integer used to track the position of the point on the Reef. This must correspond with how the points are 
defined in web application (The Laravel Dashboard).

### Encoding sensor data
The order in which data is encoded matters.
After creating a point all following sensor data belongs to that point until a new point added.
```c++
    encoder->addPoint(1); //Encode point 1 to the buffer.
    encoder->addTemperature(26.5); //Belongs to point 1.
    encoder->addRelativeHumidity(55.5); //Belongs to point 1.
    encoder->addPoint(2); //Encode point 2 to the buffer.
    encoder->addTemperature(24.3); //Belongs to point 2.
    encoder->addRelativeHumidity(40); //Belongs to point 2.
```
1. `addTemperature(float celsius)` Add temperature in Celsius with 1 decimal, ex: `15.5` 
2. `addRelativeHumidity(float rh)` Add Humidity in percentage in steps of 0.5, ex: `40.0` or `40.5`
3. `addLuminosity(uint16_t lux)` Add luminosity in lux. No decimals.

Note: Luminosity can be encoded but **CANNOT** be decoded. This still has to be added to the [URDecoder](https://github.com/Urban-Reef/Sensor-Reef-URDecoder).

## Flowchart
The 'UREncoder' instance walks through the created buffer. It tracks its position using `cursor`.

![Flowchart Encoding Process][flowchart]

[Google Drive](https://drive.google.com/open?id=1Aw3_T0eH-Hljleyd9ejlmaVrA-ZOEXto&usp=drive_fs)

[flowchart]: https://drive.google.com/uc?id=1Aw3_T0eH-Hljleyd9ejlmaVrA-ZOEXto "Flowchart visualising the encoding process"

## Extending encoder
1. In `UREncoder.h` define a new 'flag' and type size. A flag is used to identify how the following byte(s) should be decoded.
Make sure to replace `NEW_TYPE` with a descriptive name and `5` with a unique number.
```c++
//Type flags used during decoding to identify what data is being read.
#define REEF                1
//  other definitions
#define NEW_TYPE            5
```

2. Define the total size of the encoded data. That includes the 'flag'.
The flag  is currently stored as a single 8-bit unsigned integer (1 byte). That means it has a range of 0-255. Lets say that the value we are going to store requires 2 bytes then we declare a size of 3.
```c++
//total byte size of flag and value.
#define REEF_SIZE           2
//  other
#define NEW_TYPE_SIZE       3
```

3. Declare a new public function. With a return type of `uint8_t`. Change the type or amount of parameters to your use case.
```c++
uint8_t addNewType(uint16_t value);
```

4. Open `UREncoder.cpp` and below the other methods declare a new one. This function should check if there room in the buffer.
```c++
uint8_t UREncoder::addNewType(uint16_t value) {
    //Check if there is room in buffer
    if ((cursor + NEW_TYPE_SIZE) > maxsize) {
        //if not return 0
        return 0;
    }
    //write flag to buffer and increment cursor.
    buffer[cursor++] = NEW_TYPE;
    //Split the 16-bit unsigned int into 2 unsigned 8-bit int.
    //Store the two bits in Big Endian order.
    buffer[cursor++] = value >> 8; //bit shifting
    buffer[cursor++] = value;

    return cursor;
}
```

### Converting types
Only integers (whole numbers) can be stored in the buffer. To store `float`, `double` or `decimal`
they have to be converted to whole numbers. For examples look at `addTemperature()` and `addHumidity()` methods.

### Publishing changes
In `library.json` update the `version`. Commit and push changes, create a new release with the same version number as stated in `library.json`.