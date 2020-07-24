#include <Arduino.h>

#define SERIAL_DATA_BLOCK_SIZE  1024*64

uint8_t dataBlock[SERIAL_DATA_BLOCK_SIZE];
uint8_t dataBlock2[SERIAL_DATA_BLOCK_SIZE];

void setup() {
    SerialUSB.begin(115200);
  
    while (!SerialUSB) {
      ; // wait for serial port to connect. Needed for native USB port only
    }
}

uint8_t fillValue = 0;

void loop() {
  if (SerialUSB.available() > 0 && SerialUSB.read() == 0x0F) {
    
    SerialUSB.write( (uint8_t) ((SERIAL_DATA_BLOCK_SIZE >> 8) & 0xFF));
    SerialUSB.write( (uint8_t) (SERIAL_DATA_BLOCK_SIZE & 0x00FF));

    fillValue = (fillValue + 1) % 8;
    for (uint16_t i = 0; i <= SERIAL_DATA_BLOCK_SIZE; i++) {
        dataBlock[i] = fillValue;
    }
      
    SerialUSB.write(dataBlock, SERIAL_DATA_BLOCK_SIZE);
    SerialUSB.write(dataBlock2, SERIAL_DATA_BLOCK_SIZE);
  }  
}
