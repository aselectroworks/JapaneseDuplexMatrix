#include "DuplexMatrix.h"

#define NUM_COLS 4
static int8_t colPins[NUM_COLS] = {4, 45, 42, 6}; // COL0, COL1, COL2, COL3
#define NUM_ROWS 2
static int8_t rowPins[NUM_ROWS] = {35, 5}; // ROW0, ROW1

DuplexMatrix keyMatrix = DuplexMatrix(colPins, rowPins, NUM_COLS, NUM_ROWS);

void setup() {
    Serial.begin(115200);
    keyMatrix.begin();
    Serial.printf("KeyMatrix Initialized \r\n");
}

void loop() {
    static int8_t states[NUM_COLS * (NUM_ROWS * 2)]; 
    keyMatrix.scan();
    keyMatrix.state(states);

    Serial.printf("[States]\r\n");
    for (uint8_t i = 0; i < (NUM_ROWS * 2); i++) {
        for (uint8_t j = 0; j < NUM_COLS; j++) {
            Serial.printf("%d ", states[(i * NUM_COLS) + j]);
        }
        Serial.printf("\r\n");
    }
    Serial.printf("COL=2, ROW=2, VAL=%d\r\n", keyMatrix.state(2, 2)); 
    Serial.printf("\033[%d;%dH" ,0,0); 
}