#include <Arduino.h>

#define SERIAL_DATA_BLOCK_SIZE  (1024*72)

uint8_t dataBlockA[SERIAL_DATA_BLOCK_SIZE];

void setup() {
    SerialUSB.begin(115200);
  
    while (!SerialUSB) {
      ; // wait for serial port to connect. Needed for native USB port only
    }
}

uint8_t fillValue = 0;

void fillDataBlockValues() {
    fillValue = (fillValue + 1) % 8;
    for (uint32_t i = 0; i < SERIAL_DATA_BLOCK_SIZE; i++) {
        dataBlockA[i] = fillValue;
    }
}

uint32_t blockSize = SERIAL_DATA_BLOCK_SIZE;

void loop() {
  if (SerialUSB.available() > 0 && SerialUSB.read() == 0x0F) {
    size_t leftToWrite = 0;
        
    SerialUSB.write((uint8_t*)&blockSize, 4);

    fillDataBlockValues();

    leftToWrite = SERIAL_DATA_BLOCK_SIZE;
    while (leftToWrite > 0) {
      leftToWrite -= SerialUSB.write(dataBlockA, min(SerialUSB.availableForWrite(), leftToWrite));
    }
  }  
}
