#include "DuplexMatrix.h"

#define NUM_COLS 4
static int8_t colPins[NUM_COLS] = {4, 45, 42, 6}; // COL0, COL1, COL2, COL3
#define NUM_ROWS 2
static int8_t rowPins[NUM_ROWS] = {35, 5}; // ROW0, ROW1

DuplexMatrix keyMatrix = DuplexMatrix(colPins, rowPins, NUM_COLS, NUM_ROWS);

void handlePressEvent(void *data) {
    DuplexMatrix::Position_t *position = (DuplexMatrix::Position_t *)data;
    Serial.printf("Press Event: COL=%d, ROW=%d\r\n", position->col, position->row);
}

void handleClickEvent(void *data) {
    DuplexMatrix::Position_t *position = (DuplexMatrix::Position_t *)data;
    Serial.printf("Click Event: COL=%d, ROW=%d\r\n", position->col, position->row);
}

void handleDoubleClickEvent(void *data) {
    DuplexMatrix::Position_t *position = (DuplexMatrix::Position_t *)data;
    Serial.printf("Double Click Event: COL=%d, ROW=%d\r\n", position->col, position->row);
}

void handleMultiClickEvent(void *data) {
    DuplexMatrix::Position_t *position = (DuplexMatrix::Position_t *)data;
    Serial.printf("Multi Click Event: COL=%d, ROW=%d\r\n", position->col, position->row);
}

void handleLongPressStartEvent(void *data) {
    DuplexMatrix::Position_t *position = (DuplexMatrix::Position_t *)data;
    Serial.printf("Long Press Start Event: COL=%d, ROW=%d\r\n", position->col, position->row);
}

void handleLongPressStopEvent(void *data) {
    DuplexMatrix::Position_t *position = (DuplexMatrix::Position_t *)data;
    Serial.printf("Long Press Stop Event: COL=%d, ROW=%d\r\n", position->col, position->row);
}

void handeDuringLongPressEvent(void *data) {
    DuplexMatrix::Position_t *position = (DuplexMatrix::Position_t *)data;
    Serial.printf("During Long Press Event: COL=%d, ROW=%d\r\n", position->col, position->row);
}

void handleIdleEvent() {
    Serial.printf("Idle Event\r\n");
}

void setup() {
    Serial.begin(115200);
    keyMatrix.begin();
    for (uint8_t i = 0; i < NUM_COLS; i++) {
        for (uint8_t j = 0; j < NUM_ROWS * 2; j++) {
            keyMatrix.attachPress(i, j, handlePressEvent);
            keyMatrix.attachClick(i, j, handleClickEvent); 
            keyMatrix.attachDoubleClick(i, j, handleDoubleClickEvent);
            keyMatrix.attachMultiClick(i, j, handleMultiClickEvent);
            keyMatrix.attachLongPressStart(i, j, handleLongPressStartEvent);
            keyMatrix.attachLongPressStop(i, j, handleLongPressStopEvent);
            keyMatrix.attachDuringLongPress(i, j, handeDuringLongPressEvent);
            keyMatrix.attachIdle(i, j, handleIdleEvent);
        }
    }
    Serial.printf("KeyMatrix Initialized \r\n");
}

void loop() {
    static int8_t states[NUM_COLS * (NUM_ROWS * 2)]; 
    keyMatrix.scan();
    keyMatrix.state(states);
#if 0
    Serial.printf("[States]\r\n");
    for (uint8_t i = 0; i < (NUM_ROWS * 2); i++) {
        for (uint8_t j = 0; j < NUM_COLS; j++) {
            Serial.printf("%d ", states[(i * NUM_COLS) + j]);
        }
        Serial.printf("\r\n");
    }
    Serial.printf("COL=2, ROW=2, VAL=%d\r\n", keyMatrix.state(2, 2)); 
    Serial.printf("\033[%d;%dH" ,0,0); 
#endif
}