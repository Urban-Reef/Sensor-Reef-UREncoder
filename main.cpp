#include <iostream>
#include <iomanip>
#include "src/UREncoder.h"

int main() {
    auto* payload = new UREncoder(2 + 7 * 8, 15);
    payload->addPoint(1); // 2
    payload->addTemperature(26.5); // 3
    payload->addRelativeHumidity(55.5); // 2
    payload->addPoint(2); // 2
    payload->addTemperature(24.3); // 3
    payload->addRelativeHumidity(40); // 2

    uint8_t* buffer = payload->getBuffer();

    std::cout << "Hex Binary: ";
    for (int i = 0; i < payload->getSize(); ++i) {
        std::cout << "0x" << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(buffer[i]);
        if (i < payload->getSize() - 1) {
            std::cout << ", ";
        }
    }
    std::cout << std::endl;

    delete payload;
    return 0;
}
